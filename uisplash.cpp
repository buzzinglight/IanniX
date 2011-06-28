#include "uisplash.h"
#include "ui_uisplash.h"

UiSplash::UiSplash(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiSplash) {
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    ui->version->setText(tr("version ") + QString(QCoreApplication::applicationVersion()) + " beta");
    QRect screen = QApplication::desktop()->geometry();
    move(screen.center() - rect().center());
}

UiSplash::~UiSplash() {
    delete ui;
}

void UiSplash::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
