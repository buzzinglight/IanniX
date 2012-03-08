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

#include "extkinectmanager.h"

ExtKinectManager::ExtKinectManager(QWidget *parent) :
    QLabel(parent) {
    frameCounter = 0;
    threshMin = 0.55;
    threshMax = 0.75;
    kinect = 0;

    //Configuration de la Kinect
    kinect = QKinect::instance();
    if(kinect)
        kinect->setGreenLed();
    bufferCam.resize(FREENECT_VIDEO_RGB_SIZE);
    bufferDepth.resize(FREENECT_VIDEO_RGB_SIZE);
    bufferDepth16.resize(FREENECT_FRAME_PIX);
    for (quint16 indexNormal = 0; indexNormal <= 2047; indexNormal++)
        rawToMeters[indexNormal] = 1.0 / (indexNormal * -0.0030711016 + 3.3309495161);

    for (quint16 indexNormal = 0; indexNormal <= KINECT_PRECISION; indexNormal++) {
        QColor color;
        color.setHslF((qreal)indexNormal / KINECT_PRECISION / 2, 1, 0.5);
        colorR[indexNormal] = color.red();
        colorG[indexNormal] = color.green();
        colorB[indexNormal] = color.blue();
        colorK[indexNormal] = (qreal)indexNormal / KINECT_PRECISION * 255;
    }

    for (quint32 indexNormal = 0; indexNormal < FREENECT_FRAME_PIX; indexNormal++) {
        bufferFinal[indexNormal] = 0;
        bufferFinalOld[indexNormal] = 0;
    }

    //Configuration GUI
    resize(320, 240);
    setWindowFlags(Qt::Tool);
    setWindowTitle(tr("IanniX") + QString(" - ") + tr("Kinect"));
    move(0, 0);

    labelCam = new QLabel();
    labelCam->resize(width(), height());
    labelCam->move(x(), 1024 - height());
    labelCam->setWindowFlags(windowFlags());
    labelCam->show();

    timerFrame = startTimer(40);
    timerCounter = startTimer(5000);

    show();
}

void ExtKinectManager::timerEvent(QTimerEvent *event) {
    if(event->timerId() == timerFrame) {
        //Image couleur
        if(kinect)
            kinect->getRGB(bufferCam);

        //Paramètres de traitement d'image
        qreal depthValue = 0;
        quint16 depthValueInt = 0;
        QRect roi = QRect(0, 0, 640, 480);

        //Buffer original
        if(kinect)
            kinect->getDepth16Bit(bufferDepth16);
        frameCounter++;

        //Filtrage du buffer de profondeur
        for(quint32 x = 0 ; x < FREENECT_FRAME_W; x++) {
            //Détection de formes
            for(quint32 y = 0 ; y < FREENECT_FRAME_H ; y++) {
                quint32 indexNormal = x + FREENECT_FRAME_W * y;

                //Valeur linéaire et normalisation
                depthValue = (qreal)(rawToMeters[bufferDepth16[indexNormal]] - threshMin) / (qreal)(threshMax - threshMin);

                //Distribution
                depthValueInt = depthValue * KINECT_PRECISION;
                if((0 <= depthValue) && (depthValue <= 1)) {
                    //Image valide
                    bufferDepth[3*indexNormal+0] = colorR[depthValueInt];
                    bufferDepth[3*indexNormal+1] = colorG[depthValueInt];
                    bufferDepth[3*indexNormal+2] = colorB[depthValueInt];
                }
                else {
                    depthValue = rawToMeters[bufferDepth16[indexNormal]] / 6.;
                    if(depthValue > 1)
                        depthValue = 1;
                    if(depthValue < 0)
                        depthValue = 1;
                    depthValueInt = (1-depthValue) * KINECT_PRECISION;
                    //Image invalide
                    bufferDepth[3*indexNormal+0] = colorK[depthValueInt];
                    bufferDepth[3*indexNormal+1] = colorK[depthValueInt];
                    bufferDepth[3*indexNormal+2] = colorK[depthValueInt];
                    depthValue = 1;
                }

                bufferFinal[indexNormal] = bufferFinalOld[indexNormal] + ((1-depthValue) - bufferFinalOld[indexNormal] / 10.);
                bufferFinalOld[indexNormal] = bufferFinal[indexNormal];
            }
        }

        //Conversion en pixmap pour affichage
        QPixmap pixmapDepth = QPixmap::fromImage(QImage(&bufferDepth[0], FREENECT_FRAME_W, FREENECT_FRAME_H, QImage::Format_RGB888)).scaledToWidth(width());
        QPixmap pixmapCam   = QPixmap::fromImage(QImage(&bufferCam[0],   FREENECT_FRAME_W, FREENECT_FRAME_H, QImage::Format_RGB888)).scaledToWidth(width());
        //Affiche les pixmaps
        setPixmap(pixmapDepth);
        labelCam->setPixmap(pixmapCam);
    }
    else if(event->timerId() == timerCounter) {
        if(frameCounter > 0)
            qDebug("%s", qPrintable(QString("%1 fps").arg(frameCounter/5)));
        frameCounter = 0;
    }
}

qreal ExtKinectManager::getDepthAt(qreal _x, qreal _y) const {
    if(kinect) {
        quint16 x = (( _x + 5.) / 10.) * FREENECT_FRAME_W;
        quint16 y = ((-_y + 5.) / 10.) * FREENECT_FRAME_H;
        if((x < FREENECT_FRAME_W) && (y < FREENECT_FRAME_H))
            return bufferFinal[x + FREENECT_FRAME_W * y] / 5;
        else
            return 0;
    }
    else {
        return (_x + 5) / 10 * 2;
    }
}


//Paint event
void ExtKinectManager::paint() {
    return;
    //return;
    glColor4f(1, 1, 1, 0.5);
    for(qreal y = -5 ; y < 5 ; y += 0.1) {
        //Dessin des lignes
        glBegin(GL_LINE_STRIP);
        for(qreal x = -5 ; x < 5; x += 0.1)
            glVertex3f(x, y, getDepthAt(x, y));
        glEnd();
    }
}



void ExtKinectManager::keyPressEvent(QKeyEvent *event) {
    if(event->modifiers() & Qt::AltModifier) {
        if(event->key() == Qt::Key_Up)
            threshMax += 0.05;
        else if(event->key() == Qt::Key_Down)
            threshMax -= 0.05;
    }
    else {
        if(event->key() == Qt::Key_Up)
            threshMin += 0.05;
        else if(event->key() == Qt::Key_Down)
            threshMin -= 0.05;
    }
    qDebug("%f %f", threshMin, threshMax);
}
