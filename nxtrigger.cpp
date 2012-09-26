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

NxTrigger::NxTrigger(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions) :
        NxObject(parent, ccParentItem, _renderOptions) {
    setColorActive("trigger_active");
    setColorInactive("trigger_inactive");
    setColorActiveMessage("trigger_active_message");
    setColorInactiveMessage("trigger_inactive_message");
    setSize(1);
    cacheSize = 0;
    cursorTrigged = 0;
    setTextureActive("trigger_active");
    setTextureInactive("trigger_inactive");
    setTextureActiveMessage("trigger_active_message");
    setTextureInactiveMessage("trigger_inactive_message");
    setTriggerOff(0);
}

void NxTrigger::paint() {
    //Color
    if(cursorTrigged)
        color = colorTrigged;
    else if(messagePatterns.count() > 0) {
        if(active)
            color = (!colorActiveMessage.isEmpty())?(renderOptions->colors.value(colorActiveMessage)):(colorActiveColorMessage);
        else
            color = (!colorInactiveMessage.isEmpty())?(renderOptions->colors.value(colorInactiveMessage)):(colorInactiveColorMessage);
    }
    else {
        if(active)
            color = (!colorActive.isEmpty())?(renderOptions->colors.value(colorActive)):(colorActiveColor);
        else
            color = (!colorInactive.isEmpty())?(renderOptions->colors.value(colorInactive)):(colorInactiveColor);
    }

    //Size of trigger
    if(cacheSize != renderOptions->objectSize*size) {
        cacheSize = renderOptions->objectSize*size;
        calcBoundingRect();
    }

    if((color.alpha() > 0) && (cacheSize > 0)) {
        if(selectedHover)
            color = renderOptions->colors.value("object_hover");
        if(selected)
            color = renderOptions->colors.value("object_selection");

        //Start
        bool opacityCheck = ((renderOptions->paintTriggers) && (renderOptions->paintThisGroup) && ((renderOptions->paintZStart <= pos.z()) && (pos.z() <= renderOptions->paintZEnd)));

        if(!renderOptions->allowSelectionTriggers)
            color.setAlphaF(color.alphaF()/3);

        if(opacityCheck)
            glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
        else
            glColor4f(color.redF(), color.greenF(), color.blueF(), 0.1);


        glPushMatrix();
        glTranslatef(pos.x(), pos.y(), pos.z());
        glRotatef(renderOptions->rotation.z(), 0, 0, -1);
        glRotatef(renderOptions->rotation.x(), 0, -1, 0);
        glRotatef(renderOptions->rotation.y(), -1, 0, 0);

        //Draw
        Texture texture;
        if(messagePatterns.count() > 0) {
            if(active)
                texture = renderOptions->textures.value(textureActiveMessage);
            else
                texture = renderOptions->textures.value(textureInactiveMessage);
        }
        else {
            if(active)
                texture = renderOptions->textures.value(textureActive);
            else
                texture = renderOptions->textures.value(textureInactive);
        }

        //Label
        if((opacityCheck) && (renderOptions->paintLabel) && (!label.isEmpty()))
            renderOptions->render->renderText(cacheSize * 1.1 * texture.mapping.right()/2, cacheSize * 1.1 * texture.mapping.top(), 0, label, renderOptions->renderFont);
        if(selectedHover) {
            qreal startY = 0;
            foreach(const QString & messageLabelItem, messageLabel) {
                renderOptions->render->renderText(cacheSize * 1.5 * texture.mapping.right(), startY, 0, messageLabelItem, renderOptions->renderFont);
                startY -= cacheSize * 1.5;
            }
        }



        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture.texture);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0); glVertex3f(cacheSize * texture.mapping.left(),  cacheSize * texture.mapping.bottom(), 0);
        glTexCoord2d(1, 0); glVertex3f(cacheSize * texture.mapping.right(), cacheSize * texture.mapping.bottom(), 0);
        glTexCoord2d(1, 1); glVertex3f(cacheSize * texture.mapping.right(), cacheSize * texture.mapping.top(), 0);
        glTexCoord2d(0, 1); glVertex3f(cacheSize * texture.mapping.left(),  cacheSize * texture.mapping.top(), 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);

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
        factory->sendMessage(this, this, cursorTrigged);
    //}
}
void NxTrigger::trigEnd() {
    NxObject *cursorTriggedTmp = cursorTrigged;

    ////CG//// 
	//Suppress trigger-off if it is a midi message (note-off will be done by midi note duration in midi message)
    bool isMidiMessage = false;
    foreach(const QVector<QByteArray> & messagePattern, this->getMessagePatterns()) {
        if(messagePattern.at(0).startsWith("midi"))
            isMidiMessage = true;
        }
    cursorTrigged = 0;
    if(triggerOff > 0 && !isMidiMessage)
        factory->sendMessage(this, this, cursorTriggedTmp);
}
