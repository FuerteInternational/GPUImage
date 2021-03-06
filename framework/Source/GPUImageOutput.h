#import <UIKit/UIKit.h>

#import "GPUImageOpenGLESContext.h"
#import "GLProgram.h"

void runOnMainQueueWithoutDeadlocking(void (^block)(void));
void report_memory(NSString *tag);

@class GPUImageMovieWriter;

@interface GPUImageOutput : NSObject
{
    NSMutableArray *targets, *targetTextureIndices;
    
    GLuint outputTexture;
    CGSize inputTextureSize, cachedMaximumOutputSize, forcedMaximumSize;
    
    BOOL overrideInputSize;
}

@property(readwrite, nonatomic) BOOL shouldSmoothlyScaleOutput;
@property(readwrite, nonatomic) BOOL shouldIgnoreUpdatesToThisTarget;
@property(readwrite, nonatomic, retain) GPUImageMovieWriter *audioEncodingTarget;
@property(readwrite, nonatomic, unsafe_unretained) id<GPUImageInput> targetToIgnoreForUpdates;

// Managing targets
- (void)setInputTextureForTarget:(id<GPUImageInput>)target atIndex:(NSInteger)inputTextureIndex;
- (void)addTarget:(id<GPUImageInput>)newTarget;
- (void)addTarget:(id<GPUImageInput>)newTarget atTextureLocation:(NSInteger)textureLocation;
- (void)removeTarget:(id<GPUImageInput>)targetToRemove;
- (void)removeAllTargets;

// Manage the output texture
- (void)initializeOutputTexture;
- (void)deleteOutputTexture;
- (void)forceProcessingAtSize:(CGSize)frameSize;
- (void)forceProcessingAtSizeRespectingAspectRatio:(CGSize)frameSize;

// Still image processing
- (UIImage *)imageFromCurrentlyProcessedOutput;
- (UIImage *)imageFromCurrentlyProcessedOutputWithOrientation:(UIImageOrientation)imageOrientation;
- (UIImage *)imageByFilteringImage:(UIImage *)imageToFilter;
- (void)prepareForImageCapture;

@end
