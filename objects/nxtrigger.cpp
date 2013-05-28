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

#include "nxtrigger.h"

GLuint NxTrigger::glListTrigger = 0;

NxTrigger::NxTrigger(ApplicationCurrent *parent, QTreeWidgetItem *ccParentItem) :
    NxObject(parent, ccParentItem) {
    cacheSize = 0;
    cursorTrigged = 0;
    setText(0, tr("TRIGGER"));

    initializeCustom();
}

void NxTrigger::initializeCustom() {
    setSize(1);
    setColorActive  ("_trigger_active");
    setColorInactive("_trigger_inactive");
    setTextureActive  ("trigger_active");
    setTextureInactive("trigger_inactive");
    setTriggerOff(0);
    setMessagePatterns("1," + Global::defaultMessageTrigger.val());
}

void NxTrigger::paint() {
    //Color
    if(cursorTrigged)
        color = colorTrigged;
    else if(active) {
        if(colorActive.isEmpty())                                                                                   color = colorActiveColor;
        else if((colorActive.startsWith("_")) && (Global::colors->contains(Global::colorsPrefix() + colorActive)))  color = Global::colors->value(Global::colorsPrefix() + colorActive);
        else if(Global::colors->contains(colorActive))                                                              color = Global::colors->value(colorActive);
        else                                                                                                        color = Qt::gray;
    }
    else {
        if(colorInactive.isEmpty())                                                                                     color = colorInactiveColor;
        else if((colorInactive.startsWith("_")) && (Global::colors->contains(Global::colorsPrefix() + colorInactive)))  color = Global::colors->value(Global::colorsPrefix() + colorInactive);
        else if(Global::colors->contains(colorInactive))                                                                color = Global::colors->value(colorInactive);
        else                                                                                                            color = Qt::gray;
    }

    //Size of trigger
    if(cacheSize != Global::objectSize*size) {
        cacheSize = Global::objectSize*size;
        calcBoundingRect();
    }

    if((color.alpha() > 0) && (cacheSize > 0)) {
        if(selectedHover)   color = Global::colors->value(Global::colorsPrefix() + "_gui_object_hover");
        if(selected)        color = Global::colors->value(Global::colorsPrefix() + "_gui_object_selection");

        //Start
        if(!Global::allowSelectionTriggers)
            color.setAlphaF(color.alphaF()/3);

        if(Global::paintThisGroup)
            glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        else
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.1);


        glPushMatrix();
        glTranslatef(pos.x(), pos.y(), pos.z());
        glRotatef(Global::rotation.z(), 0, 0, -1);
        glRotatef(Global::rotation.x(), 0, -1, 0);
        glRotatef(Global::rotation.y(), -1, 0, 0);

        //Label
        if((Global::paintThisGroup) && (Global::paintLabel) && (!label.isEmpty()))
            Application::render->renderText(cacheSize * 1.2, cacheSize * 1.2, 0, QString::number(id) + " - " + label, Global::renderFont);
        else if(selectedHover)
            Application::render->renderText(cacheSize * 1.2, cacheSize * 1.2, 0, QString::number(id), Global::renderFont);
        if((selectedHover) && (!isDrag)) {
            qreal startY = -0.2 - cacheSize * 1.2;
            foreach(const QString & messageLabelItem, messageLabel) {
                Application::render->renderText(cacheSize * 1.2, startY, 0, messageLabelItem, Global::renderFont);
                startY -= 0.4;
            }
        }



        //Draw
        bool ok = false;
        QString textureName = (active)?(textureActive):(textureInactive);
        if(Global::textures->contains(textureName)) {
            UiRenderTexture *texture = Global::textures->value(textureName);
            if((texture) && (texture->loaded) && (texture->mapping.width() != 0 ) && (texture->mapping.height() != 0)) {
                ok = true;
                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, texture->texture);
                glBegin(GL_QUADS);
                glTexCoord2d(0, 0); glVertex3f(cacheSize * texture->mapping.left(),  cacheSize * texture->mapping.bottom(), 0);
                glTexCoord2d(1, 0); glVertex3f(cacheSize * texture->mapping.right(), cacheSize * texture->mapping.bottom(), 0);
                glTexCoord2d(1, 1); glVertex3f(cacheSize * texture->mapping.right(), cacheSize * texture->mapping.top(), 0);
                glTexCoord2d(0, 1); glVertex3f(cacheSize * texture->mapping.left(),  cacheSize * texture->mapping.top(), 0);
                glEnd();
                glDisable(GL_TEXTURE_2D);
            }
        }
        if(!ok) {
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
    /*if((!cursor) || (!cursorTrigged)) {*/
    if(cursor) {
        colorTrigged = cursor->getCurrentColor();
        colorTrigged.setAlpha(255);
    }
    cursorTrigged = cursor;
    QTimer::singleShot(qMax(triggerOff*1000, (qreal)80), this, SLOT(trigEnd()));
    MessageManager::outgoingMessage(MessageManagerDestination(this, this, cursorTrigged));
    //}
}
void NxTrigger::trigEnd() {
    NxObject *cursorTriggedTmp = cursorTrigged;
    bool isMidiMessage = false;
    foreach(const QVector<QByteArray> & messagePattern, this->getMessagePatterns()) {
        if(messagePattern.at(0).startsWith("midi"))
            isMidiMessage = true;
    }
    cursorTrigged = 0;
    if(triggerOff > 0 && !isMidiMessage)
        MessageManager::outgoingMessage(MessageManagerDestination(this, this, cursorTriggedTmp));
}
