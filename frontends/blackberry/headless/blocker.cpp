/******************************************************************************
 * This file is part of the PhoneBlocker project
 * Copyright (c) 2014 Laszlo Papp <lpapp@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "blocker.h"

#include <bb/pim/message/MimeTypes>
#include <bb/pim/message/MessageContact>

#include <QTcpSocket>
#include <QSettings>

#include <algorithm>

using namespace bb::pim::account;
using namespace bb::pim::message;
using namespace bb::system;
using namespace std;

Blocker::Blocker(QObject *parent)
    : QObject(parent)
{
    QList<Account> accountList = m_accountService.accounts(Service::Messages, "sms-mms");
    m_smsAccountIdentifier = accountList.first().id();
    connect(&m_phone, SIGNAL(callUpdated(Call&)), SLOT(checkNewCall(Call&)));
    connect(&m_messageService, SIGNAL(void messageAdded(AccountKey, ConversationKey, MessageKey)), SLOT(checkNewMessage(AccountKey, ConversationKey, MessageKey)));
    connect(&m_server, SIGNAL(newConnection()), SLOT(handleNewConnection()));
    QSettings settings(m_authorName, m_applicationName);
    m_blockedCallNumbers = settings.value(m_blockedCallNumbersKey, QStringList()).toStringList();
    m_blockedSmsNumbers = settings.value(m_blockedSmsNumbersKey, QStringList()).toStringList();
    m_blockPrivateCallNumbers = settings.value(m_blockPrivateCallNumbersKey, false).toBool();
    m_blockAllCallNumbers = settings.value(m_blockAllCallNumbersKey, false).toBool();
    m_blockOutsideContactsCallNumbers = settings.value(m_blockOutsideContactsCallNumbersKey, false).toBool();
    m_blockAllSmsNumbers = settings.value(m_blockAllSmsNumbersKey, false).toBool();
    m_blockOutsideContactsSmsNumbers = settings.value(m_blockOutsideContactsSmsNumbersKey, false).toBool();
}

Blocker::~Blocker()
{
}

void Blocker::blockCall(const QString &phoneNumber)
{
    if (!m_blockedCallNumbers.contains(phoneNumber)) {
        m_blockedCallNumbers.push_back(phoneNumber);
        QSettings settings(m_authorName, m_applicationName);
        settings.setValue(m_blockedCallNumbersKey, m_blockedCallNumbers);
        settings.sync();
    }
}

void Blocker::unblockCall(const QString &phoneNumber)
{
    if (m_blockedCallNumbers.contains(phoneNumber)) {
        m_blockedCallNumbers.removeOne(phoneNumber);
        QSettings settings(m_authorName, m_applicationName);
        settings.setValue(m_blockedCallNumbersKey, m_blockedCallNumbers);
        settings.sync();
    }
}

void Blocker::blockPrivateCall()
{
    m_blockPrivateCallNumbers = true;
}

void Blocker::unblockPrivateCall()
{
    m_blockPrivateCallNumbers = false;
}

void Blocker::blockAllCall()
{
    m_blockAllCallNumbers = true;
}

void Blocker::unblockAllCall()
{
    m_blockAllCallNumbers = false;
    m_blockedCallNumbers.clear();
}

void Blocker::blockOutsideContactsCall()
{
    m_blockOutsideContactsCallNumbers = true;
}

void Blocker::unblockOutsideContactsCall()
{
    m_blockOutsideContactsCallNumbers = false;
}

void Blocker::blockSms(const QString &phoneNumber)
{
    if (!m_blockedSmsNumbers.contains(phoneNumber)) {
        m_blockedSmsNumbers.push_back(phoneNumber);
        QSettings settings(m_authorName, m_applicationName);
        settings.setValue(m_blockedCallNumbersKey, m_blockedCallNumbers);
        settings.sync();
    }
}

void Blocker::unblockSms(const QString &phoneNumber)
{
    if (m_blockedSmsNumbers.contains(phoneNumber)) {
        m_blockedSmsNumbers.removeOne(phoneNumber);
        QSettings settings(m_authorName, m_applicationName);
        settings.setValue(m_blockedCallNumbersKey, m_blockedCallNumbers);
        settings.sync();
    }
}

void Blocker::blockAllSms()
{
    m_blockAllSmsNumbers = true;
    QSettings settings(m_authorName, m_applicationName);
    settings.setValue(m_blockedSmsNumbersKey, QStringList());
    settings.setValue(m_blockAllSmsNumbersKey, true);
    settings.sync();
}

void Blocker::unblockAllSms()
{
    m_blockAllSmsNumbers = false;
    m_blockedSmsNumbers.clear();
    QSettings settings(m_authorName, m_applicationName);
    settings.setValue(m_blockAllSmsNumbersKey, false);
    settings.sync();
}

void Blocker::blockOutsideContactsSms()
{
    m_blockOutsideContactsSmsNumbers = false;
    QSettings settings(m_authorName, m_applicationName);
    settings.setValue(m_blockOutsideContactsSmsNumbersKey, true);
    settings.sync();
}

void Blocker::unblockOutsideContactsSms()
{
    m_blockOutsideContactsSmsNumbers = true;
    QSettings settings(m_authorName, m_applicationName);
    settings.setValue(m_blockAllSmsNumbersKey, false);
    settings.sync();
}

void Blocker::checkNewMessage(AccountKey /*account_key*/, ConversationKey /*conv*/, MessageKey message_key)
{
    Message message = m_messageService.message(m_smsAccountIdentifier, message_key);
    MessageContact senderMessageContact = message.sender();
    // TODO: Add check for m_blockOutsideContactsSmsNumbers and contact list
    if ((message.mimeType() == MimeTypes::Sms) and message.isInbound() and (m_blockAllSmsNumbers or m_blockedSmsNumbers.contains(senderMessageContact.address())))
        m_messageService.remove(m_smsAccountIdentifier, message_key);
}

