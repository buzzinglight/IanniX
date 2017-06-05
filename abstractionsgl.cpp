#include "abstractionsgl.h"
#ifdef Q_OS_MAC
#include <fcntl.h>
#endif

QList<OpenGlTexture*> OpenGlTexture::textures = QList<OpenGlTexture*>();
QHash<QString, OpenGlTexture*> OpenGlTexture::texturesCache = QHash<QString, OpenGlTexture*>();
quint32 OpenGlTexture::texturesCacheCount = 0;

OpenGlTexture* OpenGlTexture::createFromFile(QObject *parent, const QString &filename) {
    if(texturesCache.contains(filename)) {
        texturesCacheCount++;
        //qDebug("[CACHE] %d / %d : %s", texturesCacheCount, texturesCache.count(), qPrintable(filename));
        return (texturesCache.value(filename));
    }
    else {
        //qDebug("[NEW TEXTURE] %d / %d : %s", texturesCacheCount, texturesCache.count(), qPrintable(filename));
        return (new OpenGlTexture(parent, filename));
    }
}

OpenGlTexture::OpenGlTexture(QObject *parent) :
    QObject(parent) {
    mirrorX = mirrorY = false;
    video          = 0;
    webView        = 0;
    texture        = 0;
    filename       = "";
    blurKernelSize = 0;
    openCvProcess  = 0;
    timerCamera    = -1;
    init           = false;
    textures.append(this);
}
OpenGlTexture::OpenGlTexture(QObject *parent, const QSizeF &_size) :
    QObject(parent) {
    mirrorX = mirrorY = false;
    video          = 0;
    webView        = 0;
    texture        = 0;
    size           = _size;
    blurKernelSize = 0;
    openCvProcess  = 0;
    timerCamera    = -1;
    init           = false;
    loadManual();
    textures.append(this);
}
OpenGlTexture::OpenGlTexture(QObject *parent, const QUrl &_url, const QSizeF &_size, qreal _blurKernelSize) :
    QObject(parent) {
    mirrorX = mirrorY = false;
    video          = 0;
    webView        = 0;
    texture        = 0;
    openCvProcess  = 0;
    timerCamera    = -1;
    init           = false;
    loadUrl(_url, _size, _blurKernelSize);
    textures.append(this);
}
OpenGlTexture::OpenGlTexture(QObject *parent, const QString &_filename, qreal _blurKernelSize) :
    QObject(parent) {
    mirrorX = mirrorY = false;
    video          = 0;
    webView        = 0;
    texture        = 0;
    init           = false;
    openCvProcess  = 0;
    timerCamera    = -1;
    loadFileImage(_filename, _blurKernelSize);
    textures.append(this);
    texturesCache.insert(_filename, this);
}
OpenGlTexture::OpenGlTexture(QObject *parent, const QString &_filename, const QSizeF &_size, bool inLoop, const QStringList &arguments, qreal _blurKernelSize) :
    QObject(parent) {
    mirrorX = mirrorY = false;
    video          = 0;
    webView        = 0;
    texture        = 0;
    init           = false;
    openCvProcess  = 0;
    loadFileVideo(_filename, _size, inLoop, arguments, _blurKernelSize);
    textures.append(this);
}
OpenGlTexture::OpenGlTexture(QObject *parent, const QPixmap &_pixmap, qreal _blurKernelSize) :
    QObject(parent) {
    mirrorX = mirrorY = false;
    video          = 0;
    webView        = 0;
    texture        = 0;
    init           = false;
    timerCamera    = -1;
    openCvProcess  = 0;
    loadPixmap(_pixmap, _blurKernelSize);
    textures.append(this);
}
OpenGlTexture::OpenGlTexture(QObject *parent, const QImage &_image, qreal _blurKernelSize) :
    QObject(parent) {
    mirrorX = mirrorY = false;
    video          = 0;
    webView        = 0;
    texture        = 0;
    init           = false;
    timerCamera    = -1;
    openCvProcess  = 0;
    loadImage(_image, _blurKernelSize);
    textures.append(this);
}
OpenGlTexture::OpenGlTexture(QObject *parent, const QString &_texte, const OpenGlFont &_texteFont, const QSizeF &_texteSize, qreal _blurKernelSize) :
    QObject(parent) {
    mirrorX = mirrorY = false;
    video          = 0;
    webView        = 0;
    texture        = 0;
    init           = false;
    timerCamera    = -1;
    openCvProcess  = 0;
    loadTexte (_texte, _texteFont, _texteSize, _blurKernelSize);
    textures.append(this);
}
OpenGlTexture::~OpenGlTexture() {
    textures.removeOne(this);
    if(texturesCache.contains(filename))
        texturesCache.remove(filename);
    //qDebug("[OPENGL] Suppression de la texture #%d", texture);
    if(video)
        delete video;
    if(texture)
        glDeleteTextures(1, &texture);
}


