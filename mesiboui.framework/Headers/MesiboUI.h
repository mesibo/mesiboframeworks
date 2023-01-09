//
//  MesiboUI.h
//  MesiboUI
//
//  Copyright © 2018 Mesibo. All rights reserved.
//
#ifndef __MESIBOUI_H
#define __MESIBOUI_H
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "Mesibo/Mesibo.h"
//#import "UITableViewWithReloadCallback.h"

@interface MesiboCell : UITableViewCell {
    
}
@end

@protocol MesiboMessageViewDelegate <NSObject>
@required
- (UITableView *) getMesiboTableView;
- (CGFloat)MesiboTableView:(UITableView *)tableView heightForMessage:(MesiboMessage *)message;
- (MesiboCell *)MesiboTableView:(UITableView *)tableView cellForMessage:(MesiboMessage *)message;
- (MesiboCell *)MesiboTableView:(UITableView *)tableView show:(MesiboMessage *)message;
@optional
@end

@protocol MesiboUIDelegate <NSObject>

@required

-(void) MesiboUI_onShowProfile:(id _Nonnull)parent profile:(MesiboProfile * _Nonnull) profile NS_SWIFT_NAME(MesiboUI_onShowProfile(parent:profile:));
-(NSArray * _Nullable) MesiboUI_onGetMenu:(id _Nonnull)parent type:(int) type profile:(MesiboProfile * _Nullable)profile NS_SWIFT_NAME(MesiboUI_onGetMenu(parent:type:profile:));
-(BOOL) MesiboUI_onMenuItemSelected:(id _Nonnull)parent type:(int)type profile:(MesiboProfile * _Nullable)profile item:(int)item NS_SWIFT_NAME(MesiboUI_onMenuItemSelected(parent:type:profile:item:));
@end

#define LOCATION_APP_APPLE      0
#define LOCATION_APP_GOOGLEMAP  1
#define LOCATION_APP_PROMPT     2
#define LOCATION_APP_PROMPTONCE 3

@interface MesiboUiOptions : NSObject
@property (nonatomic, nullable) UIImage *contactPlaceHolder;
@property (nonatomic, nullable) UIImage *messagingBackground;

@property (nonatomic) BOOL useLetterTitleImage;

@property (nonatomic) BOOL enableVoiceCall;
@property (nonatomic) BOOL enableVideoCall;
@property (nonatomic) BOOL enableForward;
@property (nonatomic) BOOL enableReply;
@property (nonatomic) BOOL enableSearch;
@property (nonatomic) BOOL enableBackButton;
@property (nonatomic) BOOL enableMessageButton;
@property (nonatomic) BOOL hidesBottomBarWhenPushed;

@property (nonatomic) BOOL e2eIndicator;


@property (copy, nonatomic, nonnull) NSString *messageListTitle;
@property (copy, nonatomic, nonnull) NSString *userListTitle;
@property (copy, nonatomic, nonnull) NSString *createGroupTitle;
@property (copy, nonatomic, nonnull) NSString *selectContactTitle;
@property (copy, nonatomic, nonnull) NSString *selectGroupContactsTitle;
@property (copy, nonatomic, nonnull) NSString *forwardTitle;
@property (copy, nonatomic, nonnull) NSString *forwardedTitle;

@property (copy, nonatomic, nonnull) NSString *userOnlineIndicationTitle;
@property (copy, nonatomic, nullable) NSString *onlineIndicationTitle;
@property (copy, nonatomic, nonnull) NSString *offlineIndicationTitle;
@property (copy, nonatomic, nonnull) NSString *connectingIndicationTitle;
@property (copy, nonatomic, nonnull) NSString *noNetworkIndicationTitle;
@property (copy, nonatomic, nonnull) NSString *suspendedIndicationTitle;

@property (copy, nonatomic, nonnull) NSString *typingIndicationTitle;
@property (copy, nonatomic, nonnull) NSString *joinedIndicationTitle;

