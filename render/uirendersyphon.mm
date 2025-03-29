#include "uirendersyphon.h"
#import <Syphon/Syphon.h>

UiRenderSyphon::UiRenderSyphon() {
    mSyphon = nil;
    texture = 0;
}

UiRenderSyphon::~UiRenderSyphon() {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    qDebug() << "Stopping Syphon server";
    [(SyphonServer *)mSyphon stop];
    [(SyphonServer *)mSyphon release];

    [pool drain];
}

void UiRenderSyphon::openPort() {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    qDebug() << "Opening Syphon port";
    if(!mSyphon) {
        mSyphon = [[SyphonServer alloc] initWithName:@"IanniX" context:CGLGetCurrentContext() options:nil];
        if(mSyphon) {
            qDebug() << "Syphon server created successfully";
        } else {
            qDebug() << "Failed to create Syphon server";
        }
    }

    [pool drain];
}

void UiRenderSyphon::publishTexture(GLuint textureId, int textureTarget, int width, int height) {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    texture = textureId;
    qDebug() << "Publishing texture" << textureId << "to Syphon" << width << "x" << height;
    [(SyphonServer *)mSyphon publishFrameTexture:texture textureTarget:textureTarget 
                                     imageRegion:NSMakeRect(0, 0, width, height) 
                               textureDimensions:NSMakeSize(width, height) flipped:false];
    
    [pool drain];
}

