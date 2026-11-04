/******************************************************************************
* By accessing or copying this work, you agree to comply with the following   *
* terms:                                                                      *
*                                                                             *
* Copyright (c) 2019-2023 mesibo                                              *
* https://mesibo.com                                                          *
* All rights reserved.                                                        *
*                                                                             *
* Redistribution is not permitted. Use of this software is subject to the     *
* conditions specified at https://mesibo.com . When using the source code,    *
* maintain the copyright notice, conditions, disclaimer, and  links to mesibo * 
* website, documentation and the source code repository.                      *
*                                                                             *
* Do not use the name of mesibo or its contributors to endorse products from  *
* this software without prior written permission.                             *
*                                                                             *
* This software is provided "as is" without warranties. mesibo and its        *
* contributors are not liable for any damages arising from its use.           *
*                                                                             *
* Documentation: https://mesibo.com/documentation/                            *
*                                                                             *
* Source Code Repository: https://github.com/mesibo/                          *
*******************************************************************************/

//
//  MesiboUI.h
//  MesiboUI
//
//  The messaging screens of mesibo: the chat list, chats, groups and profiles, ready to use with
//  the mesibo API. The same API, options and names as com.mesibo.api:ui on Android.
//
//      MesiboUserListScreenOptions *opts = [MesiboUserListScreenOptions new];
//      UIViewController *list = [MesiboUI getUserListViewController:opts];   // push or present it
//
//      MesiboMessageScreenOptions *mopts = [MesiboMessageScreenOptions new];
//      mopts.profile = [Mesibo.getInstance getProfile:@"address" groupid:0];
//      [MesiboUI launchMessaging:self opts:mopts];
//
//  Customize texts, features and colors with [MesiboUI getUiDefaults] and the screens with a
//  MesiboUIListener ([MesiboUI setListener:]).
//

#ifndef __MESIBOUI_H
#define __MESIBOUI_H

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <mesibo/Mesibo.h>

NS_ASSUME_NONNULL_BEGIN

// -- chat list modes, MesiboUserListScreenOptions.mode --
#define MESIBO_MODE_MESSAGES    0   /* chats */
#define MESIBO_MODE_CONTACTS    1   /* pick a contact to chat with */
#define MESIBO_MODE_FORWARD     2   /* pick contacts to forward to */
#define MESIBO_MODE_GROUPS      3   /* pick members of a new group */
#define MESIBO_MODE_EDITGROUP   4   /* add members to MesiboUserListScreenOptions.groupid */

// -- MesiboScreen.type --
#define MESIBO_SCREEN_USERLIST  0   /* the chat list (and contact pickers), a MesiboUserListScreen */
#define MESIBO_SCREEN_MESSAGES  1   /* a chat, a MesiboMessageScreen */
#define MESIBO_SCREEN_GENERIC   2   /* any other screen, a plain MesiboScreen (the profile popup) */

// identifiers of the profile popup's default buttons (MesiboMenuItem.identifier in MesiboScreen.menu)
#define MESIBO_MENU_POPUP_MESSAGE @"mesibo.popup.message"
#define MESIBO_MENU_POPUP_INFO    @"mesibo.popup.info"

#pragma mark - screens

@class MesiboMenuItem;
typedef void (^MesiboMenuItemHandler)(MesiboMenuItem *item);

/** An item of a screen's menu (MesiboScreen.menu). */
@interface MesiboMenuItem : NSObject
@property (nonatomic, copy) NSString *title;
@property (nonatomic, strong, nullable) UIImage *image;
/** your own id, to find the item again */
@property (nonatomic, copy, nullable) NSString *identifier;
@property (nonatomic) BOOL destructive;
@property (nonatomic) BOOL hidden;
@property (nonatomic, copy, nullable) MesiboMenuItemHandler handler;
+ (instancetype)itemWithTitle:(NSString *)title image:(nullable UIImage *)image identifier:(nullable NSString *)identifier
                      handler:(nullable MesiboMenuItemHandler)handler;
@end

@interface MesiboScreenOptions : NSObject
@property (nonatomic) long sid;
@property (nonatomic, strong, nullable) id userObject;
@end

