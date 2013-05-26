#include "uisplashscreen.h"

UiSplashScreen::UiSplashScreen(const QPixmap &_pixmap) :
    QFrame(0, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint) {
    pixmap = _pixmap;
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(pixmap.size());

    QRect screen = QApplication::desktop()->screenGeometry();
    move(screen.center() - rect().center());

    QFont textFont("Arial");
    textFont.setPixelSize(13);
    showMessage(tr("version") + " " + QString(QCoreApplication::applicationVersion()) + " " + tr("beta"), textFont, Qt::AlignCenter, QColor(255, 255, 255, 150));

    show();
    QCoreApplication::processEvents();
}

void UiSplashScreen::showMessage(const QString& _message, const QFont &_font, int _messageAlignement, const QColor& _messageColor) {
    message  = _message;
    messageAlignment = _messageAlignement;
    messageColor  = _messageColor;
    messageFont   = _font;
    repaint();
}

void UiSplashScreen::paintEvent(QPaintEvent*) {
    QRect textRect(QRect(QPoint(115, 435), QSize(285, 70)));

    QPainter painter(this);
    painter.drawPixmap(rect(), pixmap);
    painter.setPen(messageColor);
    painter.setFont(messageFont);
    painter.drawText(textRect, messageAlignment, message);
}