void OpenGlTexture::loadUrl(const QUrl &_url, const QSizeF _size, qreal _blurKernelSize) {
    Q_UNUSED(_url);
    Q_UNUSED(_size);
    filename       = "web";
    init           = true;
    blurKernelSize = _blurKernelSize;
}
void OpenGlTexture::webPageLoaded() {

}

void OpenGlTexture::loadFileImage(const QString &_filename, qreal _blurKernelSize) {
    filename       = _filename;
    init           = false;
    blurKernelSize = _blurKernelSize;
    if(filename.contains(".tile")) {
        QFile file(filename);
        if(file.open(QFile::ReadOnly | QFile::Unbuffered)) {
            filename = "glpixels";
#ifdef Q_OS_MAC
            fcntl(file.handle(), F_NOCACHE, 1); // <- disable UBC for that file
#endif

            //Taille de l'image
            QByteArray firstLineItems = file.readLine();
            QStringList lineItems = QString(firstLineItems).split(",");
            if(lineItems.count() == 2) {
                size = QSize(lineItems.at(0).toInt(), lineItems.at(1).toInt());

                //Payload
                file.seek(firstLineItems.count());
                texturePixels = file.readAll();
            }
            else
                qDebug("[OpenGL] Tile parse error");
        }
    }
    else {
        image.load(filename);
        if(image.isNull()) {
            image = QImage(QSize(1, 1), QImage::Format_ARGB32_Premultiplied);
            image.fill(Qt::transparent);
        }
        size = image.size();
    }
}
void OpenGlTexture::loadFileVideo(const QString &_filename, const QSizeF &_size, bool inLoop, const QStringList &arguments, qreal _blurKernelSize) {
    filename       = _filename;
    init           = false;
    blurKernelSize = _blurKernelSize;
    size           = _size;
    image = QImage(QSize(1, 1), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
#ifdef VLC_INSTALLED
    if(!video) {
        std::vector<std::string> vlcArguments;
        vlcArguments.push_back("--aspect-ratio=width:height");
//        vlcArguments.push_back("-vvv");

        foreach(const QString &argument, arguments)
            vlcArguments.push_back(qPrintable(argument));

        video = new VlcPlayer(size, vlcArguments);
        connect(video, SIGNAL(textureUpdate()), SLOT(vlcImageReady()));
        connect(video, SIGNAL(mediaStartEvent(const libvlc_event_t*)), SLOT(vlcMediaStartEvent(const libvlc_event_t*)));
        connect(video, SIGNAL(mediaEndEvent(const libvlc_event_t*)), SLOT(vlcMediaEndEvent(const libvlc_event_t*)));
    }
    video->setUrl(QUrl::fromLocalFile(_filename), inLoop);
#else
    Q_UNUSED(arguments);
    Q_UNUSED(inLoop);
#endif
}
void OpenGlTexture::loadWebcam(quint16 camId, bool automaticRefresh) {
    filename = QString::number(camId);
    init     = false;
    image = QImage(QSize(1, 1), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);
#ifdef OPENCV_INSTALLED
    cameraFrame = cv::Mat(size.height(), size.width(), CV_8UC3);
    qDebug("[CAMERA FIXEE] %d %d", cameraFrame.cols, cameraFrame.rows);

    //Open camera
    for(qint16 cameraIndex = camId ; cameraIndex >= 0 ; cameraIndex--)
        if(capture.open(cameraIndex))
            break;

    //Resize
    if(capture.isOpened()) {
        capture.retrieve(cameraFrameRaw);
        qDebug("[CAMERA NATIVE] %d %d", cameraFrameRaw.cols, cameraFrameRaw.rows);
        if((cameraFrameRaw.cols > 0) && (cameraFrameRaw.rows > 0)) {
            cv::resize(cameraFrameRaw, cameraFrame, cameraFrame.size());
            size = QSize(cameraFrame.cols, cameraFrame.rows);
            rgbFrame = cv::Mat(size.height(), size.width(), CV_8UC3);

            //Timers
            if(automaticRefresh)
                timerCamera = startTimer(40);
        }
    }
#else
    Q_UNUSED(automaticRefresh);
#endif
}
void OpenGlTexture::grabWebcam() {
#ifdef OPENCV_INSTALLED
    if((capture.isOpened()) && (cameraFrameRaw.cols > 0) && (cameraFrameRaw.rows > 0)) {
        //qint64 t = QDateTime::currentMSecsSinceEpoch();
        capture.grab();
        capture.retrieve(cameraFrameRaw);
        cv::resize(cameraFrameRaw, cameraFrame, cameraFrame.size());
        if(openCvProcess)
            openCvProcess->processWebcam();
        cv::cvtColor(cameraFrame, rgbFrame, cv::COLOR_BGR2RGB);
        image = QImage((uchar*)rgbFrame.data, rgbFrame.cols, rgbFrame.rows, rgbFrame.step, QImage::Format_RGB888);
        init = false;
        emit(videoWebcamReady(this));
    }
#endif
}

void OpenGlTexture::timerEvent(QTimerEvent *e) {
    if(e->timerId() == timerCamera)
        grabWebcam();
}

void OpenGlTexture::vlcImageReady() {
#ifdef VLC_INSTALLED
    image = video->image;
    init = false;
#endif
}
#ifdef VLC_INSTALLED
void OpenGlTexture::vlcMediaStartEvent(const libvlc_event_t *event) {
    emit(videoStartEvent(this, event));
}
void OpenGlTexture::vlcMediaEndEvent(const libvlc_event_t *event) {
    emit(videoEndEvent(this, event));
    if(video->inLoop)
        video->replay();
}
#endif

void OpenGlTexture::loadPixmap(const QPixmap &_pixmap, qreal _blurKernelSize) {
    filename       = "pixmap";
    init           = false;
    blurKernelSize = _blurKernelSize;
    image          = _pixmap.toImage();
    size           = image.size();
}
void OpenGlTexture::loadImage(const QImage &_image, qreal _blurKernelSize) {
    filename       = "pixmap";
    init           = false;
    blurKernelSize = _blurKernelSize;
    image          = _image;
    size           = image.size();
}
void OpenGlTexture::loadSyphon(GLuint _texture) {
    texture       = _texture;
    filename      = "syphon";
    init          = true;
}
GLuint OpenGlTexture::loadManual() {
    filename      = "manual";
    init          = false;
    pushTexture();
    popTexture();
    return texture;
}
void OpenGlTexture::loadTexte(const QString &_texte, const OpenGlFont &_texteFont, const QSizeF &_size, qreal _blurKernelSize) {
    if((_texte != texte) || (_size != size)) {
        filename        = "texte";
        texte           = _texte;
        texteFont       = _texteFont;
        size            = _size;
        init            = false;
        blurKernelSize  = _blurKernelSize;
    }
}

bool OpenGlTexture::pushTexture() {
    if((!init) && (!filename.isEmpty()) && (filename != "syphon")) {
        if(filename == "glpixels") {
            //Génération de la texture
            glEnable(GL_TEXTURE_2D);
            if(!texture)
                glGenTextures(1, &texture);
            glBindTexture  (GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_NEAREST
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_NEAREST_MIPMAP_LINEAR
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.width(), size.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texturePixels.data());
            glDisable(GL_TEXTURE_2D);
        }
        else {
            QImage sourceImage;
            if(filename == "texte")
                sourceImage = OpenGlDrawing::drawText(Qt::white, texteFont, size, texte);
            else if(filename == "manual") {
                sourceImage = QImage(size.toSize(), QImage::Format_ARGB32_Premultiplied);
                sourceImage.fill(Qt::transparent);
            }
            else if(filename == "pixmap") {
                if(!image.isNull())
                    sourceImage = image;
                else
                    return init;
            }
            else {
                if(!image.isNull())
                    sourceImage = image;
                if(sourceImage.isNull()) {
                    sourceImage = QImage(filename);
                    if(sourceImage.isNull())
                        return init;
                }
            }

            //Traitements
            size = sourceImage.size();
            if(blurKernelSize)
                sourceImage = imageBlurred(sourceImage, sourceImage.rect(), blurKernelSize);

            //Génération de la texture
            glEnable(GL_TEXTURE_2D);
            QString verboseTexte = "";
            if(!texture) {
                glGenTextures(1, &texture);
                verboseTexte = QString("[OPENGL] Création de la texture #%1 => %2 (%3)").arg(texture).arg(filename).arg(texte);
            }
            glBindTexture  (GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//GL_NEAREST
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//GL_NEAREST_MIPMAP_LINEAR
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

            if(filename == "manual") {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB , size.width(), size.height(), 0, GL_RGB , GL_UNSIGNED_BYTE, QGLWidget::convertToGLFormat(sourceImage).bits());
                //if(!verboseTexte.isEmpty())    qDebug("%s (GL_RGB - GL_UNSIGNED_BYTE / %f - %f)", qPrintable(verboseTexte), size.width(), size.height());
            }
            else if(filename == "textureFloat") {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.width(), size.height(), 0, GL_RGBA, GL_DOUBLE, 0);
                //if(!verboseTexte.isEmpty())    qDebug("%s (GL_RGBA - GL_DOUBLE / %f - %f)", qPrintable(verboseTexte), size.width(), size.height());
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.width(), size.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, QGLWidget::convertToGLFormat(sourceImage).bits());
                //if(!verboseTexte.isEmpty())    qDebug("%s (GL_RGBA - GL_UNSIGNED_BYTE / %f - %f)", qPrintable(verboseTexte), size.width(), size.height());
            }
            glDisable(GL_TEXTURE_2D);
        }
        init = true;
    }
    if(init) {
        if(isSyphon()) {
            glEnable(GL_TEXTURE_RECTANGLE_ARB);
            glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);
        }
        else {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture);
        }
        /*
        glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        */
    }

    return init;
}
bool OpenGlTexture::popTexture() const {
    if(init) {
        if(isSyphon())    glDisable(GL_TEXTURE_RECTANGLE_ARB);
        else              glDisable(GL_TEXTURE_2D);
    }
    return init;
}



