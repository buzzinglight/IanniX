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

QString NxDocument::serialize(UiRenderOptions *renderOptions) {
    QString retour = "";

    if(renderOptions) {
        retour += QString(COMMAND_ZOOM + " %1").arg(renderOptions->zoomValue) + COMMAND_END;
        retour += QString(COMMAND_SPEED + " %1").arg(renderOptions->timeFactor) + COMMAND_END;
        retour += QString(COMMAND_CENTER + " %1 %2").arg(-renderOptions->axisCenter.x()).arg(-renderOptions->axisCenter.y()) + COMMAND_END;
        ///CG/// Need to serialize rotation here?
    }

    //Browse documents
    QMapIterator<QString, NxGroup*> groupIterator(groups);
    while (groupIterator.hasNext()) {
        groupIterator.next();
        NxGroup *group = groupIterator.value();

        //Browse active/inactive objects
        for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {

            //Browse all types of objects
            for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                //Cursors are serialized with curves
                if(typeIterator != ObjectsTypeCursor) {
                    //Browse locals
                    QHashIterator< QRect, QHash<quint16, NxObject*> > localIterator(group->objects[activityIterator][typeIterator]);
                    while (localIterator.hasNext()) {
                        localIterator.next();
                        QRect local = localIterator.key();

                        //Browse objects
                        QHashIterator<quint16, NxObject*> objectIterator(group->objects[activityIterator][typeIterator].value(local));
                        while (objectIterator.hasNext()) {
                            objectIterator.next();
                            NxObject *object = objectIterator.value();

                            retour += object->serialize() + COMMAND_END;
                        }
                    }
                }
            }
        }
    }
    return retour;
}

void NxDocument::pushSnapshot() {
    setHasChanged(true);
    if(snapshotsIndex < snapshots.count())
        snapshots.replace(snapshotsIndex, serialize(0));
    else
        snapshots.append(serialize(0));
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
    snapshotsSpecial[snapshotId] = serialize(0);
    qDebug("Pushing snapshot %s", qPrintable(snapshotId));
}
void NxDocument::popSnapshot(const QString & snapshotId) {
    if(snapshotsSpecial.contains(snapshotId)) {
        qDebug("Poping snapshot %s", qPrintable(snapshotId));
        clear();
        QStringList snapshotCommands = snapshotsSpecial[snapshotId].split(COMMAND_END, QString::SkipEmptyParts);
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
        scriptFileContent.write(serialize(options).toLatin1());
        scriptFileContent.close();
        setHasChanged(false);
        return true;
    }
    return false;
}
