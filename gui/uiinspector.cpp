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

#include "uiinspector.h"
#include "ui_uiinspector.h"

UiInspector::UiInspector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiInspector) {
    ui->setupUi(this);

    ui->splitter_2->setStretchFactor(0, 1);
    ui->splitter_2->setStretchFactor(1, 2);

    ui->ccView->setColumnWidth(0, 85);
    ui->ccView->setColumnWidth(1, 25);
    ui->ccView->setColumnWidth(2, 25);
    ui->ccView->setColumnWidth(3, 40);
    ui->cc2View->setColumnWidth(0, 45);
    ui->cc2View->setColumnWidth(1, 25);

    quint16 colWidth = 45;
    ui->pointsList->setColumnWidth(0, colWidth);
    ui->pointsList->setColumnWidth(1, colWidth);
    ui->pointsList->setColumnWidth(2, colWidth);
    ui->pointsList->setColumnWidth(3, colWidth);
    ui->pointsList->setColumnWidth(4, colWidth);
    ui->pointsList->setColumnWidth(5, colWidth);
    ui->pointsList->setColumnWidth(6, colWidth);
    ui->pointsList->setColumnWidth(7, colWidth);
    ui->pointsList->setColumnWidth(8, colWidth);
    ui->pointsList->setColumnWidth(9, colWidth);
    ui->pointsList->setColumnWidth(10, colWidth);

    render = 0;
    factory = 0;
    triggerItem = new QTreeWidgetItem(ui->ccView, QStringList() << "");
    triggerItem->setFlags(Qt::ItemIsEnabled);
    curveItem = new QTreeWidgetItem(ui->ccView, QStringList() << "");
    curveItem->setFlags(Qt::ItemIsEnabled);
    cursorItem = new QTreeWidgetItem(ui->ccView, QStringList() << "");
    cursorItem->setFlags(Qt::ItemIsEnabled);

    ui->followId->setValue(-1);

    ui->ccView->expandAll();
    ui->ccView->sortByColumn(0, Qt::AscendingOrder);

    ui->colorCombo1->clear();
    ui->colorCombo2->clear();
    ui->colorCombo3->clear();
    ui->colorCombo4->clear();

    ui->syncMessageLabel->setVisible(false);
    ui->syncMessageEdit->setVisible(false);

    actionInfoLock = true;

    ui->easingCombo->clear();
    NxEasing easing;
    for(quint16 type = 0 ; type < 45 ; type++) {
        easing.setType(type);
        ui->easingCombo->addItem(QIcon(easing.getPixmap()), tr("Easing") + QString(" %1").arg(type));
    }

    //needRefresh = true;
    startTimer(100);

    refresh();
}

UiInspector::~UiInspector() {
    delete ui;
}

void UiInspector::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QTreeWidget* UiInspector::getViewGroup() const {
    return ui->cc2View;
}
qreal UiInspector::getViewZStart() const {
    return ui->viewZStartSpin->value();
}
qreal UiInspector::getViewZEnd() const {
    return ui->viewZEndSpin->value();
}

QTreeWidget* UiInspector::getProjectFiles() const {
    return ui->projectFiles;
}
QTreeWidget* UiInspector::getProjectScripts() const {
    return ui->projectScripts;
}
bool UiInspector::setProjectFiles(QString filename) {
    for(quint16 i = 0 ; i < ui->projectFiles->topLevelItemCount() ; i++) {
        for(quint16 j = 0 ; j < ui->projectFiles->topLevelItem(i)->childCount() ; j++) {
            if(ui->projectFiles->topLevelItem(i)->child(j)->text(0) == filename) {
                ui->projectFiles->setCurrentItem(ui->projectFiles->topLevelItem(i)->child(j));
                return true;
            }
        }
    }
    return false;
}
bool UiInspector::setProjectScripts(QString filename) {
    for(quint16 i = 0 ; i < ui->projectScripts->topLevelItemCount() ; i++) {
        for(quint16 j = 0 ; j < ui->projectScripts->topLevelItem(i)->childCount() ; j++) {
            if(ui->projectScripts->topLevelItem(i)->child(j)->text(0) == filename) {
                ui->projectScripts->setCurrentItem(ui->projectScripts->topLevelItem(i)->child(j));
                return true;
            }
        }
    }
    return false;
}

void UiInspector::changeID_success(bool result, quint16 newId) {  ////CG////
    if (result)
        foreach(NxObject *object, *(render->getSelection())) //This should only loop once
            object->setId(newId);
    else
        (new UiMessageBox())->display(tr("Can't change ID."), tr("Another object has this ID.\nTry deleting that object, or change its ID."), QDialogButtonBox::Ok);
}

void UiInspector::actionCCButton() {
    if(sender() == ui->unmuteGroups)
        emit(actionUnmuteGroups());
    else if(sender() == ui->unmuteObjects)
        emit(actionUnmuteObjects());
    else if(sender() == ui->unsoloGroups)
        emit(actionUnsoloGroups());
    else if(sender() == ui->unsoloObjects)
        emit(actionUnsoloObjects());
    else if(sender() == ui->followId)
        emit(actionFollowID(ui->followId->value()));
    actionCC();
    actionCC2();
}

