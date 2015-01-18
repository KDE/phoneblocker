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

#ifndef SOCKETWRITER_H
#define SOCKETWRITER_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class SocketWriter : public QObject
{
    Q_OBJECT

public:
    SocketWriter(QObject *parent = 0);
    ~SocketWriter();

    void blockSms();
    void unblockSms();
    void blockCall();
    void unblockCall();
    void blockPrivate();
    void unblockPrivate();
    void blockAll();
    void unblockAll();
    void blockOutsideContacts();
    void unblockOutsideContacts();
    void setPhoneNumber(const QByteArray &phoneNumber);
    bool write();

private:
    int m_portNumber;
    QTcpSocket m_socket;
    QByteArray m_phoneNumber;
    char m_csms;
    char m_ccall;
};

#endif
