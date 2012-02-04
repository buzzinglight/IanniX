#include "extoscpatternask.h"
#include "ui_extoscpatternask.h"

ExtOscPatternAsk::ExtOscPatternAsk(QWidget *parent, QList<NxObject*> *_objects) :
    QDialog(parent),
    ui(new Ui::ExtOscPatternAsk) {
    ui->setupUi(this);
    objects = _objects;
    QStringList messagePatterns;
    onlyCurves = true;
    foreach(NxObject *object, *objects) {
        if(object->getType() != ObjectsTypeCurve)
            onlyCurves = false;
        foreach(const QVector<QByteArray> & messagePatternItems, object->getMessagePatterns()) {
            QString messagePattern;
            foreach(const QByteArray & messagePatternItem, messagePatternItems)
                messagePattern += messagePatternItem + " ";
            messagePattern = messagePattern.trimmed();
            if(!messagePatterns.contains(messagePattern)) {
                messagePatterns.append(messagePattern);

                ExtOscPatternEditor *patternEditor = new ExtOscPatternEditor(this);
                connect(patternEditor, SIGNAL(actionRouteRemove(ExtOscPatternEditor*)), SLOT(actionRemoveMessage(ExtOscPatternEditor*)));
                foreach(const QByteArray & messagePatternItem, messagePatternItems)
                    patternEditor->addVariable(messagePatternItem);
                ui->patternListsLayout->addWidget(patternEditor);
                patternLists.append(patternEditor);
            }
        }
    }
}

ExtOscPatternAsk::~ExtOscPatternAsk() {
    delete ui;
}

void ExtOscPatternAsk::changeEvent(QEvent *e) {
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void ExtOscPatternAsk::mousePressEvent(QMouseEvent *) {
    foreach(ExtOscPatternEditor *patternList, patternLists)
        patternList->editFocusOut();
}

const QString ExtOscPatternAsk::getMessagePatterns() const {
    QString messagePattern = "";
    foreach(ExtOscPatternEditor *patternList, patternLists)
        messagePattern += ", " + patternList->getPattern();
    if(messagePattern.count() > 0)
        messagePattern = "0" + messagePattern;
    return messagePattern;
}

void ExtOscPatternAsk::actionAddMessage() {
    QSettings settings;
    bool isTrigger = false;
    bool isCursor = false;
    foreach(NxObject *object, *objects) {
        if(object->getType() == ObjectsTypeCursor)
            isCursor = true;
        else if(object->getType() == ObjectsTypeTrigger)
            isTrigger = true;
    }
    QString messagePatternItem = "";
    if((isCursor) && (!isTrigger))
        messagePatternItem = settings.value("defaultMessageCursor").toString();
    else if((!isCursor) && (isTrigger))
        messagePatternItem = settings.value("defaultMessageTrigger").toString();
    else
        messagePatternItem = settings.value("defaultMessage").toString();


    QVector< QVector<QByteArray > > messagePatternItemsList = NxObject::parseMessagesPattern(messagePatternItem);
    foreach(const QVector<QByteArray > & messagePatternItems, messagePatternItemsList) {
        ExtOscPatternEditor *patternEditor = new ExtOscPatternEditor(this);
        connect(patternEditor, SIGNAL(actionRouteRemove(ExtOscPatternEditor*)), SLOT(actionRemoveMessage(ExtOscPatternEditor*)));
        foreach(const QByteArray & messagePatternItem, messagePatternItems)
            patternEditor->addVariable(messagePatternItem);
        ui->patternListsLayout->addWidget(patternEditor);
        patternLists.append(patternEditor);
    }
}

void ExtOscPatternAsk::actionRemoveMessage(ExtOscPatternEditor *editor) {
    if(editor) {
        patternLists.removeOne(editor);
        delete editor;
    }
}