QImage OpenGlTexture::imageBlurred(const QImage& image, const QRect& rect, int radius, bool alphaOnly) {
    if(radius > 0) {
        int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
        int alpha = (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius-1];

        QImage result = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
        int r1 = rect.top();
        int r2 = rect.bottom();
        int c1 = rect.left();
        int c2 = rect.right();

        int bpl = result.bytesPerLine();
        int rgba[4];
        unsigned char* p;

        int i1 = 0;
        int i2 = 3;

        if (alphaOnly)
            i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

        for (int col = c1; col <= c2; col++) {
            p = result.scanLine(r1) + col * 4;
            for (int i = i1; i <= i2; i++)
                rgba[i] = p[i] << 4;

            p += bpl;
            for (int j = r1; j < r2; j++, p += bpl)
                for (int i = i1; i <= i2; i++)
                    p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
        }

        for (int row = r1; row <= r2; row++) {
            p = result.scanLine(row) + c1 * 4;
            for (int i = i1; i <= i2; i++)
                rgba[i] = p[i] << 4;

            p += 4;
            for (int j = c1; j < c2; j++, p += 4)
                for (int i = i1; i <= i2; i++)
                    p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
        }

        for (int col = c1; col <= c2; col++) {
            p = result.scanLine(r2) + col * 4;
            for (int i = i1; i <= i2; i++)
                rgba[i] = p[i] << 4;

            p -= bpl;
            for (int j = r1; j < r2; j++, p -= bpl)
                for (int i = i1; i <= i2; i++)
                    p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
        }

        for (int row = r1; row <= r2; row++) {
            p = result.scanLine(row) + c2 * 4;
            for (int i = i1; i <= i2; i++)
                rgba[i] = p[i] << 4;

            p -= 4;
            for (int j = c1; j < c2; j++, p -= 4)
                for (int i = i1; i <= i2; i++)
                    p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
        }

        return result;
    }
    else
        return image;
}