void Blocker::checkNewCall(const bb::system::phone::Call &call)
{
    // TODO(1): Add check for m_blockOutsideContactsCallNumbers and contact list
    // TODO(2): Add check for m_blockPrivateCallNumbers and private numbers
    if (m_phone.activeLine().isValid() and m_blockedCallNumbers.contains(call.phoneNumber()))
        m_phone.endCall(call.callId());
}

void Blocker::listen()
{
    m_server.listen(QHostAddress::LocalHost, m_portNumber);
}

void Blocker::handleNewConnection()
{
    m_socket = m_server.nextPendingConnection();
    connect(m_socket, SIGNAL(disconnected()), m_socket, SLOT(deleteLater()));
    connect(m_socket, SIGNAL(readyRead()), SLOT(read()));
}

/*
 * Protocol format:
 *
 * 1) SMS: b (Block), u (Unblock) - everything else means ignore the action
 * 2) Phone: b (Block), u (Unblock) - everything else means ignore the action
 * 3) Phone number
 *   a) a (All) 
 *   b) empty (Private) - only phone unless the technology evolves to sending
 *     SMSs via unknown numbers
 *   c) c (Contacts) - block or unblock everyone if not in contacts
 *   d) digits (Specific) - perhaps list support in future variants of the
 *     protocol?
 * 4) \n (terminator)
 */

void Blocker::read()
{
    if (!m_socket->canReadLine())
        return;
    QByteArray data = m_socket->readLine();
    int sdata = data.size();
    if (sdata < 3) {
        qWarning() << "Invalid message";
        return;
    }
    char csms = data.at(0);
    char ccall = data.at(1);
    if (sdata == 3) {
        if (ccall == 'b') blockPrivateCall();
        else if (ccall == 'u') unblockPrivateCall();
    } else if (sdata == 4) {
        char phoneNumber = data.at(2);
        if (csms == 'b') {
            if (phoneNumber == 'a') blockAllSms();
            else if (phoneNumber == 'c') blockOutsideContactsSms();
        } else if (csms == 'u') {
            if (phoneNumber == 'a') unblockAllSms();
            else if (phoneNumber == 'c') unblockOutsideContactsSms();
        }
        if (ccall == 'b') {
            if (phoneNumber == 'a') blockAllCall();
            else if (phoneNumber == 'c') blockOutsideContactsCall();
        } else if (csms == 'u') {
            if (phoneNumber == 'a') unblockAllCall();
            else if (phoneNumber == 'c') unblockOutsideContactsCall();
        }
    } else {
        QByteArray phoneNumber = data.mid(2, sdata-3);
        if (csms == 'b') blockSms(phoneNumber);
        else if (csms == 'u') unblockSms(phoneNumber);
        if (ccall == 'b') blockCall(phoneNumber);
        else if (ccall == 'u') unblockCall(phoneNumber);
    }
}
