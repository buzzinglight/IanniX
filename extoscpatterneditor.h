#ifndef EXTOSCPATTERNEDITOR_H
#define EXTOSCPATTERNEDITOR_H

#include <QWidget>
#include <QPlainTextEdit>
#include "nxobject.h"

namespace Ui {
    class ExtOscPatternEditor;
}

class QPlainTextEditWithFocus : public QPlainTextEdit {
    Q_OBJECT

public:
    QPlainTextEditWithFocus(QWidget *parent = 0):
        QPlainTextEdit(parent) {}

signals:
    void focusOut();
    void focusIn();
protected:
    void focusOutEvent(QFocusEvent *) {    emit(focusOut());   }
    void focusInEvent(QFocusEvent *)  {    emit(focusIn());    }
};

class ExtOscPatternEditor : public QWidget{
    Q_OBJECT

public:
    explicit ExtOscPatternEditor(QWidget *parent = 0);
    ~ExtOscPatternEditor();

public:
    void addVariable(const QString & variable);
    const QString getPattern();

signals:
    void actionRouteRemove(ExtOscPatternEditor*);

public slots:
    void listDoubleClick();
    void editFocusOut();
    void actionRemove();

private:
    Ui::ExtOscPatternEditor *ui;
};

#endif // EXTOSCPATTERNEDITOR_H
