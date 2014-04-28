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

#include "nxtrigger.h"

GLuint NxTrigger::glListTrigger = 0;

NxTrigger::NxTrigger(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem) :
    NxObject(parent, ccParentItem) {
    cacheSize = 0;
    cursorTrigged = 0;
    lastTrigTime = 0;
    setText(0, tr("TRIGGER"));

    initializeCustom();
}

void NxTrigger::initializeCustom() {
    setSize(1);
    setColorActive  ("_trigger_active");
    setColorInactive("_trigger_inactive");
    setTextureActive  ("trigger_active");
    setTextureInactive("trigger_inactive");
    setTriggerOff(1);
    setMessagePatterns("1," + Application::defaultMessageTrigger.val());
}

void NxTrigger::paint() {
    //Color
    if(cursorTrigged)
        color = colorTrigged;
    else if(active) {
        if(colorActive.isEmpty())                                                                                   color = colorActiveColor;
        else if((colorActive.startsWith("_")) && (Render::colors->contains(Application::colorsPrefix() + colorActive)))  color = Render::colors->value(Application::colorsPrefix() + colorActive);
        else if(Render::colors->contains(colorActive))                                                              color = Render::colors->value(colorActive);
        else                                                                                                        color = Qt::gray;
    }
    else {
        if(colorInactive.isEmpty())                                                                                     color = colorInactiveColor;
        else if((colorInactive.startsWith("_")) && (Render::colors->contains(Application::colorsPrefix() + colorInactive)))  color = Render::colors->value(Application::colorsPrefix() + colorInactive);
        else if(Render::colors->contains(colorInactive))                                                                color = Render::colors->value(colorInactive);
        else                                                                                                            color = Qt::gray;
    }
    color.setRgb (qBound(0., color.red()   * colorMultiplyColor.redF(),   255.),
                  qBound(0., color.green() * colorMultiplyColor.greenF(), 255.),
                  qBound(0., color.blue()  * colorMultiplyColor.blueF(),  255.),
                  qBound(0., color.alpha() * colorMultiplyColor.alphaF(), 255.));

    //Size of trigger
    if(cacheSize != Render::objectSize*size) {
        cacheSize = Render::objectSize*size;
        calcBoundingRect();
    }

    if((color.alpha() > 0) && (cacheSize > 0)) {
        if(selectedHover)   color = Render::colors->value(Application::colorsPrefix() + "_gui_object_hover");
        if(selected)        color = Render::colors->value(Application::colorsPrefix() + "_gui_object_selection");

        //Start
        if(!Application::allowSelectionTriggers)
            color.setAlphaF(color.alphaF()/3);

        if(Render::paintThisGroup)
            glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        else
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.1);


        glPushMatrix();
        glTranslatef(pos.x(), pos.y(), pos.z());
        glRotatef(Render::rotation.z(), 0, 0, -1);
        glRotatef(Render::rotation.x(), 0, -1, 0);
        glRotatef(Render::rotation.y(), -1, 0, 0);

        //Label
        if((Render::paintThisGroup) && (Application::paintLabel || selectedHover) && (!label.isEmpty()))
            Application::render->renderText(cacheSize * 1.2, cacheSize * 1.2, 0, QString::number(id) + " - " + label.toUpper(), Application::renderFont);
        else if(selectedHover)
            Application::render->renderText(cacheSize * 1.2, cacheSize * 1.2, 0, QString::number(id), Application::renderFont);
        if((selectedHover) && (!isDrag)) {
            qreal startY = -0.2 - cacheSize * 1.2;
            foreach(const QString & messageLabelItem, messageLabel) {
                Application::render->renderText(cacheSize * 1.2, startY, 0, messageLabelItem.trimmed(), Application::renderFont);
                startY -= 0.2 * Render::zoomLinear;
            }
        }



        //Draw
        bool textureOk = false;
        QString textureName = (active)?(textureActive):(textureInactive);
        if(Render::textures->contains(textureName)) {
            UiRenderTexture *texture = Render::textures->value(textureName);
            if((texture) && (texture->loaded) && (texture->mapping.width() != 0 ) && (texture->mapping.height() != 0)) {
                textureOk = true;
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texture->texture);
                glBegin(GL_QUADS);
                qreal widthRatio = cacheSize * texture->originalSize.width() / texture->originalSize.height();
                glTexCoord2d(0, 0); glVertex3f(widthRatio * texture->mapping.left(),  cacheSize * texture->mapping.bottom(), 0);
                glTexCoord2d(1, 0); glVertex3f(widthRatio * texture->mapping.right(), cacheSize * texture->mapping.bottom(), 0);
                glTexCoord2d(1, 1); glVertex3f(widthRatio * texture->mapping.right(), cacheSize * texture->mapping.top(), 0);
                glTexCoord2d(0, 1); glVertex3f(widthRatio * texture->mapping.left(),  cacheSize * texture->mapping.top(), 0);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
        }
        if(!textureOk) {
            glScalef(cacheSize, cacheSize, cacheSize);
            if(glListTrigger == 0) {
                glListTrigger = glGenLists(1);
                glNewList(glListTrigger, GL_COMPILE_AND_EXECUTE);
                glLineWidth(size);
                glBegin(GL_POLYGON);
                for(qreal drawAngle = 0 ; drawAngle < 2*M_PI ; drawAngle += 0.3)
                    glVertex2d(0.7 * qCos(drawAngle), 0.7 * qSin(drawAngle));
                glEnd();
                glLineWidth(1.5);
                glBegin(GL_LINE_LOOP);
                for(qreal drawAngle = 0 ; drawAngle < 2*M_PI ; drawAngle += 0.3)
                    glVertex2d(1.2 * qCos(drawAngle), 1.2 * qSin(drawAngle));
                glEnd();
                glLineWidth(1);
                glEndList();
            }
            else
                glCallList(glListTrigger);
        }

        //End
        glPopMatrix();
    }
}

void NxTrigger::trig(NxObject *cursor) {
    if(cursor) {
        colorTrigged = cursor->getCurrentColor();
        colorTrigged.setAlpha(255);
    }
    cursorTrigged = cursor;
    MessageManager::outgoingMessage(MessageManagerDestination(this, this, cursorTrigged));
    if(triggerOff > 0)  QTimer::singleShot(triggerOff*1000, this, SLOT(trigEnd()));
    else                trigEnd();
}
void NxTrigger::trigEnd() {
    if(triggerOff > 0) {
        NxObject *cursorTriggedTmp = cursorTrigged;
        bool sendMessage = false;
        foreach(const QVector<QByteArray> & messagePattern, this->getMessagePatterns()) {
            foreach(const QByteArray &messageArgument, messagePattern) {
                if(messageArgument == "trigger_value")
                    sendMessage = true;
            }
        }
        if(sendMessage)
            MessageManager::outgoingMessage(MessageManagerDestination(this, this, cursorTriggedTmp));
    }
    cursorTrigged = 0;
}
