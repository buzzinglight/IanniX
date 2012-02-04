
#include "nxobject.h"

NxObject::NxObject(NxObjectFactoryInterface *parent, QTreeWidgetItem *ccParentItem, UiRenderOptions *_renderOptions) :
    QObject(parent), QTreeWidgetItem(ccParentItem) {
    renderOptions = _renderOptions;
    factory = parent;
    documentId.clear();
    groupId.clear();
    id = 0;
    active = ObjectsActivityInactive;
    pos = NxPoint();
    parentObject = 0;
    selectedHover = false;
    selected = false;
    setMessageTimeInterval(1);
    isDrag = false;
    performCollision = false;
    setMessageId(0);
}

void NxObject::setMessagePatterns(const QString & messagePatternsStr) {
    messagePatterns.clear();
    messageLabel.clear();
    performCollision = false;

    QString messagePatternsStrTemp = messagePatternsStr;

    QVector<QByteArray> messagePattern;
    QString messagePatternItem = "";
    QString messageLabelItem = "";
    quint16 messagePatternItemJS = 0;
    bool first = true;

    messagePatternsStrTemp.append(' '); //Pad with a space to simplify end-string handling

    for(quint16 messagePatternsStrIndex = 0 ; messagePatternsStrIndex < messagePatternsStrTemp.count() ; messagePatternsStrIndex++) {

        QChar messagePatternsStrChar = messagePatternsStrTemp.at(messagePatternsStrIndex);
        if((!messagePatternItemJS) && (messagePatternsStrChar == ' ')) {
            if(messagePatternItem.count() > 0)
                messagePattern.append(qPrintable(messagePatternItem));

            messageLabelItem.append(qPrintable(QString(messagePatternItem + " ")));
            if(messagePatternItem.contains("collision_"))
                performCollision = true;
            messagePatternItem = "";
        }
        else if((messagePatternItemJS) && (messagePatternsStrChar == '}')) {
            messagePatternItemJS--;
            if(!messagePatternItemJS) {
                if(messagePatternItem.count() > 0) {
                    messagePattern.append(qPrintable(QString("{" + messagePatternItem + "}")));
                    messageLabelItem.append(qPrintable(QString("{" + messagePatternItem + "}")));
                    if(messagePatternItem.contains("collision_"))
                        performCollision = true;
                }
                messagePatternItem = "";
            }
            else
                messagePatternItem += messagePatternsStrChar;
        }
        else if((!messagePatternItemJS) && (messagePatternsStrChar == ',')) {
            if(messagePatternItem.count() > 0) {
                if(first) {
                    quint16 interval = messagePatternItem.toUInt();
                    if(interval > 0) {
                        //qDebug("-- %d -- ", interval);
                        setMessageTimeInterval(interval);
                    }
                }
                else {
                    messagePattern.append(qPrintable(messagePatternItem));
                    messageLabel.append(messageLabelItem);
                }
            }
            first = false;
            if(messagePattern.count() > 0)
                messagePatterns.append(messagePattern);
            messagePatternItem = "";
            messagePattern.clear();
            messageLabelItem = "";
            messagePatternItemJS = 0;
        }
        else if(messagePatternsStrChar == '{') {
            if(!messagePatternItemJS)
                messagePatternItem = "";
            else
                messagePatternItem += messagePatternsStrChar;
            messagePatternItemJS++;
        }
        else {
            messagePatternItem += messagePatternsStrChar;
        }
    }

    if (messagePatternItem.count() > 0) {   //Should only get here if curly brackets are unbalanced to the left
        messageLabelItem.append(qPrintable(QString("{" + messagePatternItem)));
        messagePattern.append(qPrintable(QString("{" + messagePatternItem)));
    }

    if (messageLabelItem.count() > 0)
        messageLabel.append(qPrintable(messageLabelItem));

    if(messagePattern.count() > 0)
        messagePatterns.append(messagePattern);

    /*
    foreach(const QVector<QByteArray> & m1, messagePatterns) {
        qDebug("----");
        foreach(const QByteArray & m2, m1)
            qDebug("%s", qPrintable(QString(m2)));
        qDebug("----");
    }
    */
}

QVector< QVector<QByteArray> > NxObject::parseMessagesPattern(const QString & messagePatternsStr, quint16 *messageInterval) {
    QVector< QVector<QByteArray> > messagePatterns;

    QVector<QByteArray> messagePattern;
    QString messagePatternItem = "";
    quint16 messagePatternItemJS = 0;
    bool first = true;
    for(quint16 messagePatternsStrIndex = 0 ; messagePatternsStrIndex < messagePatternsStr.count() ; messagePatternsStrIndex++) {
        QChar messagePatternsStrChar = messagePatternsStr.at(messagePatternsStrIndex);
        if((!messagePatternItemJS) && (messagePatternsStrChar == ' ')) {
            if(messagePatternItem.count() > 0)
                messagePattern.append(qPrintable(messagePatternItem));
            messagePatternItem = "";
        }
        else if((messagePatternItemJS) && (messagePatternsStrChar == '}')) {
            messagePatternItemJS--;
            if(!messagePatternItemJS) {
                if(messagePatternItem.count() > 0)
                    messagePattern.append(qPrintable(QString("{" + messagePatternItem + "}")));
                messagePatternItem = "";
            }
            else
                messagePatternItem += messagePatternsStrChar;
        }
        else if((!messagePatternItemJS) && (messagePatternsStrChar == ',')) {
            if(messagePatternItem.count() > 0) {
                if(first) {
                    quint16 interval = messagePatternItem.toUInt();
                    if((interval > 0) && (messageInterval))
                        *messageInterval = interval;
                }
                else
                    messagePattern.append(qPrintable(messagePatternItem));
            }
            first = false;
            if(messagePattern.count() > 0)
                messagePatterns.append(messagePattern);
            messagePatternItem = "";
            messagePattern.clear();
        }
        else if(messagePatternsStrChar == '{') {
            if(!messagePatternItemJS)
                messagePatternItem = "";
            else
                messagePatternItem += messagePatternsStrChar;
            messagePatternItemJS++;
        }
        else {
            messagePatternItem += messagePatternsStrChar;
        }
    }
    if(messagePatternItem.count() > 0)
        messagePattern.append(qPrintable(messagePatternItem));
    if(messagePattern.count() > 0)
        messagePatterns.append(messagePattern);

    return messagePatterns;
}
