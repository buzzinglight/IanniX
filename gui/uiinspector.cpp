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

#include "uiinspector.h"
#include "ui_uiinspector.h"

UiInspector::UiInspector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiInspector) {
    ui->setupUi(this);
    slidersLock = false;
    toolbarButton = 0;
    lastTabBeforeRessources = 0;

    Help::syncHelpWith(ui->positionX,         COMMAND_POS_X);
    Help::syncHelpWith(ui->positionY,         COMMAND_POS_Y);
    Help::syncHelpWith(ui->positionZ,         COMMAND_POS_Z);
    Help::syncHelpWith(ui->activityCheck,     COMMAND_ACTIVE);
    Help::syncHelpWith(ui->labelLine,         COMMAND_LABEL);
    Help::syncHelpWith(ui->sizeSpin,          COMMAND_SIZE);
    Help::syncHelpWith(ui->messagesButton,    COMMAND_MESSAGE);
    Help::syncHelpWith(ui->messagesSpin,      COMMAND_MESSAGE_INTERVAL);
    Help::syncHelpWith(ui->widthSpin,         COMMAND_CURSOR_WIDTH);
    Help::syncHelpWith(ui->depthSpin,         COMMAND_CURSOR_DEPTH);
    Help::syncHelpWith(ui->speedFSpin,        COMMAND_CURSOR_SPEEDF);
    Help::syncHelpWith(ui->speedSpin,         COMMAND_CURSOR_SPEED);
    Help::syncHelpWith(ui->intertiaSpin,      COMMAND_CURVE_INERTIE);
    Help::syncHelpWith(ui->cursorLengthSpin,  COMMAND_CURSOR_SPEED);
    Help::syncHelpWith(ui->triggerOffSpin,    COMMAND_TRIGGER_OFF);
    Help::syncHelpWith(ui->equationPoints,    COMMAND_CURVE_EQUATION_POINTS);
    Help::syncHelpWith(ui->cursorSourceMode0, COMMAND_CURSOR_BOUNDS_SOURCE_MODE);
    Help::syncHelpWith(ui->cursorSourceMode1, COMMAND_CURSOR_BOUNDS_SOURCE_MODE);
    Help::syncHelpWith(ui->cursorSourceMode2, COMMAND_CURSOR_BOUNDS_SOURCE_MODE);
    Help::syncHelpWith(ui->cursorSourceMode3, COMMAND_CURSOR_BOUNDS_SOURCE_MODE);
    Help::syncHelpWith(ui->cursorSourceX1,    COMMAND_CURSOR_BOUNDS_SOURCE);
    Help::syncHelpWith(ui->cursorSourceY1,    COMMAND_CURSOR_BOUNDS_SOURCE);
    Help::syncHelpWith(ui->cursorSourceZ1,    COMMAND_CURSOR_BOUNDS_SOURCE);
    Help::syncHelpWith(ui->cursorSourceX2,    COMMAND_CURSOR_BOUNDS_SOURCE);
    Help::syncHelpWith(ui->cursorSourceY2,    COMMAND_CURSOR_BOUNDS_SOURCE);
    Help::syncHelpWith(ui->cursorSourceZ2,    COMMAND_CURSOR_BOUNDS_SOURCE);
    Help::syncHelpWith(ui->cursorTargetX1,    COMMAND_CURSOR_BOUNDS_TARGET);
    Help::syncHelpWith(ui->cursorTargetY1,    COMMAND_CURSOR_BOUNDS_TARGET);
    Help::syncHelpWith(ui->cursorTargetZ1,    COMMAND_CURSOR_BOUNDS_TARGET);
    Help::syncHelpWith(ui->cursorTargetX2,    COMMAND_CURSOR_BOUNDS_TARGET);
    Help::syncHelpWith(ui->cursorTargetY2,    COMMAND_CURSOR_BOUNDS_TARGET);
    Help::syncHelpWith(ui->cursorTargetZ2,    COMMAND_CURSOR_BOUNDS_TARGET);
    Help::syncHelpWith(ui->equationEdit,      COMMAND_CURVE_EQUATION);
    Help::syncHelpWith(ui->groupIdButton,     COMMAND_GROUP);
    Help::syncHelpWith(ui->newIdButton,       COMMAND_ID);
    //Help::syncHelpWith(ui->pointsLists,     COMMAND_CURVE_EDITOR);

    Help::syncHelpWith(ui->offsetInitialSpin, COMMAND_CURSOR_OFFSET);
    Help::syncHelpWith(ui->offsetStartSpin,   COMMAND_CURSOR_OFFSET);
    Help::syncHelpWith(ui->offsetEndSpin,     COMMAND_CURSOR_OFFSET);
    Help::syncHelpWith(ui->sizeWSpin,         COMMAND_RESIZE);
    Help::syncHelpWith(ui->sizeHSpin,         COMMAND_RESIZE);

    Help::syncHelpWith(ui->easingCombo,       COMMAND_CURSOR_START);
    Help::syncHelpWith(ui->patternLine,       COMMAND_CURSOR_START);

    Help::syncHelpWith(ui->colorCombo1,       COMMAND_COLOR_ACTIVE);
    Help::syncHelpWith(ui->colorCombo1,       COMMAND_COLOR_ACTIVE_HUE);
    Help::syncHelpWith(ui->colorCombo2,       COMMAND_COLOR_INACTIVE);
    Help::syncHelpWith(ui->colorCombo2,       COMMAND_COLOR_INACTIVE_HUE);
    Help::syncHelpWith(ui->colorComboMultiply,COMMAND_COLOR_MULTIPLY);
    Help::syncHelpWith(ui->colorComboMultiply,COMMAND_COLOR_MULTIPLY_HUE);
    Help::syncHelpWith(ui->textureCombo1,     COMMAND_TEXTURE_ACTIVE);
    Help::syncHelpWith(ui->textureCombo1,     COMMAND_TEXTURE_INACTIVE);

    Help::syncHelpWith(ui->ressourcesTextures,COMMAND_TEXTURE);
    Help::syncHelpWith(ui->ressourcesColors,  COMMAND_GLOBAL_COLOR);
    Help::syncHelpWith(ui->ressourcesColors,  COMMAND_GLOBAL_COLOR_HUE);


    Application::objectsAutosize.setAction(ui->autoresizeSlider, "guiObjectsAutosize");

    MessageManager::setInterfaces(0, 0, ui->spaceForMessageLog);
    ui->ressourcesTextures->showImport(true);
    ui->ressourcesTextures->showNew(false);
    ui->ressourcesTextures->showDuplicate(false);
    Render::textures->configure(tr("Textures"),   ui->ressourcesTextures);
    Render::colors->configure(tr("Score colors"), ui->ressourcesColors);
    ui->ressourcesColors->showDuplicate(false);

    ui->files->importAsFiles = false;
    UiFileItem::configure(ui->files);
    UiFileItem::syncWith(QFileInfoList() << QFileInfo(Application::pathApplication.absoluteFilePath() + "/Examples/") << QFileInfo(Application::pathDocuments.absoluteFilePath() + "/"), ui->files->getTree());
    ui->files->getTree()->collapseAll();
    for(quint16 i = 0 ; i < ui->files->getTree()->topLevelItemCount() ; i++) {
        UiFileItem *searchItem = ((UiFileItem*)ui->files->getTree()->topLevelItem(i))->find(Application::pathApplication.absoluteFilePath() + "/IanniX/");
        if(searchItem)
            ui->files->getTree()->expandItem(searchItem);
    }
    ui->files->showNewRoot(true);
    ui->files->showOpen(true);
    //UiRenderOptions::texturesWidget = ui->ressourcesTextures;
    /*
    UiRenderOptions::texturesWidget->setColumnWidth(0, 100);
    UiRenderOptions::texturesWidget->setColumnWidth(1, 55);
    UiRenderOptions::texturesWidget->setColumnWidth(2, 55);
    UiRenderOptions::texturesWidget->setColumnWidth(3, 55);
    UiRenderOptions::texturesWidget->setColumnWidth(4, 55);
    */

    ui->ccView->setColumnWidth(0, 105);
    ui->ccView->setColumnWidth(1, 25);
    ui->ccView->setColumnWidth(2, 25);
    ui->ccView->setColumnWidth(3, 40);

    //ui->ssTabInfo->setTabEnabled(4, false);
    ui->ssTabInfo->setCurrentIndex(lastTabBeforeRessources);

    render = 0;

    Application::followId          .setAction(ui->followId,              "scoreFollowId");
    Application::paintCurvesOpacity.setAction(ui->viewCurveOpacityCheck, "guiPaintCurvesOpacity");

    ui->followId->setValue(-1);
    ui->ccView->expandAll();
    ui->ccView->sortByColumn(0, Qt::AscendingOrder);

    ui->colorCombo1->clear();
    ui->colorCombo2->clear();
    ui->colorComboMultiply->clear();
    ui->textureCombo1->clear();
    ui->textureCombo2->clear();

    actionInfoLock = true;

    ui->easingCombo->clear();
    NxEasing easing;
    for(quint16 type = 0 ; type < 45 ; type++) {
        easing.setType(type);
        ui->easingCombo->addItem(QIcon(easing.getPixmap()), tr("Easing") + QString(" %1").arg(type));
    }


    //Templates
    ui->equationTemplate->clear();
    addEquationTemplate("Templates", "", true);
    addEquationTemplate("--", "");
    QFileInfoList files = QDir(Application::pathApplication.absoluteFilePath() + "/Tools/Templates/").entryInfoList(QStringList() << "*.txt", QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
    files <<              QDir(Application::pathDocuments.absoluteFilePath()   + "/Templates/").entryInfoList(QStringList() << "*.txt", QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
    bool firstTemplate = true;
    QString title;
    foreach(const QFileInfo &file, files) {
        QString header;
        QHash<QString, QString> params;
        QFile templateFile(file.absoluteFilePath());
        if(templateFile.open(QFile::ReadOnly)) {
            QStringList templatesLong = QString(templateFile.readAll()).split("\n", QString::SkipEmptyParts);
            foreach(const QString &templateLong, templatesLong) {
                if(templateLong.startsWith("["))
                    header = templateLong.toLower();
                else if(header == "[general]") {
                    QStringList templateLongSplit = templateLong.split("=");
                    if(templateLongSplit.count() > 1) {
                        QString key = templateLongSplit.at(0).toLower(), value = templateLongSplit.at(1);
                        params.insert(key, value);
                        if(key == "name")
                            title = value;
                    }
                }
                else if(header == "[equations]") {
                    if(!title.isEmpty()) {
                        if(!firstTemplate)
                            addEquationTemplate("--", "");
                        firstTemplate = false;
                        addEquationTemplate(title, "");
                        title.clear();
                    }
                    QStringList templateLongSplited = templateLong.trimmed().split(" | ");
                    addEquationTemplate("          " + templateLongSplited.at(qMax(1, templateLongSplited.count()-1)), templateLongSplited.first(), true);
                }
            }
        }
    }

    //needRefresh = true;
    startTimer(100);

    refresh();
    refreshIp();
}
void UiInspector::addEquationTemplate(const QString &text, const QString &valeur, bool enabled) {
    if(text.trimmed() == "--")      ui->equationTemplate->insertSeparator(ui->equationTemplate->count());
    else                            ui->equationTemplate->addItem(text, valeur);
    if(!enabled)
        qobject_cast<QStandardItemModel*>(ui->equationTemplate->model())->item(ui->equationTemplate->count()-1)->setEnabled(false);
}

void UiInspector::addInterfaces() {
    QHashIterator<MessagesType, NetworkInterface*> interfacesIterator(MessageManager::interfaces);
    while (interfacesIterator.hasNext()) {
        interfacesIterator.next();
        if(interfacesIterator.key() == MessagesTypeSerial)
            ui->ssTabConfigArduinoLayout->addWidget(interfacesIterator.value());
        else if(interfacesIterator.key() == MessagesTypeMidi)
            ui->ssTabConfigMIDILayout->addWidget(interfacesIterator.value());
        else if((interfacesIterator.key() == MessagesTypeOsc) || (interfacesIterator.key() == MessagesTypeUdp) || (interfacesIterator.key() == MessagesTypeTcp) || (interfacesIterator.key() == MessagesTypeHttp))
            ui->ssTabConfigNetworkLayout->addWidget(interfacesIterator.value());
        else if((interfacesIterator.key() == MessagesTypeSyphon) || (interfacesIterator.key() == MessagesTypeDirect))
            ui->ssTabConfigSyphonLayout->addWidget(interfacesIterator.value());
    }
}

UiInspector::~UiInspector() {
    delete ui;
}

void UiInspector::showEvent(QShowEvent *e) {
    if(toolbarButton)
        toolbarButton->setChecked(true);
    QWidget::showEvent(e);
}
void UiInspector::closeEvent(QCloseEvent *e) {
    if(toolbarButton)
        toolbarButton->setChecked(false);
    QWidget::closeEvent(e);
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

void UiInspector::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Escape)
        setFocus();
}

UiTreeView* UiInspector::getFileWidget() const {
    return ui->files;
}

void UiInspector::actionCCButton() {
    if(sender() == ui->unmuteGroups)        { emit(actionUnmuteGroups());  actionCC(); }
    else if(sender() == ui->unmuteObjects)  { emit(actionUnmuteObjects()); actionCC(); }
    else if(sender() == ui->unsoloGroups)   { emit(actionUnsoloGroups());  actionCC(); }
    else if(sender() == ui->unsoloObjects)  { emit(actionUnsoloObjects()); actionCC(); }
    else if(sender() == ui->followIdClear)  ui->followId->setValue(-1);
}

void UiInspector::actionInfo() {
    if(!slidersLock) {
        slidersLock = true;
        if(sender() == ui->equationParamReset)  {
            ui->equationParam1Value ->setValue(0.5);
            ui->equationParam2Value ->setValue(0.5);
            ui->equationParam3Value ->setValue(0.5);
            ui->equationParam4Value ->setValue(0.5);
            ui->equationParam5Value ->setValue(0.5);
            ui->equationParam1Slider->setValue(500);
            ui->equationParam2Slider->setValue(500);
            ui->equationParam3Slider->setValue(500);
            ui->equationParam4Slider->setValue(500);
            ui->equationParam5Slider->setValue(500);
        }
        if(sender() == ui->equationParam1Slider) ui->equationParam1Value->setValue(ui->equationParam1Slider->value() / 1000.);
        if(sender() == ui->equationParam2Slider) ui->equationParam2Value->setValue(ui->equationParam2Slider->value() / 1000.);
        if(sender() == ui->equationParam3Slider) ui->equationParam3Value->setValue(ui->equationParam3Slider->value() / 1000.);
        if(sender() == ui->equationParam4Slider) ui->equationParam4Value->setValue(ui->equationParam4Slider->value() / 1000.);
        if(sender() == ui->equationParam5Slider) ui->equationParam5Value->setValue(ui->equationParam5Slider->value() / 1000.);
        if(sender() == ui->equationParam1Value)  ui->equationParam1Slider->setValue(ui->equationParam1Value->value() * 1000.);
        if(sender() == ui->equationParam2Value)  ui->equationParam2Slider->setValue(ui->equationParam2Value->value() * 1000.);
        if(sender() == ui->equationParam3Value)  ui->equationParam3Slider->setValue(ui->equationParam3Value->value() * 1000.);
        if(sender() == ui->equationParam4Value)  ui->equationParam4Slider->setValue(ui->equationParam4Value->value() * 1000.);
        if(sender() == ui->equationParam5Value)  ui->equationParam5Slider->setValue(ui->equationParam5Value->value() * 1000.);
        slidersLock = false;
    }

    if(!actionInfoLock) {
        Application::current->pushSnapshot();

        if(ui->positionX == sender())                       Application::current->execute(QString("%1 selection %2").arg(COMMAND_POS_X).arg(ui->positionX->value()), ExecuteSourceGui);
        else if(ui->positionY == sender())                  Application::current->execute(QString("%1 selection %2").arg(COMMAND_POS_Y).arg(ui->positionY->value()), ExecuteSourceGui);
        else if(ui->positionZ == sender())                  Application::current->execute(QString("%1 selection %2").arg(COMMAND_POS_Z).arg(ui->positionZ->value()), ExecuteSourceGui);
        else if(ui->activityCheck == sender())              Application::current->execute(QString("%1 selection %2").arg(COMMAND_ACTIVE).arg(ui->activityCheck->isChecked()), ExecuteSourceGui);
        else if(ui->labelLine == sender())                  Application::current->execute(QString("%1 selection %2").arg(COMMAND_LABEL).arg(ui->labelLine->text()), ExecuteSourceGui);
        else if(ui->sizeSpin == sender())                   Application::current->execute(QString("%1 selection %2").arg(COMMAND_SIZE).arg(ui->sizeSpin->value()), ExecuteSourceGui);
        else if(ui->messagesSpin == sender())               Application::current->execute(QString("%1 selection %2").arg(COMMAND_MESSAGE_INTERVAL).arg(ui->messagesSpin->value()), ExecuteSourceGui);
        else if(ui->widthSpin == sender())                  Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURSOR_WIDTH).arg(ui->widthSpin->value()), ExecuteSourceGui);
        else if(ui->depthSpin == sender())                  Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURSOR_DEPTH).arg(ui->depthSpin->value()), ExecuteSourceGui);
        else if(ui->speedFSpin == sender())                 Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURSOR_SPEEDF).arg(ui->speedFSpin->value()), ExecuteSourceGui);
        else if(ui->speedSpin == sender())                  Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURSOR_SPEED).arg(ui->speedSpin->value()), ExecuteSourceGui);
        else if(ui->intertiaSpin == sender())               Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURVE_INERTIE).arg(ui->intertiaSpin->value()), ExecuteSourceGui);
        else if(ui->triggerOffSpin == sender())             Application::current->execute(QString("%1 selection %2").arg(COMMAND_TRIGGER_OFF).arg(ui->triggerOffSpin->value()), ExecuteSourceGui);
        else if(ui->pointsLists == sender())                Application::current->execute(QString("%1 selection 1").arg(COMMAND_CURVE_EDITOR), ExecuteSourceGui);
        else if(ui->pointsResample == sender())             Application::current->execute(QString("%1 selection 1").arg(COMMAND_CURVE_RESAMPLE), ExecuteSourceGui);
        else if(ui->cursorSourceX1 == sender())             Application::current->execute(QString("%1 selection 0 %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE).arg(ui->cursorSourceX1->value()), ExecuteSourceGui);
        else if(ui->cursorSourceY1 == sender())             Application::current->execute(QString("%1 selection 1 %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE).arg(ui->cursorSourceY1->value()), ExecuteSourceGui);
        else if(ui->cursorSourceZ1 == sender())             Application::current->execute(QString("%1 selection 2 %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE).arg(ui->cursorSourceZ1->value()), ExecuteSourceGui);
        else if(ui->cursorSourceX2 == sender())             Application::current->execute(QString("%1 selection 3 %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE).arg(ui->cursorSourceX2->value()), ExecuteSourceGui);
        else if(ui->cursorSourceY2 == sender())             Application::current->execute(QString("%1 selection 4 %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE).arg(ui->cursorSourceY2->value()), ExecuteSourceGui);
        else if(ui->cursorSourceZ2 == sender())             Application::current->execute(QString("%1 selection 5 %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE).arg(ui->cursorSourceZ2->value()), ExecuteSourceGui);
        else if(ui->cursorTargetX1 == sender())             Application::current->execute(QString("%1 selection 0 %2").arg(COMMAND_CURSOR_BOUNDS_TARGET).arg(ui->cursorTargetX1->value()), ExecuteSourceGui);
        else if(ui->cursorTargetY1 == sender())             Application::current->execute(QString("%1 selection 1 %2").arg(COMMAND_CURSOR_BOUNDS_TARGET).arg(ui->cursorTargetY1->value()), ExecuteSourceGui);
        else if(ui->cursorTargetZ1 == sender())             Application::current->execute(QString("%1 selection 2 %2").arg(COMMAND_CURSOR_BOUNDS_TARGET).arg(ui->cursorTargetZ1->value()), ExecuteSourceGui);
        else if(ui->cursorTargetX2 == sender())             Application::current->execute(QString("%1 selection 3 %2").arg(COMMAND_CURSOR_BOUNDS_TARGET).arg(ui->cursorTargetX2->value()), ExecuteSourceGui);
        else if(ui->cursorTargetY2 == sender())             Application::current->execute(QString("%1 selection 4 %2").arg(COMMAND_CURSOR_BOUNDS_TARGET).arg(ui->cursorTargetY2->value()), ExecuteSourceGui);
        else if(ui->cursorTargetZ2 == sender())             Application::current->execute(QString("%1 selection 5 %2").arg(COMMAND_CURSOR_BOUNDS_TARGET).arg(ui->cursorTargetZ2->value()), ExecuteSourceGui);
        else if(ui->equationPoints == sender())             Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURVE_EQUATION_POINTS).arg(ui->equationPoints->value()), ExecuteSourceGui);
        else if(ui->equationParam1Value == sender())        Application::current->execute(QString("%1 selection param1 %2").arg(COMMAND_CURVE_EQUATION_PARAM).arg(ui->equationParam1Value->value()), ExecuteSourceGui);
        else if(ui->equationParam2Value == sender())        Application::current->execute(QString("%1 selection param2 %2").arg(COMMAND_CURVE_EQUATION_PARAM).arg(ui->equationParam2Value->value()), ExecuteSourceGui);
        else if(ui->equationParam3Value == sender())        Application::current->execute(QString("%1 selection param3 %2").arg(COMMAND_CURVE_EQUATION_PARAM).arg(ui->equationParam3Value->value()), ExecuteSourceGui);
        else if(ui->equationParam4Value == sender())        Application::current->execute(QString("%1 selection param4 %2").arg(COMMAND_CURVE_EQUATION_PARAM).arg(ui->equationParam4Value->value()), ExecuteSourceGui);
        else if(ui->equationParam5Value == sender())        Application::current->execute(QString("%1 selection param5 %2").arg(COMMAND_CURVE_EQUATION_PARAM).arg(ui->equationParam5Value->value()), ExecuteSourceGui);
        else if(ui->cursorSourceMode0 == sender())          Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE_MODE).arg(0), ExecuteSourceGui);
        else if(ui->cursorSourceMode1 == sender())          Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE_MODE).arg(1), ExecuteSourceGui);
        else if(ui->cursorSourceMode2 == sender())          Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE_MODE).arg(2), ExecuteSourceGui);
        else if(ui->cursorSourceMode3 == sender())          Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURSOR_BOUNDS_SOURCE_MODE).arg(3), ExecuteSourceGui);
        else if((ui->cursorLengthSpin == sender()) || (ui->cursorSpeedLock == sender())) {
            if(ui->cursorSpeedLock->isChecked())            Application::current->execute(QString("%1 selection autolock %2").arg(COMMAND_CURSOR_SPEED).arg(ui->cursorLengthSpin->value()), ExecuteSourceGui);
            else                                            Application::current->execute(QString("%1 selection auto     %2").arg(COMMAND_CURSOR_SPEED).arg(ui->cursorLengthSpin->value()), ExecuteSourceGui);
        }
        else if((ui->equationType0 == sender()) || (ui->equationType1 == sender()) || (ui->equationEdit == sender())) {
            if(ui->equationType0->isChecked())  Application::current->execute(QString("%1 selection cartesian %2").arg(COMMAND_CURVE_EQUATION).arg(ui->equationEdit->toPlainText().remove("\n").trimmed()), ExecuteSourceGui);
            else                                Application::current->execute(QString("%1 selection polar %2").arg(COMMAND_CURVE_EQUATION).arg(ui->equationEdit->toPlainText().remove("\n").trimmed()), ExecuteSourceGui);
        }
        else if((ui->offsetInitialSpin == sender()) || (ui->offsetStartSpin == sender()) || (ui->offsetEndSpin == sender()))
            Application::current->execute(QString("%1 selection %2 %3 %4").arg(COMMAND_CURSOR_OFFSET).arg(ui->offsetInitialSpin->value()).arg(ui->offsetStartSpin->value()).arg(ui->offsetEndSpin->value()), ExecuteSourceGui);
        else if((ui->sizeWSpin == sender()) || (ui->sizeHSpin == sender()))
            Application::current->execute(QString("%1 selection %2 %3").arg(COMMAND_RESIZE).arg(ui->sizeWSpin->value()).arg(ui->sizeHSpin->value()), ExecuteSourceGui);
        else if((ui->patternLine == sender()) || (ui->easingCombo == sender()))
            Application::current->execute(QString("%1 selection %2 0 %3").arg(COMMAND_CURSOR_START).arg(ui->easingCombo->currentIndex()).arg(ui->patternLine->currentText().split(" - ").at(0)), ExecuteSourceGui);

        else if((ui->equationTemplate == sender()) && (!ui->equationTemplate->itemData(ui->equationTemplate->currentIndex()).toString().isEmpty()))
            Application::current->execute(QString("%1 selection %2").arg(COMMAND_CURVE_EQUATION).arg(ui->equationTemplate->itemData(ui->equationTemplate->currentIndex()).toString()), ExecuteSourceGui);

        refresh();
    }
}
void UiInspector::actionColor() {
    if(!actionInfoLock) {
        QComboBox *combo = (QComboBox*)sender();
        QString val = combo->currentText();
        QStringList oldValStr = combo->currentText().split(" ", QString::SkipEmptyParts);
        if(combo->currentText() == tr("Choose…")) {
            QColor oldVal = Qt::white;
            if(oldValStr.count() == 4)
                oldVal = QColor(oldValStr.at(0).toUInt(), oldValStr.at(1).toUInt(), oldValStr.at(2).toUInt(), oldValStr.at(3).toUInt());
            QColor valColor = QColorDialog::getColor(oldVal, 0, tr("IanniX Color Inspector"), QColorDialog::ShowAlphaChannel);
            val = QString("%1 %2 %3 %4").arg(valColor.red()).arg(valColor.green()).arg(valColor.blue()).arg(valColor.alpha());
        }
        Application::current->pushSnapshot();

        if(ui->colorCombo1 == sender())                 Application::current->execute(QString("%1 selection %2").arg(COMMAND_COLOR_ACTIVE).arg(val), ExecuteSourceGui);
        else if(ui->colorCombo2 == sender())            Application::current->execute(QString("%1 selection %2").arg(COMMAND_COLOR_INACTIVE).arg(val), ExecuteSourceGui);
        else if(ui->colorComboMultiply == sender())     Application::current->execute(QString("%1 selection %2").arg(COMMAND_COLOR_MULTIPLY).arg(val), ExecuteSourceGui);

        refresh();
    }
}
void UiInspector::actionTexture() {
    if(!actionInfoLock) {
        QComboBox *combo = (QComboBox*)sender();
        QString val = combo->currentText();
        Application::current->pushSnapshot();

        if(ui->textureCombo1 == sender())         Application::current->execute(QString("%1 selection %2").arg(COMMAND_TEXTURE_ACTIVE).arg(val), ExecuteSourceGui);
        else if(ui->textureCombo2 == sender())    Application::current->execute(QString("%1 selection %2").arg(COMMAND_TEXTURE_INACTIVE).arg(val), ExecuteSourceGui);

        refresh();
    }
}