/**
 * A screen, given to MesiboUIListener's MesiboUI_onInitScreen. Check type before using a
 * subclass: MESIBO_SCREEN_USERLIST is a MesiboUserListScreen, MESIBO_SCREEN_MESSAGES a
 * MesiboMessageScreen.
 */
@interface MesiboScreen : NSObject
@property (nonatomic, weak, nullable) UIViewController *parent;
/** MESIBO_SCREEN_USERLIST, MESIBO_SCREEN_MESSAGES or MESIBO_SCREEN_GENERIC */
@property (nonatomic) int type;
/** the user or group of the screen, if any (chat, profile popup) */
@property (nonatomic, strong, nullable) MesiboProfile *profile;
@property (nonatomic, weak, nullable) UITableView *table;
/** buttons shown in the navigation bar; add yours */
@property (nonatomic, strong) NSMutableArray<UIBarButtonItem *> *buttons;
/**
 * The screen's menu: on the chat list and chats, the items of the "more" button in the
 * navigation bar; on the profile popup, the buttons below the picture (their image, or their
 * title without one).
 */
@property (nonatomic, strong) NSMutableArray<MesiboMenuItem *> *menu;
/** the item with this identifier, or nil */
- (nullable MesiboMenuItem *)menuItem:(NSString *)identifier;
@property (nonatomic, weak, nullable) UILabel *title;
@property (nonatomic, weak, nullable) UILabel *subtitle;
@property (nonatomic, weak, nullable) UIView *titleArea;
@property (nonatomic, strong, nullable) MesiboScreenOptions *options;
@end

@interface MesiboUserListScreen : MesiboScreen
@property (nonatomic) int mode;
@property (nonatomic, weak, nullable) UISearchBar *search;
@end

/** The message input of a chat screen. */
@interface MesiboMessageScreenControls : NSObject
@property (nonatomic, weak, nullable) UITextView *editText;
@property (nonatomic, weak, nullable) UIButton *attachButton;
@property (nonatomic, weak, nullable) UIButton *cameraButton;
@property (nonatomic, weak, nullable) UIButton *sendButton;
@end

@interface MesiboMessageScreen : MesiboScreen
@property (nonatomic, weak, nullable) UIImageView *profileImage;
@property (nonatomic, strong) MesiboMessageScreenControls *controls;
@end

#pragma mark - rows

/** Base class of your own rows (MesiboUIListener's MesiboUI_onGetCustomRow). */
@interface MesiboCell : UITableViewCell
@end

/** A row, given to MesiboUIListener. */
@interface MesiboRow : NSObject
@property (nonatomic, weak, nullable) UITableViewCell *row;
@property (nonatomic, strong, nullable) MesiboMessage *message;
@property (nonatomic, weak, nullable) MesiboScreen *screen;
@end

@interface MesiboUserListRow : MesiboRow
@property (nonatomic, strong, nullable) MesiboProfile *profile;
@property (nonatomic, weak, nullable) UILabel *name;
@property (nonatomic, weak, nullable) UILabel *subtitle;
@property (nonatomic, weak, nullable) UILabel *timestamp;
@property (nonatomic, weak, nullable) UIImageView *image;
@end

@interface MesiboMessageRow : MesiboRow
@property (nonatomic, weak, nullable) UILabel *title;
@property (nonatomic, weak, nullable) UILabel *subtitle;
@property (nonatomic, weak, nullable) UILabel *messageText;
@property (nonatomic, weak, nullable) UILabel *name;
@property (nonatomic, weak, nullable) UILabel *timestamp;
@property (nonatomic, weak, nullable) UIImageView *image;
@property (nonatomic, weak, nullable) UIImageView *status;
@property (nonatomic, weak, nullable) UIView *replyView;
@property (nonatomic) BOOL selected;
@end

#pragma mark - listener

