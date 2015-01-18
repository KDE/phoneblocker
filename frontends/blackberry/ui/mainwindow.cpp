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
    ImageView *backgroundImage = ImageView::create("asset:///images/Book_background.amd");
    backgroundImage->setVerticalAlignment(VerticalAlignment::Fill);
    backgroundImage->setHorizontalAlignment(HorizontalAlignment::Fill);

    Container *blockedListContainer = new Container();
    UIConfig *ui = blockedListContainer->ui();
    blockedListContainer->setTopPadding(ui->px(15.0f));
    blockedListContainer->setBottomPadding(ui->px(15.0f));
    blockedListContainer->setLayout(new DockLayout());
    blockedListContainer->setHorizontalAlignment(HorizontalAlignment::Fill);

    createBlockedListView();
    m_blockedCallListView.setScrollRole(ScrollRole::Main);
    m_blockedCallListView.setHorizontalAlignment(HorizontalAlignment::Fill);
    m_blockedSmsListView.setScrollRole(ScrollRole::Main);
    m_blockedSmsListView.setHorizontalAlignment(HorizontalAlignment::Fill);

    blockedListContainer->add(&m_blockedCallListView);
    blockedListContainer->add(&m_blockedSmsListView);

    blockedListContainer->add(backgroundImage);
    blockedListContainer->add(blockedListContainer);

    m_blockedListPage.setContent(blockedListContainer);
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

void MainWindow::createBlockedListView()
{
    QSettings settings(m_authorName, m_applicationName);

    m_blockPrivateCallNumbers = settings.value(m_blockPrivateCallNumbersKey, false).toBool();
    m_blockAllCallNumbers = settings.value(m_blockAllCallNumbersKey, false).toBool();
    m_blockOutsideContactsCallNumbers = settings.value(m_blockOutsideContactsCallNumbersKey, false).toBool();
    m_blockAllSmsNumbers = settings.value(m_blockAllSmsNumbersKey, false).toBool();
    m_blockOutsideContactsSmsNumbers = settings.value(m_blockOutsideContactsSmsNumbersKey, false).toBool();

    QVariantMap callMap = QVariantMap();
    QStringList blockedCallNumbers = settings.value(m_blockedCallNumbersKey, QStringList()).toStringList();
    foreach (const QString &blockedCallNumber, blockedCallNumbers) {
        callMap["phoneNumber"] = blockedCallNumber;
        m_blockedCallListModel << callMap;
    }

    QVariantMap smsMap = QVariantMap();
    QStringList blockedSmsNumbers = settings.value(m_blockedSmsNumbersKey, QStringList()).toStringList();
    foreach (const QString &blockedSmsNumber, blockedSmsNumbers) {
        smsMap["phoneNumber"] = blockedSmsNumber;
        m_blockedSmsListModel << smsMap;
    }

    m_blockedCallListView.setDataModel(&m_blockedCallListModel);
    // m_blockedCallListView.setListItemProvider(blockedCallItemManager);
    m_blockedSmsListView.setDataModel(&m_blockedSmsListModel);
    // m_blockedSmsListView.setListItemProvider(blockedSmsItemManager);

    connect(&m_blockedCallListView, SIGNAL(triggered(const QVariantList)), SLOT(handleBlockedCallListTriggered(const QVariantList)));
    connect(&m_blockedSmsListView, SIGNAL(triggered(const QVariantList)), SLOT(handleBlockedSmsListTriggered(const QVariantList)));
}

void MainWindow::handleBlockedCallListTriggered(const QVariantList)
{
}

void MainWindow::handleBlockedSmsListTriggered(const QVariantList)
{
}
