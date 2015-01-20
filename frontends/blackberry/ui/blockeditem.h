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
