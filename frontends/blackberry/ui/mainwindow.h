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

#ifndef BLOCKER_H
#define BLOCKER_H

#include "socketwriter.h"

#include <bb/cascades/Button>
#include <bb/cascades/CheckBox>
#include <bb/cascades/ListView>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Option>
#include <bb/cascades/Page>
#include <bb/cascades/RadioGroup>
#include <bb/cascades/TextField>
#include <bb/cascades/QListDataModel>

#include <QStringList>

typedef QMap<QString, QPair<bool, bool>> BlockedNumbers;

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow(QObject *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void handleBlockedListTriggered(const QVariantList);
    void handleBlockButtonClicked();
    void handleTopChanged(bb::cascades::Page* page);
    void handlePopTransitionEnded(bb::cascades::Page *page);
    void showAddBlockedItemPage();

private:
    void createBlockedListPage();
    void createAddBlockedItemPage();
    void createBlockedListView();
    void addApplicationCover();

    bb::cascades::NavigationPane m_navigationPane;
    bb::cascades::Page m_blockedListPage;
    bb::cascades::Page m_addBlockedItemPage;

    bb::cascades::ListView m_blockedListView;
    bb::cascades::QVariantListDataModel m_blockedListModel;

    bool m_blockAllSmsNumbers{false};
    bool m_blockOutsideContactsSmsNumbers{false};

    bool m_blockPrivateCallNumbers{false};
    bool m_blockAllCallNumbers{false};
    bool m_blockOutsideContactsCallNumbers{false};

    const QString m_blockedNumbersKey{"blockedNumbers"};
    const QString m_blockAllCallNumbersKey{"blockAllCallNumbers"};
    const QString m_blockAllSmsNumbersKey{"blockAllSmsNumbers"};
    const QString m_blockOutsideContactsCallNumbersKey{"blockOutsideContactsCallNumbers"};
    const QString m_blockOutsideContactsSmsNumbersKey{"blockOutsideContactsSmsNumbers"};
    const QString m_blockPrivateCallNumbersKey{"blockPrivateCallNumbers"};

    const QString m_authorName{"Laszlo Papp"};
    const QString m_applicationName{"PhoneBlocker"};

    bb::cascades::RadioGroup *m_phoneNumberRadioGroup;
    bb::cascades::Option *m_phoneNumberOption;
    bb::cascades::Option *m_allOption;
    bb::cascades::Option *m_privateOption;
    bb::cascades::TextField *m_phoneNumberTextField;
    bb::cascades::CheckBox *m_callCheckBox;
    bb::cascades::CheckBox *m_smsCheckBox;
    bb::cascades::Button *m_blockButton;

    SocketWriter m_socketWriter;
};
Q_DECLARE_METATYPE(BlockedNumbers)

#endif
