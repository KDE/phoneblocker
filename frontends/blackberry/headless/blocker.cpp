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

#include <algorithm>

using namespace bb::pim::account;
using namespace bb::pim::message;
using namespace bb::system;
using namespace std;

Blocker::Blocker(QObject *parent)
    : QObject(parent)
    , m_portNumber(9877)
{
    QList<Account> accountList = m_accountService.accounts(Service::Messages, "sms-mms");
    m_smsAccountIdentifier = accountList.first().id();
    connect(&m_phone, SIGNAL(callUpdated(Call&)), SLOT(checkNewCall(Call&)));
    connect(&m_messageService, SIGNAL(void messageAdded(AccountKey, ConversationKey, MessageKey)), SLOT(checkNewMessage(AccountKey, ConversationKey, MessageKey)));
    connect(&m_server, SIGNAL(newConnection()), SLOT(handleNewConnection()));
}

Blocker::~Blocker()
{
}

void Blocker::blockCall(const string &phoneNumber)
{
    if (find(m_blockedCallNumbers.begin(), m_blockedCallNumbers.end(), phoneNumber) == m_blockedCallNumbers.end())
        m_blockedCallNumbers.push_back(phoneNumber);
}

void Blocker::unblockCall(const string &phoneNumber)
{
    if (find(m_blockedCallNumbers.begin(), m_blockedCallNumbers.end(), phoneNumber) != m_blockedCallNumbers.end())
        m_blockedCallNumbers.remove(phoneNumber);
}

void Blocker::blockPrivateCall()
{
}

void Blocker::unblockPrivateCall()
{
}

void Blocker::blockAllCall()
{
}

void Blocker::unblockAllCall()
{
}

void Blocker::blockOutsideContactsCall()
{
}

void Blocker::unblockOutsideContactsCall()
{
}

void Blocker::blockSms(const string &phoneNumber)
{
    if (find(m_blockedSmsNumbers.begin(), m_blockedSmsNumbers.end(), phoneNumber) == m_blockedSmsNumbers.end())
        m_blockedSmsNumbers.push_back(phoneNumber);
}

void Blocker::unblockSms(const string &phoneNumber)
{
    if (find(m_blockedSmsNumbers.begin(), m_blockedSmsNumbers.end(), phoneNumber) != m_blockedSmsNumbers.end())
        m_blockedSmsNumbers.remove(phoneNumber);
}

void Blocker::blockAllSms()
{
}

void Blocker::unblockAllSms()
{
}

void Blocker::blockOutsideContactsSms()
{
}

void Blocker::unblockOutsideContactsSms()
{
}

void Blocker::checkNewMessage(AccountKey /*account_key*/, ConversationKey /*conv*/, MessageKey message_key)
{
    Message message = m_messageService.message(m_smsAccountIdentifier, message_key);
    MessageContact senderMessageContact = message.sender();
    QString contactAddress = senderMessageContact.address();
    if ((message.mimeType() == MimeTypes::Sms) and message.isInbound() and find(m_blockedSmsNumbers.begin(), m_blockedSmsNumbers.end(), contactAddress.toStdString()) != m_blockedSmsNumbers.end())
        m_messageService.remove(m_smsAccountIdentifier, message_key);
}

void Blocker::checkNewCall(const bb::system::phone::Call &call)
{
    QString phoneNumber = call.phoneNumber();
    if (m_phone.activeLine().isValid() and find(m_blockedCallNumbers.begin(), m_blockedCallNumbers.end(), phoneNumber.toStdString()) != m_blockedCallNumbers.end())
        m_phone.endCall(call.callId());
}

void Blocker::listen()
{
    m_server.listen(QHostAddress::LocalHost, m_portNumber);
}

void Blocker::handleNewConnection()
{
    m_socket = m_server.nextPendingConnection();
    connect(m_socket, SIGNAL(disconnected()), SLOT(disconnected()));
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
    QByteArray badata = m_socket->readLine();
    string data = badata.data();
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
        string phoneNumber = data.substr(2, sdata-3);
        if (csms == 'b') blockSms(phoneNumber);
        else if (csms == 'u') unblockSms(phoneNumber);
        if (ccall == 'b') blockCall(phoneNumber);
        else if (ccall == 'u') unblockCall(phoneNumber);
    }
}