/** Customize the screens. Every method is optional; return NO to keep the default behaviour. */
@protocol MesiboUIListener <NSObject>
@optional
/** A screen was created: add buttons or menu items, change the bar, ... Check screen.type. */
-(BOOL) MesiboUI_onInitScreen:(MesiboScreen *)screen NS_SWIFT_NAME(MesiboUI_onInitScreen(screen:));
/** Your own row (a MesiboCell, self-sizing with Auto Layout) for row.message / row.profile, or nil. */
-(nullable MesiboCell *) MesiboUI_onGetCustomRow:(MesiboScreen *)screen row:(MesiboRow *)row NS_SWIFT_NAME(MesiboUI_onGetCustomRow(screen:row:));
/** A row was bound; change its views (row fields). last: the last row. */
-(BOOL) MesiboUI_onUpdateRow:(MesiboScreen *)screen row:(MesiboRow *)row last:(BOOL)last NS_SWIFT_NAME(MesiboUI_onUpdateRow(screen:row:last:));
/** A row was tapped; return YES if you handled it. */
-(BOOL) MesiboUI_onClickedRow:(MesiboScreen *)screen row:(MesiboRow *)row NS_SWIFT_NAME(MesiboUI_onClickedRow(screen:row:));
/** The user wants to share a location; return YES to use your own location picker. */
-(BOOL) MesiboUI_onShowLocation:(UIViewController *)parent profile:(MesiboProfile *)profile NS_SWIFT_NAME(MesiboUI_onShowLocation(parent:profile:));
/**
 * An open screen is to be updated (+[MesiboUI updateScreens]), e.g. show or hide buttons or menu
 * items when a call starts or ends. Same screen object as in MesiboUI_onInitScreen.
 */
-(void) MesiboUI_onUpdateScreen:(MesiboScreen *)screen NS_SWIFT_NAME(MesiboUI_onUpdateScreen(screen:));
@end

/** Told when the user saves their profile; see +[MesiboUI setEditProfileListener:]. */
@protocol MesiboEditProfileListener <NSObject>
/**
 * The profile was saved; the screen closes after this returns. Open the next screen here, e.g.
 * the chat list when newUser.
 */
-(void) MesiboEditProfile_onSaved:(UIViewController *)parent profile:(MesiboProfile *)profile newUser:(BOOL)newUser NS_SWIFT_NAME(MesiboEditProfile_onSaved(parent:profile:newUser:));
@end

#pragma mark - options

@interface MesiboUserListScreenOptions : MesiboScreenOptions
@property (nonatomic) int mode;
/** messages to forward (MESIBO_MODE_FORWARD), NSNumber message ids */
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *forwardIds;
/** one message to forward (same as forwardIds with one id) */
@property (nonatomic) uint64_t forwardId;
/** a text to forward (MESIBO_MODE_FORWARD) */
@property (nonatomic, copy, nullable) NSString *forwardedMessage;
/** forward and close, instead of opening the chat when forwarding to one contact */
@property (nonatomic) BOOL forwardAndClose;
/** MESIBO_MODE_EDITGROUP: the group to add members to */
@property (nonatomic) uint32_t groupid;
/** only chats with messages matching this text */
@property (nonatomic, copy, nullable) NSString *readQuery;
@end

@interface MesiboMessageScreenOptions : MesiboScreenOptions
@property (nonatomic, strong, nullable) MesiboProfile *profile;
/** a message to forward to this chat when it opens */
@property (nonatomic) uint64_t forwardId;
/** no message input */
@property (nonatomic) BOOL readOnly;
@end

@interface MesiboEditProfileOptions : MesiboScreenOptions
/**
 * The "profile info" step after a new user signs in: an explanation (newProfileText), Next
 * instead of Save, the name required and no way back.
 */
@property (nonatomic) BOOL newUser;
/** show the user's address (phone number) below the fields */
@property (nonatomic) BOOL showAddress;
@end

#pragma mark - attachments

// -- MesiboAttachment.type: the built-in tiles of the attachment sheet, or your own --
#define MESIBO_ATTACH_GALLERY   0
#define MESIBO_ATTACH_CAMERA    1
#define MESIBO_ATTACH_VIDEO     2
#define MESIBO_ATTACH_DOCUMENT  3
#define MESIBO_ATTACH_AUDIO     4
#define MESIBO_ATTACH_LOCATION  5
#define MESIBO_ATTACH_CUSTOM    100

