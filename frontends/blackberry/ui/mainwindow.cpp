#include "mainwindow.h"

#include <bb/cascades/ActionItem>
#include <bb/cascades/ChromeVisibility>
#include <bb/cascades/CheckBox>
#include <bb/cascades/Container>

MainWindow::MainWindow()
{
    CheckBox *checkbox = CheckBox::create().text("Simple check box");
}

MainWindow::~MainWindow()
{
}

void MainWindow::createContentPage()
{
    ActionItem* backAction = ActionItem::create();
    connectResult = connect(backAction, SIGNAL(triggered()), &m_NavigationPane, SLOT(pop()));
    m_page->setPaneProperties(NavigationPaneProperties::create().backButton(backAction));
    m_page->setActionBarAutoHideBehavior(ActionBarAutoHideBehavior::Disabled);
    TitleBar* titleBar = TitleBar::create(TitleBarScrollBehavior::Sticky).visibility(
            ChromeVisibility::Visible).title("Phone Blocker");
    m_page->setTitleBar(titleBar);
    Container *content = new Container();
    ImagePaint paint(QUrl("asset:///images/background.amd"), RepeatPattern::XY);
    content->setBackground(paint);
    content->setLayout(DockLayout::create());

    m_page->setContent(content);
    ThemeSupport *appThemeSupport = Application::instance()->themeSupport();
    connectResult = connect(appThemeSupport, SIGNAL(themeChanged(const bb::cascades::Theme *)),
            SLOT(onThemeChanged(const bb::cascades::Theme *)));
}
