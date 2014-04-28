/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2014 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