@class MesiboAttachment;
/** a tile was tapped in a chat with profile */
typedef void (^MesiboAttachmentHandler)(UIViewController *parent, MesiboProfile *profile, MesiboAttachment *attachment);

/**
 * One tile of the attachment sheet (MesiboUiDefaults.attachments): icon drawn in iconColor on a
 * circle of color. Built-in tiles run their own action; set handler to run yours instead. Your
 * own tiles are MESIBO_ATTACH_CUSTOM with a handler.
 */
@interface MesiboAttachment : NSObject
@property (nonatomic, readonly) int type;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, strong, nullable) UIImage *icon;
/** 0xAARRGGBB */
@property (nonatomic) uint32_t color;
@property (nonatomic) uint32_t iconColor;
/** NO: not shown */
@property (nonatomic) BOOL enabled;
/** called instead of the built-in action; required for MESIBO_ATTACH_CUSTOM */
@property (nonatomic, copy, nullable) MesiboAttachmentHandler handler;
- (instancetype)initWithType:(int)type title:(NSString *)title icon:(nullable UIImage *)icon color:(uint32_t)color;
/** your own tile */
- (instancetype)initWithTitle:(NSString *)title icon:(nullable UIImage *)icon color:(uint32_t)color handler:(MesiboAttachmentHandler)handler;
@end

#pragma mark - defaults

/**
 * Options, texts and colors of the messaging UI: change them through [MesiboUI getUiDefaults]
 * before showing a screen. The same names as MesiboUiDefaults on Android. Colors are 0xAARRGGBB;
 * 0 uses the theme color (light and dark).
 */
@interface MesiboUiDefaults : NSObject

// -- features --
@property (nonatomic) BOOL enableForward;
@property (nonatomic) BOOL enableEdit;
@property (nonatomic) BOOL enableReply;
/** swipe a message to the right to reply */
@property (nonatomic) BOOL enableSwipeToReply;
@property (nonatomic) BOOL enableSearch;
/** a back button on the chat list (when it is not the app's main screen) */
@property (nonatomic) BOOL enableBackButton;
/** attachments (camera, gallery, documents, audio, location) in the message input */
@property (nonatomic) BOOL showRichMessageButtons;
/**
 * Tiles of the attachment sheet, in this order: gallery, camera, video, document, audio and
 * location to begin with. Change, disable, remove, reorder or add tiles, e.g.
 *     [o getAttachment:MESIBO_ATTACH_LOCATION].enabled = NO;
 *     [o.attachments addObject:[[MesiboAttachment alloc] initWithTitle:@"Contact" icon:img color:0xFF009DE2 handler:...]];
 */
@property (nonatomic, strong) NSMutableArray<MesiboAttachment *> *attachments;
/** the tile of a built-in type, nil if removed */
- (nullable MesiboAttachment *)getAttachment:(int)type;
/** recent photos at the top of the attachment sheet (only when photo access was given) */
@property (nonatomic) BOOL showRecentPhotos;
@property (nonatomic) BOOL showMissedCalls;
/** jump to new messages even when the user has scrolled up */
@property (nonatomic) BOOL forceScrollToLatest;
/** replace :) and others with emoji when sending */
@property (nonatomic) BOOL convertSmileyToEmoji;
/** letter avatars for profiles without a picture; NO: a person / group icon */
@property (nonatomic) BOOL useLetterTitleImage;
@property (nonatomic) BOOL showRecentInForward;
/** a time on chats whose messages were cleared */
@property (nonatomic) BOOL showTimestampForClearedChats;
/** see -[MesiboProfile clearMessages:] */
@property (nonatomic) int clearMessageMode;
@property (nonatomic) BOOL signedFiles;
/** longest side of sent pictures, in pixels */
@property (nonatomic) int imageMaxDimension;
/** space between bubbles of the same sender, in points */
@property (nonatomic) int messageSpacing;
/** space above the first bubble when the sender changes, in points */
@property (nonatomic) int messageGroupSpacing;
/** a tail on the first bubble of a run (NO: a small corner on the sender's side) */
@property (nonatomic) BOOL showBubbleTail;
/** messages of only one to three emoji in large, without a bubble */
@property (nonatomic) BOOL largeEmoji;
/** opening a chat with unread messages: a divider above the first one, shown on screen */
@property (nonatomic) BOOL showUnreadDivider;
/** a faint pattern on the chat background (when there is no messagingBackground image) */
@property (nonatomic) BOOL showWallpaperPattern;
/**
 * Long-pressing a message shows these emoji above it (and selects it); tapping one reacts with it.
 * Until mesibo has reactions, a reaction is sent as a message with the emoji. Empty: no panel.
 */
