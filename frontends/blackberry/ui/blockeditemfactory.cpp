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