@property (copy, nonatomic, nonnull) NSString *groupDeletedTitle;
@property (copy, nonatomic, nonnull) NSString *groupNotMemberTitle;

@property (copy, nonatomic, nonnull) NSString *e2eeActive;
@property (copy, nonatomic, nonnull) NSString *e2eeIdentityChanged;
@property (copy, nonatomic, nonnull) NSString *e2eeInactive;


@property (copy, nonatomic, nonnull) NSString *emptyUserListMessage;
@property (copy, nonatomic, nonnull) NSString *emptyMessageListMessage;
@property (copy, nonatomic, nonnull) NSString *emptySearchListMessage;
@property (copy, nonatomic, nonnull) UIFont *emptyUserListMessageFont;
@property (assign, nonatomic) int emptyUserListMessageColor;

@property (nonatomic) BOOL showRecentInForward;
@property (nonatomic) BOOL mConvertSmilyToEmoji;

@property (assign, nonatomic, nullable) int *mLetterTitleColors;
@property (assign, nonatomic) uint32_t mToolbarColor;
@property (assign, nonatomic) uint32_t mStatusBarColor;
@property (assign, nonatomic) uint32_t mToolbarTextColor;
@property (assign, nonatomic) uint32_t mUserListTypingIndicationColor;
@property (assign, nonatomic) uint32_t mUserListStatusColor;
@property (assign, nonatomic) uint32_t mUserListMaxRows;
@property (assign, nonatomic) uint32_t messageBackgroundColorForMe;
@property (assign, nonatomic) uint32_t messageBackgroundColorForPeer;
@property (assign, nonatomic) uint32_t titleBackgroundColorForMe;
@property (assign, nonatomic) uint32_t titleBackgroundColorForPeer;
@property (assign, nonatomic) uint32_t messagingBackgroundColor;
@property (assign, nonatomic) uint32_t messageInputBackgroundColor;
@property (assign, nonatomic) uint32_t messageInputButtonsColor;
@property (assign, nonatomic) uint32_t messageInputBorderColor;
@property (assign, nonatomic) uint32_t messageInputTextColor;
@property (assign, nonatomic) uint32_t messageInputTextBackgroundColor;
@property (assign, nonatomic) int messageInputTextCornerRadiusRatio;


@property (assign, nonatomic) uint32_t customTextColor;
@property (assign, nonatomic) uint32_t customBackgroundColor;
@property (assign, nonatomic) uint32_t e2eeBackgroundColor;

@property (assign, nonatomic) uint32_t dateTextColor;
@property (assign, nonatomic) uint32_t dateBackgroundColor;

@property (assign, nonatomic) uint32_t titleTextColor;
@property (copy, nonatomic, nonnull) UIFont *titleFont;
@property (copy, nonatomic, nonnull) UIFont *subtitleFont;
@property (copy, nonatomic, nonnull) UIFont *messageFont;
@property (copy, nonatomic, nonnull) UIFont *customFont;
@property (copy, nonatomic, nonnull) UIFont *dateFont;

@property (copy, nonatomic, nonnull) UIFont *headingFont;
@property (assign, nonatomic) uint32_t headingTextColor;

@property (assign, nonatomic) uint32_t timeTextColor;

@property (assign, nonatomic) uint32_t messageTextColor;
@property (assign, nonatomic) uint32_t messageDeletedTextColor;
@property (assign, nonatomic) uint32_t messagePictureTextColor;
@property (assign, nonatomic) uint32_t messageReplyTextColor;



@property (assign, nonatomic) uint32_t searchBarBackgroundColor;

@property (assign, nonatomic) int mediaButtonPosition;
@property (assign, nonatomic) int locationButtonPosition;
@property (assign, nonatomic) int docButtonPosition;
@property (assign, nonatomic) int audioButtonPosition;

@property (assign, nonatomic) int preferredLocationApp;

