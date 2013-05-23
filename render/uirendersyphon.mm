#include "uirendersyphon.h"
#import <Syphon/Syphon.h>

UiRenderSyphon::UiRenderSyphon() {
    mSyphon = nil;
}

UiRenderSyphon::~UiRenderSyphon() {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    [(SyphonServer *)mSyphon stop];
    [(SyphonServer *)mSyphon release];

    [pool drain];
}

void UiRenderSyphon::openPort() {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    if(!mSyphon)
        mSyphon = [[SyphonServer alloc] initWithName:nil context:CGLGetCurrentContext() options:nil];

    [pool drain];
}

void UiRenderSyphon::publishTexture(int textureTarget, int width, int height) {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    [(SyphonServer *)mSyphon publishFrameTexture:texture textureTarget:textureTarget imageRegion:NSMakeRect(0, 0, width, height) textureDimensions:NSMakeSize(width, height) flipped:false];
    [pool drain];
}

