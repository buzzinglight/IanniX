#ifndef ABSTRACTIONSGL_H
#define ABSTRACTIONSGL_H

#include <QGLWidget>
#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QTextLayout>
#include <QStaticText>
#include <qmath.h>
#include <QDateTime>
#include <QUrl>
#include <QFile>
#ifdef VLC_INSTALLED
#include "drivers/vlc.h"
#endif
#ifdef Q_OS_WIN
#define GL_TEXTURE_RECTANGLE_ARB   GL_TEXTURE_2D
#define GL_CLAMP_TO_EDGE           GL_REPEAT
#endif
#ifdef OPENCV_INSTALLED
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/legacy/compat.hpp>
#endif

class OpenGlFont : public QFont {
private:
    qreal _leading, _pLeading;
    int _alignement;

public:
    explicit OpenGlFont() : QFont() {
        _leading  = 100;
        _pLeading = 0;
        _alignement = Qt::AlignCenter | Qt::TextWordWrap;
    }
    inline qreal leading() const { return _leading; }
    inline void setLeading(qreal __leading) { _leading = __leading; }
    inline qreal pLeading() const { return _pLeading; }
    inline void setPLeading(qreal __pLeading) { _pLeading = __pLeading; }
    inline int alignement() const { return _alignement; }
    inline Qt::Alignment alignementFlags() const { return (Qt::Alignment)_alignement; }
    inline void setAlignement(int __alignement) { _alignement = __alignement; }

public:
    static inline const OpenGlFont getFont(const QString &family, int options = Qt::AlignCenter, quint16 size = 16, qreal leading = 100, qreal spacing = 100, qreal pLeading = 0, QFont::Stretch strech = QFont::Unstretched, QFont::Weight graisse = QFont::Normal, bool italic = false) {
        OpenGlFont font;
        QStringList familySplit = family.split("|", QString::SkipEmptyParts);
        if(familySplit.count() > 1) {
            font.setFamily   (familySplit.at(0));
#ifndef IANNIX_32
            font.setStyleName(familySplit.at(1));
#endif
        }
        else
            font.setFamily(familySplit.at(0));
        font.setWeight(graisse);
        font.setStretch(strech);
        font.setPixelSize(size);
        font.setItalic(italic);
        font.setLeading(leading);
        font.setPLeading(pLeading);
        font.setAlignement(options);
        font.setLetterSpacing(QFont::PercentageSpacing, spacing);
#ifndef IANNIX_32
        if(!font.exactMatch())
            qDebug("[FONT] %s —> %s, %s", qPrintable(family), qPrintable(font.family()), qPrintable(font.styleName()));
#endif
        return font;
    }
};

class OpenCvProcess {
public:
    virtual void processWebcam() = 0;
};

