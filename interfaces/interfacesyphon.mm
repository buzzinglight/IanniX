#include "interfacesyphon.h"
#include "ui_interfacesyphon.h"
#import <Syphon/Syphon.h>

InterfaceSyphon::InterfaceSyphon(QWidget *parent) :
    NetworkInterface(parent),
    ui(new Ui::InterfaceSyphon) {
    ui->setupUi(this);

    //Interfaces link
    serverEnable.setAction(ui->serverEnable, "interfaceSyphonServerEnable");

    //Init code
    serverInit    = false;
    serverTexture = 0;
    clientInit    = false;
    clientSyphon  = 0;
    initSyphonServer();
}

InterfaceSyphon::~InterfaceSyphon() {
    releaseSyphonServer();
    delete ui;
}


void InterfaceSyphon::initSyphonServer() {
    serverSyphon = nil;
}

void InterfaceSyphon::releaseSyphonServer() {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    [(SyphonServer *)serverSyphon stop];
    [(SyphonServer *)serverSyphon release];

    [pool drain];
}

void InterfaceSyphon::createSyphonServer() {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    serverSyphon = [[SyphonServer alloc] initWithName:nil context:CGLGetCurrentContext() options:nil];
    serverInit = true;

    [pool drain];
}
void InterfaceSyphon::createSyphonClient() {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    SyphonServerDirectory *servers = [SyphonServerDirectory sharedDirectory];
    if(servers) {
        if([servers.servers count] > 0) {
            clientSyphon = [[SyphonClient alloc] initWithServerDescription:[servers.servers objectAtIndex:0] options:nil newFrameHandler:^(SyphonClient *clientSyphon) {
                clientTextureOk = true;
            }];
        }
    }

    [pool drain];
}

void InterfaceSyphon::publishTexture(int textureTarget, int width, int height) {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    [(SyphonServer *)serverSyphon publishFrameTexture:serverTexture textureTarget:textureTarget imageRegion:NSMakeRect(0, 0, width, height) textureDimensions:NSMakeSize(width, height) flipped:false];
    [pool drain];
}

GLuint InterfaceSyphon::getTexture(QSizeF *size) {
    clientTextureOk = false;
    SyphonImage *frame = [(SyphonClient*)clientSyphon newFrameImageForContext:CGLGetCurrentContext()];
    if(frame) {
        GLuint texture = frame.textureName;
        if(size) {
            size->setWidth(frame.textureSize.width);
            size->setHeight(frame.textureSize.height);
        }
        [frame release];
        return texture;
    }
    return 0;
}


