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

Blocker::Blocker(QObject *parent)
    : QObject(parent)
{

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

void Blocker::onCallUpdated(const bb::system::phone::Call &call)
{
    if (m_phone.activeLine().isValid() && m_blockedPhoneNumbers.contains(call.phoneNumber())) m_phone.endCall(call.callId());
}

#include <blocker.moc>
