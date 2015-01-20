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

#include "blockeditem.h"

#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImageView>
#include <bb/cascades/ImagePaint>
#include <bb/cascades/Label>
#include <bb/cascades/StackLayout>
#include <bb/cascades/SystemDefaults>
#include <bb/cascades/TextStyle>
#include <bb/cascades/UIConfig>

using namespace bb::cascades;

BlockedItem::BlockedItem(Container *parent) :
        CustomListItem(HighlightAppearance::None, parent)
{
    Container *itemContainer = Container::create().layout(DockLayout::create())
                                        .horizontal(HorizontalAlignment::Fill).vertical(VerticalAlignment::Fill);

    UIConfig *ui = itemContainer->ui();
    itemContainer->setTopPadding(ui->du(0.2));
    itemContainer->setBottomPadding(ui->du(0.6));
    ImagePaint paint(QUrl("asset:///images/white_photo.amd"));
    itemContainer->setBackground(paint);
    m_highlighContainer = Container::create().background(Color::fromARGB(0xff75b5d3))
                            .horizontal(HorizontalAlignment::Fill).vertical(VerticalAlignment::Fill)
                            .opacity(0.0);

    // Content Container containing an image and label with padding for the alignment
    // on background image. Note that we disable implicit layout animations to avoid
    // unsynchronized animations on the list items as the item image is asynchronously loaded.
    Container *contentContainer = new Container();
    contentContainer->setLeftPadding(ui->du(0.3));
    contentContainer->setLayout(StackLayout::create().orientation(LayoutOrientation::LeftToRight));
    contentContainer->setImplicitLayoutAnimationsEnabled(false);

    m_phoneNumberLabel = Label::create();
    m_phoneNumberLabel->setVerticalAlignment(VerticalAlignment::Center);
    m_phoneNumberLabel->setLeftMargin(ui->du(3.0));
    m_phoneNumberLabel->textStyle()->setBase(SystemDefaults::TextStyles::titleText());
    m_phoneNumberLabel->textStyle()->setColor(Color::Black);
    m_phoneNumberLabel->setImplicitLayoutAnimationsEnabled(false);

    contentContainer->add(m_phoneNumberLabel);
    contentContainer->add(m_callLabel);
    contentContainer->add(m_smsLabel);

    // Add the background image and the content to the full item container.
    itemContainer->add(m_highlighContainer);
    itemContainer->add(contentContainer);

    setDividerVisible(false);
    setPreferredHeight(ui->du(17.6));
    setContent(itemContainer);
}

void BlockedItem::updateItem(const QString phoneNumber, bool call, bool sms)
{
    m_phoneNumberLabel->setText(phoneNumber);
    if (call) m_callLabel->setText("Call");
    if (sms) m_smsLabel->setText("Sms");
}

void BlockedItem::select(bool select)
{
    m_highlighContainer->setOpacity(select ? 0.9f : 0.0f);
}

void BlockedItem::reset(bool selected, bool activated)
{
    Q_UNUSED(activated);
    select(selected);
}

void BlockedItem::activate(bool activate)
{
    select(activate);
}
