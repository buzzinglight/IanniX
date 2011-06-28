#include "uiabout.h"
#include "ui_uiabout.h"

UiAbout::UiAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiAbout) {
    ui->setupUi(this);
    ui->version->setText(tr("version ") + QCoreApplication::applicationVersion() + tr(" beta"));
    QRect screen = QApplication::desktop()->geometry();
    move(screen.center() - rect().center());
}

UiAbout::~UiAbout() {
    delete ui;
}

void UiAbout::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
