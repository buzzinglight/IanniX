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
            if(!messagePatterns.contains(messagePattern))
                messagePatterns.append(messagePattern);
        }
    }
    foreach(const QString & messagePattern, messagePatterns) {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->listWidget);
        item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setText(0, messagePattern);
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

const QVector< QVector<QByteArray> > ExtOscPatternAsk::getMessagePatterns() const {
    QVector< QVector<QByteArray> > messagePatterns;
    for(quint16 index = 0 ; index < ui->listWidget->topLevelItemCount() ; index++) {
        QVector<QByteArray> messagePatternsItems;
        QStringList messagePatternsItemsStr = ui->listWidget->topLevelItem(index)->text(0).split(" " , QString::SkipEmptyParts);
        foreach(const QString & messagePatternsItemStr, messagePatternsItemsStr)
            messagePatternsItems.append(qPrintable(messagePatternsItemStr));
        messagePatterns.append(messagePatternsItems);
    }

    return messagePatterns;
}

void ExtOscPatternAsk::actionAddMessage() {
    QSettings settings;
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->listWidget);
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    bool isTrigger = false;
    bool isCursor = false;
    foreach(NxObject *object, *objects) {
        if(object->getType() == ObjectsTypeCursor)
            isCursor = true;
        else if(object->getType() == ObjectsTypeTrigger)
            isTrigger = true;
    }
    if((isCursor) && (!isTrigger))
        item->setText(0, settings.value("defaultMessageCursor").toString());
    else if((!isCursor) && (isTrigger))
        item->setText(0, settings.value("defaultMessageTrigger").toString());
    else
        item->setText(0, settings.value("defaultMessage").toString());
}

void ExtOscPatternAsk::actionRemoveMessage() {
    if(ui->listWidget->currentItem())
        delete ui->listWidget->currentItem();
}
