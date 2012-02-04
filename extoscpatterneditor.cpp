#include "extoscpatterneditor.h"
#include "ui_extoscpatterneditor.h"

ExtOscPatternEditor::ExtOscPatternEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtOscPatternEditor) {
    ui->setupUi(this);
    ui->patternList->clear();
    ui->patternEdit->setPlainText("");
}

ExtOscPatternEditor::~ExtOscPatternEditor() {
    delete ui;
}


void ExtOscPatternEditor::addVariable(const QString &variable) {
    QListWidgetItem *item = new QListWidgetItem(variable, ui->patternList);
    item->setFlags(Qt::ItemIsSelectable | /*Qt::ItemIsEditable | */Qt::ItemIsEnabled);
}

const QString ExtOscPatternEditor::getPattern() {
    QString messagePattern = "";
    for(quint16 index = 0 ; index < ui->patternList->count() ; index++)
        messagePattern += ui->patternList->item(index)->text() + " ";
    return messagePattern;
}

void ExtOscPatternEditor::listDoubleClick() {
    ui->patternEdit->setPlainText(getPattern());
    ui->stackedWidget->setCurrentIndex(1);
}
void ExtOscPatternEditor::editFocusOut() {
    if(ui->patternEdit->toPlainText() != "") {
        ui->patternList->clear();
        QVector< QVector<QByteArray > > messagePatternItemsList = NxObject::parseMessagesPattern(ui->patternEdit->toPlainText().replace("\t", " "));
        foreach(const QVector<QByteArray > & messagePatternItems, messagePatternItemsList) {
            foreach(const QByteArray & messagePatternItem, messagePatternItems)
                addVariable(messagePatternItem);
        }
    }
    ui->stackedWidget->setCurrentIndex(0);
}
void ExtOscPatternEditor::actionRemove() {
    emit(actionRouteRemove(this));
}