void UiInspector::actionInfoID() {
    bool ok = false;
    quint16 oldId = ui->newIdButton->text().toInt();
    quint16 newId = (new UiMessageBox())->getDouble(tr("Object ID"), tr("Enter the new ID:"), oldId, 0, 32767, 1, 0, "", &ok);
    if((ok) && (oldId != newId)) {
        if(Application::current->getObjectById(newId))
            (new UiMessageBox())->display(tr("Object ID"), tr("Another object has this ID.\nTry deleting that object, or change its ID."));
        else {
            Application::current->pushSnapshot();
            Application::current->execute(QString("%1 %2 %3").arg(COMMAND_ID).arg(oldId).arg(newId), ExecuteSourceGui);
            needRefresh = true;
        }
    }
}


void UiInspector::actionInfoGroup() {
    bool ok = false;
    QString groupeId = (new UiMessageBox())->getText(tr("Object Group ID"), tr("Enter the name of the desired group:"), ui->groupIdButton->text(), &ok);
    if(ok) {
        Application::current->pushSnapshot();
        Application::current->execute(QString("%1 selection %2").arg(COMMAND_GROUP).arg(groupeId), ExecuteSourceGui);
        needRefresh = true;
    }
}
void UiInspector::actionMessages() {
    if(render->getSelection()->count()) {
        Application::current->pushSnapshot();
        ExtOscPatternAsk *ask = new ExtOscPatternAsk(Application::current->getMainWindow(), render->getSelection());
        if(!ask->onlyCurves)
            if(ask->exec()) {
                if(ask->getMessagePatterns().length())  Application::current->execute(QString("%1 selection %2").arg(COMMAND_MESSAGE).arg(ask->getMessagePatterns()), ExecuteSourceGui);
                else                                    Application::current->execute(QString("%1 selection -").arg(COMMAND_MESSAGE), ExecuteSourceGui);
            }
    }
}

