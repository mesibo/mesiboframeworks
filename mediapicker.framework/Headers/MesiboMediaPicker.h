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

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>


#define PICK_CAMERA_IMAGE 0
#define PICK_IMAGE_GALLERY 1
#define PICK_VIDEO_GALLERY 2
#define PICK_VIDEO_RECORDING 3
#define PICK_AUDIO_FILES 4
#define PICK_LOCATION 5
#define PICK_DOCUMENTS 6


typedef BOOL (^MesiboImageEditorBlock)(UIImage *image, NSString *caption);
typedef void (^MesiboMediaFilesBlock)(UIImage *image);
typedef void (^MesiboImageViewerBlock)(UIImageView *image, UILabel *caption);

@interface MesiboMediaPickerFile : NSObject

@property (atomic) NSString *filePath;
@property (atomic) NSString *mp4Path;
@property (strong,nonatomic) UIImage *image;
@property (atomic) NSString *message;
@property (atomic) NSString *title;
@property (atomic) int fileType;
@property (atomic) int mp4state;
@property (nonatomic) double lat;
@property (nonatomic) double lon;
@property (nonatomic) int zoom;
@property (nonatomic) int size;
@property (nonatomic) NSString *url;
@property (nonatomic) id phasset;
@property (atomic) NSString *localIdentifier;
@property (nonatomic) void (^mp4TranscodingHandler)(MesiboMediaPickerFile * file);

-(void) setMp4TranscodingHandler:(void (^)(MesiboMediaPickerFile *))handler;
-(void) setMp4Ready:(BOOL)ready;
@end

// gallery floating button, see MesiboMediaPickerOptions.mGalleryButton
#define GALLERY_BUTTON_CAMERA 0     // the built-in camera; the photo / video is returned as the pick
#define GALLERY_BUTTON_MORE_APPS 1  // iOS photo picker (all photos, iCloud, ...)
#define GALLERY_BUTTON_FOLDERS 2    // the album list
#define GALLERY_BUTTON_NONE 3

@interface MesiboMediaPickerOptions : NSObject
@property (assign, nonatomic) uint32_t mToolbarColor;

/** Send button and selection color, 0xAARRGGBB. */
@property (assign, nonatomic) uint32_t mAccentColor;
/** The library's own gallery (default); NO: the iOS photo picker. */
@property (assign, nonatomic) BOOL mUseBuiltInGallery;
/** Gallery full screen instead of a bottom sheet. */
@property (assign, nonatomic) BOOL mGalleryFullScreen;
/** The gallery's floating button, GALLERY_BUTTON_*; default GALLERY_BUTTON_CAMERA. */
@property (assign, nonatomic) int mGalleryButton;
/** The library's own camera (default); NO: the iOS camera. */
@property (assign, nonatomic) BOOL mUseBuiltInCamera;
/** Filters and adjustments in the editor (default YES). */
@property (assign, nonatomic) BOOL mFiltersEnabled;
/** Text, stickers, drawing and canvas in the editor (default YES). */
@property (assign, nonatomic) BOOL mAnnotationEnabled;
/** The app's own image stickers, shown in the sticker panel. */
@property (strong, nonatomic) NSArray<UIImage *> *mStickers;
/**
 * Editor: the resolution it edits at, in pixels on the longer side (default 4096). Larger keeps more
 * detail when cropping, smaller uses less memory and is faster. The output size (maxDimension of
 * getImageEditor) is applied last; the editor never works below it.
 */
@property (assign, nonatomic) int mEditMaxDimension;
/** Editor: a light sharpening after scaling down to the output size (default YES). */
@property (assign, nonatomic) BOOL mSharpenOnResize;

- (UIColor *) toolBarColor;
- (UIColor *) accentColor;
@end


@interface MesiboMediaPicker : NSObject <UIDocumentPickerDelegate>
{
    void (^_completionHandler)(MesiboMediaPickerFile * file);
    
}


@property (strong ,nonatomic) UIViewController * mParent;
//@property (strong, nonatomic) NSMutableArray  *mAlbumListed;



-(void)pickMedia:(int) PICK_MEDIA :(void(^)(MesiboMediaPickerFile *file))handler ;

/**
 * Picks a file with the system document picker (Files, iCloud Drive, ...). The file is copied
 * into the app, so file.filePath stays readable. extensions: accepted extensions without the dot,
 * e.g. @[@"db"], checked after picking (nil: any). picked: called with nil when cancelled.
 * rejected: the picked file has another extension (optional). Same as FilePicker on Android.
 */
-(void)pickFile:(NSArray<NSString *> *)extensions picked:(void(^)(MesiboMediaPickerFile *file))picked rejected:(void(^)(NSString *name))rejected;


-(void)getImageEditor:(UIImage *) image  title:(NSString*)title hideEditControl:(BOOL)hideControls showCaption:(BOOL)showCaption showCropOverlay:(BOOL)showCropOverlay squareCrop:(BOOL)squareCrop maxDimension:(int) maxDimension withBlock: (MesiboImageEditorBlock)handler;

+ (MesiboMediaPicker *)sharedInstance;

-(void) showPhotoInViewer:(UIViewController *)presentController withImage : (UIImage*) photoImage withTitle:(NSString*) title;
-(void) showPhotoInViewer:(UIViewController *)presentController withImage : (UIImage*) photoImage withTitle:(NSString*)title handler:(MesiboImageViewerBlock) handler;

-(void) showMediaFiles : (UIViewController *)presentController withMediaData :(NSArray *) data withTitle:(NSString*) title;

-(void) showMediaFilesInViewer:(UIViewController *)presentController withInitialIndex:(int)index withData : (NSArray*) filesArray withTitle:(NSString*) title;

+(void) showFile:(UIViewController *)parent path:(NSString *)path title:(NSString *)title type:(int)type;
+(void) mapSnapShot:(double)lat lon:(double)lon handler:(void(^)(MesiboMediaPickerFile *file)) handler;
+ (UIImage *)getDefaultImageForExt:(NSString *)ext;

+(void) setUiOptions:(MesiboMediaPickerOptions *)options;
+(MesiboMediaPickerOptions *) getUiOptions;
@end
