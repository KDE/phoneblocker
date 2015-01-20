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

#include "blockeditemfactory.h"
#include "blockeditem.h"

using namespace bb::cascades;

BlockedItemFactory::BlockedItemFactory()
{
}

VisualNode *BlockedItemFactory::createItem(ListView* list, const QString &type)
{
    Q_UNUSED(type);
    Q_UNUSED(list);
    BlockedItem *blockedItem = new BlockedItem();
    return blockedItem;
}

void BlockedItemFactory::updateItem(ListView* list, bb::cascades::VisualNode *listItem,
        const QString &type, const QVariantList &indexPath, const QVariant &data)
{
    Q_UNUSED(list);
    Q_UNUSED(indexPath);
    Q_UNUSED(type);

    QVariantMap map = data.value<QVariantMap>();
    BlockedItem *blockedItem = static_cast<BlockedItem *>(listItem);
    blockedItem->updateItem(map["phoneNumber"].toString(), map["call"].toBool(), map["sms"].toBool());
}
