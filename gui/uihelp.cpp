#include "uihelp.h"
#include "ui_uihelp.h"

UiHelp::UiHelp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiHelp) {
    ui->setupUi(this);
    currentTextEdit = 0;
}

UiHelp::~UiHelp() {
    delete ui;
}

void UiHelp::display(QPlainTextEdit *textEdit, const QStringList &lookCategories) {
    currentTextEdit = textEdit;
    currentCombo = 0;
    display(currentTextEdit->textCursor().block().text(), lookCategories);
}
void UiHelp::display(QComboBox *comboBox, const QStringList &lookCategories) {
    currentTextEdit = 0;
    currentCombo = comboBox;
    display(currentCombo->currentText(), lookCategories);
}
void UiHelp::display(const QString &looking, const QStringList &lookCategories) {
    if(isVisible()) {
        QString html = "";

        html += "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
        html += "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">";
        html += "body   { background-color: #EEEDE8; font-family: Arial; font-size: 11px; }";
        html += ".code  { font-family:Monaco, Lucida Console, Monospace; font-size: 11px; }";
        html += ".bold  { font-weight: bold; }";
        html += ".titre { font-size: 14px; }";
        html += ".description { background-color: rgb(227,226,220); }";
        html += ".syntax      { background-color: rgb(227,226,220); }";
        html += ".example     { background-color: rgb(227,226,220); }";
        html += ".snippet     { background-color: rgb(227,226,220); }";
        html += ".sstitre     { font-weight: bold;}";
        html += ".action      { font-size: 9px;}";
        html += ".category    { font-size: 16px; font-weight: bold; }";
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
                        QString keyword = info.keyword, title = info.title.toUpper(), syntax = info.syntax, description = info.description, example = info.example, snippet = info.snippet;
                        syntax      = syntax.     replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>");
                        description = description.replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>");
                        example     = example.    replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>");
                        snippet     = snippet.    replace(">", "&gt;").replace("<", "&lt;").replace("\n", "<br/>");

                        if(!description.isEmpty()) {
                            htmlCategory += QString("<p class='titre'><span class='code'>%1</span>&nbsp;&mdash;&nbsp;<span class='bold'>%2</span></p>").arg(keyword).arg(title);
                            if(!description.isEmpty())
                                htmlCategory += QString("<span class='sstitre'>%1</span>     <table width='100%'><tr><td></td><td width='97%' class='description'><span             >%2</span></td></tr></table><br/><br/>").arg(title).arg(description);
                            if(!syntax.isEmpty())
                                htmlCategory += QString("<span class='sstitre'>%3</span> <table width='100%'><tr><td></td><td width='97%' class='syntax'     ><span class='code'>%1</span></td></tr><tr><td></td><td align='right'><a class='action' href='%2'>%4</a></td></tr></table><br/><br/>").arg(syntax).arg(info.syntax).arg(tr("SYNTAX")).arg(tr("IMPLEMENT IN SCRIPT"));
                            if(!example.isEmpty())
                                htmlCategory += QString("<span class='sstitre'>%3</span><table width='100%'><tr><td></td><td width='97%' class='example'    ><span class='code'>%1</span></td></tr><tr><td></td><td align='right'><a class='action' href='%2'>%4</a></td></tr></table><br/><br/>").arg(example).arg(info.example).arg(tr("EXAMPLE")).arg(tr("IMPLEMENT IN SCRIPT"));
                            if(!snippet.isEmpty())
                                htmlCategory += QString("<span class='sstitre'>%3</span><table width='100%'><tr><td></td><td width='97%' class='snippet'    ><span class='code'>%1</span></td></tr><tr><td></td><td align='right'><a class='action' href='%2'>%4</a></td></tr></table><br/><br/>").arg(snippet).arg(info.snippet).arg(tr("SNIPPET")).arg(tr("IMPLEMENT IN SCRIPT"));
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
    if(currentTextEdit)
        currentTextEdit->textCursor().insertText(url.toString());
    if(currentCombo)
        currentCombo->setEditText(currentCombo->currentText() + url.toString());
}