@property (nonatomic, copy) NSArray<NSString *> *reactions;
/** longest side of profile pictures (own and groups), in pixels */
@property (nonatomic) int profileImageMaxDimension;

// -- profile --
/** tapping a picture in the chat list opens a popup with the picture and buttons; NO: tapping it opens the chat */
@property (nonatomic) BOOL showProfilePopup;
@property (nonatomic, copy) NSString *messageButtonTitle;
@property (nonatomic, copy) NSString *infoButtonTitle;
@property (nonatomic) BOOL showAddressInProfileView;
@property (nonatomic) BOOL showLastSeenInProfileView;
@property (nonatomic) BOOL showGroupMembersInProfileView;
/** the rows of the profile screen; turn off what the app does not use, e.g. block calls without calls */
@property (nonatomic) BOOL showAboutInProfileView;
@property (nonatomic) BOOL showMediaInProfileView;
@property (nonatomic) BOOL showMuteInProfileView;
@property (nonatomic) BOOL showBlockMessagesInProfileView;
@property (nonatomic) BOOL showBlockCallsInProfileView;
@property (nonatomic) BOOL showClearChatInProfileView;

// -- new chat with an address not in the list (contact picker, MESIBO_MODE_CONTACTS) --
/** a row to enter a phone number or address and chat with it */
@property (nonatomic) BOOL showEnterAddress;
@property (nonatomic, copy) NSString *enterAddressTitle;
@property (nonatomic, copy) NSString *enterAddressSubtitle;
/** the prompt: its title, message, input placeholder, keyboard and button */
@property (nonatomic, copy) NSString *enterAddressPromptTitle;
@property (nonatomic, copy, nullable) NSString *enterAddressPromptMessage;
@property (nonatomic, copy, nullable) NSString *enterAddressHint;
@property (nonatomic) UIKeyboardType enterAddressKeyboard;
@property (nonatomic, copy) NSString *enterAddressButtonTitle;
/** shown when enterAddressFilter returns nil */
@property (nonatomic, copy) NSString *enterAddressInvalid;
/**
 * Turns what the user typed into the address to chat with (e.g. add the country code), or nil
 * if it is not valid. nil filter: spaces, dashes, dots and brackets are removed from a phone
 * number; anything else is used as typed.
 */
@property (nonatomic, copy, nullable) NSString *_Nullable (^enterAddressFilter)(NSString *input);

// -- edit profile (+[MesiboUI launchEditProfile:opts:]) --
@property (nonatomic, copy) NSString *editProfileTitle;
@property (nonatomic, copy, getter=getNewProfileTitle) NSString *newProfileTitle;
@property (nonatomic, copy, getter=getNewProfileText) NSString *newProfileText;
@property (nonatomic, copy) NSString *nameTitle;
@property (nonatomic, copy) NSString *nameHint;
@property (nonatomic, copy) NSString *nameRequired;
@property (nonatomic, copy) NSString *statusTitle;
@property (nonatomic, copy) NSString *statusHint;
@property (nonatomic, copy) NSString *addressTitle;
@property (nonatomic, copy) NSString *profilePhotoTitle;
@property (nonatomic, copy) NSString *viewPhotoTitle;
@property (nonatomic, copy) NSString *removePhotoTitle;
@property (nonatomic, copy) NSString *takePhotoTitle;
@property (nonatomic, copy) NSString *choosePhotoTitle;
@property (nonatomic, copy) NSString *saveButtonTitle;
@property (nonatomic, copy) NSString *nextButtonTitle;
@property (nonatomic) int maxNameLength;
@property (nonatomic) int maxStatusLength;

// -- end-to-end encryption --
@property (nonatomic) BOOL e2eeIndicator;

