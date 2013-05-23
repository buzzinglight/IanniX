#ifndef UIHELP_H
#define UIHELP_H

#include <QWidget>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QTextCursor>
#include <QTextBlock>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QClipboard>
#include "misc/help.h"
#include "misc/options.h"

namespace Ui {
class UiHelp;
}

class UiHelp : public QWidget {
    Q_OBJECT

private:
    QPlainTextEdit *currentTextEdit;
    QComboBox *currentCombo;
    QStringList messageTexts, statusTexts;
    QString statusTextOld;
    bool statusRefresh;
public:
    static quint16 oscPort;
    static UiHelp *statusHelpWidget;

public:
    explicit UiHelp(QWidget *parent = 0);
    ~UiHelp();

public:
    static void statusHelp(const QWidget *widget);
    void statusHelp();
    void scriptHelp(QPlainTextEdit *textEdit, const QStringList &lookCategories);
    void scriptHelp(QComboBox      *textEdit, const QStringList &lookCategories);
    void scriptHelp(const QString  &looking,  const QStringList &lookCategories);

public:
    UiBool visibility;
public slots:
    void statusHelp(QString _statusText);
    void messageHelp(QString _messageText);
    void linkClicked(QUrl);

protected:
    void timerEvent(QTimerEvent *);
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);
    
private:
    Ui::UiHelp *ui;
};

#endif // UIHELP_H