void UiInspector::setMousePos(const NxPoint & pos) {
    ui->mouseLabel->setText(tr("MOUSE:") + QString(" %1 s. / %2 s.").arg(pos.x(), 0, 'f', 3).arg(pos.y(), 0, 'f', 3));
}
void UiInspector::setMouseZoom(qreal zoom) {
    ui->zoomLabel->setText(tr("ZOOM:") + QString(" %1%").arg(zoom, 0, 'f', 1));
}
void UiInspector:: setRotationAngles(const NxPoint &angles) {
    ui->rotationLabel->setText(tr("ANGLES:") + QString(" %1° / %2°").arg(angles.y(), 0, 'f', 3).arg(angles.z(), 0, 'f', 3));
}

void UiInspector::actionTabChange(int) {
    if(ui->tab->currentIndex() == 1)
        askRefresh();
    else if((ui->tab->currentIndex() == 3) && (ui->ssTabConfig->currentIndex() == 0))
        MessageManager::setLogVisibility(true);
    else
        MessageManager::setLogVisibility(false);
}

void UiInspector::timerEvent(QTimerEvent *) {
    if(needRefresh)
        refresh();
}
void UiInspector::refreshIp() {
    //IPs
    QStringList ipsName;
    foreach(const QNetworkInterface &interf, QNetworkInterface::allInterfaces()) {
        foreach(const QNetworkAddressEntry &addressEntry, interf.addressEntries()) {
            bool ok = false;
            QString ipName;
            if(addressEntry.ip().toIPv4Address() > 0)                    {  ipName += QString("     - %1 (%2)").arg(addressEntry.ip().toString()).arg(interf.humanReadableName()); ok = true; }
            if((ok) && (addressEntry.broadcast().toIPv4Address() > 0))      ipName += QString(", broadcast on %1").arg(addressEntry.broadcast().toString());
            if(ok)                                                       {  ipsName << ipName; }
        }
    }
    if(ipsName.count()) {
        QString ipNameTotal;
        foreach(const QString &ipName, ipsName)
            ipNameTotal += ipName + "\n";
        ipNameTotal.chop(1);
        if(ui->myIP->toPlainText() != ipNameTotal)
            ui->myIP->setPlainText(ipNameTotal);
        ui->myIP->setVisible(true);
        ui->myIPLabel->setVisible(true);
    }
    else {
        ui->myIP->setVisible(false);
        ui->myIPLabel->setVisible(false);
    }
    QTimer::singleShot(5000, this, SLOT(refreshIp()));
}