void UiInspector::actionInfo() {
    if(!actionInfoLock) {
        factory->pushSnapshot();
        foreach(NxObject *object, *(render->getSelection())) {
            //if(ui->IDSpin == sender()) {  ///Issue - if object was not changed, it conflicts with itself - change spin into a button/dialog combo like group
            //    object->setId(ui->IDSpin->value());
            //    emit(actionChangeID(ui->IDSpin->value()));   ////CG////
            //}
            //else
            if(ui->positionX == sender())
                object->setPos(NxPoint(ui->positionX->value(), object->getPos().y(), object->getPos().z()));
            else if(ui->positionY == sender())
                object->setPos(NxPoint(object->getPos().x(), ui->positionY->value(), object->getPos().z()));
            else if(ui->positionZ == sender())
                object->setPos(NxPoint(object->getPos().x(), object->getPos().y(), ui->positionZ->value()));
            else if(ui->activityCheck == sender())
                object->setActive(ui->activityCheck->isChecked());
            else if(ui->labelLine == sender())
                object->setLabel(ui->labelLine->text());
            else if(ui->sizeSpin == sender())
                object->setSize(ui->sizeSpin->value());
            else if(ui->messagesSpin == sender())
                object->setMessageTimeInterval(ui->messagesSpin->value());

            if(object->getType() == ObjectsTypeCursor) {
                NxCursor *cursor = (NxCursor*)object;
                if(ui->widthSpin == sender())
                    cursor->setWidth(ui->widthSpin->value());
                else if(ui->depthSpin == sender())
                    cursor->setDepth(ui->depthSpin->value());
                else if(ui->speedFSpin == sender())
                    cursor->setTimeFactorF(ui->speedFSpin->value());
                else if(ui->patternLine == sender())
                    cursor->setStart(ui->patternLine->currentText().split(" - ").at(0));
                else if(ui->easingCombo == sender())
                    cursor->setEasing(ui->easingCombo->currentIndex());
                else if(ui->speedSpin == sender())
                    cursor->setTimeFactor(ui->speedSpin->value());
                else if(ui->cursorLengthSpin == sender())
                    cursor->setTimeFactor(cursor->getCurve()->getPathLength() / ui->cursorLengthSpin->value());
                else if(ui->offsetInitialSpin == sender())
                    cursor->setTimeInitialOffset(ui->offsetInitialSpin->value());
                else if(ui->offsetStartSpin == sender())
                    cursor->setTimeStartOffset(ui->offsetStartSpin->value());
                else if(ui->offsetEndSpin == sender())
                    cursor->setTimeEndOffset(ui->offsetEndSpin->value());
                else if(ui->cursorSourceX1 == sender())
                    cursor->setBoundsRect(0, ui->cursorSourceX1->value(), true);
                else if(ui->cursorSourceY1 == sender())
                    cursor->setBoundsRect(1, ui->cursorSourceY1->value(), true);
                else if(ui->cursorSourceZ1 == sender())
                    cursor->setBoundsRect(2, ui->cursorSourceZ1->value(), true);
                else if(ui->cursorSourceX2 == sender())
                    cursor->setBoundsRect(3, ui->cursorSourceX2->value(), true);
                else if(ui->cursorSourceY2 == sender())
                    cursor->setBoundsRect(4, ui->cursorSourceY2->value(), true);
                else if(ui->cursorSourceZ2 == sender())
                    cursor->setBoundsRect(5, ui->cursorSourceZ2->value(), true);
                else if(ui->cursorTargetX1 == sender())
                    cursor->setBoundsRect(0, ui->cursorTargetX1->value(), false);
                else if(ui->cursorTargetY1 == sender())
                    cursor->setBoundsRect(1, ui->cursorTargetY1->value(), false);
                else if(ui->cursorTargetZ1 == sender())
                    cursor->setBoundsRect(2, ui->cursorTargetZ1->value(), false);
                else if(ui->cursorTargetX2 == sender())
                    cursor->setBoundsRect(3, ui->cursorTargetX2->value(), false);
                else if(ui->cursorTargetY2 == sender())
                    cursor->setBoundsRect(4, ui->cursorTargetY2->value(), false);
                else if(ui->cursorTargetZ2 == sender())
                    cursor->setBoundsRect(5, ui->cursorTargetZ2->value(), false);
            }
            else if(object->getType() == ObjectsTypeCurve) {
                NxCurve *curve = (NxCurve*)object;
                if(ui->sizeWSpin == sender())
                    curve->setResize(NxSize(ui->sizeWSpin->value(), curve->getResize().height()));
                else if(ui->sizeHSpin == sender())
                    curve->setResize(NxSize(curve->getResize().width(), ui->sizeHSpin->value()));
                if(ui->pointsList == sender()) {
                    if(curve->getCurveType() == CurveTypePoints) {
                        ui->pointsList->sortItems(0, Qt::AscendingOrder);
                        for(quint16 itemIndex = 0 ; itemIndex < ui->pointsList->topLevelItemCount() ; itemIndex++) {
                            QTreeWidgetItem *item = ui->pointsList->topLevelItem(itemIndex);
                            curve->setPointAt(itemIndex, NxPoint(item->text(1).toDouble(), item->text(2).toDouble(), item->text(3).toDouble()), NxPoint(item->text(5).toDouble(), item->text(6).toDouble(), item->text(7).toDouble()), NxPoint(item->text(8).toDouble(), item->text(9).toDouble(), item->text(10).toDouble()), (item->checkState(4)==Qt::Checked)?(true):(false), false);
                        }
                        curve->calcBoundingRect();
                        curve->calculate();
                    }
                }
            }
            else if(object->getType() == ObjectsTypeTrigger) {
                NxTrigger *trigger = (NxTrigger*)object;
                if(ui->triggerOffSpin == sender())
                    trigger->setTriggerOff(ui->triggerOffSpin->value());
            }
        }
        refresh();
    }
}
void UiInspector::actionColor() {
    if(!actionInfoLock) {
        QComboBox *combo = (QComboBox*)sender();
        QString val = combo->currentText();
        QStringList oldValStr = combo->currentText().split(" ", QString::SkipEmptyParts);
        if((combo->currentText() == "Custom") || (oldValStr.count() == 4)) {
            QColor oldVal = Qt::white;
            if(oldValStr.count() == 4)
                oldVal = QColor(oldValStr.at(0).toUInt(), oldValStr.at(1).toUInt(), oldValStr.at(2).toUInt(), oldValStr.at(3).toUInt());
            QColor valColor = QColorDialog::getColor(oldVal, 0, tr("IanniX Color Inspector"), QColorDialog::ShowAlphaChannel);
            val = QString("%1 %2 %3 %4").arg(valColor.red()).arg(valColor.green()).arg(valColor.blue()).arg(valColor.alpha());
        }
        factory->pushSnapshot();
        foreach(NxObject *object, *(render->getSelection())) {
            if(ui->colorCombo1 == sender())
                object->setColorActive(val);
            else if(ui->colorCombo2 == sender())
                object->setColorInactive(val);
            else if(object->getType() == ObjectsTypeTrigger) {
                NxTrigger *trigger = (NxTrigger*)object;
                if(ui->colorCombo3 == sender())
                    trigger->setColorActiveMessage(val);
                else if(ui->colorCombo4 == sender())
                    trigger->setColorInactiveMessage(val);
            }
        }
        refresh();
    }
}