void OpenGlDrawing::drawRectCentred(const QSizeF &center, const QSizeF &size, const OpenGlColors &colors, OpenGlTexture *texture, qreal alpha, qreal selected, qreal croppingMode, bool ninePatch, QRectF partialTextureRect) {
    drawRect(QRectF(QPointF(center.width()/2 - size.width()/2, center.height()/2 - size.height()/2), size), colors, texture, alpha, selected, croppingMode, ninePatch, partialTextureRect);
}
void OpenGlDrawing::drawRectCentred(const QPointF &center, const QSizeF &size, const OpenGlColors &colors, OpenGlTexture *texture, qreal alpha, qreal selected, qreal croppingMode, bool ninePatch, QRectF partialTextureRect) {
    drawRect(QRectF(QPointF(center.x() - size.width()/2, center.y() - size.height()/2), size), colors, texture, alpha, selected, croppingMode, ninePatch, partialTextureRect);
}
void OpenGlDrawing::drawRect(const QSizeF &size, const OpenGlColors &colors, OpenGlTexture *texture, qreal alpha, qreal selected, qreal croppingMode, bool ninePatch, QRectF partialTextureRect) {
    drawRect(QRectF(QPointF(0, 0), size), colors, texture, alpha, selected, croppingMode, ninePatch, partialTextureRect);
}
void OpenGlDrawing::drawRect(OpenGlTexture *texture, const OpenGlColors &colors, qreal alpha, qreal selected, qreal croppingMode, bool ninePatch, QRectF partialTextureRect) {
    drawRect(QRectF(QPointF(0, 0), texture->size), colors, texture, alpha, selected, croppingMode, ninePatch, partialTextureRect);
}
void OpenGlDrawing::drawRect(OpenGlTexture *texture, qreal alpha, qreal selected, qreal croppingMode, bool ninePatch, QRectF partialTextureRect) {
    drawRect(QRectF(QPointF(0, 0), texture->size), OpenGlColors(Qt::white), texture, alpha, selected, croppingMode, ninePatch, partialTextureRect);
}
void OpenGlDrawing::drawRect(const QRectF &rect, const OpenGlColors &colors, OpenGlTexture *texture, qreal alpha, qreal selected, qreal croppingMode, bool ninePatch, QRectF partialTextureRect) {
    QRectF textureRect, targetRect = rect;
    alpha    = qBound(qreal(0.), alpha,    qreal(1.));
    selected = qBound(qreal(0.), selected, qreal(1.));

    //Cropping
    if(!colors.isColorTransparent()) {
        QList< QPair<QRectF, QRectF> > drawingRects;
        if(texture) {
            if((texture->filename == "texte") && (croppingMode == -1))
                croppingMode = -3;

            if(croppingMode == -3)
                textureRect = QRectF(QPointF(0, 0), targetRect.size());
            else if(croppingMode == -2) {
                textureRect = QRectF(QPointF(0, 0), texture->size);
                targetRect.setSize(textureRect.size() / qMax(textureRect.width(), textureRect.height()) * qMax(rect.width(), rect.height()));
                qreal scaleDepassement = qMax(targetRect.width() / rect.width(), targetRect.height() / rect.height());
                if(scaleDepassement > 1)
                    targetRect.setSize(targetRect.size() / scaleDepassement);
                targetRect = QRectF(QPointF(rect.x() + rect.width() / 2 - targetRect.width() / 2, rect.y() + rect.height() / 2 - targetRect.height() / 2), QSizeF(targetRect.width(), targetRect.height()));
            }
            else if(croppingMode == -1) {
                textureRect = QRectF(QPointF(0, 0), texture->size);
                if((partialTextureRect.width() > 0) && (partialTextureRect.height() > 0))
                    textureRect = QRectF(QPointF(partialTextureRect.x()     * texture->size.width(), partialTextureRect.y()      * texture->size.width()),
                                         QSizeF (partialTextureRect.width() * texture->size.width(), partialTextureRect.height() * texture->size.height()));
            }
            else if(croppingMode >= 0) {
                textureRect.setSize(targetRect.size() / qMax(targetRect.width(), targetRect.height()) * qMax(texture->size.width(), texture->size.height()));
                qreal scaleDepassement = qMax(textureRect.width() / texture->size.width(), textureRect.height() / texture->size.height());
                if(scaleDepassement > 1)
                    textureRect.setSize(textureRect.size() / scaleDepassement);
                qreal panXMax = textureRect.width() - texture->size.width(), panYMax = textureRect.height() - texture->size.height();
                qreal panX = ((2*croppingMode)-1) * panXMax/2, panY = ((2*croppingMode)-1) * panYMax/2;
                textureRect = QRectF(QPointF(panX + texture->size.width() / 2 - textureRect.width() / 2, panY + texture->size.height() / 2 - textureRect.height() / 2), QSizeF(textureRect.width(), textureRect.height()));
            }

            if(ninePatch) {
                QPointF part;
                qreal textureRectCote = qMin(textureRect.width() / 3., textureRect.height() / 3.);
                qreal targetRectCote  = qMin(targetRect.width()  / 3., targetRect.height()  / 3.);

                //4 Coins
                part = QPointF(0, 0);
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  +    part.x()  * (targetRect.width()   - targetRectCote),
                                                             targetRect.y()  +    part.y()  * (targetRect.height()  - targetRectCote)),  QSizeF(targetRectCote,  targetRectCote)),
                                              QRectF(QPointF(textureRect.x() +    part.x()  * (textureRect.width()  - textureRectCote),
                                                             textureRect.y() + (1-part.y()) * (textureRect.height() - textureRectCote)), QSizeF(textureRectCote, textureRectCote))));
                part = QPointF(1, 0);
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  +    part.x()  * (targetRect.width()   - targetRectCote),
                                                             targetRect.y()  +    part.y()  * (targetRect.height()  - targetRectCote)),  QSizeF(targetRectCote,  targetRectCote)),
                                              QRectF(QPointF(textureRect.x() +    part.x()  * (textureRect.width()  - textureRectCote),
                                                             textureRect.y() + (1-part.y()) * (textureRect.height() - textureRectCote)), QSizeF(textureRectCote, textureRectCote))));
                part = QPointF(1, 1);
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  +    part.x()  * (targetRect.width()   - targetRectCote),
                                                             targetRect.y()  +    part.y()  * (targetRect.height()  - targetRectCote)),  QSizeF(targetRectCote,  targetRectCote)),
                                              QRectF(QPointF(textureRect.x() +    part.x()  * (textureRect.width()  - textureRectCote),
                                                             textureRect.y() + (1-part.y()) * (textureRect.height() - textureRectCote)), QSizeF(textureRectCote, textureRectCote))));
                part = QPointF(0, 1);
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  +    part.x()  * (targetRect.width()   - targetRectCote),
                                                             targetRect.y()  +    part.y()  * (targetRect.height()  - targetRectCote)),  QSizeF(targetRectCote,  targetRectCote)),
                                              QRectF(QPointF(textureRect.x() +    part.x()  * (textureRect.width()  - textureRectCote),
                                                             textureRect.y() + (1-part.y()) * (textureRect.height() - textureRectCote)), QSizeF(textureRectCote, textureRectCote))));

                //Haut-Bas
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  + 1 * targetRectCote  + 0 * (targetRect.width()   - targetRectCote),
                                                             targetRect.y()  + 0 * targetRectCote  + 0 * (targetRect.height()  - targetRectCote)),  QSizeF(0 * targetRectCote  + 1 * (targetRect.width()  - 2 * targetRectCote),  1 * targetRectCote  + 0 * (targetRect.height()  - 2 * targetRectCote))),
                                              QRectF(QPointF(textureRect.x() + 1 * textureRectCote + 0 * (textureRect.width()  - textureRectCote),
                                                             textureRect.y() + 0 * textureRectCote + 1 * (textureRect.height() - textureRectCote)), QSizeF(0 * textureRectCote + 1 * (textureRect.width() - 2 * textureRectCote), 1 * textureRectCote + 0 * (textureRect.height() - 2 * textureRectCote)))));
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  + 1 * targetRectCote  + 0 * (targetRect.width()   - targetRectCote),
                                                             targetRect.y()  + 0 * targetRectCote  + 1 * (targetRect.height()  - targetRectCote)),  QSizeF(0 * targetRectCote  + 1 * (targetRect.width()  - 2 * targetRectCote),  1 * targetRectCote  + 0 * (targetRect.height()  - 2 * targetRectCote))),
                                              QRectF(QPointF(textureRect.x() + 1 * textureRectCote + 0 * (textureRect.width()  - textureRectCote),
                                                             textureRect.y() + 0 * textureRectCote + 0 * (textureRect.height() - textureRectCote)), QSizeF(0 * textureRectCote + 1 * (textureRect.width() - 2 * textureRectCote), 1 * textureRectCote + 0 * (textureRect.height() - 2 * textureRectCote)))));
                //Gauche-Droite
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  + 0 * targetRectCote  + 0 * (targetRect.width()   - targetRectCote),
                                                             targetRect.y()  + 1 * targetRectCote  + 0 * (targetRect.height()  - targetRectCote)),  QSizeF(1 * targetRectCote  + 0 * (targetRect.width()  - 2 * targetRectCote),  0 * targetRectCote  + 1 * (targetRect.height()  - 2 * targetRectCote))),
                                              QRectF(QPointF(textureRect.x() + 0 * textureRectCote + 0 * (textureRect.width()  - textureRectCote),
                                                             textureRect.y() + 1 * textureRectCote + 0 * (textureRect.height() - textureRectCote)), QSizeF(1 * textureRectCote + 0 * (textureRect.width() - 2 * textureRectCote), 0 * textureRectCote + 1 * (textureRect.height() - 2 * textureRectCote)))));
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  + 0 * targetRectCote  + 1 * (targetRect.width()   - targetRectCote),
                                                             targetRect.y()  + 1 * targetRectCote  + 0 * (targetRect.height()  - targetRectCote)),  QSizeF(1 * targetRectCote  + 0 * (targetRect.width()  - 2 * targetRectCote),  0 * targetRectCote  + 1 * (targetRect.height()  - 2 * targetRectCote))),
                                              QRectF(QPointF(textureRect.x() + 0 * textureRectCote + 1 * (textureRect.width()  - textureRectCote),
                                                             textureRect.y() + 1 * textureRectCote + 0 * (textureRect.height() - textureRectCote)), QSizeF(1 * textureRectCote + 0 * (textureRect.width() - 2 * textureRectCote), 0 * textureRectCote + 1 * (textureRect.height() - 2 * textureRectCote)))));
                //Central
                drawingRects.append(qMakePair(QRectF(QPointF(targetRect.x()  + targetRectCote,  targetRect.y()  + targetRectCote),  QSizeF(targetRect.width()  - 2 * targetRectCote,  targetRect.height()  - 2 * targetRectCote)),
                                              QRectF(QPointF(textureRect.x() + textureRectCote, textureRect.y() + textureRectCote), QSizeF(textureRect.width() - 2 * textureRectCote, textureRect.height() - 2 * textureRectCote))));
            }
        }

        //Rectangle intégral
        if(!drawingRects.count())
            drawingRects.append(qMakePair(targetRect, textureRect));


        //Dessin
        if(texture)
            texture->pushTexture();
        for(quint8 drawingRectsIndex = 0 ; drawingRectsIndex < drawingRects.count() ; drawingRectsIndex++) {
            QRectF currentTargetRect = drawingRects.at(drawingRectsIndex).first, currentTextureRect = drawingRects.at(drawingRectsIndex).second;

            if((texture) && (!texture->isSyphon()))
                currentTextureRect = QRectF(QPointF(currentTextureRect.x()     / texture->size.width(), currentTextureRect.y()      / texture->size.height()),
                                            QSizeF (currentTextureRect.width() / texture->size.width(), currentTextureRect.height() / texture->size.height()));

            if(texture)
                currentTextureRect = QRectF(QPointF(currentTextureRect.x(), currentTextureRect.y() + currentTextureRect.height()), QSizeF(currentTextureRect.width(), -currentTextureRect.height()));


            //currentTargetRect = currentTargetRect.toRect();
            if(texture) {
                if(texture->mirrorX) {
                    QRectF oldCurrentTextureRect = currentTextureRect;
                    currentTextureRect.setTopLeft    (oldCurrentTextureRect.topRight());
                    currentTextureRect.setBottomRight(oldCurrentTextureRect.bottomLeft());
                }
                if(texture->mirrorY) {
                    QRectF oldCurrentTextureRect = currentTextureRect;
                    currentTextureRect.setTopLeft    (oldCurrentTextureRect.bottomLeft());
                    currentTextureRect.setBottomRight(oldCurrentTextureRect.topRight());
                }
            }

            glBegin(GL_QUADS);

            colors.glColorStart(alpha, selected);
            if(texture)  glTexCoord2f(currentTextureRect.topLeft().x(), currentTextureRect.topLeft().y());
            glVertex2f(currentTargetRect.topLeft()    .x(), currentTargetRect.topLeft()    .y());

            if(colors.colorDirection(selected))  colors.glColorEnd(alpha, selected);
            if(texture)  glTexCoord2f(currentTextureRect.topRight().x(), currentTextureRect.topRight().y());
            glVertex2f(currentTargetRect.topRight()   .x(), currentTargetRect.topRight()   .y());

            colors.glColorEnd(alpha, selected);
            if(texture)  glTexCoord2f(currentTextureRect.bottomRight().x(), currentTextureRect.bottomRight().y());
            glVertex2f(currentTargetRect.bottomRight().x(), currentTargetRect.bottomRight().y());

            if(colors.colorDirection(selected))  colors.glColorStart(alpha, selected);
            if(texture)  glTexCoord2f(currentTextureRect.bottomLeft().x(), currentTextureRect.bottomLeft().y());
            glVertex2f(currentTargetRect.bottomLeft() .x(), currentTargetRect.bottomLeft() .y());

            glEnd();
        }
        if(texture)
            texture->popTexture();
    }

    //Bordure
    if((colors.borderNeed()) & (!colors.isBorderTransparent())) {
        glLineWidth(colors.borderWidth(selected));
        glBegin(GL_LINE_LOOP);

        colors.glBorderStart(alpha, selected);
        glVertex2f(targetRect.topLeft()    .x(), targetRect.topLeft()    .y());

        if(colors.borderDirection(selected))  colors.glBorderEnd(alpha, selected);
        glVertex2f(targetRect.topRight()   .x(), targetRect.topRight()   .y());

        colors.glBorderEnd(alpha, selected);
        glVertex2f(targetRect.bottomRight().x(), targetRect.bottomRight().y());

        if(colors.borderDirection(selected))  colors.glBorderStart(alpha, selected);
        glVertex2f(targetRect.bottomLeft() .x(), targetRect.bottomLeft() .y());

        glEnd();
        glLineWidth(1);
    }
}