class OpenGlTexture : public QObject {
    Q_OBJECT

public:
    bool mirrorX, mirrorY;
    static QList<OpenGlTexture*> textures;
    static QHash<QString, OpenGlTexture*> texturesCache;
    static quint32 texturesCacheCount;
    GLuint     texture;
    QByteArray texturePixels;
    bool    init;
    QString filename, texte;
    QImage  image;
    OpenGlFont texteFont;
    qreal   blurKernelSize;
    void   *webView;
#ifdef VLC_INSTALLED
    VlcPlayer *video;
#else
    void* video;
#endif

private:
    int timerCamera;
#ifdef OPENCV_INSTALLED
    cv::VideoCapture capture;
public:
    cv::Mat cameraFrame, rgbFrame, cameraFrameRaw;
signals:
    void videoWebcamReady(OpenGlTexture*);
#endif
public slots:
    void grabWebcam();
    void timerEvent(QTimerEvent *);

public:
    QSizeF  size;
    OpenCvProcess *openCvProcess;

public:
    static OpenGlTexture* createFromFile(QObject *parent, const QString &filename);
public:
    explicit OpenGlTexture(QObject *parent);
    explicit OpenGlTexture(QObject *parent, const QSizeF  &_size);
    explicit OpenGlTexture(QObject *parent, const QString &_filename, qreal _blurKernelSize = 0);
    explicit OpenGlTexture(QObject *parent, const QString &_filename, const QSizeF &_size, bool inLoop = false, const QStringList &arguments = QStringList(), qreal _blurKernelSize = 0);
    explicit OpenGlTexture(QObject *parent, const QUrl &_url, const QSizeF &_size, qreal _blurKernelSize = 0);
    explicit OpenGlTexture(QObject *parent, const QPixmap &_pixmap,   qreal _blurKernelSize = 0);
    explicit OpenGlTexture(QObject *parent, const QImage  &_image,    qreal _blurKernelSize = 0);
    explicit OpenGlTexture(QObject *parent, const QString &_texte, const OpenGlFont &_texteFont, const QSizeF &_texteSize, qreal _blurKernelSize = 0);
    ~OpenGlTexture();

public:
    inline bool isSyphon() const { return (filename == "syphon"); }
    void loadUrl(const QUrl &_url, const QSizeF _size, qreal _blurKernelSize = 0);
    void loadFileImage(const QString &_filename, qreal _blurKernelSize = 0);
    void loadFileVideo(const QString &_filename, const QSizeF &_size, bool inLoop = false, const QStringList &arguments = QStringList(), qreal _blurKernelSize = 0);
    void loadPixmap(const QPixmap &_pixmap, qreal _blurKernelSize = 0);
    void loadImage(const QImage  &_image, qreal _blurKernelSize = 0);
    void loadSyphon(GLuint _texture);
    void loadWebcam(quint16 camId = 1, bool automaticRefresh = true);
    void loadTexte(const QString &_texte, const OpenGlFont &_texteFont, const QSizeF &_size, qreal _blurKernelSize = 0);
    GLuint loadManual();

public:
    bool pushTexture();
    bool popTexture() const;

#ifdef VLC_INSTALLED
signals:
    void videoStartEvent(OpenGlTexture*, const libvlc_event_t*);
    void videoEndEvent(OpenGlTexture*, const libvlc_event_t*);
private slots:
    void vlcMediaStartEvent(const libvlc_event_t*);
    void vlcMediaEndEvent(const libvlc_event_t*);
#endif
private slots:
    void webPageLoaded();
    void vlcImageReady();

public:
    static QImage imageBlurred(const QImage& image, const QRect& rect, int radius, bool alphaOnly = false);
};


class OpenGlColor : public QList<QColor> {
public:
    bool direction;
public:
    explicit OpenGlColor() :
        QList<QColor>() {
        append(Qt::transparent);
        append(Qt::transparent);
    }
    explicit OpenGlColor(const QColor &colorStart, const QColor &colorEnd, bool _direction = false) :
        QList<QColor>() {
        append(Qt::transparent);
        append(Qt::transparent);
        setColor(colorStart, colorEnd, _direction);
    }
    explicit OpenGlColor(const QColor &globalColor) :
        QList<QColor>() {
        append(Qt::transparent);
        append(Qt::transparent);
        setColor(globalColor);
    }

public:
    inline bool isTransparent() const {
        return ((at(0).alpha() == 0) && (at(1).alpha() == 0));
    }
    inline void setColorStart(const QColor &color, bool _direction = false)   { replace(0, color); direction = _direction; }
    inline void setColorEnd  (const QColor &color, bool _direction = false)   { replace(1, color); direction = _direction; }
    inline void setColor(const QColor &colorStart, const QColor &colorEnd, bool _direction = false) {
        setColorStart(colorStart, _direction);
        setColorEnd  (colorEnd  , _direction);
    }
    inline void setColor(const QColor &globalColor) {
        setColorStart(globalColor);
        setColorEnd  (globalColor);
    }

public:
    inline OpenGlColor& operator=(const QColor &globalColor) {
        setColor(globalColor);
        return *this;
    }

public:
    inline void glColor     (qreal alpha = 1) const {  glColorStart(alpha); }
    inline void glColorStart(qreal alpha = 1) const {  glColor4f(at(0).redF(), at(0).greenF(), at(0).blueF(), at(0).alphaF() * alpha);  }
    inline void glColorEnd  (qreal alpha = 1) const {  glColor4f(at(1).redF(), at(1).greenF(), at(1).blueF(), at(1).alphaF() * alpha);  }
};