void UiInspector::refresh() {
    needRefresh = false;
    if(!Application::current)
        return;

    MessageManager::transportNbTriggers = Application::current->getCount(ObjectsTypeTrigger);
    MessageManager::transportNbCursors  = Application::current->getCount(ObjectsTypeCursor);
    MessageManager::transportNbCurves   = Application::current->getCount(ObjectsTypeCurve);
    MessageManager::transportNbGroups   = Application::current->getCount(-2);
    actionInfoLock = true;

    quint16 counterTriggers = 0, counterCurves = 0, counterCurvePoints = 0, counterCurveEllipse = 0, counterCurveEquation = 0, counterCursors = 0, counterCursorsCurve = 0;

    if((render) && (ui->tab->currentIndex() == 1)) {
        UiRenderSelection *objects = render->getSelection();
        NxObject *objectsHover = 0;
        if((objects->count() == 0) && (render->getSelectedHover()))
            objectsHover = render->getSelectedHover();
        NxCursor  *prevCursor = 0;
        NxTrigger *prevTrigger = 0;
        NxObject  *prevObject = 0;
        NxCurve   *prevCurve = 0;

        if(!ui->colorCombo1->hasFocus()) {
            ui->colorCombo1->clear();
            colorComboAdd(ui->colorCombo1,          Render::colors->keys());
            colorComboAdd(ui->colorCombo1,          QStringList() << tr("Choose…"));
        }
        if(!ui->colorCombo2->hasFocus()) {
            ui->colorCombo2->clear();
            colorComboAdd(ui->colorCombo2,          Render::colors->keys());
            colorComboAdd(ui->colorCombo2,          QStringList() << tr("Choose…"));
        }
        if(!ui->colorComboMultiply->hasFocus()) {
            ui->colorComboMultiply->clear();
            colorComboAdd(ui->colorComboMultiply,   QStringList() << tr("Choose…"));
        }

        ui->textureCombo1->clear();
        ui->textureCombo2->clear();
        textureComboAdd(ui->textureCombo1, QStringList() << "");
        textureComboAdd(ui->textureCombo2, QStringList() << "");
        textureComboAdd(ui->textureCombo1, Render::textures->keys());
        textureComboAdd(ui->textureCombo2, Render::textures->keys());

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
            if((object->getType() == ObjectsTypeCurve) && (((NxCurve*)object)->getCurveType() == CurveTypeEllipse))
                counterCurveEllipse++;
            if((object->getType() == ObjectsTypeCurve) && ((((NxCurve*)object)->getCurveType() == CurveTypeEquationCartesian) || (((NxCurve*)object)->getCurveType() == CurveTypeEquationPolar)))
                counterCurveEquation++;



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
            change(indexObject, ui->colorCombo1, object->getColorActiveVerbose(), prevObject->getColorActiveVerbose(), true);
            change(indexObject, ui->colorCombo2, object->getColorInactiveVerbose(), prevObject->getColorInactiveVerbose(), true);
            change(indexObject, ui->colorComboMultiply, object->getColorMultiplyVerbose(), prevObject->getColorMultiplyVerbose(), true);
            change(indexObject, ui->sizeSpin, object->getSize(), prevObject->getSize());

            if(object->getType() == ObjectsTypeCursor) {
                NxCursor *cursor = (NxCursor*)object;
                if(prevCursor == 0)
                    prevCursor = cursor;

                change(indexObject, ui->widthSpin, cursor->getWidth(), prevCursor->getWidth());
                change(indexObject, ui->depthSpin, cursor->getDepth(), prevCursor->getDepth());
                if(sender() != ui->patternLine)
                    change(indexObject, ui->patternLine, cursor->getStart().mid(4), prevCursor->getStart().mid(4), false);
                change(indexObject, ui->easingCombo, cursor->getEasing(), prevCursor->getEasing());
                change(indexObject, ui->speedSpin, cursor->getTimeFactor(), prevCursor->getTimeFactor());
                change(indexObject, ui->speedFSpin, cursor->getTimeFactorF(), prevCursor->getTimeFactorF());
                change(indexObject, ui->cursorSpeedLock, cursor->getLockPathLength(), prevCursor->getLockPathLength());
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
                change(indexObject, ui->cursorSourceMode0, cursor->getBoundsSourceMode()==0, prevCursor->getBoundsSourceMode()==0);
                change(indexObject, ui->cursorSourceMode1, cursor->getBoundsSourceMode()==1, prevCursor->getBoundsSourceMode()==1);
                change(indexObject, ui->cursorSourceMode2, cursor->getBoundsSourceMode()==2, prevCursor->getBoundsSourceMode()==2);
                change(indexObject, ui->cursorSourceMode3, cursor->getBoundsSourceMode()==3, prevCursor->getBoundsSourceMode()==3);
                change(indexObject, ui->textureCombo1, cursor->getTextureActive(),    prevCursor->getTextureActive(), false);
                change(indexObject, ui->textureCombo2, cursor->getTextureInactive(), prevCursor->getTextureInactive(), false);

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

                change(indexObject, ui->sizeWSpin,      curve->getResize().width(), prevCurve->getResize().width());
                change(indexObject, ui->sizeHSpin,      curve->getResize().height(), prevCurve->getResize().height());
                change(indexObject, ui->intertiaSpin,   curve->getInertie(), prevCurve->getInertie());
                change(indexObject, ui->equationPoints, curve->getEquationPoints(), prevCurve->getEquationPoints());
                change(indexObject, ui->equationType0,  curve->getEquationType()==0, prevCurve->getEquationType()==0);
                change(indexObject, ui->equationType1,  curve->getEquationType()==1, prevCurve->getEquationType()==1);
                change(indexObject, ui->equationEdit,   curve->getEquation(true), prevCurve->getEquation(true));
                change(indexObject, ui->equationParam1Value, curve->getEquationParam("param1"), prevCurve->getEquationParam("param1"));
                change(indexObject, ui->equationParam2Value, curve->getEquationParam("param2"), prevCurve->getEquationParam("param2"));
                change(indexObject, ui->equationParam3Value, curve->getEquationParam("param3"), prevCurve->getEquationParam("param3"));
                change(indexObject, ui->equationParam4Value, curve->getEquationParam("param4"), prevCurve->getEquationParam("param4"));
                change(indexObject, ui->equationParam5Value, curve->getEquationParam("param5"), prevCurve->getEquationParam("param5"));

                prevCurve = curve;
            }
            else if(object->getType() == ObjectsTypeTrigger) {
                NxTrigger *trigger = (NxTrigger*)object;
                if(prevTrigger == 0)
                    prevTrigger = trigger;

                change(indexObject, ui->triggerOffSpin, trigger->getTriggerOff(), prevTrigger->getTriggerOff());
                change(indexObject, ui->textureCombo1, trigger->getTextureActive(), prevTrigger->getTextureActive(), false);
                change(indexObject, ui->textureCombo2, trigger->getTextureInactive(), prevTrigger->getTextureInactive(), false);
                prevTrigger = trigger;
            }
            prevObject = object;
        }
    }

    ui->typeLabel->setText("");
    QString typeLabelText;
    if(counterTriggers == 1)        typeLabelText += QString::number(counterTriggers) + tr(" TRIGGER, ");
    else if(counterTriggers > 1)    typeLabelText += QString::number(counterTriggers) + tr(" TRIGGERS, ");
    if(counterCurves == 1)          typeLabelText += QString::number(counterCurves)   + tr(" CURVE, ");
    else if(counterCurves > 1)      typeLabelText += QString::number(counterCurves)   + tr(" CURVES, ");
    if(counterCursors == 1)         typeLabelText += QString::number(counterCursors)  + tr(" CURSOR, ");
    else if(counterCursors > 1)     typeLabelText += QString::number(counterCursors)  + tr(" CURSORS, ");
    typeLabelText.chop(2);
    ui->typeLabel->setText(typeLabelText);

    bool showCursorInfo = false, showTriggerInfo = false, showCurveInfo = false, showCurvePointsInfo = false, showCurveEllipseInfo = false, showCursorCurveInfo = false, showGenericInfo = false, showCurveEquationInfo = false;
    if(counterCurves > 0)
        showCurveInfo = true;
    if(counterCursors > 0)
        showCursorInfo = true;
    if(counterTriggers > 0)
        showTriggerInfo = true;
    if(counterCurveEllipse > 0)
        showCurveEllipseInfo = true;
    if(counterCursorsCurve > 0)
        showCursorCurveInfo = true;
    if(counterCurvePoints > 0)
        showCurvePointsInfo = true;
    if(counterCurveEquation > 0)
        showCurveEquationInfo = true;
    if((counterCursors + counterCurves + counterTriggers) > 0)
        showGenericInfo = true;

    ui->newIdButton->setVisible(showGenericInfo);
    ui->IDLabel->setVisible(showGenericInfo);
    ui->groupIdButton->setVisible(showGenericInfo);
    ui->groupIdLabel->setVisible(showGenericInfo);
    ui->positionX->setVisible(showCurveInfo | showTriggerInfo);
    ui->positionY->setVisible(showCurveInfo | showTriggerInfo);
    ui->positionZ->setVisible(showCurveInfo | showTriggerInfo);
    ui->positionLabel->setVisible(showCurveInfo | showTriggerInfo);
    ui->activityCheck->setVisible(showGenericInfo);
    ui->activityLabel->setVisible(showGenericInfo);
    ui->messagesButton->setVisible(showCursorInfo | showTriggerInfo);
    ui->messagesSpin->setVisible(showCursorInfo);
    ui->sizeSpin->setVisible(showGenericInfo);
    ui->sizeLabel2->setVisible(showGenericInfo);
    ui->labelLabel->setVisible(showGenericInfo);
    ui->labelLine->setVisible(showGenericInfo);
    ui->colorLabel1->setVisible(showGenericInfo);
    ui->colorLabel2->setVisible(showGenericInfo);
    ui->colorCombo1->setVisible(showGenericInfo);
    ui->colorCombo2->setVisible(showGenericInfo);
    ui->colorComboMultiply->setVisible(showGenericInfo);
    ui->textureLabel1->setVisible(showCursorInfo | showTriggerInfo);
    ui->textureLabel2->setVisible(showCursorInfo | showTriggerInfo);
    ui->textureCombo1->setVisible(showCursorInfo | showTriggerInfo);
    ui->textureCombo2->setVisible(showCursorInfo | showTriggerInfo);

    ui->widthSpin->setVisible(showCursorInfo);
    ui->depthSpin->setVisible(showCursorInfo);
    ui->widthLabel->setVisible(showCursorInfo);
    ui->patternLine->setVisible(showCursorInfo);
    ui->easingLabel->setVisible(showCursorInfo);
    ui->easingCombo->setVisible(showCursorInfo);
    ui->patternLabel->setVisible(showCursorInfo);
    ui->offsetInitialSpin->setVisible(showCursorCurveInfo);
    ui->offsetStartSpin->setVisible(showCursorCurveInfo);
    ui->offsetEndSpin->setVisible(showCursorCurveInfo);
    ui->offsetLabel->setVisible(showCursorCurveInfo);
    ui->offsetLabel1->setVisible(showCursorCurveInfo);
    ui->offsetLabel2->setVisible(showCursorCurveInfo);
    ui->offsetLabel2_2->setVisible(showCursorCurveInfo);
    ui->offsetLabel3->setVisible(showCursorCurveInfo);
    ui->cursorLengthSpin->setVisible(showCursorCurveInfo);
    ui->cursorSpeedLabel->setVisible(showCursorCurveInfo);
    ui->cursorSpeedLock->setVisible(showCursorCurveInfo);
    if(ui->cursorSpeedLock->isChecked()) {
        ui->cursorSpeedLabel_2->setVisible(false);
        ui->speedSpin->setVisible(false);
    }
    else {
        ui->speedSpin->setVisible(showCursorCurveInfo);
        ui->cursorSpeedLabel_2->setVisible(showCursorCurveInfo);
    }
    ui->cursorTargetX1->setVisible(showCursorCurveInfo);
    ui->cursorTargetX2->setVisible(showCursorCurveInfo);
    ui->cursorTargetY1->setVisible(showCursorCurveInfo);
    ui->cursorTargetY2->setVisible(showCursorCurveInfo);
    ui->cursorTargetZ1->setVisible(showCursorCurveInfo);
    ui->cursorTargetZ2->setVisible(showCursorCurveInfo);
    if(!ui->cursorSourceMode3->isChecked()) {
        ui->cursorSourceX1->setVisible(false);
        ui->cursorSourceY1->setVisible(false);
        ui->cursorSourceZ1->setVisible(false);
        ui->cursorSourceX2->setVisible(false);
        ui->cursorSourceY2->setVisible(false);
        ui->cursorSourceZ2->setVisible(false);
        ui->cursorTargetLabel1->setVisible(false);
        ui->cursorTargetLabel2->setVisible(false);
        ui->cursorTargetLabel5->setVisible(false);
        ui->cursorTargetLabel6->setVisible(false);
        ui->cursorTargetLabel11->setVisible(false);
        ui->cursorTargetLabel13->setVisible(false);
    }
    else {
        ui->cursorSourceX1->setVisible(showCursorCurveInfo);
        ui->cursorSourceX2->setVisible(showCursorCurveInfo);
        ui->cursorSourceY1->setVisible(showCursorCurveInfo);
        ui->cursorSourceY2->setVisible(showCursorCurveInfo);
        ui->cursorSourceZ1->setVisible(showCursorCurveInfo);
        ui->cursorSourceZ2->setVisible(showCursorCurveInfo);
        ui->cursorTargetLabel1->setVisible(showCursorCurveInfo);
        ui->cursorTargetLabel2->setVisible(showCursorCurveInfo);
        ui->cursorTargetLabel5->setVisible(showCursorCurveInfo);
        ui->cursorTargetLabel6->setVisible(showCursorCurveInfo);
        ui->cursorTargetLabel11->setVisible(showCursorCurveInfo);
        ui->cursorTargetLabel13->setVisible(showCursorCurveInfo);
    }
    ui->cursorTargetLabel3->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel4->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel7->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel8->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel12->setVisible(showCursorCurveInfo);
    ui->cursorTargetLabel14->setVisible(showCursorCurveInfo);
    ui->cursorSourceMode->setVisible(showCursorCurveInfo);
    ui->speedFLabel->setVisible(showCursorCurveInfo);
    ui->speedFSpin->setVisible(showCursorCurveInfo);

    ui->triggerOffLabel->setVisible(showTriggerInfo);
    ui->triggerOffSpin->setVisible(showTriggerInfo);

    ui->sizeHSpin->setVisible(showCurvePointsInfo || showCurveEllipseInfo);
    ui->sizeWSpin->setVisible(showCurvePointsInfo || showCurveEllipseInfo);
    ui->sizeLabel->setVisible(showCurvePointsInfo || showCurveEllipseInfo);
    ui->intertiaSpin->setVisible(showCurvePointsInfo);
    ui->intertiaLabel->setVisible(showCurvePointsInfo);
    ui->pointsLabel->setVisible(showCurveInfo);
    ui->pointsResample->setVisible(showCurveInfo);
    ui->pointsLists->setVisible(showCurvePointsInfo);
    ui->equationTemplate->setVisible(showCurveEquationInfo);
    ui->equationLabel->setVisible(showCurveEquationInfo);
    ui->equationType->setVisible(showCurveEquationInfo);
    ui->equationPoints->setVisible(showCurveEquationInfo);
    ui->equationEdit->setVisible(showCurveEquationInfo);
    ui->equationParam1Label->setVisible(showCurveEquationInfo);
    ui->equationParam1Slider->setVisible(showCurveEquationInfo);
    ui->equationParam1Value->setVisible(showCurveEquationInfo);
    ui->equationParam2Label->setVisible(showCurveEquationInfo);
    ui->equationParam2Slider->setVisible(showCurveEquationInfo);
    ui->equationParam2Value->setVisible(showCurveEquationInfo);
    ui->equationParam3Label->setVisible(showCurveEquationInfo);
    ui->equationParam3Slider->setVisible(showCurveEquationInfo);
    ui->equationParam3Value->setVisible(showCurveEquationInfo);
    ui->equationParam4Label->setVisible(showCurveEquationInfo);
    ui->equationParam4Slider->setVisible(showCurveEquationInfo);
    ui->equationParam4Value->setVisible(showCurveEquationInfo);
    ui->equationParam5Label->setVisible(showCurveEquationInfo);
    ui->equationParam5Slider->setVisible(showCurveEquationInfo);
    ui->equationParam5Value->setVisible(showCurveEquationInfo);
    ui->equationParamReset->setVisible(showCurveEquationInfo);

    if((!showGenericInfo) && (ui->ssTabInfo->currentIndex() != 4))
        lastTabBeforeRessources = ui->ssTabInfo->currentIndex();
    ui->ssTabInfo->setTabEnabled(0, showGenericInfo);
    ui->ssTabInfo->setTabEnabled(1, showGenericInfo);
    ui->ssTabInfo->setTabEnabled(2, showCursorInfo | showTriggerInfo);
    ui->ssTabInfo->setTabEnabled(3, showCursorInfo | showTriggerInfo);
    if((ui->ssTabInfo->currentIndex() == 4) && (showGenericInfo)) {
        if(ui->ssTabInfo->isTabEnabled(lastTabBeforeRessources))
            ui->ssTabInfo->setCurrentIndex(lastTabBeforeRessources);
        else if(ui->ssTabInfo->isTabEnabled(lastTabBeforeRessources-1))
            ui->ssTabInfo->setCurrentIndex(lastTabBeforeRessources -1);
        else if(ui->ssTabInfo->isTabEnabled(lastTabBeforeRessources-2))
            ui->ssTabInfo->setCurrentIndex(lastTabBeforeRessources -2);
    }

    actionInfoLock = false;
}
void UiInspector::change(quint16 indexObject, QRadioButton *spin, bool val, bool prevVal) {
    if(indexObject == 0) {
        if(spin->styleSheet() != "")
            spin->setStyleSheet("");
        if(!spin->hasFocus())
            spin->setChecked(val);
    }
    else if((spin->styleSheet() == "") && (prevVal != val)) {
        spin->setStyleSheet("color: gray;");
    }
}

