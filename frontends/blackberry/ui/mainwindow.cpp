#include "mainwindow.h"
#include "blockeditemfactory.h"

#include <bb/cascades/ActionItem>
#include <bb/cascades/Application>
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
#include <bb/cascades/TextFieldInputMode>
#include <bb/cascades/TitleBar>

using namespace bb::cascades;

MainWindow::MainWindow(QObject *parent)
    : QObject(parent)
{
    connect(&m_navigationPane, SIGNAL(topChanged(bb::cascades::Page*)), SLOT(handleTopChanged(bb::cascades::Page*)));
    connect(&m_navigationPane, SIGNAL(popTransitionEnded(bb::cascades::Page*)), SLOT(handlePopTransitionEnded(bb::cascades::Page*)));
    createBlockedListPage();
    createAddBlockedItemPage();
    m_navigationPane.push(&m_blockedListPage);
    Application::instance()->setScene(&m_navigationPane);
    addApplicationCover();
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
    m_blockedListView.setScrollRole(ScrollRole::Main);
    m_blockedListView.setHorizontalAlignment(HorizontalAlignment::Fill);

    blockedListContainer->add(backgroundImage);
    blockedListContainer->add(&m_blockedListView);

    m_blockedListPage.setContent(blockedListContainer);

    ActionItem* addAction = ActionItem::create().title("Add");
    connect(addAction, SIGNAL(triggered()), SLOT(showAddBlockedItemPage()));
}

void MainWindow::createAddBlockedItemPage()
{
    ActionItem* backAction = ActionItem::create().title("Previous Page");
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

    m_phoneNumberOption = Option::create().text("Phone Number").selected(true);
    m_allOption = Option::create().text("All");
    m_privateOption = Option::create().text("Private");
    m_phoneNumberRadioGroup = RadioGroup::create().add(m_allOption).add(m_privateOption);
    m_phoneNumberTextField = TextField::create().hintText("Some phone number (e.g. +44747865325)").inputMode(TextFieldInputMode::Type::PhoneNumber);
    m_callCheckBox = CheckBox::create().text("Call");
    m_smsCheckBox = CheckBox::create().text("Sms");
    m_blockButton = Button::create().text("Block");
    connect(m_blockButton, SIGNAL(clicked()), SLOT(handleBlockButtonClicked()));
    content->add(m_phoneNumberRadioGroup);
    content->add(m_phoneNumberTextField);
    content->add(m_callCheckBox);
    content->add(m_smsCheckBox);
    content->add(m_blockButton);

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
    BlockedNumbers blockedNumbers = settings.value(m_blockedNumbersKey).value<BlockedNumbers>();
    for (auto phoneNumber : blockedNumbers.keys()) {
        callMap["phoneNumber"] = phoneNumber;
        callMap["call"] = blockedNumbers.value(phoneNumber).first;
        callMap["sms"] = blockedNumbers.value(phoneNumber).second;
        m_blockedListModel << callMap;
    }

    m_blockedListView.setDataModel(&m_blockedListModel);
    BlockedItemFactory *blockedItemManager = new BlockedItemFactory();
    m_blockedListView.setListItemProvider(blockedItemManager);

    connect(&m_blockedListView, SIGNAL(triggered(const QVariantList)), SLOT(handleBlockedListTriggered(const QVariantList)));
}

void MainWindow::handleBlockedListTriggered(const QVariantList)
{
}

void MainWindow::handleBlockButtonClicked()
{
    if (m_phoneNumberOption->isSelected())
        m_socketWriter.setPhoneNumber(m_phoneNumberTextField->text().toLatin1());
    else if (m_privateOption->isSelected())
        m_socketWriter.blockPrivate();
    else if (m_allOption->isSelected())
        m_socketWriter.blockAll();
    if (m_callCheckBox->isChecked())
        m_socketWriter.blockCall();
    if (m_smsCheckBox->isChecked())
        m_socketWriter.blockSms();
    m_socketWriter.write();
}

void MainWindow::handleTopChanged(bb::cascades::Page* page)
{
    if (page != &m_addBlockedItemPage)
        m_blockedListView.clearSelection();
}

void MainWindow::handlePopTransitionEnded(bb::cascades::Page *page)
{
    if (page == &m_addBlockedItemPage)
        m_phoneNumberTextField->resetText();
}

void MainWindow::showAddBlockedItemPage()
{
    m_navigationPane.push(&m_addBlockedItemPage);
}