// -- images --
@property (nonatomic, strong, nullable) UIImage *contactPlaceHolder;
/** wallpaper of the chat screen; nil: messagingBackgroundColor */
@property (nonatomic, strong, nullable) UIImage *messagingBackground;
/** colors of letter avatars (NSNumber 0xAARRGGBB), picked by name; nil: built-in palette */
@property (nonatomic, strong, nullable) NSArray<NSNumber *> *letterTileColors;

// -- colors (0: theme) --
@property (nonatomic) uint32_t toolbarColor;
@property (nonatomic) uint32_t toolbarTextColor;
/** toolbar icons (back, buttons, menu); 0: same as toolbarTextColor. A button with its own tintColor keeps it */
@property (nonatomic) uint32_t toolbarIconColor;
@property (nonatomic) uint32_t accentColor;
@property (nonatomic) uint32_t messageBackgroundColorForMe;
@property (nonatomic) uint32_t messageBackgroundColorForPeer;
@property (nonatomic) uint32_t messagingBackgroundColor;
@property (nonatomic) uint32_t userListBackgroundColor;

// -- texts --
@property (nonatomic, copy) NSString *messageListTitle;   // the app name if empty
@property (nonatomic, copy) NSString *userListTitle;
@property (nonatomic, copy) NSString *createGroupTitle;
@property (nonatomic, copy) NSString *createGroupSubtitle;
@property (nonatomic, copy) NSString *modifyGroupTitle;
@property (nonatomic, copy) NSString *selectGroupContactsTitle;
@property (nonatomic, copy) NSString *forwardTitle;
@property (nonatomic, copy) NSString *editTitle;
@property (nonatomic, copy) NSString *headerTitle;        // a notice above the first message
@property (nonatomic, copy) NSString *searchHint;
@property (nonatomic, copy) NSString *messageHint;

@property (nonatomic, copy) NSString *e2eeTitle;
@property (nonatomic, copy) NSString *e2eeActive;
@property (nonatomic, copy) NSString *e2eeIdentityChanged;
@property (nonatomic, copy) NSString *e2eeInactive;

@property (nonatomic, copy) NSString *userOnlineIndicationTitle;
@property (nonatomic, copy, nullable) NSString *onlineIndicationTitle;   // subtitle of the chat list when connected
@property (nonatomic, copy) NSString *typingIndicationTitle;
@property (nonatomic, copy) NSString *joinedIndicationTitle;
@property (nonatomic, copy) NSString *lastSeenTitle;
@property (nonatomic, copy) NSString *offlineIndicationTitle;
@property (nonatomic, copy) NSString *connectingIndicationTitle;
@property (nonatomic, copy) NSString *noNetworkIndicationTitle;
@property (nonatomic, copy) NSString *suspendIndicationTitle;

@property (nonatomic, copy) NSString *recentUsersTitle;
@property (nonatomic, copy) NSString *allUsersTitle;
@property (nonatomic, copy) NSString *groupMembersTitle;
@property (nonatomic, copy) NSString *messagesTitle;
@property (nonatomic, copy) NSString *groupNameHint;
@property (nonatomic, copy) NSString *groupNameTooShort;
@property (nonatomic, copy) NSString *groupCreateFailed;
@property (nonatomic, copy) NSString *mediaTitle;
@property (nonatomic, copy) NSString *addMembersTitle;
@property (nonatomic, copy) NSString *leaveGroupTitle;
@property (nonatomic, copy) NSString *deleteGroupTitle;
@property (nonatomic, copy) NSString *makeAdminTitle;
@property (nonatomic, copy) NSString *removeAdminTitle;
@property (nonatomic, copy) NSString *removeMemberTitle;
@property (nonatomic, copy) NSString *messageMemberTitle;
@property (nonatomic, copy) NSString *adminTitle;
@property (nonatomic, copy) NSString *blockMessagesTitle;
@property (nonatomic, copy) NSString *blockCallsTitle;
@property (nonatomic, copy) NSString *muteTitle;
@property (nonatomic, copy) NSString *clearChatTitle;
@property (nonatomic, copy) NSString *e2eeVerifyTitle;
@property (nonatomic, copy) NSString *e2eeVerifyHelp;
@property (nonatomic, copy) NSString *e2eeResetTitle;
@property (nonatomic, copy) NSString *youTitle;
@property (nonatomic, copy) NSString *unknownTitle;
@property (nonatomic, copy) NSString *forwardedTitle;
@property (nonatomic, copy) NSString *editedTitle;
@property (nonatomic, copy) NSString *missedVoiceCallTitle;
@property (nonatomic, copy) NSString *missedVideoCallTitle;
@property (nonatomic, copy) NSString *deletedMessageTitle;
@property (nonatomic, copy) NSString *photoTitle;
@property (nonatomic, copy) NSString *videoTitle;
@property (nonatomic, copy) NSString *audioTitle;
@property (nonatomic, copy) NSString *documentTitle;
@property (nonatomic, copy) NSString *locationTitle;

