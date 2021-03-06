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
#include <bb/system/InvokeManager>

#include <QTcpServer>
#include <QObject>
#include <QMap>
#include <QPair>
#include <QString>

class QTcpSocket;

typedef QMap<QString, QPair<bool, bool>> BlockedNumbers;

class Blocker : public QObject
{
    Q_OBJECT

public:
    Blocker(QObject *parent = nullptr);
    ~Blocker();

private Q_SLOTS:
    void block(const QString& phoneNumber, bool call, bool sms);
    void unblock(const QString& phoneNumber, bool call, bool sms);

    void blockPrivateCall();
    void unblockPrivateCall();
    void blockAllCall();
    void unblockAllCall();
    void blockOutsideContactsCall();
    void unblockOutsideContactsCall();

    void blockAllSms();
    void unblockAllSms();
    void blockOutsideContactsSms();
    void unblockOutsideContactsSms();

    void checkNewCall(const bb::system::phone::Call &call);
    void checkNewMessage(bb::pim::account::AccountKey accountId, bb::pim::message::ConversationKey conversationId, bb::pim::message::MessageKey messageId);

    void listen();
    void handleNewConnection();
    void read();

private:
    bb::system::phone::Phone m_phone;
    bb::pim::message::MessageService m_messageService;
    bb::pim::account::AccountService m_accountService;

    int m_smsAccountIdentifier;
    const int m_portNumber{9987};

    BlockedNumbers m_blockedNumbers;

    QTcpServer m_server;
    QTcpSocket *m_socket{nullptr};

    bool m_blockAllSmsNumbers{false};
    bool m_blockOutsideContactsSmsNumbers{false};

    bool m_blockPrivateCallNumbers{false};
    bool m_blockAllCallNumbers{false};
    bool m_blockOutsideContactsCallNumbers{false};

    const QString m_blockedNumbersKey{"blockedNumbers"};
    const QString m_blockAllCallNumbersKey{"blockAllCallNumbers"};
    const QString m_blockAllSmsNumbersKey{"blockAllSmsNumbers"};
    const QString m_blockOutsideContactsCallNumbersKey{"blockOutsideContactsCallNumbers"};
    const QString m_blockOutsideContactsSmsNumbersKey{"blockOutsideContactsSmsNumbers"};
    const QString m_blockPrivateCallNumbersKey{"blockPrivateCallNumbers"};

    const QString m_authorName{"Laszlo Papp"};
    const QString m_applicationName{"PhoneBlocker"};
};
Q_DECLARE_METATYPE(BlockedNumbers)

#endif
