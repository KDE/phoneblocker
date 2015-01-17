#include "mainwindow.h"

#include <bb/cascades/ActionItem>
#include <bb/cascades/ChromeVisibility>
#include <bb/cascades/CheckBox>
#include <bb/cascades/Container>
#include <bb/cascades/NavigationPaneProperties>
#include <bb/cascades/TitleBar>
#include <bb/cascades/ImagePaint>
#include <bb/cascades/DockLayout>

using namespace bb::cascades;

MainWindow::MainWindow(QObject *parent)
    : QObject(parent)
{
    CheckBox *checkbox = CheckBox::create().text("Simple check box");
}

MainWindow::~MainWindow()
{
}

void MainWindow::createContentPage()
{
    ActionItem* backAction = ActionItem::create();
    connect(backAction, SIGNAL(triggered()), &m_NavigationPane, SLOT(pop()));
    m_page.setPaneProperties(NavigationPaneProperties::create().backButton(backAction));
    m_page.setActionBarAutoHideBehavior(ActionBarAutoHideBehavior::Disabled);
    TitleBar* titleBar = TitleBar::create(TitleBarScrollBehavior::Sticky).visibility(
            ChromeVisibility::Visible).title("Phone Blocker");
    m_page.setTitleBar(titleBar);
    Container *content = new Container();
    ImagePaint paint(QUrl("asset:///images/background.amd"), RepeatPattern::XY);
    content->setBackground(paint);
    content->setLayout(DockLayout::create());

    m_page.setContent(content);
}