@property (nonatomic, copy) NSString *clearMessagesTitle;
@property (nonatomic, copy) NSString *deleteChatsTitle;
@property (nonatomic, copy) NSString *deleteMessagesTitle;
@property (nonatomic, copy) NSString *deleteForEveryoneTitle;
@property (nonatomic, copy) NSString *deleteForMeTitle;
@property (nonatomic, copy) NSString *deleteTitle;
@property (nonatomic, copy) NSString *copiedTitle;
@property (nonatomic, copy) NSString *emptyUserListMessage;
@property (nonatomic, copy) NSString *emptyContactsMessage;
@property (nonatomic, copy) NSString *emptySearchListMessage;
@property (nonatomic, copy) NSString *messageAlertOnScrolledView;
/** the unread divider: "1 unread message", "%d unread messages" */
@property (nonatomic, copy) NSString *unreadMessageTitle;
@property (nonatomic, copy) NSString *unreadMessagesTitle;

@property (nonatomic, copy) NSString *sendLimitReachedTitle;
@property (nonatomic, copy) NSString *sendLimitReached;
@property (nonatomic, copy) NSString *blockedMessage;
@property (nonatomic, copy) NSString *notGroupMemberMessage;
@property (nonatomic, copy) NSString *recordHint;
@property (nonatomic, copy) NSString *recordCancel;
@property (nonatomic, copy) NSString *micPermissionDenied;
@property (nonatomic, copy) NSString *invalidGroupTitle;
@property (nonatomic, copy) NSString *invalidGroupMessage;

@property (nonatomic) BOOL showMonthFirst;
@property (nonatomic, copy) NSString *today;
@property (nonatomic, copy) NSString *yesterday;
@property (nonatomic, copy) NSString *yes;
@property (nonatomic, copy) NSString *no;
@property (nonatomic, copy) NSString *ok;
@property (nonatomic, copy) NSString *cancel;

@end

#pragma mark - dialogs

typedef void (^MesiboDialogSelectHandler)(NSInteger index);

/** What MesiboDialogs shows. */
@interface MesiboDialogOptions : NSObject
@property (nonatomic, copy, nullable) NSString *title;
@property (nonatomic, copy, nullable) NSString *message;
/** list of choices; if set, onSelect gets the tapped index (no positive / negative buttons) */
@property (nonatomic, copy, nullable) NSArray<NSString *> *items;
@property (nonatomic, copy, nullable) MesiboDialogSelectHandler onSelect;
/** indexes of items shown as destructive (red), e.g. delete or remove */
@property (nonatomic, copy, nullable) NSArray<NSNumber *> *destructiveItems;
/** nil: MesiboUiDefaults.ok */
@property (nonatomic, copy, nullable) NSString *positiveLabel;
/** nil: no negative button (a sheet always has MesiboUiDefaults.cancel to close it) */
@property (nonatomic, copy, nullable) NSString *negativeLabel;
@property (nonatomic, copy, nullable) dispatch_block_t onPositive;
@property (nonatomic, copy, nullable) dispatch_block_t onNegative;
/** an action sheet from the bottom instead of a centered alert */
@property (nonatomic) BOOL sheet;
/** the positive button as destructive (red) */
@property (nonatomic) BOOL destructive;
@end