void UiInspector::change(quint16 indexObject, QDoubleSpinBox *spin, qreal val, qreal prevVal) {
    if(indexObject == 0) {
        if(spin->styleSheet() != "")
            spin->setStyleSheet("");
        if(!spin->hasFocus())
            spin->setValue(val);
    }
    else if((spin->styleSheet() == "") && (prevVal != val)) {
        spin->setStyleSheet("color: gray;");
    }
}
void UiInspector::change(quint16 indexObject, QSpinBox *spin, qint32 val, qint32 prevVal) {
    if(indexObject == 0) {
        if(spin->styleSheet() != "")
            spin->setStyleSheet("");
        if(!spin->hasFocus())
            spin->setValue(val);
    }
    else if((spin->styleSheet() == "") && (prevVal != val)) {
        spin->setStyleSheet("color: gray;");
    }
}
void UiInspector::change(quint16 indexObject, QPushButton *spin, const QString & val, const QString & prevVal) {
    if(indexObject == 0) {
        if(spin->styleSheet() != "")
            spin->setStyleSheet("");
        if(!spin->hasFocus())
            spin->setText(val);
    }
    else if((spin->styleSheet() == "") && (prevVal != val)) {
        spin->setStyleSheet("color: gray;");
    }
}
void UiInspector::change(quint16 indexObject, QCheckBox *spin, quint8 val, quint8 prevVal) {
    if(indexObject == 0) {
        if(spin->styleSheet() != "")
            spin->setStyleSheet("");
        if(!spin->hasFocus())
            spin->setChecked(val);
    }
    else if((spin->styleSheet() == "") && (prevVal != val)) {
        spin->setStyleSheet("QCheckBox::indicator { background-color: rgba(50, 237, 255, 128); }");
    }
}
void UiInspector::change(quint16 indexObject, QLineEdit *spin, const QString & val, const QString & prevVal) {
    if(indexObject == 0) {
        if(spin->styleSheet() != "")
            spin->setStyleSheet("");
        if(!spin->hasFocus())
            spin->setText(val);
    }
    else if((spin->styleSheet() == "") && (prevVal != val)) {
        spin->setStyleSheet("QCheckBox::indicator { background-color: rgba(50, 237, 255, 128); }");
    }
}
void UiInspector::change(quint16 indexObject, QPlainTextEdit *spin, const QString & val, const QString & prevVal) {
    if(indexObject == 0) {
        if(spin->styleSheet() != "")
            spin->setStyleSheet("");
        if(!spin->hasFocus())
            spin->setPlainText(val);
    }
    else if((spin->styleSheet() == "") && (prevVal != val)) {
        spin->setStyleSheet("QCheckBox::indicator { background-color: rgba(50, 237, 255, 128); }");
    }
}
void UiInspector::change(quint16 indexObject, QComboBox *spin, const QString & val, const QString & prevVal, bool isColor) {
    if(!isColor) {
        if((!spin->hasFocus()) && (spin->isEditable()))
            spin->setEditText(val);
    }

    if(indexObject == 0) {
        qint16 indexVal = spin->findText(val);
        if(!spin->hasFocus()) {
            if(indexVal < 0) {
                if(isColor) colorComboAdd(spin, QStringList() << val);
                else        spin->addItem(val);
                indexVal = spin->count()-1;
            }
            spin->setCurrentIndex(indexVal);
            //spin->setEditText(val);
        }
    }
    else if(prevVal != val) {
        if((isColor) && (spin->currentIndex() >= 0))
            spin->setCurrentIndex(-1);
    }
}
void UiInspector::change(quint16 indexObject, QComboBox *spin, qint16 val, qint16 prevVal) {
    if(indexObject == 0) {
        if(!spin->hasFocus())
            spin->setCurrentIndex(val);
    }
    else if((spin->styleSheet() == "") && (prevVal != val)) {
        if(spin->currentIndex() >= 0)
            spin->setCurrentIndex(-1);
    }
}

