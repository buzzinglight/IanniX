#ifndef UIEDITOR_H
#define UIEDITOR_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDesktopWidget>
#include <QFile>


namespace Ui {
    class UiEditor;
}

class UiEditor : public QMainWindow {
    Q_OBJECT

public:
    explicit UiEditor(QWidget *parent = 0);
    ~UiEditor();

protected:
    void changeEvent(QEvent *e);

private:
    QFileInfo scriptFile;
public:
    void openFile(const QFileInfo &  _scriptFile);
public slots:
    void save();

private:
    Ui::UiEditor *ui;
};

#endif // UIEDITOR_H