/** The same dialogs and action sheets as the messaging UI, for a consistent look in the app. */
@interface MesiboDialogs : NSObject
+ (void)show:(UIViewController *)parent options:(MesiboDialogOptions *)options;
/** a message with OK */
+ (void)alert:(UIViewController *)parent title:(nullable NSString *)title message:(nullable NSString *)message;
@end

#pragma mark - MesiboUI

// -- +[MesiboUI setTheme:] --
#define MESIBO_THEME_SYSTEM  0   /* follow the system light / dark setting (default) */
#define MESIBO_THEME_LIGHT   1
#define MESIBO_THEME_DARK    2

@interface MesiboUI : NSObject

+(MesiboUiDefaults *) getUiDefaults NS_SWIFT_NAME(getUiDefaults());
+(void) setListener:(nullable id<MesiboUIListener>)listener;
+(nullable id<MesiboUIListener>) getListener;
/** Registers the callback of the edit profile screen (nil to remove). */
+(void) setEditProfileListener:(nullable id<MesiboEditProfileListener>)listener;
+(nullable id<MesiboEditProfileListener>) getEditProfileListener;

/** The chat list (or a contact picker, see opts.mode), to push or present yourself. */
+(UIViewController *) getUserListViewController:(nullable MesiboUserListScreenOptions *)opts;
/** A chat, to push or present yourself; nil without opts.profile. */
+(nullable UIViewController *) getMessageViewController:(MesiboMessageScreenOptions *)opts;

/** Shows the chat list: pushed when parent is in a navigation controller, else presented. */
+(void) launchUserList:(UIViewController *)parent opts:(nullable MesiboUserListScreenOptions *)opts;
+(void) launchMessaging:(UIViewController *)parent opts:(MesiboMessageScreenOptions *)opts;
+(void) launchForwardActivity:(UIViewController *)parent message:(NSString *)message forwardAndClose:(BOOL)forwardAndClose;
+(void) launchForwardActivity:(UIViewController *)parent messageIds:(NSArray<NSNumber *> *)messageIds forwardAndClose:(BOOL)forwardAndClose;
+(void) launchCreateGroup:(UIViewController *)parent;
/** Name and picture of a group (members are managed from its profile). */
+(void) launchEditGroup:(UIViewController *)parent groupid:(uint32_t)groupid;
/**
 * The user's own profile: picture, name and about. Use it as the app's edit profile screen, and
 * with opts.newUser for a new user to set their name and picture. When saved, the listener set
 * with setEditProfileListener: is called.
 */
+(void) launchEditProfile:(UIViewController *)parent opts:(nullable MesiboEditProfileOptions *)opts;

/** The profile of a user or group: picture, status, media, members, settings. */
+(void) showProfile:(UIViewController *)parent profile:(MesiboProfile *)profile;
/**
 * A small popup with the picture and name of a user or group and a row of buttons: Message,
 * Info and your own. The chat list shows it when a picture is tapped (unless showProfilePopup is
 * NO). It is a MESIBO_SCREEN_GENERIC screen for MesiboUI_onInitScreen with profile, title and
 * menu: each MesiboMenuItem of the menu (not hidden) is a button. Remove the defaults with the identifiers
 * MESIBO_MENU_POPUP_MESSAGE and MESIBO_MENU_POPUP_INFO.
 */
+(void) showProfilePopup:(UIViewController *)parent profile:(MesiboProfile *)profile;
+(void) showEndToEndEncryptionInfo:(UIViewController *)parent profile:(nullable MesiboProfile *)profile;

/**
 * Light or dark for the app: MESIBO_THEME_SYSTEM (default), MESIBO_THEME_LIGHT or
 * MESIBO_THEME_DARK. Call it at the start, e.g. in application:didFinishLaunchingWithOptions:.
 */
+(void) setTheme:(int)theme;
/**
 * Calls MesiboUIListener's MesiboUI_onUpdateScreen for every open chat list and chat screen, so
 * the app can update them, e.g. its buttons when a call starts or ends. Any thread.
 */
+(void) updateScreens;

+(NSString *) version;

@end

NS_ASSUME_NONNULL_END

#endif
