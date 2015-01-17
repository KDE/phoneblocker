#include "mainwindow.h"

#include <bb/cascades/ActionItem>
#include <bb/cascades/Application>
#include <bb/cascades/CheckBox>
#include <bb/cascades/ChromeVisibility>
#include <bb/cascades/Container>
#include <bb/cascades/CoverDetailLevel>
#include <bb/cascades/DockLayout>
#include <bb/cascades/ImagePaint>
#include <bb/cascades/ImageView>
#include <bb/cascades/Label>
#include <bb/cascades/MultiCover>
#include <bb/cascades/NavigationPaneProperties>
#include <bb/cascades/SceneCover>
#include <bb/cascades/TitleBar>

using namespace bb::cascades;

MainWindow::MainWindow(QObject *parent)
    : QObject(parent)
{
    createBlockedListPage();
    createAddBlockedItemPage();
    m_navigationPane.push(&m_blockedListPage);
    addApplicationCover();

    Application::instance()->setScene(&m_navigationPane);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createBlockedListPage()
{
}

void MainWindow::createAddBlockedItemPage()
{
    ActionItem* backAction = ActionItem::create();
    connect(backAction, SIGNAL(triggered()), &m_navigationPane, SLOT(pop()));
    m_addBlockedItemPage.setPaneProperties(NavigationPaneProperties::create().backButton(backAction));
    m_addBlockedItemPage.setActionBarAutoHideBehavior(ActionBarAutoHideBehavior::Disabled);
    TitleBar* titleBar = TitleBar::create(TitleBarScrollBehavior::Sticky).visibility(
            ChromeVisibility::Visible).title("Phone Blocker");
    m_addBlockedItemPage.setTitleBar(titleBar);
    Container *content = new Container();
    ImagePaint paint(QUrl("asset:///images/background.amd"), RepeatPattern::XY);
    content->setBackground(paint);
    content->setLayout(DockLayout::create());

    m_addBlockedItemPage.setContent(content);
}

void MainWindow::addApplicationCover()
{
    Container *coverContainerHigh = Container::create().layout(DockLayout::create());
    ImagePaint imagePaint(QUrl("asset:///images/application-cover.amd"));
    coverContainerHigh->setBackground(imagePaint);
    UIConfig *ui = coverContainerHigh->ui();
    Container *pepperContainer = Container::create().top(ui->du(3)).vertical(
            VerticalAlignment::Bottom).horizontal(HorizontalAlignment::Center);
    ImageView *pepperImage =
            ImageView::create("asset:///images/active_frames_pepper.png").scalingMethod(
                    ScalingMethod::AspectFit);
    Container *headerContainer = Container::create().layout(DockLayout::create()).horizontal(
            HorizontalAlignment::Fill).preferredHeight(ui->sdu(6.2));
    Container *headerBackground =
            Container::create().background(Color::fromARGB(0xff36412d)).opacity(0.5).horizontal(
                    HorizontalAlignment::Fill).vertical(VerticalAlignment::Fill);
    Label* title = Label::create("PhoneBlocker");
    title->textStyle()->setColor(Color::fromARGB(0xffebebeb));
    Container *titleContainer = Container::create().left(ui->du(3)).vertical(
            VerticalAlignment::Center);
    titleContainer->add(title);
    headerContainer->add(headerBackground);
    headerContainer->add(titleContainer);
    pepperContainer->add(pepperImage);
    coverContainerHigh->add(pepperContainer);
    coverContainerHigh->add(headerContainer);
    SceneCover *sceneCoverHigh = SceneCover::create().content(coverContainerHigh);

    Container *coverContainerMedium = Container::create().layout(DockLayout::create()).background(Color::fromARGB(0xff060606));
    UIConfig *uiMedium = coverContainerMedium->ui();
    Container *pepperContainerMedium = Container::create().vertical(
            VerticalAlignment::Center).horizontal(HorizontalAlignment::Center);
    pepperContainerMedium->setMaxHeight(ui->px(150));
    ImageView *pepperImageMedium = ImageView::create("asset:///images/active_frames_pepper.png").scalingMethod(
            ScalingMethod::AspectFit);
    Container *headerContainerMedium = Container::create().layout(DockLayout::create()).horizontal(
            HorizontalAlignment::Fill).preferredHeight(uiMedium->sdu(6.2));
    Container *headerBackgroundMedium = Container::create().background(Color::fromARGB(0xff36412d)).opacity(0.5).horizontal(
                    HorizontalAlignment::Fill).vertical(VerticalAlignment::Fill);
    Label* titleMedium = Label::create("PhoneBlocker");
    titleMedium->textStyle()->setColor(Color::fromARGB(0xffebebeb));

    Container *titleContainerMedium = Container::create().left(uiMedium->du(3)).vertical(
            VerticalAlignment::Center);
    titleContainerMedium->add(titleMedium);
    headerContainerMedium->add(headerBackgroundMedium);
    headerContainerMedium->add(titleContainerMedium);
    pepperContainerMedium->add(pepperImageMedium);
    coverContainerMedium->add(pepperContainerMedium);
    coverContainerMedium->add(headerContainerMedium);
    SceneCover *sceneCoverMedium = SceneCover::create().content(coverContainerMedium);
    AbstractCover* cover = MultiCover::create().add(sceneCoverHigh, CoverDetailLevel::High).add(
            sceneCoverMedium, CoverDetailLevel::Medium);
    Application::instance()->setCover(cover);
}