void UiInspector::actionNetwork() {
    if(ui->oscInPortSpin == sender()) {
        factory->pushSnapshot();
        ui->oscInPortSpin->setStyleSheet("");
        emit(oscPortChange(ui->oscInPortSpin->value()));
    }
    else if(ui->udpInPortSpin == sender()) {
        factory->pushSnapshot();
        ui->udpInPortSpin->setStyleSheet("");
        emit(udpPortChange(ui->udpInPortSpin->value()));
    }
    else if(ui->tcpInPortSpin == sender()) {
        factory->pushSnapshot();
        ui->tcpInPortSpin->setStyleSheet("");
        emit(tcpPortChange(ui->tcpInPortSpin->value()));
    }
    if(ui->httpInPortSpin == sender()) {
        factory->pushSnapshot();
        ui->httpInPortSpin->setStyleSheet("");
        emit(httpPortChange(ui->httpInPortSpin->value()));
    }
    else if(ui->ipOutEdit == sender()) {
        factory->pushSnapshot();
        ui->ipOutEdit->setStyleSheet("");
        emit(ipOutChange(ui->ipOutEdit->text()));
    }
    else if(ui->midiOutCombo == sender()) {
        factory->pushSnapshot();
        ui->midiOutCombo->setStyleSheet("");
        emit(midiOutChange(ui->midiOutCombo->currentText()));
    }
    else if(ui->midiTempoSpin == sender()) {
        factory->pushSnapshot();
        ui->midiTempoSpin->setStyleSheet("");
        emit(midiTempoChange(ui->midiTempoSpin->value()));
    }
    else if(ui->midiSyncClock == sender()) {
        factory->pushSnapshot();;
        emit(midiSyncClockChanged(ui->midiSyncClock->isChecked()));
    }
    else if(ui->midiSyncSong == sender()) {
        factory->pushSnapshot();;
        emit(midiSyncSongChanged(ui->midiSyncSong->isChecked()));
    }
    else if(ui->serialInPortEdit == sender()) {
        factory->pushSnapshot();
        ui->serialInPortEdit->setStyleSheet("");
        emit(serialPortChange(ui->serialInPortEdit->text()));
    }
    else if(ui->transportMessageEdit == sender()) {
        factory->pushSnapshot();
        emit(transportMessageChange(ui->transportMessageEdit->text()));
    }
    else if(ui->syncMessageEdit == sender()) {
        factory->pushSnapshot();
        emit(syncMessageChange(ui->syncMessageEdit->text()));
    }
    else if((sender() == ui->bundleMessageEdit) || (sender() == ui->bundleMessagePort)) {
        factory->pushSnapshot();
        emit(bundleMessageChange(ui->bundleMessageEdit->text(), ui->bundleMessagePort->value()));
    }
}

void UiInspector::actionInfoID() {
    bool ok = false;
    quint16 oldId = ui->newIdButton->text().toInt();
    quint16 newId = (new UiMessageBox())->getDouble(tr("IanniX Inspector"), tr("Enter the new ID:"), oldId, 0, 32767, 1, 0, "", &ok);
    if(ok && (newId != oldId)) {
        factory->pushSnapshot();
        emit(actionChangeID(oldId, newId));
        needRefresh = true;
    }
}


void UiInspector::actionInfoGroup() {
    bool ok = false;
    QString groupeId = (new UiMessageBox())->getText(tr("IanniX Inspector"), tr("Enter the name of the destination group:"), ui->groupIdButton->text(), &ok);
    if(ok) {
        factory->pushSnapshot();
        foreach(NxObject *object, *(render->getSelection()))
            object->setGroupId(groupeId);
        needRefresh = true;
    }
}
void UiInspector::actionMessages() {
    if(render->getSelection()->count()) {
        factory->pushSnapshot();
        ExtOscPatternAsk *ask = new ExtOscPatternAsk(factory, 0, render->getSelection());
        if(!ask->onlyCurves) {
            if(ask->exec()) {
                foreach(NxObject *object, *(render->getSelection()))
                    object->setMessagePatterns(ask->getMessagePatterns());
            }
        }
    }
}

void UiInspector::logOscSend(const QString & message) {
    ui->oscSendText->appendPlainText(message);
}
void UiInspector::logOscReceive(const QString & message) {
    ui->oscReceiveText->appendPlainText(message);
}
void UiInspector::setMousePos(const NxPoint & pos) {
    ui->mouseLabel->setText(tr("MOUSE:") + QString(" %1 / %2").arg(pos.x(), 0, 'f', 3).arg(pos.y(), 0, 'f', 3));
}
void UiInspector::setMouseZoom(qreal zoom) {
    ui->zoomLabel->setText(tr("ZOOM:") + QString(" %1%").arg(zoom, 0, 'f', 1));
}