class OpenGlColors {
private:
    OpenGlColor unselectedColor,  selectedColor;
    OpenGlColor unselectedBorder, selectedBorder;

public:
    qreal unselectedBorderWidth, selectedBorderWidth;

public:
    explicit OpenGlColors() {   }
    OpenGlColors(const OpenGlColor &globalColor) {
        OpenGlColors();
        setColor(globalColor);
        selectedBorderWidth = unselectedBorderWidth = 0;
    }
    OpenGlColors(const QColor &globalColor) {
        OpenGlColors();
        selectedBorderWidth = unselectedBorderWidth = 0;
        setColor(globalColor);
    }
    OpenGlColors(const OpenGlColor &_unselected, const OpenGlColor &_selected) {
        OpenGlColors();
        selectedBorderWidth = unselectedBorderWidth = 0;
        setColor(_unselected, _selected);
    }
    OpenGlColors(const QColor &_unselected, const OpenGlColor &_selected) {
        OpenGlColors();
        selectedBorderWidth = unselectedBorderWidth = 0;
        setColor(_unselected, _selected);
    }
    OpenGlColors(const OpenGlColor &_unselected, const QColor &_selected) {
        OpenGlColors();
        selectedBorderWidth = unselectedBorderWidth = 0;
        setColor(_unselected, _selected);
    }
    OpenGlColors(const QColor &_unselected, const QColor &_selected) {
        OpenGlColors();
        selectedBorderWidth = unselectedBorderWidth = 0;
        setColor(_unselected, _selected);
    }

public:
    inline OpenGlColors& operator=(const OpenGlColor &globalColor) {
        setColor(globalColor);
        return *this;
    }
    inline OpenGlColors& operator=(const QColor &globalColor) {
        setColor(globalColor);
        return *this;
    }

public:
    inline bool isColorTransparent() const {
        return (selectedColor.isTransparent() && unselectedColor.isTransparent());
    }
    inline bool isBorderTransparent() const {
        return (selectedBorder.isTransparent() && unselectedBorder.isTransparent());
    }
    inline void setColor(const QColor &globalColor) {
        unselectedColor = globalColor;
        selectedColor   = globalColor;
    }
    inline void setColor(const OpenGlColor &globalColor) {
        unselectedColor = globalColor;
        selectedColor   = globalColor;
    }
    inline void setColor(const OpenGlColor &_unselected, const OpenGlColor &_selected) {
        unselectedColor = _unselected;
        selectedColor   = _selected;
    }
    inline void setColor(const QColor &_unselected, const OpenGlColor &_selected) {
        unselectedColor = _unselected;
        selectedColor   = _selected;
    }
    inline void setColor(const OpenGlColor &_unselected, const QColor &_selected) {
        unselectedColor = _unselected;
        selectedColor   = _selected;
    }
    inline void setColor(const QColor &_unselected, const QColor &_selected) {
        unselectedColor = _unselected;
        selectedColor   = _selected;
    }

public:
    inline void setBorder(const QColor &globalBorder, qreal _borderWidth = 1) {
        unselectedBorder = globalBorder;
        selectedBorder   = globalBorder;
        selectedBorderWidth   = _borderWidth;
        unselectedBorderWidth = _borderWidth;
    }
    inline void setBorder(const OpenGlColor &globalBorder, qreal _borderWidth = 1) {
        unselectedBorder = globalBorder;
        selectedBorder   = globalBorder;
        selectedBorderWidth   = _borderWidth;
        unselectedBorderWidth = _borderWidth;
    }
    inline void setBorder(const OpenGlColor &_unselected, const OpenGlColor &_selected, qreal _unselectedBorderWidth = 1, qreal _selectedBorderWidth = 1) {
        unselectedBorder = _unselected;
        selectedBorder   = _selected;
        selectedBorderWidth   = _selectedBorderWidth;
        unselectedBorderWidth = _unselectedBorderWidth;
    }
    inline void setBorder(const QColor &_unselected, const OpenGlColor &_selected, qreal _unselectedBorderWidth = 1, qreal _selectedBorderWidth = 1) {
        unselectedBorder = _unselected;
        selectedBorder   = _selected;
        selectedBorderWidth   = _selectedBorderWidth;
        unselectedBorderWidth = _unselectedBorderWidth;
    }
    inline void setBorder(const OpenGlColor &_unselected, const QColor &_selected, qreal _unselectedBorderWidth = 1, qreal _selectedBorderWidth = 1) {
        unselectedBorder = _unselected;
        selectedBorder   = _selected;
        selectedBorderWidth   = _selectedBorderWidth;
        unselectedBorderWidth = _unselectedBorderWidth;
    }
    inline void setBorder(const QColor &_unselected, const QColor &_selected, qreal _unselectedBorderWidth = 1, qreal _selectedBorderWidth = 1) {
        unselectedBorder = _unselected;
        selectedBorder   = _selected;
        selectedBorderWidth   = _selectedBorderWidth;
        unselectedBorderWidth = _unselectedBorderWidth;
    }

public:
    inline void glColor      (qreal alpha = 1, qreal selected = 0) const  {  glColorStart (   alpha, selected);   }
    inline void glColorStart (qreal alpha = 1, qreal selected = 0) const  {  glColorIndex (0, alpha, selected);   }
    inline void glColorEnd   (qreal alpha = 1, qreal selected = 0) const  {  glColorIndex (1, alpha, selected);   }
    inline void glBorder     (qreal alpha = 1, qreal selected = 0) const  {  glBorderStart(   alpha, selected);   }
    inline void glBorderStart(qreal alpha = 1, qreal selected = 0) const  {  glBorderIndex(0, alpha, selected);   }
    inline void glBorderEnd  (qreal alpha = 1, qreal selected = 0) const  {  glBorderIndex(1, alpha, selected);   }
    inline bool colorDirection(qreal selected = 0) const {
        if(selected < 0.5)  return unselectedColor.direction;
        else                return selectedColor  .direction;
    }
    inline bool borderDirection(qreal selected = 0) const {
        if(selected < 0.5)  return unselectedBorder.direction;
        else                return selectedBorder  .direction;
    }
    inline bool borderNeed() const {
        return ((unselectedBorderWidth > 0) || (selectedBorderWidth > 0));
    }
    inline qreal borderWidth(qreal selected = 0) const {
        return (selectedBorderWidth * selected) + (unselectedBorderWidth * (1 - selected));
    }

private:
    inline void glColorIndex (qint8 index = 0, qreal alpha = 1, qreal selected = 0) const  {
        glColor4f(   selectedColor.at(index).redF()   * selected + unselectedColor.at(index).redF()   * (1 - selected),
                     selectedColor.at(index).greenF() * selected + unselectedColor.at(index).greenF() * (1 - selected),
                     selectedColor.at(index).blueF()  * selected + unselectedColor.at(index).blueF()  * (1 - selected),
                     (selectedColor.at(index).alphaF() * selected + unselectedColor.at(index).alphaF() * (1 - selected)) * alpha);
    }
    inline void glBorderIndex(qint8 index = 0, qreal alpha = 1, qreal selected = 0) const  {
        glColor4f(   selectedBorder.at(index).redF()   * selected + unselectedBorder.at(index).redF()   * (1 - selected),
                     selectedBorder.at(index).greenF() * selected + unselectedBorder.at(index).greenF() * (1 - selected),
                     selectedBorder.at(index).blueF()  * selected + unselectedBorder.at(index).blueF()  * (1 - selected),
                     (selectedBorder.at(index).alphaF() * selected + unselectedBorder.at(index).alphaF() * (1 - selected)) * alpha);
    }

};


