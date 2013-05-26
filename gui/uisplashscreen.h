#ifndef UISPLASHSCREEN_H
#define UISPLASHSCREEN_H

#include <QFrame>
#include <QPainter>
#include <QPixmap>
#include <QDesktopWidget>
#include <QApplication>

class UiSplashScreen : public QFrame {
    Q_OBJECT

public:
    explicit UiSplashScreen(const QPixmap&);

public:
    void showMessage(const QString& _message, const QFont &_font, int _messageAlignment = Qt::AlignCenter, const QColor& _messageColor = Qt::white);

private:
    void paintEvent(QPaintEvent* e);
    QPixmap  pixmap;
    QString  message;
    int      messageAlignment;
    QColor   messageColor;
    QFont    messageFont;
    
signals:
    
public slots:
    
};

#endif // UISPLASHSCREEN_H