void UiInspector::timerEvent(QTimerEvent *) {
    if(needRefresh)
        refresh();
}
void UiInspector::refresh() {
    needRefresh = false;

    nbTriggers = triggerItem->childCount();
    nbCursors  = cursorItem->childCount();
    nbCurves   = curveItem->childCount();
    QString triggerStr = tr("TRIGGERS") + QString(" (%1)").arg(nbTriggers);
    QString cursorStr  = tr("CURSORS")  + QString(" (%1)").arg(nbCursors);
    QString curveStr   = tr("CURVES")   + QString(" (%1)").arg(nbCurves);
    triggerItem->setText(0, triggerStr);
    cursorItem ->setText(0, cursorStr);
    curveItem  ->setText(0, curveStr);
    ui->viewTriggerCheck->setText(triggerStr);
    ui->viewCursorCheck ->setText(cursorStr);
    ui->viewCurveCheck  ->setText(curveStr);
    ui->viewGroupLabel  ->setText(tr("GROUPS") + QString(" (%1)").arg(ui->cc2View->topLevelItemCount()));

    actionInfoLock = true;

    quint16 counterTriggers = 0, counterCurves = 0, counterCurvePoints = 0, counterCursors = 0, counterCursorsCurve = 0;

    if(render) {
        QList<NxObject*> *objects = render->getSelection();
        NxObject *objectsHover = 0;
        if((objects->count() == 0) && (render->getSelectedHover()))
            objectsHover = render->getSelectedHover();
        NxCursor  *prevCursor = 0;
        NxTrigger *prevTrigger = 0;
        NxObject  *prevObject = 0;
        NxCurve   *prevCurve = 0;

        ui->colorCombo1->clear();
        ui->colorCombo2->clear();
        ui->colorCombo3->clear();
        ui->colorCombo4->clear();
        colorComboAdd(ui->colorCombo1, render->getRenderOptions()->colors.keys());
        colorComboAdd(ui->colorCombo2, render->getRenderOptions()->colors.keys());
        colorComboAdd(ui->colorCombo3, render->getRenderOptions()->colors.keys());
        colorComboAdd(ui->colorCombo4, render->getRenderOptions()->colors.keys());
        colorComboAdd(ui->colorCombo1, QStringList() << "Custom");
        colorComboAdd(ui->colorCombo2, QStringList() << "Custom");
        colorComboAdd(ui->colorCombo3, QStringList() << "Custom");
        colorComboAdd(ui->colorCombo4, QStringList() << "Custom");

        for(quint16 indexObject = 0 ; indexObject < objects->count()+1 ; indexObject++) {
            NxObject *object = 0;
            if(indexObject == objects->count())
                object = objectsHover;
            else
                object = objects->at(indexObject);
            if(!object)
                continue;

            if(prevObject == 0)
                prevObject = object;

            if(object->getType() == ObjectsTypeCursor)
                counterCursors++;
            else if(object->getType() == ObjectsTypeCurve)
                counterCurves++;
            else if(object->getType() == ObjectsTypeTrigger)
                counterTriggers++;

            if((object->getType() == ObjectsTypeCursor) && (((NxCursor*)object)->getCurve()))
                counterCursorsCurve++;
            if((object->getType() == ObjectsTypeCurve) && (((NxCurve*)object)->getCurveType() == CurveTypePoints))
                counterCurvePoints++;

            if (objects->count() > 1)  ////CG//// Don't allow ID change if more than one object selected
                ui->newIdButton->setDisabled(true);
            else
                ui->newIdButton->setDisabled(false);

            QString thisID = QString::number(object->getId());
            QString prevID = QString::number(prevObject->getId());
            change(indexObject, ui->newIdButton, thisID , prevID);

            change(indexObject, ui->groupIdButton, object->getGroupId(), prevObject->getGroupId());

            change(indexObject, ui->positionX, object->getPos().x(), prevObject->getPos().x());
            change(indexObject, ui->positionY, object->getPos().y(), prevObject->getPos().y());
            change(indexObject, ui->positionZ, object->getPos().z(), prevObject->getPos().z());
            change(indexObject, ui->activityCheck, object->getActive(), prevObject->getActive());
            change(indexObject, ui->labelLine, object->getLabel(), prevObject->getLabel());
            change(indexObject, ui->colorCombo1, object->getColorActiveVerbose(), prevObject->getColorActiveVerbose());
            change(indexObject, ui->colorCombo2, object->getColorInactiveVerbose(), prevObject->getColorInactiveVerbose());
            change(indexObject, ui->sizeSpin, object->getSize(), prevObject->getSize());

            if(object->getType() == ObjectsTypeCursor) {
                NxCursor *cursor = (NxCursor*)object;
                if(prevCursor == 0)
                    prevCursor = cursor;

                change(indexObject, ui->widthSpin, cursor->getWidth(), prevCursor->getWidth());
                change(indexObject, ui->depthSpin, cursor->getDepth(), prevCursor->getDepth());
                if(sender() != ui->patternLine)
                    change(indexObject, ui->patternLine, cursor->getStart(), prevCursor->getStart(), false);
                change(indexObject, ui->easingCombo, cursor->getEasing(), prevCursor->getEasing());
                change(indexObject, ui->speedSpin, cursor->getTimeFactor(), prevCursor->getTimeFactor());
                change(indexObject, ui->speedFSpin, cursor->getTimeFactorF(), prevCursor->getTimeFactorF());
                change(indexObject, ui->offsetInitialSpin, cursor->getTimeInitialOffset(), prevCursor->getTimeInitialOffset());
                change(indexObject, ui->offsetStartSpin, cursor->getTimeStartOffset(), prevCursor->getTimeStartOffset());
                change(indexObject, ui->offsetEndSpin, cursor->getTimeEndOffset(), prevCursor->getTimeEndOffset());
                change(indexObject, ui->cursorSourceX1, cursor->getBoundsRect(0, true), prevCursor->getBoundsRect(0, true));
                change(indexObject, ui->cursorSourceY1, cursor->getBoundsRect(1, true), prevCursor->getBoundsRect(1, true));
                change(indexObject, ui->cursorSourceZ1, cursor->getBoundsRect(2, true), prevCursor->getBoundsRect(2, true));
                change(indexObject, ui->cursorSourceX2, cursor->getBoundsRect(3, true), prevCursor->getBoundsRect(3, true));
                change(indexObject, ui->cursorSourceY2, cursor->getBoundsRect(4, true), prevCursor->getBoundsRect(4, true));
                change(indexObject, ui->cursorSourceZ2, cursor->getBoundsRect(5, true), prevCursor->getBoundsRect(5, true));
                change(indexObject, ui->cursorTargetX1, cursor->getBoundsRect(0, false), prevCursor->getBoundsRect(0, false));
                change(indexObject, ui->cursorTargetY1, cursor->getBoundsRect(1, false), prevCursor->getBoundsRect(1, false));
                change(indexObject, ui->cursorTargetZ1, cursor->getBoundsRect(2, false), prevCursor->getBoundsRect(2, false));
                change(indexObject, ui->cursorTargetX2, cursor->getBoundsRect(3, false), prevCursor->getBoundsRect(3, false));
                change(indexObject, ui->cursorTargetY2, cursor->getBoundsRect(4, false), prevCursor->getBoundsRect(4, false));
                change(indexObject, ui->cursorTargetZ2, cursor->getBoundsRect(5, false), prevCursor->getBoundsRect(5, false));
                change(indexObject, ui->messagesSpin, object->getMessageTimeInterval(), prevObject->getMessageTimeInterval());

                if(cursor->getCurve()) {
                    change(indexObject, ui->speedSpin, cursor->getTimeFactor(), prevCursor->getTimeFactor());
                    change(indexObject, ui->cursorLengthSpin, cursor->getCurve()->getPathLength() / cursor->getTimeFactor(), prevCursor->getCurve()->getPathLength() / prevCursor->getTimeFactor());
                }
                prevCursor = cursor;
            }
            else if(object->getType() == ObjectsTypeCurve) {
                NxCurve *curve = (NxCurve*)object;
                if(prevCurve == 0)
                    prevCurve = curve;

                change(indexObject, ui->sizeWSpin,  curve->getResize().width(), prevCurve->getResize().width());
                change(indexObject, ui->sizeHSpin,  curve->getResize().height(), prevCurve->getResize().height());
                change(indexObject, ui->pointsList, curve->getPathPoints(), prevCurve->getPathPoints());
                prevCurve = curve;
            }
            else if(object->getType() == ObjectsTypeTrigger) {
                NxTrigger *trigger = (NxTrigger*)object;
                if(prevTrigger == 0)
                    prevTrigger = trigger;

                change(indexObject, ui->triggerOffSpin, trigger->getTriggerOff(), prevTrigger->getTriggerOff());
                change(indexObject, ui->colorCombo3, trigger->getColorActiveMessageVerbose(), prevTrigger->getColorActiveMessageVerbose());
                change(indexObject, ui->colorCombo4, trigger->getColorInactiveMessageVerbose(), prevTrigger->getColorInactiveMessageVerbose());
                //change(indexObject, ui->messagesSpin, object->getMessageTimeInterval(), prevObject->getMessageTimeInterval());
                prevTrigger = trigger;
            }
            prevObject = object;
        }
    }
    ui->typeLabel->setText("");
    if(counterTriggers == 1)
        ui->typeLabel->setText(ui->typeLabel->text() + " " + QString::number(counterTriggers) + " " + tr("TRIGGER"));
    else if(counterTriggers > 1)
        ui->typeLabel->setText(ui->typeLabel->text() + " " + QString::number(counterTriggers) + " " + tr("TRIGGERS"));
    if(counterCurves == 1)
        ui->typeLabel->setText(ui->typeLabel->text() + " " + QString::number(counterCurves) + " " + tr("CURVE"));
    else if(counterCurves > 1)
        ui->typeLabel->setText(ui->typeLabel->text() + " " + QString::number(counterCurves) + " " + tr("CURVES"));
    if(counterCursors == 1)
        ui->typeLabel->setText(ui->typeLabel->text() + " " + QString::number(counterCursors) + " " + tr("CURSOR"));
    else if(counterCursors > 1)
        ui->typeLabel->setText(ui->typeLabel->text() + " " + QString::number(counterCursors) + " " + tr("CURSORS"));

    bool showCursorInfo = false, showTriggerInfo = false, showCurveInfo = false, showCurvePointsInfo = false, showCursorCurveInfo = false, showGenericInfo = false;
    if(counterCurves > 0)
        showCurveInfo = true;
    if(counterCursors > 0)
        showCursorInfo = true;
    if(counterTriggers > 0)
        showTriggerInfo = true;
    if(counterCursorsCurve > 0)
        showCursorCurveInfo = true;
    if(counterCurvePoints > 0)
        showCurvePointsInfo = true;
    if((counterCursors + counterCurves + counterTriggers) > 0)
        showGenericInfo = true;

    ui->labelSelection->setVisible(!showGenericInfo);
    ui->separator1->setVisible(showCursorInfo | showTriggerInfo);

    ui->newIdButton->setVisible(showGenericInfo);
    ui->IDLabel->setVisible(showGenericInfo);
    ui->groupIdButton->setVisible(showGenericInfo);
    ui->positionX->setVisible(showCurveInfo | showTriggerInfo);
    ui->positionY->setVisible(showCurveInfo | showTriggerInfo);
    ui->positionZ->setVisible(showCurveInfo | showTriggerInfo);
    ui->positionLabel->setVisible(showCurveInfo | showTriggerInfo);
    ui->activityCheck->setVisible(showGenericInfo);
    ui->activityLabel->setVisible(showGenericInfo);
    ui->messagesButton->setVisible(showCursorInfo | showTriggerInfo);
    ui->messagesLabel->setVisible(showCursorInfo | showTriggerInfo);
    ui->messagesSpin->setVisible(showCursorInfo | showTriggerInfo);
    ui->messagesLabel2->setVisible(showCursorInfo | showTriggerInfo);
    ui->sizeSpin->setVisible(showGenericInfo);
    ui->sizeLabel2->setVisible(showGenericInfo);
    ui->labelLabel->setVisible(showGenericInfo);
    ui->labelLine->setVisible(showGenericInfo);
    ui->colorLabel->setVisible(showGenericInfo);
    ui->colorCombo1->setVisible(showGenericInfo);
    ui->colorCombo2->setVisible(showGenericInfo);

    ui->widthSpin->setVisible(showCursorInfo);
    ui->depthSpin->setVisible(showCursorInfo);
    ui->widthLabel->setVisible(showCursorInfo);
    ui->patternLine->setVisible(showCursorInfo);
    ui->easingCombo->setVisible(showCursorInfo);
    ui->patternLabel->setVisible(showCursorInfo);
    ui->speedSpin->setVisible(showCursorCurveInfo);
    ui->offsetInitialSpin->setVisible(showCursorCurveInfo);
    ui->offsetStartSpin->setVisible(showCursorCurveInfo);
    ui->offsetEndSpin->setVisible(showCursorCurveInfo);
    ui->offsetLabel->setVisible(showCursorCurveInfo);
    ui->offsetLabel1->setVisible(showCursorCurveInfo);
    ui->offsetLabel2->setVisible(showCursorCurveInfo);
    ui->offsetLabel3->setVisible(showCursorCurveInfo);
    ui->cursorLengthSpin->setVisible(showCursorCurveInfo);
    ui->cursorSpeedLabel->setVisible(showCursorCurveInfo);
    ui->cursorPosLabel2->setVisible(showCursorCurveInfo);
    ui->cursorBoundsLabel->setVisible(showCursorCurveInfo);
    ui->cursorSourceX1->setVisible(showCursorCurveInfo);
    ui->cursorSourceX2->setVisible(showCursorCurveInfo);
    ui->cursorSourceY1->setVisible(showCursorCurveInfo);
    ui->cursorSourceY2->setVisible(showCursorCurveInfo);
    ui->cursorSourceZ1->setVisible(showCursorCurveInfo);
    ui->cursorSourceZ2->setVisible(showCursorCurveInfo);
    ui->cursorTargetX1->setVisible(showCursorCurveInfo);
    ui->cursorTargetX2->setVisible(showCursorCurveInfo);
    ui->cursorTargetY1->setVisible(showCursorCurveInfo);
    ui->cursorTargetY2->setVisible(showCursorCurveInfo);
    ui->cursorTargetZ1->setVisible(showCursorCurveInfo);
    ui->cursorTargetZ2->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel1->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel2->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel3->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel4->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel5->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel6->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel7->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel8->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel9->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel10->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel11->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel12->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel13->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel14->setVisible(showCursorCurveInfo);
    ui->speedFLabel->setVisible(showCursorCurveInfo);
    ui->speedFSpin->setVisible(showCursorCurveInfo);

    ui->triggerOffLabel->setVisible(showTriggerInfo);
    ui->triggerOffSpin->setVisible(showTriggerInfo);
    ui->colorCombo3->setVisible(showTriggerInfo);
    ui->colorCombo4->setVisible(showTriggerInfo);

    ui->sizeHSpin->setVisible(showCurveInfo);
    ui->sizeWSpin->setVisible(showCurveInfo);
    ui->sizeLabel->setVisible(showCurveInfo);
    ui->pointsLabel->setVisible(showCurvePointsInfo);
    ui->pointsList->setVisible(showCurvePointsInfo);


    actionInfoLock = false;
}
void UiInspector::change(quint16 indexObject, QDoubleSpinBox *spin, qreal val, qreal prevVal) {
    if(indexObject == 0) {
        spin->setStyleSheet("");
        spin->setValue(val);
    }
    else if((spin->styleSheet().isEmpty()) && (prevVal != val)) {
        spin->setStyleSheet("color: gray;");
    }
}
void UiInspector::change(quint16 indexObject, QSpinBox *spin, qint32 val, qint32 prevVal) {
    if(indexObject == 0) {
        spin->setStyleSheet("");
        spin->setValue(val);
    }
    else if((spin->styleSheet().isEmpty()) && (prevVal != val)) {
        spin->setStyleSheet("color: gray;");
    }
}
void UiInspector::change(quint16 indexObject, QPushButton *spin, const QString & val, const QString & prevVal) {
    if(indexObject == 0) {
        spin->setStyleSheet("");
        spin->setText(val);
    }
    else if((spin->styleSheet().isEmpty()) && (prevVal != val)) {
        spin->setStyleSheet("color: gray;");
    }
}
void UiInspector::change(quint16 indexObject, QCheckBox *spin, quint8 val, quint8 prevVal) {
    if(indexObject == 0) {
        spin->setStyleSheet("");
        spin->setChecked(val);
    }
    else if((spin->styleSheet().isEmpty()) && (prevVal != val)) {
        spin->setStyleSheet("QCheckBox::indicator { background-color: rgba(50, 237, 255, 128); }");
    }
}
void UiInspector::change(quint16 indexObject, QLineEdit *spin, const QString & val, const QString & prevVal) {
    if(indexObject == 0) {
        spin->setStyleSheet("");
        spin->setText(val);
    }
    else if((spin->styleSheet().isEmpty()) && (prevVal != val)) {
        spin->setStyleSheet("QCheckBox::indicator { background-color: rgba(50, 237, 255, 128); }");
    }
}
void UiInspector::change(quint16 indexObject, QComboBox *spin, const QString & val, const QString & prevVal, bool isColor) {
    qint16 indexVal = spin->findText(val);
    if(isColor) {
        if(indexVal < 0)
            colorComboAdd(spin, QStringList() << val);
    }
    else
        spin->setEditText(val);

    if(indexObject == 0) {
        spin->setStyleSheet("");
        if(isColor) spin->setCurrentIndex(spin->findText(val));
        else        spin->setEditText(val);
    }
    else if((spin->styleSheet().isEmpty()) && (prevVal != val)) {
        spin->setStyleSheet("");
        if(isColor) spin->setCurrentIndex(-1);
        //else        spin->setEditText("");
    }
}
void UiInspector::change(quint16 indexObject, QComboBox *spin, quint16 val, quint16 prevVal) {
    if(indexObject == 0) {
        spin->setStyleSheet("");
        spin->setCurrentIndex(val);
    }
    else if((spin->styleSheet().isEmpty()) && (prevVal != val)) {
        spin->setStyleSheet("");
        spin->setCurrentIndex(-1);
    }
}
void UiInspector::change(quint16 indexObject, QTreeWidget *spin, const QList<NxCurvePoint> &val, const QList<NxCurvePoint> &prevVal) {
    if(indexObject == 0) {
        spin->setStyleSheet("");
        quint16 ptIndex = 0;
        if(val.count() != spin->topLevelItemCount())
            spin->clear();
        foreach(const NxCurvePoint &pt, val) {
            QTreeWidgetItem *item;
            if(ptIndex < spin->topLevelItemCount()) item = spin->topLevelItem(ptIndex);
            else                                    item = new QTreeWidgetItem();
            item->setText(0, QString::number(ptIndex++));
            item->setText(1, QString::number(pt.x()));
            item->setText(2, QString::number(pt.y()));
            item->setText(3, QString::number(pt.z()));
            item->setText(4, "");
            item->setText(5, QString::number(pt.c1.x()));
            item->setText(6, QString::number(pt.c1.y()));
            item->setText(7, QString::number(pt.c1.z()));
            item->setText(8, QString::number(pt.c2.x()));
            item->setText(9, QString::number(pt.c2.y()));
            item->setText(10, QString::number(pt.c2.z()));
            item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            if(pt.smooth)   item->setCheckState(4, Qt::Checked);
            else            item->setCheckState(4, Qt::Unchecked);
            spin->addTopLevelItem(item);
        }
    }
    else if((spin->styleSheet().isEmpty()) && (prevVal != val)) {
        spin->setStyleSheet("QCheckBox::indicator { background-color: rgba(50, 237, 255, 128); }");
    }
}

