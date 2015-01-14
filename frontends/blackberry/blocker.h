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

#ifndef BLOCKER_H
#define BLOCKER_H

#include <bb/system/phone/Call>
#include <bb/system/phone/Phone>
#include <bb/pim/message/MessageService>
#include <bb/pim/account/AccountService>

#include <QStringList>

class Blocker : public QObject
{
    Q_OBJECT

public:
    Blocker(QObject *parent = 0);
    ~Blocker();

public Q_SLOTS:
    void unblockPhoneNumber(const QString& phoneNumber);
    void blockPhoneNumber(const QString& phoneNumber);

Q_SIGNALS:

private Q_SLOTS:
    void checkNewCall(const bb::system::phone::Call &call);
    void checkNewMessage(bb::pim::account::AccountKey accountId, bb::pim::message::ConversationKey conversationId, bb::pim::message::MessageKey messageId);

private:
    bb::system::phone::Phone m_phone;
    QStringList m_blockedPhoneNumbers;
    bb::pim::message::MessageService m_messageService;
    bb::pim::account::AccountService m_accountService;
    int m_smsAccountIdentifier;
};

#endif
