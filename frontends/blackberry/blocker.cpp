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

using namespace bb::pim::account;
using namespace bb::pim::message;

Blocker::Blocker(QObject *parent)
    : QObject(parent)
{
    QList<Account> accountList = m_accountService.accounts(Service::Messages, "sms-mms");
    m_smsAccountIdentifier = accountList.first().id();
    connect(&m_phone, SIGNAL(callUpdated(Call&)), SLOT(checkNewCall(Call&)));
    connect(&m_messageService, SIGNAL(void messageAdded(AccountKey, ConversationKey, MessageKey)), SLOT(checkNewMessage(AccountKey, ConversationKey, MessageKey)));
}

Blocker::~Blocker()
{
}

void Blocker::blockPhoneNumber(const QString &phoneNumber)
{
    if (!m_blockedPhoneNumbers.contains(phoneNumber)) m_blockedPhoneNumbers.append(phoneNumber);
}

void Blocker::unblockPhoneNumber(const QString &phoneNumber)
{
    if (m_blockedPhoneNumbers.contains(phoneNumber)) m_blockedPhoneNumbers.removeOne(phoneNumber);
}

void Blocker::checkNewMessage(AccountKey /*account_key*/, ConversationKey /*conv*/, MessageKey message_key)
{
    Message message = m_messageService.message(m_smsAccountIdentifier, message_key);
    MessageContact senderMessageContact = message.sender();
    if ((message.mimeType() == MimeTypes::Sms) and message.isInbound() and m_blockedPhoneNumbers.contains(senderMessageContact.address()))
        m_messageService.remove(m_smsAccountIdentifier, message_key);
}

void Blocker::checkNewCall(const bb::system::phone::Call &call)
{
    if (m_phone.activeLine().isValid() and m_blockedPhoneNumbers.contains(call.phoneNumber())) m_phone.endCall(call.callId());
}

#include <blocker.moc>