void UiInspector::colorComboAdd(QComboBox *spin, QStringList values) {
    foreach(const QString & value, values) {
        QPixmap icon(32, 32);
        QColor color = Qt::gray;
        QStringList valueSplit = value.split(" ", QString::SkipEmptyParts);
        if(valueSplit.count() == 4)
            color = QColor(valueSplit.at(0).toUInt(), valueSplit.at(1).toUInt(), valueSplit.at(2).toUInt(), valueSplit.at(3).toUInt());
        else
            color = render->getRenderOptions()->colors.value(value);
        icon.fill(color);
        if(value != "Custom")
            spin->addItem(QIcon(icon), value);
        else
            spin->addItem(value);
    }
}

QList<NxObject*> UiInspector::getSelectedCCObject() const {
    QList<NxObject*> objects;
    foreach(const QTreeWidgetItem* item, ui->ccView->selectedItems())
        if((item != triggerItem) && (item != cursorItem) && (item != curveItem))
            objects.append((NxObject*)item);
    return objects;
}
QList<NxGroup*> UiInspector::getSelectedCC2Object() const {
    QList<NxGroup*> groups;
    foreach(const QTreeWidgetItem* item, ui->cc2View->selectedItems())
        groups.append((NxGroup*)item);
    return groups;
}

////CG//// Created to clear treewidget selections to avoid a crash on object deletion
void UiInspector::clearCCselections() {
    ui->ccView->clearSelection();
    ui->cc2View->clearSelection();
}

