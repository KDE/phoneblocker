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

SocketWriter::SocketWriter(QObject *parent)
    : QObject(parent)
    , m_portNumber(9877)
{
}

SocketWriter::~SocketWriter()
{
}

void SocketWriter::blockSms()
{
}

void SocketWriter::unblockSms()
{
}

void SocketWriter::blockCall()
{
}

void SocketWriter::unblockCall()
{
}

void SocketWriter::blockPrivate()
{
}

void SocketWriter::unblockPrivate()
{
}

void SocketWriter::blockAll()
{
}

void SocketWriter::unblockAll()
{
}

void SocketWriter::blockNumber(const QString &phoneNumber)
{
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
}

#include <socketwriter.moc>
