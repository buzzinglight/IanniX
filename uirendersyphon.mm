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

    NSString *title = @"IanniX";

    if(!mSyphon)
        mSyphon = [[SyphonServer alloc] initWithName:title context:CGLGetCurrentContext() options:nil];
    else
        [(SyphonServer *)mSyphon setName:title];

    [pool drain];
}

void UiRenderSyphon::publishTexture(GLuint textureId, int textureTarget, int width, int height) {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    [(SyphonServer *)mSyphon publishFrameTexture:textureId textureTarget:textureTarget imageRegion:NSMakeRect(0, 0, width, height) textureDimensions:NSMakeSize(width, height) flipped:false];
    [pool drain];
}