qreal OpenGlDrawing::measureText(const OpenGlFont &font, qreal width, const QString &text) {
    return drawText(0, Qt::black, font, QRectF(0, 0, width, 0), text);
}
QImage OpenGlDrawing::drawText(const QColor &color, const OpenGlFont &font, const QSizeF &size, const QString &text) {
    QImage sourceImage(size.toSize(), QImage::Format_ARGB32_Premultiplied);
    sourceImage.fill(Qt::transparent);

    QPainter painter(&sourceImage);
    OpenGlDrawing::drawText(&painter, color, font, QRectF(QPointF(0, 0), sourceImage.size()), text);
    painter.end();
    return sourceImage;
}
qreal OpenGlDrawing::drawText(QPainter *painter, const QColor &color, const OpenGlFont &font, const QRectF &rect, const QString &_text) {
    if(painter)
        painter->setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing | QPainter::TextAntialiasing);

    QFontMetrics fontMetrics(font);
    QString text = _text;
    if((font.alignement() & Qt::TextSingleLine) == Qt::TextSingleLine)
        text = QFontMetrics(font).elidedText(text, Qt::ElideRight, rect.width());

    if((text.toLower().startsWith("<p")) || (text.toLower().startsWith("<span"))) {
        QTextOption textOption(font.alignementFlags());
        textOption.setTabStop(40);

        QStaticText staticText(text);
        staticText.setTextWidth(rect.width());
        staticText.setTextOption(textOption);

        if(painter) {
            QPointF pos = rect.topLeft();
            painter->setFont(font);
            if(((font.alignementFlags() & Qt::AlignVCenter) == Qt::AlignVCenter) || ((font.alignementFlags() & Qt::AlignBottom ) == Qt::AlignBottom)) {
                painter->setPen(Qt::transparent);

                QString textMeasure = text;
                textMeasure = textMeasure.replace("<br/>", "\n").replace("<br>", "\n");
                qreal fontHeight = 0;
                if(text.toLower().startsWith("<p"))
                    fontHeight = fontMetrics.boundingRect(rect.toRect(), font.alignement(), textMeasure).height();
                else
                    fontHeight = staticText.size().height();

                //painter->drawStaticText(QPointF(0, 0), staticText);
                //qDebug("%s\tH:%f\tC:%f\tSH:%f\tPOS:%f", qPrintable(text), rect.height(), rect.center().y(), staticText.size().height(), rect.center().y() - staticText.size().height()/2);
                if((font.alignementFlags() & Qt::AlignVCenter) == Qt::AlignVCenter)
                    pos.setY(qMax(qreal(0.), rect.center().y() - fontHeight/2));
                else if((font.alignementFlags() & Qt::AlignBottom) == Qt::AlignBottom)
                    pos.setY(rect.bottom() - fontHeight);

                painter->setPen(color);
                painter->drawStaticText(pos, staticText);
            }
            else {
                painter->setPen(color);
                painter->drawStaticText(pos, staticText);
            }
        }
        return staticText.size().height();
    }
    else if((font.leading() == 100) && (font.pLeading() == 0)) {
        if(painter) {
            painter->setPen(color);
            painter->setFont(font);
            painter->drawText(rect, font.alignement(), text);
        }
        return fontMetrics.boundingRect(rect.toRect(), font.alignement(), text).height();
    }
    else {
        QTextOption textOption(font.alignementFlags());
        textOption.setTabStop(40);
        qreal leading = fontMetrics.leading() + fontMetrics.height() * font. leading() / 100.;
        qreal interparagraph =                  fontMetrics.height() * font.pLeading() / 100.;
        qreal height = 0;

        //qreal totalHeight = fontMetrics.boundingRect(0, 0, rect.width(), 0, font.alignement(), _text).height();
        QStringList paragraphs = text.split("\n");

        qreal textPreCalculatedHeight = rect.height();
        if(((font.alignementFlags() & Qt::AlignVCenter) == Qt::AlignVCenter) || ((font.alignementFlags() & Qt::AlignBottom ) == Qt::AlignBottom))
            textPreCalculatedHeight = fontMetrics.boundingRect(0, 0, rect.width(), 0, font.alignement(), text).height() + paragraphs.count() * interparagraph;

        foreach(const QString &paragraph, paragraphs) {
            QTextLayout textLayout(paragraph, font);
            textLayout.setTextOption(textOption);
            textLayout.beginLayout();
            while (1) {
                QTextLine line = textLayout.createLine();
                if (!line.isValid())
                    break;

                line.setLineWidth(rect.width());
                line.setPosition(QPointF(0, height));
                height += leading;
            }
            textLayout.endLayout();

            if(painter)
                painter->setPen(color);

            QPointF margin(0, 1);
            if(     (font.alignementFlags() & Qt::AlignVCenter) == Qt::AlignVCenter)
                margin.setY(rect.height() / 2 - textPreCalculatedHeight / 2);
            else if((font.alignementFlags() & Qt::AlignBottom ) == Qt::AlignBottom)
                margin.setY(rect.height() - textPreCalculatedHeight);

            if(painter)
                textLayout.draw(painter, rect.topLeft() + margin);

            height += interparagraph;
        }
        return height;
    }
}
