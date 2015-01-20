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

#ifndef BLOCkEDITEMFACTORY_H
#define BLOCKEDITEMFACTORY_H

#include <bb/cascades/ListItemProvider>

using namespace bb::cascades;

namespace bb
{
    namespace cascades
    {
        class ListView;
    }
}

class BlockedItemFactory: public bb::cascades::ListItemProvider
{
public:
    BlockedItemFactory();
    VisualNode *createItem(ListView* list, const QString &type);
    void updateItem(ListView* list, VisualNode *listItem, const QString &type,
            const QVariantList &indexPath, const QVariant &data);
};

#endif
