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

#include "socketwriter.h"

#include <QHostAddress>

SocketWriter::SocketWriter(QObject *parent)
    : QObject(parent)
    , m_portNumber(9877)
    , m_csms('i')
    , m_ccall('i')
{
}

SocketWriter::~SocketWriter()
{
}

void SocketWriter::blockSms(const QByteArray &phoneNumber)
{
    m_csms = 'b';
    m_phoneNumber = phoneNumber;
}

void SocketWriter::unblockSms(const QByteArray &phoneNumber)
{
    m_csms = 'u';
    m_phoneNumber = phoneNumber;
}

void SocketWriter::blockCall(const QByteArray &phoneNumber)
{
    m_ccall = 'b';
    m_phoneNumber = phoneNumber;
}

void SocketWriter::unblockCall(const QByteArray &phoneNumber)
{
    m_ccall = 'u';
    m_phoneNumber = phoneNumber;
}

void SocketWriter::blockPrivate()
{
    m_ccall = 'b';
    m_phoneNumber.clear();
}

void SocketWriter::unblockPrivate()
{
    m_ccall = 'u';
    m_phoneNumber.clear();
}

void SocketWriter::blockAllSms()
{
    m_csms = 'b';
    m_phoneNumber = "a";
}

void SocketWriter::unblockAllSms()
{
    m_csms = 'u';
    m_phoneNumber = "a";
}

void SocketWriter::blockAllCall()
{
    m_ccall = 'b';
    m_phoneNumber = "a";
}

void SocketWriter::unblockAllCall()
{
    m_ccall = 'u';
    m_phoneNumber = "a";
}

void SocketWriter::blockOutsideContactsSms()
{
    m_csms = 'b';
    m_phoneNumber = "c";
}

void SocketWriter::unblockOutsideContactsSms()
{
    m_csms = 'u';
    m_phoneNumber = "c";
}

void SocketWriter::blockOutsideContactsCall()
{
    m_ccall = 'b';
    m_phoneNumber = "c";
}

void SocketWriter::unblockOutsideContactsCall()
{
    m_ccall = 'u';
    m_phoneNumber = "c";
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

bool SocketWriter::write()
{
    m_socket.connectToHost(QHostAddress::LocalHost, m_portNumber);
    if (!m_socket.waitForConnected())
        return false;
    QByteArray data;
    data.append(m_csms); data.append(m_ccall); data.append(m_phoneNumber); data.append('\n');
    m_socket.write(data);
    return m_socket.waitForBytesWritten();
}
