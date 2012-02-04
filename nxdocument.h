#ifndef NXDOCUMENT_H
#define NXDOCUMENT_H

#include <QObject>
#include "nxgroup.h"
#include "extscriptmanager.h"
#include "uirenderoptions.h"

class NxDocument : public ExtScriptManager, public NxObjectDispatchProperty {
    Q_OBJECT

private:
    bool isLoaded;
    QList<QString> snapshots;
    quint16 snapshotsIndex;
    QMap<QString,QString> snapshotsSpecial;
public:
    explicit NxDocument(NxObjectFactoryInterface *_factory, QFileInfo _scriptFile, QTreeWidgetItem *parentList);
    inline void dispatchProperty(const QString & property, const QVariant & value) {
        //Browse groups
        QMapIterator<QString, NxGroup*> groupIterator(groups);
        while (groupIterator.hasNext()) {
            groupIterator.next();
            NxGroup *group = groupIterator.value();
            group->dispatchProperty(property, value);
        }
    }
    inline const QVariant getProperty(const QString &) const {
        return id;
    }
    inline quint8 getType() const {
        return ObjectsTypeDocument;
    }
    inline const QString getTypeStr() const {
        return "document";
    }
    inline const NxRect getBoundingRect() const {
        NxRect boundingRect;

        //Browse groups
        QMapIterator<QString, NxGroup*> groupIterator(groups);
        while (groupIterator.hasNext()) {
            groupIterator.next();
            NxGroup *group = groupIterator.value();
            boundingRect = boundingRect.united(group->getBoundingRect());
        }

        return boundingRect;
    }

    inline void clear() {
        QStringList commands;
        foreach(NxObject *object, objects)
            commands << COMMAND_REMOVE + " " + QString().setNum(object->getId());
        foreach(const QString & command, commands)
            execute(command);
        groups.clear();
    }
    QString serialize(UiRenderOptions *options);
    void pushSnapshot();
    void popSnapshot(bool revert=false);
    void pushSnapshot(const QString & snapshotId);
    void popSnapshot(const QString & snapshotId);
    void load();
    bool save(UiRenderOptions *options);

public:
    QMap<QString, NxGroup*> groups;
    QHash<quint16, NxObject*> objects;

private:
    NxObject *currentObject;
    NxGroup *currentGroup;
    NxCurve *currentCurve;
protected:
    QString id;
public slots:
    inline void setId(const QString & _id) {
        id = _id;
        updateTitle();
    }
    inline const QString & getId() const {
        return id;
    }
    inline NxObject* getCurrentObject() const {
        return currentObject;
    }
    inline void setCurrentObject(NxObject *_currentObject) {
        currentObject = _currentObject;
        if((currentObject) && (currentObject->getType() == ObjectsTypeCurve))
            currentCurve = (NxCurve*)currentObject;
    }
    inline NxCurve* getCurrentCurve() const {
        return currentCurve;
    }
    inline NxGroup* getCurrentGroup() const {
        return currentGroup;
    }
    inline void setCurrentGroup(NxGroup *_currentGroup) {
        currentGroup = _currentGroup;
    }

public:
    inline NxObject* getObject(quint16 id) const {
        if(objects.contains(id))
            return objects.value(id);
        else
            return 0;
    }
    inline quint16 nextAvailableId() const {
        //return objects.count();
        quint16 nextId = 0;
        for(quint16 index = 0 ; index < objects.count() ; index++)
            if(objects.keys().at(index) > nextId)
                nextId = objects.keys().at(index);
        return nextId+1;
    }
    inline bool getHasChanged() const {
        return hasChanged;
    }


signals:

public slots:

};

#endif // NXDOCUMENT_H