quint16 UiInspector::getCurrentTab() const {
    return ui->tab->currentIndex();
}
void UiInspector::setCurrentTab(quint16 val) {
    ui->tab->setCurrentIndex(val);
}

bool UiInspector::getViewTriggerCheck() const {
    return ui->viewTriggerCheck->isChecked();
}
void UiInspector::setViewTriggerCheck(bool val) {
    ui->viewTriggerCheck->setChecked(val);
}

bool UiInspector::getViewCurveCheck() const {
    return ui->viewCurveCheck->isChecked();
}
void UiInspector::setViewCurveCheck(bool val) {
    ui->viewCurveCheck->setChecked(val);
}

bool UiInspector::getViewCursorCheck() const {
    return ui->viewCursorCheck->isChecked();
}
void UiInspector::setViewCursorCheck(bool val) {
    ui->viewCursorCheck->setChecked(val);
}

bool UiInspector::getViewCurveOpacityCheck() const {
    return ui->viewCurveOpacityCheck->isChecked();
}
void UiInspector::setViewCurveOpacityCheck(bool val) {
    ui->viewCurveOpacityCheck->setChecked(val);
}

void UiInspector::setOSCOk(bool val) {
    if(val)
        ui->oscInPortSpin->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(151, 209, 38, 255), stop:1 rgba(86, 170, 28, 255));");
    else
        ui->oscInPortSpin->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");
}
void UiInspector::setTCPOk(bool val) {
    if(val)
        ui->tcpInPortSpin->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(151, 209, 38, 255), stop:1 rgba(86, 170, 28, 255));");
    else
        ui->tcpInPortSpin->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");
}
void UiInspector::setUDPOk(bool val) {
    if(val)
        ui->udpInPortSpin->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(151, 209, 38, 255), stop:1 rgba(86, 170, 28, 255));");
    else
        ui->udpInPortSpin->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");
}
void UiInspector::setHttpOk(bool val) {
    if(val)
        ui->httpInPortSpin->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(151, 209, 38, 255), stop:1 rgba(86, 170, 28, 255));");
    else
        ui->httpInPortSpin->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");
}
void UiInspector::setIpOutOk(bool val) {
    if(val)
        ui->ipOutEdit->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(151, 209, 38, 255), stop:1 rgba(86, 170, 28, 255));");
    else
        ui->ipOutEdit->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");
}
void UiInspector::setSerialOk(bool val) {
    if(val)
        ui->serialInPortEdit->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(151, 209, 38, 255), stop:1 rgba(86, 170, 28, 255));");
    else
        ui->serialInPortEdit->setStyleSheet("background: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgb(248, 31, 29), stop:1 rgb(179, 33, 32));");
}
void UiInspector::setOSCPort(quint16 port) {
    ui->oscInPortSpin->setValue(port);
    oscPortChange(port);
}
void UiInspector::setTCPPort(quint16 port) {
    ui->tcpInPortSpin->setValue(port);
    tcpPortChange(port);
}
void UiInspector::setTCPClients(quint16 nb) {
    if(nb == 0)
        ui->tcpInClientLabel->setText(tr("No client connected"));
    else if(nb == 1)
        ui->tcpInClientLabel->setText(tr("1 client connected"));
    else
        ui->tcpInClientLabel->setText(tr("%1 clients connected").arg(nb));
}

