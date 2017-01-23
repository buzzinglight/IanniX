/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (https://www.buzzinglight.com)

    This file was written by Guillaume Jacquemin.

    IanniX is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "uieditor.h"
#include "ui_uieditor.h"

UiEditor::UiEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiEditor) {
    ui->setupUi(this);
    toolbarButton = 0;

    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.bottomRight().x() - rect().width(), 20);

    connect(ui->actionSave,        SIGNAL(triggered()), SLOT(save()));
    connect(ui->actionClose,       SIGNAL(triggered()), SLOT(close()));
    connect(ui->actionRefreshCode, SIGNAL(triggered()), SLOT(refresh()));

    ui->jsEditor->setTextWrapEnabled(false);
    ui->jsEditor->setLineNumbersVisible(true);
    ui->jsEditor->setCodeFoldingEnabled(true);
    ui->jsEditor->setBracketsMatchingEnabled(true);
    ui->jsEditor->setTabStopWidth(20);

    /*
    ui->jsEditor->setWindowTitle(QFileInfo(fileName).fileName());
    ui->jsEditor->setFrameShape(JSEdit::NoFrame);
    ui->jsEditor->setWordWrapMode(QTextOption::NoWrap);
    ui->jsEditor->setTabStopWidth(4);
    ui->jsEditor->resize(QApplication::desktop()->availableGeometry().size() / 2);
    */
    /*
    ui->jsEditor->setColor(JSEdit::Background,    QColor("#0C152B"));
    ui->jsEditor->setColor(JSEdit::Normal,        QColor("#FFFFFF"));
    ui->jsEditor->setColor(JSEdit::Comment,       QColor("#666666"));
    ui->jsEditor->setColor(JSEdit::Number,        QColor("#DBF76C"));
    ui->jsEditor->setColor(JSEdit::String,        QColor("#5ED363"));
    ui->jsEditor->setColor(JSEdit::Operator,      QColor("#FF7729"));
    ui->jsEditor->setColor(JSEdit::Identifier,    QColor("#FFFFFF"));
    ui->jsEditor->setColor(JSEdit::Keyword,       QColor("#FDE15D"));
    ui->jsEditor->setColor(JSEdit::BuiltIn,       QColor("#9CB6D4"));
    ui->jsEditor->setColor(JSEdit::Cursor,        QColor("#1E346B"));
    ui->jsEditor->setColor(JSEdit::Marker,        QColor("#DBF76C"));
    ui->jsEditor->setColor(JSEdit::BracketMatch,  QColor("#1AB0A6"));
    ui->jsEditor->setColor(JSEdit::BracketError,  QColor("#A82224"));
    ui->jsEditor->setColor(JSEdit::FoldIndicator, QColor("#555555"));
    */

    ui->splitter_2->setStretchFactor(0, 5);
    ui->splitter_2->setStretchFactor(1, 1);

    ui->statusBar->setVisible(false);
}

UiEditor::~UiEditor() {
    delete ui;
}

void UiEditor::setContent(const QString &content, bool raiseWindow) {
    //contents.replace("\t", "  ");
    quint16 cursorPos = ui->jsEditor->textCursor().position();
    quint16 scrollPos = ui->jsEditor->verticalScrollBar()->sliderPosition();
    ui->jsEditor->setPlainText(content);
    if((!isVisible()) && (raiseWindow)) {
        show();
        Application::current->getMainWindow()->raise();
    }
    QTextCursor cursor = ui->jsEditor->textCursor();
    cursor.setPosition(cursorPos);
    ui->jsEditor->setTextCursor(cursor);
    ui->jsEditor->verticalScrollBar()->setSliderPosition(scrollPos);
}
const QString UiEditor::getContent() {
    return ui->jsEditor->toPlainText();
}

void UiEditor::cursorChanged() {
    ui->help->scriptHelp(ui->jsEditor, QStringList() << "commands" << "javascript" << "values");
}

void UiEditor::scriptError(const QStringList &errors, qint16 line) {
    if(line < 0)
        ui->statusBar->setVisible(false);
    else {
        QString errorsMessage = "";
        foreach(const QString & error, errors)
            errorsMessage += error + " - ";

        QTextCursor cursorLine = QTextCursor(ui->jsEditor->document()->findBlockByLineNumber(line-1));
        ui->jsEditor->setTextCursor(cursorLine);
        ui->statusBar->setVisible(true);
        ui->statusBar->showMessage(errorsMessage);
        raise();
    }
}


void UiEditor::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::ActivationChange:
        refresh();
        break;
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UiEditor::showEvent(QShowEvent *e) {
    if(toolbarButton)
        toolbarButton->setChecked(true);
    QMainWindow::showEvent(e);
}
void UiEditor::closeEvent(QCloseEvent *e) {
    if(toolbarButton)
        toolbarButton->setChecked(false);
    QMainWindow::closeEvent(e);
}
