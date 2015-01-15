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

import bb.cascades 1.0

Page {

    id: mainPage

    // It is commented for now as it is just consumes the space uselessly

    // titleBar: TitleBar {
    //     title : "Phone Blocker"
    // }

    actions: [
        // The page should be refactored later into two pages
        // 1) WebView + potentially the Action Bar
        // 2) SearchBar + ListView

        ActionItem {
            id: backActionItem
            title: "Back"
            imageSource: "asset:///images/previous.png"
            ActionBar.placement: ActionBarPlacement.OnBar

            onTriggered: {
                wikiWebView.goBack();
            }
        },

        ActionItem {
            id: nextActionItem
            title: "Next"
            imageSource: "asset:///images/next.png"
            ActionBar.placement: ActionBarPlacement.OnBar

            onTriggered: {
                wikiWebView.goForward();
            }
        },

        ActionItem {
            id: searchActionItem
            title: "Search"
            imageSource: "asset:///images/search.png"
            ActionBar.placement: ActionBarPlacement.OnBar

            onTriggered: {
                searchBar.visible = true;
            }
        },

        // ActionItem {
        //     id: languageActionItem
        //     // title: selectionDialog.model.get(searchModel.language).name
        //     title: "Languages"
        //     imageSource: "asset:///images/language.png"
        //     ActionBar.placement: ActionBarPlacement.OnBar

        //     onTriggered: {
        //         // languageSelectionDialog.open();
        //     }
        // },
        
        // This is to ponder later whether it is a common enough use case to
        // rearrange the layout. There could be a group here because "Find in
        // page" can also be a useful action. There could could be an ActionSet
        // used with context menu. That could be really awesome! So, in short:
        //
        // - Copy
        // - Language
        // - Find in
        // - Download the content to read offline?
        // - Send in email
        // - Go home?
        //
        // Unfortunately, the "Cancel" has to stay at the top because the search
        // cannot be dismissed otherwise from the Action Bar for instance as the
        // Virtual Keyboard may well cover that part intentionally for good.

        // ActionItem {
        //     id: copyUrlActionItem
        //     title: "Copy Url"
        //     imageSource: "asset:///copy_link.png"
        //     ActionBar.placement: ActionBarPlacement.OnBar

        //     onTriggered: {
        //         searchModel.shareArticle(wikiWebView.url);
        //     }
        // },

        // ActionItem {
        //     id: findActionItem
        //     title: "Find"
        //     imageSource: "asset:///find.png"
        //     ActionBar.placement: ActionBarPlacement.OnBar

        //     onTriggered: {
        //         // searchModel.shareArticle(wikiWebView.url);
        //     }
        // },
        
        InvokeActionItem {
            id: shareActionItem
            title: "Share"
            imageSource: "asset:///images/share.png"
            ActionBar.placement: ActionBarPlacement.OnBar

            query {
                mimeType: "text/plain"
                uri: wikiWebView.url
                invokeActionId: "bb.action.SHARE"
            }
        }
    ]

    Container {
        id: rootContainer
    
        animations: [
            TranslateTransition {
                id: userInteractionDelay
                delay: 3000
                onEnded: {
                    mainPage.actionBarVisibility = ChromeVisibility.Hidden;
                }
            }
        ] 

        topPadding: 15.0
        leftPadding: 15.0
        rightPadding: 15.0

        background: Color.Black

        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }

        onCreationCompleted: {
            OrientationSupport.supportedDisplayOrientation =
                SupportedDisplayOrientation.All;
        }

        Container {
            id: searchBar

            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }

            horizontalAlignment: HorizontalAlignment.Right
            visible: true

            TextField {
                id: searchTextField

                layoutProperties: StackLayoutProperties {
                    spaceQuota: 8
                }

                verticalAlignment: VerticalAlignment.Center

                hintText: "Enter a Search Term"

                onTextChanging: {
                }

                input {
                    submitKey: SubmitKey.Search;

                    onSubmitted: {
                        searchModel.setSearchString(text);

                        // This should be done in a signal handler for
                        // itemsChanged

                        wikiScrollView.visible = false
                        resultsListView.visible = true
                    }
                }
            }

            Button {
                id: cancelButton

                layoutProperties: StackLayoutProperties {
                    spaceQuota: 2
                }

                verticalAlignment: VerticalAlignment.Center

                imageSource: "asset:///images/cancel.png"

                onClicked: {
                    searchBar.visible = false;
                }
            }

            // No language changing support for now, but it is already possible
            // to type the search word in any language. This could now be done
            // with a language ListView on a new page for instance or in a
            // dialog, or even on the same page as a workaround.

            // SelectionDialog {
                // id: language selectionDialog
                // titleText: "Select your language"
                // model: ListModel {
                    // ListElement { name: "English";  value: "0";}
                    // ListElement { name: "Catala";   value: "1";}
                    // ListElement { name: "Cesky";    value: "2";}
                    // ListElement { name: "Dansk";    value: "3";}
                    // ListElement { name: "Deutsch";  value: "4";}
                    // ListElement { name: "Espanol";  value: "5";}
                    // ListElement { name: "Francais"; value: "6";}
                    // ListElement { name: "Italiano"; value: "7";}
                    // ListElement { name: "Magyar";   value: "8";}
                    // ListElement { name: "Nederlands"; value: "9";}
                    // ListElement { name: "Norsk";    value: "10";}
                    // ListElement { name: "Portugues";value: "11";}
                    // ListElement { name: "Polski";   value: "12";}
                    // ListElement { name: "Suomi";    value: "13";}
                    // ListElement { name: "Svenska";  value: "14";}
                    // ListElement { name: "Russian";  value: "15";}
                // }

                // onRejected: {
                    // searchbar.focus = true;
                // }

                // onAccepted: {
                    // searchModel.language = selectedIndex
                    // langicon.text = selectionDialog.model.get(searchModel.p_language).name
                    // searchbar.focus = true;
                // }
            // }

            // onVisibleChanged: {
                // if(visible)
                    // searchbar.focus = true;
            // }
        }

        // Dock Container is the way to hold overlapping controls with
        // Cascades, at least for now. There is no 'z' index support establish
        // by Cascades QML either.

        Container {
            id: overlappingControlsContainer

            preferredWidth: 768.0
            preferredHeight: 1180.0

            layout: DockLayout {
            }
            
            verticalAlignment: VerticalAlignment.Top
            horizontalAlignment: HorizontalAlignment.Left

            ListView {
                id: resultsListView

                dataModel: searchModel

                listItemComponents: [

                    // ListItemComponent {
                    //     type: "header"
                         
                    //   Label {
                    //         text: ListItemData.title
                    //     }
                    // },

                    ListItemComponent {
                        type: "title"

                        StandardListItem {
                            title: ListItem.data
                        }
                    }

                ]

                onTriggered: {
                    if (dataModel.data(indexPath) == searchModel.googleSearchString()) {
                        searchModel.searchGoogle(searchTextField.text);
                    } else {
                        searchModel.showArticle(indexPath[0]);

                        // This should be done in a signal handler for urlChanged

                       wikiScrollView.visible = true
                       searchBar.visible = false
                       resultsListView.visible = false
                    }
                }
                    
                onSelectionChanged: {

                }
            }

            ScrollView {
                id: wikiScrollView

                scrollViewProperties {
                    pinchToZoomEnabled: true
                    scrollMode: ScrollMode.Both
                    initialScalingMethod: ScalingMethod.AspectFit
                }

                verticalAlignment: VerticalAlignment.Fill
                visible: false

                WebView {
                    id: wikiWebView

                    url: searchModel.url

                    settings.viewport: {
                        // "width" : "device-width"
                        // "height": "devide-height"
                        // defaultFontSize: searchModel.fontSize
                        "initial-scale" : 1.0
                    }
                    
                    onLoadingChanged: {
                        if (loadRequest.status == WebLoadStatus.Started) {
                            activityIndicator.start();
                        }
                        else if (loadRequest.status == WebLoadStatus.Succeeded) {
                            userInteractionDelay.play();
                            activityIndicator.stop();
                        }
                        else if (loadRequest.status == WebLoadStatus.Failed) {
                            activityIndicator.stop();
                        }
                    }
                }

                gestureHandlers: [
                    DoubleTapHandler {
                        onDoubleTapped: {
                            wikiScrollView.resetViewableArea();
                        }
                    }
                ]

                onTouch: {
                    if (mainPage.actionBarVisibility != ChromeVisibility.Hidden) {
                        if (userInteractionDelay.isPlaying()) {
                            userInteractionDelay.stop();
                        }

                        userInteractionDelay.play();
                    }

                    mainPage.actionBarVisibility = ChromeVisibility.Default;
                }

            }

            // This is necessary to place the activity indicator horizontally
            // and vertically in the middle

            Container {
                id: activityIndicatorContainer
                
                layout: StackLayout {                        
                }

                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                
                ActivityIndicator {
                    id: activityIndicator

                    minWidth: 200.0
                    minHeight: 200.0

                    onStarted: {
                        activityIndicator.visible = true
                        wikiScrollView.visible = false
                        resultsListView.visible = false
                    }
                    
                    onStopped: {
                        activityIndicatorContainer.visible = false
                        wikiScrollView.visible = true
                        resultsListView.visible = false
                    }
                }
            }
        }
    }
}
