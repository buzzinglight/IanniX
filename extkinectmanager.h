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