void UiInspector::setUDPPort(quint16 port) {
    ui->udpInPortSpin->setValue(port);
    udpPortChange(port);
}
void UiInspector::setHttpPort(quint16 port) {
    ui->httpInPortSpin->setValue(port);
    httpPortChange(port);
}
void UiInspector::setIpOut(const QString & ip) {
    ui->ipOutEdit->setText(ip);
    ipOutChange(ip);
}
void UiInspector::setMidiOut(const QString & _midi) {
    QString midi = _midi;
    if(midi.toLower() == "iannix_out") midi = "from_IanniX";
    ui->midiOutCombo->setCurrentIndex(ui->midiOutCombo->findText(midi, Qt::MatchFixedString));
    midiOutChange(ui->midiOutCombo->currentText());
}
void UiInspector::setMidiTempo(qreal tempo) {
    ui->midiTempoSpin->setValue(tempo);
}
void UiInspector::setMidiOutNewDevice(const QString &midi) {
    ui->midiOutCombo->addItem(midi);
}
void UiInspector::setMidiSyncClock(bool val) {
    ui->midiSyncClock->setChecked(val);
}
void UiInspector::setMidiSyncSong(bool val) {
    ui->midiSyncSong->setChecked(val);
}

void UiInspector::setSerialPort(const QString & port) {
    ui->serialInPortEdit->setText(port);
    serialPortChange(port);
}
void UiInspector::setTransportMessage(const QString & message) {
    ui->transportMessageEdit->setText(message);
    transportMessageChange(message);
}
void UiInspector::setSyncMessage(const QString & message) {
    ui->syncMessageEdit->setText(message);
    syncMessageChange(message);
}
void UiInspector::setBundleMessage(const QString &message, quint16 port) {
    ui->bundleMessageEdit->setText(message);
    ui->bundleMessagePort->setValue(port);
    bundleMessageChange(message, port);
}

