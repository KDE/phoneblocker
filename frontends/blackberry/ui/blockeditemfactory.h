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
