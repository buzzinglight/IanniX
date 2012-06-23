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
#include "help.h"

namespace Ui {
class UiHelp;
}

class UiHelp : public QWidget
{
    Q_OBJECT
    
public:
    explicit UiHelp(QWidget *parent = 0);
    ~UiHelp();

public:
    void display(QPlainTextEdit *textEdit, const QStringList &lookCategories);
    void display(QComboBox      *textEdit, const QStringList &lookCategories);
    void display(const QString  &looking,  const QStringList &lookCategories);

private:
    QPlainTextEdit *currentTextEdit;
    QComboBox *currentCombo;

public slots:
    void linkClicked(QUrl);
    
private:
    Ui::UiHelp *ui;
};

#endif // UIHELP_H