@property (assign, nonatomic) uint64_t mMaxImageFileSize;
@property (assign, nonatomic) uint64_t mMaxVideoFileSize;

@property (assign, nonatomic) BOOL mEnableNotificationBadge;

@property (copy, nonatomic, nonnull) NSString *recentUsersTitle;
@property (copy, nonatomic, nonnull) NSString *allUsersTitle;
@property (copy, nonatomic, nonnull) NSString *groupMembersTitle;

@property (copy, nonatomic, nonnull) NSString *today;
@property (copy, nonatomic, nonnull) NSString *yesterday;
@property (copy, nonatomic, nonnull) NSString *at;

@property (copy, nonatomic, nonnull) NSString *you;

@property (copy, nonatomic, nonnull) NSString *shareMediaTitle;
@property (copy, nonatomic, nonnull) NSString *shareMediaSubTitle;
@property (copy, nonatomic, nonnull) NSString *shareMediaCameraTitle;
@property (copy, nonatomic, nonnull) NSString *shareMediaGalleryTitle;
@property (copy, nonatomic, nonnull) NSString *shareMediaAudioTitle;
@property (copy, nonatomic, nonnull) NSString *shareMediaLocationTitle;
@property (copy, nonatomic, nonnull) NSString *shareMediaDocumentTitle;
@property (copy, nonatomic, nonnull) NSString *cancelTitle;

@property (copy, nonatomic, nonnull) NSString *missedVoiceCallTitle;
@property (copy, nonatomic, nonnull) NSString *missedVideoCallTitle;
@property (copy, nonatomic, nonnull) NSString *deletedMessageTitle;

@property (copy, nonatomic, nonnull) NSString *deleteMessagesTitle;
@property (copy, nonatomic, nonnull) NSString *deleteForEveryoneTitle;
@property (copy, nonatomic, nonnull) NSString *deleteForMeTitle;
@property (copy, nonatomic, nonnull) NSString *deleteTitle;
@property (copy, nonatomic, nonnull) NSString *deleteAlertTitle;

@property (assign, nonatomic) int verticalImageWidth;
@property (assign, nonatomic) int horizontalImageWidth;

@end


@interface MesiboUI : NSObject

+(void) setListener:(id<MesiboUIDelegate> _Nullable)delegate;
+(id<MesiboUIDelegate> _Nullable) getListener;

+(void) launchEditGroupDetails:(id _Nonnull)parent groupid:(uint32_t) groupid;

+(UIViewController * _Nullable) getMesiboUIViewController ;
+ (UIViewController * _Nullable) getMesiboUIViewController:(id _Nonnull)uidelegate;
+(void) launchMesiboUIViewController:(UIViewController * _Nonnull)parent uidelegate:(id _Nonnull)uidelegate back:(BOOL)back;

+(UIImage * _Nullable) getDefaultImage:(BOOL) group;



+(nonnull MesiboUiOptions *) getUiOptions;
//+(void) setUiOptions:(MesiboUiOptions * _Nonnull)options;

+(void) launchMessageViewControllerWithNavigation:(UIViewController * _Nonnull)parent profile:(id _Nonnull)profile uidelegate:(id _Nonnull)uidelegate;
+(void) launchMessageViewController:(UIViewController * _Nonnull) parent profile:(MesiboProfile* _Nonnull)profile ;
+(void) launchMessageViewController:(UIViewController * _Nonnull) parent profile:(MesiboProfile* _Nonnull)profile uidelegate:(id _Nonnull)uidelegate;

+(void) showEndToEncEncryptionInfo:(UIViewController * _Nonnull) parent profile:(MesiboProfile* _Nonnull)profile;

+ (UIViewController * _Nullable) getE2EViewController:(MesiboProfile * _Nullable)profile ;

//+(void) getUITableViewInstance:(UITableViewWithReloadCallback *) table;
+(NSBundle * _Nonnull) getMesiboUIBumble;

@end


#endif
