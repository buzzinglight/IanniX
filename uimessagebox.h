#ifndef UIMESSAGEBOX_H
#define UIMESSAGEBOX_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QDesktopWidget>

namespace Ui {
class UiMessageBox;
}

class UiMessageBox : public QDialog {
    Q_OBJECT
    
public:
    explicit UiMessageBox(QWidget *parent = 0);
    ~UiMessageBox();

public:
    qreal getDouble(const QString &title, const QString &description, qreal value, qreal min, qreal max, qreal step, quint16 decimals, const QString &suffix, bool *ok = 0);
    qreal getDouble(const QString &title, const QString &description, const QPixmap &pixmap, qreal value, qreal min, qreal max, qreal step, quint16 decimals, const QString &suffix, bool *ok = 0);
    int display(const QString &title, const QString &description, QDialogButtonBox::StandardButtons buttons, bool *ok = 0);
    QString getText(const QString &title, const QString &description, const QString &value, bool *ok = 0);
    int display(const QString &title, const QString &description1, const QString &description2, const QString &description3, const QPixmap &pixmap, QDialogButtonBox::StandardButtons buttons, bool *ok = 0);

private:
    Ui::UiMessageBox *ui;
};

#endif // UIMESSAGEBOX_H
