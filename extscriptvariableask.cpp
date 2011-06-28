#include "extscriptvariableask.h"
#include "ui_extscriptvariableask.h"

ExtScriptVariableAsk::ExtScriptVariableAsk(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ExtScriptVariableAsk) {
    ui->setupUi(this);
    ui->variablesList->setColumnWidth(0, 165);
    ui->variablesList->setColumnWidth(1, 100);
}

ExtScriptVariableAsk::~ExtScriptVariableAsk() {
    delete ui;
}

void ExtScriptVariableAsk::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void ExtScriptVariableAsk::clear() {
    ui->variablesList->clear();
}

void ExtScriptVariableAsk::ask(const QString & group, const QString & prompt, const QString & value, const QString & def) {
    QTreeWidgetItem *topLevel = 0;
    for(quint16 index = 0 ; index < ui->variablesList->topLevelItemCount() ; index++) {
        if(ui->variablesList->topLevelItem(index)->text(0) == group) {
            topLevel = ui->variablesList->topLevelItem(index);
            break;
        }
    }

    if(!topLevel) {
        topLevel = new QTreeWidgetItem(ui->variablesList);
        topLevel->setText(0, group);
    }
    ExtScriptVariable *variable = new ExtScriptVariable(topLevel);
    variable->setInfos(group, prompt, value, def);
    variables.append(variable);
}
void ExtScriptVariableAsk::meta(const QString & _title) {
    title = _title;
}

const QList<ExtScriptVariable*> & ExtScriptVariableAsk::ask() {
    if(variables.count() > 0) {
        ui->variablesList->expandAll();
        setWindowTitle(title);
        exec();
        foreach(ExtScriptVariable *variable, variables)
            variable->setDef(variable->text(1));
    }
    else
        accept();
    return variables;
}
