#ifndef EXTSCRIPTVARIABLEASK_H
#define EXTSCRIPTVARIABLEASK_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
    class ExtScriptVariableAsk;
}


class ExtScriptVariable : public QTreeWidgetItem {

public:
    ExtScriptVariable(QTreeWidgetItem *topLevel) : QTreeWidgetItem(topLevel) {
        setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled);
    }

private:
    QString group, prompt, value, def;
public:
    void setInfos(const QString & _group, const QString & _prompt, const QString & _value, const QString & _def) {
        group = _group;
        prompt = _prompt;
        value = _value;
        def = _def;
        setText(0, prompt);
        setText(1, def);
    }
    inline const QString & getGroup() const  { return group; }
    inline const QString & getPrompt() const { return prompt; }
    inline const QString & getValue() const  { return value; }
    inline const QString & getDef() const    { return def; }
    inline void setDef(const QString & _def) { def = _def; }
};


class ExtScriptVariableAsk : public QDialog {
    Q_OBJECT

public:
    explicit ExtScriptVariableAsk(QWidget *parent = 0);
    ~ExtScriptVariableAsk();

protected:
    void changeEvent(QEvent *e);

private:
    QList<ExtScriptVariable*> variables;
    QString title;
public:
    const QList<ExtScriptVariable*> & ask();
    inline const QString & getTitle() {
        return title;
    }
    void clear();
    void ask(const QString & group, const QString & prompt, const QString & value, const QString & def);
    void meta(const QString & _title);

private:
    Ui::ExtScriptVariableAsk *ui;
};

#endif // EXTSCRIPTVARIABLEASK_H