void UiInspector::colorComboAdd(QComboBox *spin, QStringList values) {
    foreach(const QString & value, values) {
        QString colorName = value;
        QPixmap icon(32, 32);
        QColor color = Qt::gray;
        QStringList valueSplit = colorName.split(" ", QString::SkipEmptyParts);
        if(valueSplit.count() == 4) color = QColor(valueSplit.at(0).toUInt(), valueSplit.at(1).toUInt(), valueSplit.at(2).toUInt(), valueSplit.at(3).toUInt());
        else if((colorName.startsWith(Application::colorsPrefix(0))) || (colorName.startsWith(Application::colorsPrefix(1)))) {
            if((!colorName.contains("_gui_")) && (((colorName.startsWith(Application::colorsPrefix(0))) && (Application::colorsPrefix() == Application::colorsPrefix(0))) || ((colorName.startsWith(Application::colorsPrefix(1))) && (Application::colorsPrefix() == Application::colorsPrefix(1))))) {
                color = Render::colors->value(colorName);
                colorName = colorName.remove(Application::colorsPrefix());
            }
            else
                continue;
        }
        else
            color = Render::colors->value(colorName);
        icon.fill(color);
        if(colorName != tr("Choose…"))  spin->addItem(QIcon(icon), colorName);
        else                            spin->addItem(colorName);
    }
}
void UiInspector::textureComboAdd(QComboBox *spin, QStringList values) {
    foreach(const QString & value, values) {
        if((value.isEmpty()) || (Render::textures->value(value)->loaded))
            spin->addItem(value);
    }
}

QTreeWidgetItem* UiInspector::getObjectRootItem() const {
    return ui->ccView->invisibleRootItem();
}
QPair< QList<NxGroup*>, UiRenderSelection> UiInspector::getSelectedCCObject() const {
    UiRenderSelection objects;
    QList<NxGroup*>  groups;
    foreach(const QTreeWidgetItem* item, ui->ccView->selectedItems())
        if(item->text(0) == tr("GROUP"))     groups .append((NxGroup*) item);
        else                                 objects.append((NxObject*)item);
    return qMakePair(groups, objects);
}

void UiInspector::showSpaceTab() {
    ui->tab->setCurrentIndex(1);
    ui->ssTabInfo->setCurrentIndex(1);
}
void UiInspector::showRessourcesTab(const QString &) {
    ui->tab->setCurrentIndex(1);
    ui->ssTabInfo->setTabEnabled(4, true);
    ui->ssTabInfo->setCurrentIndex(4);
}
void UiInspector::showConfigTab() {
    ui->tab->setCurrentIndex(3);
}

void UiInspector::clearCCselections() {
    ui->ccView->clearSelection();
}