class OpenGlDrawing {
public:
    static void drawRectCentred(const QSizeF  &center, const QSizeF &size, const OpenGlColors &colors, OpenGlTexture *texture = 0, qreal alpha = 1., qreal selected = 0, qreal croppingMode = -1, bool ninePatch = false, QRectF partialTextureRect = QRectF(0,0,-1,-1));
    static void drawRectCentred(const QPointF &center, const QSizeF &size, const OpenGlColors &colors, OpenGlTexture *texture = 0, qreal alpha = 1., qreal selected = 0, qreal croppingMode = -1, bool ninePatch = false, QRectF partialTextureRect = QRectF(0,0,-1,-1));
    static void drawRect(OpenGlTexture *texture, const OpenGlColors &colors = OpenGlColors(Qt::white), qreal alpha = 1., qreal selected = 0, qreal croppingMode = -1, bool ninePatch = false, QRectF partialTextureRect = QRectF(0,0,-1,-1));
    static void drawRect(OpenGlTexture *texture, qreal alpha, qreal selected = 0, qreal croppingMode = -1, bool ninePatch = false, QRectF partialTextureRect = QRectF(0,0,-1,-1));
    static void drawRect(const QSizeF &size, const OpenGlColors &colors, OpenGlTexture *texture = 0, qreal alpha = 1., qreal selected = 0, qreal croppingMode = -1, bool ninePatch = false, QRectF partialTextureRect = QRectF(0,0,-1,-1));
    static void drawRect(const QRectF &rect, const OpenGlColors &colors, OpenGlTexture *texture = 0, qreal alpha = 1., qreal selected = 0, qreal croppingMode = -1, bool ninePatch = false, QRectF partialTextureRect = QRectF(0,0,-1,-1));
    static qreal measureText(const OpenGlFont &font, qreal width, const QString &text);
    static QImage drawText(const QColor &color, const OpenGlFont &font, const QSizeF &size, const QString &text);
    static qreal drawText(QPainter *painter, const QColor &color, const OpenGlFont &font, const QRectF &rect, const QString &text);
};



#endif // ABSTRACTIONSGL_H
