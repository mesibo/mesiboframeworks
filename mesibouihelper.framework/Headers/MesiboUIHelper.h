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
//  MesiboUIHelper.h
//  MesiboUIHelper
//
//  Welcome and phone login screens for mesibo apps, built in code (no storyboards or resource
//  bundle), the same options and listener as com.mesibo.api:uihelper on Android.
//
//      MesiboWelcomeOptions *w = [MesiboWelcomeOptions new];
//      w.title = @"Messaging & Calls in your apps";
//      MesiboLoginOptions *l = [MesiboLoginOptions new];
//      window.rootViewController = [MesiboUIHelper getWelcomeViewController:w login:l listener:self];
//
//  The listener requests a verification code (code nil) and verifies the entered code, and
//  reports the result; after a successful login the app opens its next screen.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/** The welcome screen. Colors are 0xAARRGGBB. */
@interface MesiboWelcomeOptions : NSObject
/** shown at the top left; nil: none */
@property (nonatomic, strong, nullable) UIImage *logo;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *descriptionText;
@property (nonatomic, copy) NSString *buttonText;
/** the GitHub icon at the top right opens this; empty: hidden */
@property (nonatomic, copy) NSString *githubUrl;

@property (nonatomic) uint32_t backgroundColor;
@property (nonatomic) uint32_t titleColor;
@property (nonatomic) uint32_t descriptionColor;
@property (nonatomic) uint32_t buttonColor;
@property (nonatomic) uint32_t buttonTextColor;
@property (nonatomic) uint32_t githubIconColor;
@end

/** The phone login screens. %PHONE% and %SECONDS% are replaced. Colors are 0xAARRGGBB. */
@interface MesiboLoginOptions : NSObject
// -- phone number --
@property (nonatomic, copy) NSString *phoneTitle;
@property (nonatomic, copy) NSString *phoneMessage;
@property (nonatomic, copy) NSString *phoneHint;
@property (nonatomic, copy) NSString *phoneButtonText;
@property (nonatomic, copy) NSString *invalidPhoneMessage;
@property (nonatomic) int defaultCountryCode;

// -- verification code --
@property (nonatomic, copy) NSString *codeTitle;
@property (nonatomic, copy) NSString *codeMessage;
@property (nonatomic, copy) NSString *codeHint;
@property (nonatomic, copy) NSString *codeButtonText;
@property (nonatomic, copy) NSString *invalidCodeMessage;
@property (nonatomic, copy) NSString *changeNumberText;
@property (nonatomic, copy) NSString *resendText;
@property (nonatomic, copy) NSString *resendWaitText;
@property (nonatomic) int codeLength;
@property (nonatomic) int resendDelaySeconds;

// -- a note below the phone number, e.g. how to get a code; empty: hidden --
@property (nonatomic, copy) NSString *note;
@property (nonatomic, strong, nullable) UIImage *noteIcon;
@property (nonatomic) uint32_t noteColor;
@property (nonatomic) uint32_t noteBorderColor;
@property (nonatomic) uint32_t noteBackgroundColor;

@property (nonatomic, copy) NSString *selectCountryTitle;
@property (nonatomic, copy) NSString *searchCountryHint;
@property (nonatomic, copy) NSString *loginFailedMessage;

// -- colors --
@property (nonatomic) uint32_t backgroundColor;
@property (nonatomic) uint32_t titleColor;
@property (nonatomic) uint32_t messageColor;
@property (nonatomic) uint32_t inputColor;
/** input outline, links, progress */
@property (nonatomic) uint32_t accentColor;
@property (nonatomic) uint32_t buttonColor;
@property (nonatomic) uint32_t buttonTextColor;
@property (nonatomic) uint32_t errorColor;
@end

/** YES on success; call on any thread */
typedef void (^MesiboLoginResultBlock)(BOOL result);

@protocol MesiboLoginUiHelperListener <NSObject>
/**
 * Called with code nil to request a verification code for phone (with the country code, no +),
 * and with the entered code to verify it. Report the outcome through result.
 */
-(BOOL) MesiboLoginUiHelper_onLogin:(UIViewController *)parent phone:(NSString *)phone code:(nullable NSString *)code
                             result:(MesiboLoginResultBlock)result NS_SWIFT_NAME(MesiboLoginUiHelper_onLogin(parent:phone:code:result:));
@optional
/** country calling code to preselect; 0: MesiboLoginOptions.defaultCountryCode */
-(int) MesiboLoginUiHelper_getCountryCode:(UIViewController *)parent NS_SWIFT_NAME(MesiboLoginUiHelper_getCountryCode(parent:));
/** NO to reject phone (with the country code, no +) before a code is requested */
-(BOOL) MesiboLoginUiHelper_isPhoneValid:(UIViewController *)parent phone:(NSString *)phone NS_SWIFT_NAME(MesiboLoginUiHelper_isPhoneValid(parent:phone:));
@end

@interface MesiboUIHelper : NSObject

+(void) setLoginListener:(nullable id<MesiboLoginUiHelperListener>)listener;

/** The welcome screen in a navigation controller (its button opens the login), e.g. the window's root. */
+(UIViewController *) getWelcomeViewController:(nullable MesiboWelcomeOptions *)welcome login:(nullable MesiboLoginOptions *)login
                                      listener:(nullable id<MesiboLoginUiHelperListener>)listener;
/** The login screen in a navigation controller, e.g. the window's root after logout. */
+(UIViewController *) getLoginViewController:(nullable MesiboLoginOptions *)login listener:(nullable id<MesiboLoginUiHelperListener>)listener;

/** Presents the welcome screen full screen over parent. */
+(void) launchWelcome:(UIViewController *)parent welcome:(nullable MesiboWelcomeOptions *)welcome login:(nullable MesiboLoginOptions *)login
             listener:(nullable id<MesiboLoginUiHelperListener>)listener;
/** Presents the login screen full screen over parent. */
+(void) launchLogin:(UIViewController *)parent login:(nullable MesiboLoginOptions *)login listener:(nullable id<MesiboLoginUiHelperListener>)listener;

@end

NS_ASSUME_NONNULL_END
