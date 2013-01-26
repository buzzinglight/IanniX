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

#include "nxdocument.h"

NxDocument::NxDocument(NxObjectFactoryInterface *_factory, QFileInfo _scriptFile, QTreeWidgetItem *parentList) :
    ExtScriptManager(_factory, _scriptFile, parentList) {
    setCurrentObject(0);
    setCurrentGroup(0);
    currentCurve = 0;
    snapshotsIndex = 0;
    isLoaded = false;
    if(scriptFile.isFile())
        setId(qPrintable(scriptFile.baseName()));
    setHasChanged(false);
}

QString NxDocument::serialize(UiRenderOptions *renderOptions, bool hasAScript) {
    QString retour = "";
    QString prefix = "", postfix = COMMAND_END;
    if(hasAScript) {
        prefix = "run(\"";
        postfix =  "\");" + COMMAND_END;
    }

    if(renderOptions) {
        retour += prefix + QString(COMMAND_ZOOM + " %1").arg(renderOptions->zoomValue) + postfix;
        retour += prefix + QString(COMMAND_SPEED + " %1").arg(renderOptions->timeFactor) + postfix;
        retour += prefix + QString(COMMAND_CENTER + " %1 %2").arg(-renderOptions->axisCenter.x()).arg(-renderOptions->axisCenter.y()) + postfix;
        retour += prefix + QString(COMMAND_ROTATE + " %1 %2 %3").arg(renderOptions->rotationDest.x()).arg(renderOptions->rotationDest.y()).arg(renderOptions->rotationDest.z()) + postfix;
        retour += prefix + QString(COMMAND_AUTOSIZE + " %1").arg(renderOptions->triggerAutosize) + postfix;
        foreach(const QString &command, registredTextures)
            retour += prefix + command + postfix;
        foreach(const QString &command, registredColors)
            retour += prefix + command + postfix;
    }

    //Browse documents
    foreach(NxGroup *group, groups) {
        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {

            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                //Browse objects
                foreach(NxObject *object, group->objects[activityIterator][typeIterator]) {
                    if(((typeIterator == ObjectsTypeCursor) && (((NxCursor*)object)->getCurve() == 0)) || (typeIterator == ObjectsTypeCurve) || (typeIterator == ObjectsTypeTrigger))
                        retour += object->serialize(hasAScript) + COMMAND_END;
                }
            }
        }
    }

    foreach(NxGroup *group, groups) {
        if(group->checkState(0) == Qt::Unchecked)
            retour += COMMAND_MUTE + QString(" %1 0").arg(group->getId()) + COMMAND_END;
        if(group->checkState(1) == Qt::Checked)
            retour += COMMAND_SOLO + QString(" %1 1").arg(group->getId()) + COMMAND_END;
    }
    foreach(NxObject *object, objects) {
        if(object->checkState(1) == Qt::Unchecked)
            retour += COMMAND_MUTE + QString(" %1 0").arg(object->getId()) + COMMAND_END;
        if(object->checkState(2) == Qt::Checked)
            retour += COMMAND_SOLO + QString(" %1 1").arg(object->getId()) + COMMAND_END;
    }
    return retour;
}

void NxDocument::pushSnapshot() {
    setHasChanged(true);
    if(snapshotsIndex < snapshots.count())
        snapshots.replace(snapshotsIndex, serialize(0, false));
    else
        snapshots.append(serialize(0, false));
    //qDebug("PUSH snapshot %d", snapshotsIndex);
    snapshotsIndex++;
}
void NxDocument::popSnapshot(bool revert) {
    bool canDo = false;
    if((revert) && (snapshotsIndex < snapshots.count()-1)) {
        snapshotsIndex++;
        canDo = true;
    }
    else if ((!revert) && (snapshotsIndex > 0) && (snapshotsIndex == snapshots.count())) {
        pushSnapshot();
        snapshotsIndex--;
        snapshotsIndex--;
        canDo = true;
    }
    else if ((!revert) && (snapshotsIndex > 0)) {
        snapshotsIndex--;
        canDo = true;
    }
    if(canDo) {
        clear();
        //qDebug("POP  snapshot %d", snapshotsIndex);
        QString snapshot = snapshots.at(snapshotsIndex);
        //snapshots.removeLast();
        QStringList snapshotCommands = snapshot.split(COMMAND_END, QString::SkipEmptyParts);
        foreach(const QString & command, snapshotCommands)
            factory->execute(command);
    }
}

void NxDocument::pushSnapshot(const QString & snapshotId) {
    snapshotsSpecial[snapshotId] = serialize(0, false);
    qDebug("Pushing snapshot %s", qPrintable(snapshotId));
}
void NxDocument::popSnapshot(const QString & snapshotId) {
    if(snapshotsSpecial.contains(snapshotId)) {
        qDebug("Poping snapshot %s", qPrintable(snapshotId));
        clear();
        QStringList snapshotCommands = snapshotsSpecial.value(snapshotId).split(COMMAND_END, QString::SkipEmptyParts);
        foreach(const QString & command, snapshotCommands)
            factory->execute(command);
    }
}



void NxDocument::load() {
    if(!isLoaded) {
        clear();
        parseScript();
        isLoaded = true;
    }
}

bool NxDocument::save(UiRenderOptions *options) {
    QFile scriptFileContent(getScriptFile().absoluteFilePath());
    if(scriptFileContent.open(QIODevice::WriteOnly | QIODevice::Text)) {
        //Write file
        scriptFileContent.write(serialize(options, false).toLatin1());
        scriptFileContent.close();
        setHasChanged(false);
        return true;
    }
    return false;
}