quint16 UiInspector::getOSCPort() const {
    return ui->oscInPortSpin->value();
}
quint16 UiInspector::getUDPPort() const {
    return ui->udpInPortSpin->value();
}
quint16 UiInspector::getHttpPort() const {
    return ui->httpInPortSpin->value();
}
quint16 UiInspector::getTCPPort() const {
    return ui->tcpInPortSpin->value();
}
qreal UiInspector::getMidiTempo() const {
    return ui->midiTempoSpin->value();
}
bool UiInspector::getMidiSyncClock() const {
    return ui->midiSyncClock->isChecked();
}
bool UiInspector::getMidiSyncSong() const {
    return ui->midiSyncSong->isChecked();
}
const QString UiInspector::getIpOut() const {
    return ui->ipOutEdit->text();
}
const QString UiInspector::getMidiOut() const {
    return ui->midiOutCombo->currentText();
}
const QString UiInspector::getSerialPort() const {
    return ui->serialInPortEdit->text();
}
const QString UiInspector::getTransportMessage() const {
    return ui->transportMessageEdit->text();
}
const QString UiInspector::getSyncMessage() const {
    return ui->syncMessageEdit->text();
}
const QString UiInspector::getBundleHost() const {
    return ui->bundleMessageEdit->text();
}
quint16 UiInspector::getBundlePort() const {
    return ui->bundleMessagePort->value();
}
