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

#ifndef BLOCKEDITEM_H
#define BLOCKEDITEM_H

#include <bb/cascades/CustomListItem>
#include <bb/cascades/ListItemListener>

using namespace bb::cascades;

namespace bb
{
    namespace cascades
    {
        class Container;
        class Label;
    }
}

class BlockedItem: public bb::cascades::CustomListItem, public ListItemListener
{
    Q_OBJECT

public:
    BlockedItem(Container *parent = 0);

    void updateItem(const QString phoneNumber, bool call, bool sms);
    void select(bool select);
    void reset(bool selected, bool activated);
    void activate(bool activate);

private:
    Label *m_phoneNumberLabel;
    Label *m_callLabel;
    Label *m_smsLabel;
    Container *m_highlighContainer;
};

#endif
