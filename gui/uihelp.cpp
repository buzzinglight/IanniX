/*
    This file is part of IanniX, a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2015 — IanniX Association

    Project Manager: Thierry Coduys (http://www.le-hub.org)
    Development:     Guillaume Jacquemin (http://www.buzzinglight.com)

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

#include "uihelp.h"
#include "ui_uihelp.h"

quint16 UiHelp::oscPort = 0;
UiHelp *UiHelp::statusHelpWidget = 0;

UiHelp::UiHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiHelp) {
    ui->setupUi(this);
    statusRefresh   = false;
    currentCombo    = 0;
    currentTextEdit = 0;
    visibility      = true;
    if(parent == 0) {
        statusHelpWidget = this;
        setWindowFlags(Qt::Tool);
        setWindowOpacity(0.9);
    }
    startTimer(150);
}

UiHelp::~UiHelp() {
    delete ui;
}
void UiHelp::timerEvent(QTimerEvent *) {
    if(statusRefresh)
        statusHelp();
    statusRefresh = false;
}

void UiHelp::showEvent(QShowEvent *e) {
    visibility = true;
    QWidget::showEvent(e);
    if(parent() == 0)
        statusRefresh = true;
}
void UiHelp::closeEvent(QCloseEvent *e) {
    visibility = false;
    QWidget::closeEvent(e);
}

void UiHelp::statusHelp(const QWidget *widget) {
    if((statusHelpWidget) && (widget))
        statusHelpWidget->statusHelp(widget->statusTip());
}
void UiHelp::statusHelp(QString _statusText) {
    if((isVisible()) && (!_statusText.isEmpty()) && (statusTextOld != _statusText)) {
        statusTextOld = _statusText;
        qint16 splitIndex = _statusText.indexOf("|");
        statusTexts.clear();
        if(splitIndex < 0)
            statusTexts.append(_statusText.replace("\\n", "<br/>"));
        else {
            statusTexts.append(_statusText.left(splitIndex).toUpper());
            statusTexts.append(_statusText.mid(splitIndex+1).replace("\\n ", "<br/>").replace("\\n", "<br/>"));
        }
        statusRefresh = true;
    }
}
void UiHelp::messageHelp(QString _messageText) {
    if(isVisible()) {
        _messageText = _messageText.replace("\\n", "<br/>");
        QStringList messageTextsArguments = _messageText.split(" ", QString::SkipEmptyParts);

        quint16 radix = 0;
        HelpInfo helpInfo = Help::getHelpFor(messageTextsArguments.first());
        QStringList syntaxes = helpInfo.syntax.split(" <");
        QString radixMessage;
        for(quint16 i = 0 ; i < syntaxes.count() ; i++) {
            if((syntaxes.at(i) == "<target>") || (syntaxes.at(i) == "point_index>"))
                radix = i+1;
        }
        for(quint16 i = 0 ; i < messageTextsArguments.count() ; i++) {
            if(i <= radix)   radixMessage += messageTextsArguments.at(i) + " ";
            else             break;
        }

        if((messageTexts.count()) && messageTexts.last().first.startsWith(radixMessage))
            messageTexts[messageTexts.count()-1] = qMakePair(_messageText, helpInfo);
        else
            messageTexts.append(qMakePair(_messageText, helpInfo));

        while(messageTexts.count() > 10) messageTexts.removeFirst();

        statusRefresh = true;
    }
}

void UiHelp::statusHelp() {
    if((isVisible()) && (statusTexts.count())) {
        QString html = "";

        html += "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
        html += "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">";
        html += "body   { background-color: #EEEDE8; font-family: Museo Sans, Museo Sans 500, Arial; font-size: 11px; padding: 11px }";
        html += ".code  { font-family:Monaco, Lucida Console, Monospace; font-size: 11px; }";
        html += ".bold  {  }";
        html += ".titre { font-size: 14px; }";
        html += ".description { background-color: rgb(227,226,220); }";
        html += ".syntax      { background-color: rgb(227,226,220); }";
        html += ".example     { background-color: rgb(227,226,220); }";
        html += ".snippet     { background-color: rgb(227,226,220); }";
        html += ".sstitre     { }";
        html += ".action      { font-size: 9px;}";
        html += ".category    { font-size: 16px;  }";
        html += ".hint        { color: rgb(115,159,89); }";
        html += "a	          { color: rgb(244,98,0); text-decoration: none; }";
        html += "a:hover      { text-decoration: underline; }";
        html += "</style></head><body><p>";

        if(statusTexts.count() == 2) html += QString("<p class='titre'>%1</p>").arg(statusTexts.first());
        else                         html += QString("<p class='titre'>%1</p>").arg(tr("INTERACTIVE HELP"));
        html += statusTexts.last();

        if(messageTexts.count()) {
            html += QString("<p class='titre'>%1</p>").arg(tr("GUI MESSAGES"));
            html += QString("<p class='sstitre'>%1</p>").arg(tr("You've just performed action through graphical user interface. Here are the messages you would have to use if you wanted to control IannIX from an other software ou interface."));

            html += QString("<p class='code snippet'>");
            for(quint16 i = 0 ; i < messageTexts.count() ; i++) {
                const QString messageText   = messageTexts.at(i).first.trimmed();
                QString messageDescription  = messageTexts.at(i).second.description.trimmed();
                QString messageSyntax       = messageTexts.at(i).second.syntax.trimmed();

                QStringList messageTextsArguments = messageText.split(" ", QString::SkipEmptyParts);

                QString messageVerbose = messageText;
                messageVerbose = messageVerbose.replace(" selection ", " <span class='hint'>&lt;object id or group&gt;</span> ");

                QString parametersMessage = "";
                quint16 messageTextsArgumentIndex = 0;
                bool paramOk = false;
                foreach(const QString &messageTextsArgument, messageTextsArguments) {
                    bool added = false;
                    if(!paramOk) {
                        bool ok = false;
                        messageTextsArgument.toDouble(&ok);
                        if(ok) {
                            if(((messageTextsArgumentIndex == 1) && (messageTextsArgumentIndex == (messageTextsArguments.count()-1))) ||
                                    ((messageTextsArgumentIndex == 2) && (messageTextsArgumentIndex == (messageTextsArguments.count()-1))) || (messageTextsArgumentIndex > 2)) {
                                parametersMessage += "$1 ";
                                added = true;
                                paramOk = true;
                            }
                        }
                    }
                    if(!added)
                        parametersMessage += messageTextsArgument + " ";
                    messageTextsArgumentIndex++;
                }
                parametersMessage.chop(1);

                QString codeMessage = "";
                foreach(const QString &messageTextsArgument, messageTextsArguments) {
                    bool ok = false;
                    messageTextsArgument.toDouble(&ok);
                    if(ok)  codeMessage += messageTextsArgument + ", ";
                    else    codeMessage += "\"" + messageTextsArgument + "\", ";
                }
                codeMessage.chop(2);

                html += QString("<span class='action'>%1</span><br/>").arg(messageDescription.replace("\n", "<br/>"));
                html += messageVerbose;
                html += "<span class='action'>";
                html += QString("  &nbsp;<a href='%1 | Copied to clipboard! You can now paste this message in a script (through run() function) or in an OSC message.'>&gt;&nbsp;Copy</a>").arg(messageText);
                html += QString(" /&nbsp;<a href='%1 | Copied to clipboard! Open a Max patch and choose Edit > Paste. It will automatically create objects to interact with IanniX.'>&gt;&nbsp;for MaxMSP</a>").arg(QString("{ \"boxes\" : [ { \"box\" : { \"maxclass\" : \"flonum\", \"outlettype\" : [ \"float\", \"bang\" ], \"fontname\" : \"Arial\", \"numinlets\" : 1, \"patching_rect\" : [ 37.0, 58.0, 50.0, 20.0 ], \"fontsize\" : 12.0, \"id\" : \"obj-5\", \"numoutlets\" : 2, \"parameter_enable\" : 0 }  } , { \"box\" : { \"maxclass\" : \"message\", \"text\" : \"/iannix/%1\", \"outlettype\" : [ \"\" ], \"fontname\" : \"Arial\", \"numinlets\" : 2, \"patching_rect\" : [ 37.0, 85.0, 95.0, 18.0 ], \"fontsize\" : 12.0, \"id\" : \"obj-3\", \"numoutlets\" : 1 }  } , { \"box\" : { \"maxclass\" : \"newobj\", \"text\" : \"udpsend 127.0.0.1 %2\", \"fontname\" : \"Arial\", \"numinlets\" : 1, \"patching_rect\" : [ 37.0, 110.0, 140.0, 20.0 ], \"fontsize\" : 12.0, \"id\" : \"obj-1\", \"numoutlets\" : 0 }  }  ], \"lines\" : [ { \"patchline\" : { \"source\" : [ \"obj-5\", 0 ], \"destination\" : [ \"obj-3\", 0 ], \"hidden\" : 0, \"disabled\" : 0 }  } , { \"patchline\" : { \"source\" : [ \"obj-3\", 0 ], \"destination\" : [ \"obj-1\", 0 ], \"hidden\" : 0, \"disabled\" : 0 }  }  ], \"appversion\" : { \"major\" : 6, \"minor\" : 0, \"revision\" : 8 }  } ").arg(parametersMessage).arg(oscPort));
                html += QString(" /&nbsp;<a href='%1 | Copied to clipboard! Open a Processing sketch with IanniX class (provided with IanniX). Paste the code where you want to interact with IanniX.'>&gt;&nbsp;for Processing</a>").arg(QString("iannix.send(%1);").arg(codeMessage));
                html += "</span><br/>";
                html += QString("<span class='action'>%1 %2</span><br/>").arg(messageTexts.at(i).second.keyword).arg(messageSyntax.replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>"));
                html += "<br/>";
            }
            html += QString("</p>");
        }

        html += "</body></html>";
        qreal currenScrollValue = ui->html->verticalScrollBar()->value() / (qreal)ui->html->verticalScrollBar()->maximum();
        ui->html->setHtml(html);
        ui->html->verticalScrollBar()->setValue(currenScrollValue * ui->html->verticalScrollBar()->maximum());
    }
}




void UiHelp::scriptHelp(QPlainTextEdit *textEdit, const QStringList &lookCategories) {
    currentTextEdit = textEdit;
    currentCombo = 0;
    scriptHelp(currentTextEdit->textCursor().block().text(), lookCategories);
}
void UiHelp::scriptHelp(QComboBox *comboBox, const QStringList &lookCategories) {
    currentTextEdit = 0;
    currentCombo = comboBox;
    scriptHelp(currentCombo->currentText(), lookCategories);
}
void UiHelp::scriptHelp(const QString &looking, const QStringList &lookCategories) {
    if(isVisible()) {
        QString html = "";

        html += "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
        html += "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">";
        html += "body   { background-color: #EEEDE8; font-family: Museo Sans, Museo Sans 500, Arial; font-size: 11px; }";
        html += ".code  { font-family:Monaco, Lucida Console, Monospace; font-size: 11px; }";
        html += ".bold  {  }";
        html += ".titre { font-size: 14px; }";
        html += ".description { background-color: rgb(227,226,220); }";
        html += ".syntax      { background-color: rgb(227,226,220); }";
        html += ".example     { background-color: rgb(227,226,220); }";
        html += ".snippet     { background-color: rgb(227,226,220); }";
        html += ".sstitre     { }";
        html += ".action      { font-size: 9px;}";
        html += ".category    { font-size: 16px;  }";
        html += ".hint        { color: rgb(115,159,89); }";
        html += "a	          { color: rgb(244,98,0); text-decoration: none; }";
        html += "a:hover      { text-decoration: underline; }";
        html += "</style></head><body><p>";

        bool foundInfo = false;
        QList<QPair<QString,QString> > htmlCategories;
        for(quint16 i = 0 ; i < 3 ; i++) {
            foreach(const QString &category, lookCategories) {
                QString htmlCategory = "";
                HelpCategory helpCategory = Help::categories.value(category);
                foreach(const HelpInfo &info, helpCategory.infos) {
                    if(((i == 0) && (looking.toLower().contains(info.keyword.toLower()))) || ((i == 1) && (looking.toLower().contains(info.keyword.toLower().left(5)))) || ((i == 2) && (looking.toLower().contains(info.keyword.toLower().left(3))))) {
                        QString keyword = info.keyword, title = info.title.toUpper(), syntax = info.syntax, description = info.description.trimmed();
                        if(category == "commands")
                            syntax = keyword + " " + syntax;
                        syntax      = syntax.     replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>");
                        description = description.replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>");

                        if(!description.isEmpty()) {
                            htmlCategory += QString("<p class='titre'><span class='code'>%1</span>&nbsp;&mdash;&nbsp;<span class='bold'>%2</span></p>").arg(keyword).arg(title);
                            if(!description.isEmpty())
                                htmlCategory += QString("<span class='sstitre'>%1</span><table width='100%'><tr><td></td><td width='97%' class='description'><span             >%2</span></td></tr></table><br/><br/>").arg(title).arg(description);
                            if(!syntax.isEmpty())
                                htmlCategory += QString("<span class='sstitre'>%3</span><table width='100%'><tr><td></td><td width='97%' class='syntax'     ><span class='code'>%1</span></td></tr><tr><td></td><td align='right'><a class='action' href='%2'>%4</a></td></tr></table><br/><br/>").arg(syntax).arg(info.keyword + " " + info.syntax).arg(tr("SYNTAX")).arg(tr("IMPLEMENT IN SCRIPT"));
                            htmlCategory += QString("<hr/>");
                        }
                        else {
                            if(syntax.isEmpty())
                                syntax = keyword;
                            htmlCategory += QString("<p><a href='%3'><span class='code'>%1</span>&nbsp;&mdash;&nbsp;<span class='bold'>%2</span></a></p>").arg(keyword).arg(title).arg(syntax);
                        }
                        foundInfo = true;
                    }
                }
                if(!htmlCategory.isEmpty())
                    htmlCategories << qMakePair(QString("<center><p class='category'>&mdash;&nbsp;&nbsp;%1&nbsp;&nbsp;&mdash;</p></center>").arg(helpCategory.category.toUpper()), htmlCategory);
            }
            if(foundInfo)
                break;
        }
        if(!foundInfo) {
            foreach(const QString &category, lookCategories) {
                QString htmlCategory;
                HelpCategory helpCategory = Help::categories.value(category);
                foreach(const HelpInfo &info, helpCategory.infos) {
                    QString keyword = info.keyword, title = info.title.toUpper(), syntax = info.syntax;
                    if(syntax.isEmpty())
                        syntax = keyword;
                    htmlCategory += QString("<p><a href='%3'><span class='code'>%1</span>&nbsp;&mdash;&nbsp;<span class='bold'>%2</span></a></p>").arg(keyword).arg(title).arg(syntax);
                }
                if(!htmlCategory.isEmpty())
                    htmlCategories << qMakePair(QString("<center><p class='category'>&mdash;&nbsp;&nbsp;%1&nbsp;&nbsp;&mdash;</p></center>").arg(helpCategory.category.toUpper()), htmlCategory);
            }
        }
        for(quint16 i = 0 ; i < htmlCategories.count() ; i++) {
            if(htmlCategories.count() > 1)
                html += htmlCategories.at(i).first;
            html += htmlCategories.at(i).second;
        }

        html += "</body></html>";
        ui->html->setHtml(html);
    }
}


void UiHelp::linkClicked(QUrl url) {
    QStringList urls = url.toString().split(" | ");

    if(urls.count()) {
        if((currentTextEdit) || (currentCombo)) {
            if(currentTextEdit)
                currentTextEdit->textCursor().insertText(urls.first());
            if(currentCombo)
                currentCombo->setEditText(currentCombo->currentText() + urls.first());
        }
        else
            QApplication::clipboard()->setText(urls.first());

        if(urls.count() > 1)
            (new UiMessageBox())->display(tr("Help Center"), urls.at(1));
    }
}
