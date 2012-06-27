#include "uimessagebox.h"
#include "ui_uimessagebox.h"

UiMessageBox::UiMessageBox(QWidget *parent) :
    QDialog(parent, Qt::Tool),
    ui(new Ui::UiMessageBox) {
    ui->setupUi(this);
}

UiMessageBox::~UiMessageBox() {
    delete ui;
}

qreal UiMessageBox::getDouble(const QString &title, const QString &description, qreal value, qreal min, qreal max, qreal step, quint16 decimals, const QString &suffix, bool *ok) {
    setUpdatesEnabled(false);
    ui->choices->setCurrentIndex(0);
    ui->spinLabel->setText(description.toUpper());
    setWindowTitle(title);
    ui->spinSpin->setMinimum(min);
    ui->spinSpin->setMaximum(max);
    ui->spinSpin->setDecimals(decimals);
    ui->spinSpin->setSingleStep(step);
    ui->spinSpin->setValue(value);
    ui->spinSpin->setSuffix(" " + suffix);
    ui->spinSpin->setFocus();
    setUpdatesEnabled(true);

    show();
    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.center() - QPoint(200, 100));

    exec();
    if(ok) {
        if(result())    *ok = true;
        else            *ok = false;
    }
    qreal ret = ui->spinSpin->value();
    delete this;
    return ret;
}
qreal UiMessageBox::getDouble(const QString &title, const QString &description, const QPixmap &pixmap, qreal value, qreal min, qreal max, qreal step, quint16 decimals, const QString &suffix, bool *ok) {
    setUpdatesEnabled(false);
    ui->choices->setCurrentIndex(1);
    ui->spinpLabel->setText(description.toUpper());
    setWindowTitle(title);
    ui->spinpSpin->setMinimum(min);
    ui->spinpSpin->setMaximum(max);
    ui->spinpSpin->setDecimals(decimals);
    ui->spinpSpin->setSingleStep(step);
    ui->spinpSpin->setValue(value);
    ui->spinpPicture->resize(pixmap.size());
    ui->spinpPicture->setPixmap(pixmap);
    ui->spinpSpin->setSuffix(" " + suffix);
    ui->spinpSpin->setFocus();
    setUpdatesEnabled(true);

    updateGeometry();
    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.center() - QPoint(200, 100));

    exec();
    if(ok) {
        if(result())    *ok = true;
        else            *ok = false;
    }
    qreal ret = ui->spinpSpin->value();
    delete this;
    return ret;
}
int UiMessageBox::display(const QString &title, const QString &description, QDialogButtonBox::StandardButtons buttons, bool *ok) {
    setUpdatesEnabled(false);
    ui->choices->setCurrentIndex(2);
    ui->messageLabel->setText(description.toUpper());
    ui->messageButtons->setStandardButtons(buttons);
    setWindowTitle(title);
    setUpdatesEnabled(true);

    updateGeometry();
    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.center() - QPoint(200, 100));

    exec();
    if(ok) {
        if(result())    *ok = true;
        else            *ok = false;
    }
    int ret = result();
    delete this;
    return ret;
}
QString UiMessageBox::getText(const QString &title, const QString &description, const QString &value, bool *ok) {
    setUpdatesEnabled(false);
    ui->choices->setCurrentIndex(3);
    ui->textLabel->setText(description.toUpper());
    setWindowTitle(title);
    ui->textEdit->setText(value);
    setUpdatesEnabled(true);

    updateGeometry();
    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.center() - QPoint(200, 100));

    exec();
    if(ok) {
        if(result())    *ok = true;
        else            *ok = false;
    }
    QString ret = ui->textEdit->text();
    delete this;
    return ret;
}

int UiMessageBox::display(const QString &title, const QString &description1, const QString &description2, const QString &description3, const QPixmap &pixmap, QDialogButtonBox::StandardButtons buttons, bool *ok) {
    setUpdatesEnabled(false);
    ui->choices->setCurrentIndex(4);
    ui->updateLabel->setText(description1.toUpper());
    ui->updatePlain->setMinimumSize(0, 200);
    ui->updatePlain->setPlainText(description2);
    ui->updateLabel2->setText(description3.toUpper());
    ui->updatePicture->resize(pixmap.size());
    ui->updatePicture->setPixmap(pixmap);
    ui->messageButtons->setStandardButtons(buttons);
    setWindowTitle(title);
    setUpdatesEnabled(true);

    updateGeometry();
    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.center() - QPoint(200, 300));

    exec();
    if(ok) {
        if(result())    *ok = true;
        else            *ok = false;
    }
    int ret = result();
    delete this;
    return ret;
}
