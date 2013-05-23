#ifndef INTERFACESYPHON_H
#define INTERFACESYPHON_H

#include <QGLWidget>
#include <QWidget>
#include "misc/options.h"
#include "messages/messagemanager.h"

namespace Ui {
class InterfaceSyphon;
}

class InterfaceSyphon : public NetworkInterface {
    Q_OBJECT
    
#ifdef SYPHON_INSTALLED
public:
    explicit InterfaceSyphon(QWidget *parent = 0);
    ~InterfaceSyphon();

public:
    UiBool serverEnable, clientEnable;
    bool   serverInit, clientInit, clientTextureOk;
    GLuint serverTexture;
private:
    void *serverSyphon, *clientSyphon;

private:
    void initSyphonServer();
    void releaseSyphonServer();
public:
    void createSyphonServer();
    void createSyphonClient();
public:
    void publishTexture(int textureTarget, int width, int height);
    bool hasNewFrame() const { return clientTextureOk; }
    GLuint getTexture(QSizeF *size = 0);
#endif

private:
    Ui::InterfaceSyphon *ui;
};

#endif // INTERFACESYPHON_H
