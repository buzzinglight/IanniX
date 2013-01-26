/*
    IanniX — a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2012 — IanniX Association

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KINECT_H
#define KINECT_H

#include <QObject>
#include <QPixmap>
#include <QLabel>
#include <QKeyEvent>
#include <QGLWidget>
#include <QPainter>
#include <qmath.h>
#include "qkinect/QKinect.h"

#define KINECT_PRECISION  1280

class ExtKinectManager : public QLabel {
    Q_OBJECT
public:
    explicit ExtKinectManager(QWidget *parent = 0);

public:
    void paint();
    qreal getDepthAt(qreal x, qreal y) const;

private:
    quint16 frameCounter;
    int timerCounter, timerFrame;
    qreal threshMin, threshMax;
    QKinect *kinect;
    QLabel *labelCam;
    std::vector<uint8_t> bufferCam, bufferDepth;
    std::vector<uint16_t> bufferDepth16;
    qreal bufferFinal[FREENECT_FRAME_PIX], bufferFinalOld[FREENECT_FRAME_PIX];
    qreal rawToMeters[2048];
    quint8 colorK[KINECT_PRECISION+1], colorR[KINECT_PRECISION+1], colorG[KINECT_PRECISION+1], colorB[KINECT_PRECISION+1];

private:
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *);

signals:

public slots:

};

#endif // KINECT_H
