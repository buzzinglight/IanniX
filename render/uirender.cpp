/*
    IanniX — a graphical real-time open-source sequencer for digital art
    Copyright (C) 2010-2012 — IanniX Association

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "uirender.h"
#include "ui_uirender.h"

UiRender::UiRender(QWidget *parent) :
    Render(parent),
    ui(new Ui::UiRender) {
    firstLaunch = true;
    capturedFramesStart = false;

    setFocusPolicy(Qt::StrongFocus);

    //Initialize view
    ui->setupUi(this);
    setCursor(Qt::OpenHandCursor);
    grabGesture(Qt::PinchGesture);
    setAcceptDrops(true);

    //Syphon
    interfaceSyphon = new InterfaceSyphon();
    renderPreviewTextureInit = false;
    performanceMode = false;

    //Initialisations
    document = 0;
    setDocument(0);
    setMouseTracking(true);
    isRemoving = false;
    mousePressed = false;
    mouseShift = false;
    mouseObjectDrag = false;
    selectedHover = 0;
    scale = 1;
    scaleDest = 3;

    //Render options
    Application::render = this;
    Global::renderFont = QFont("Arial");
    Global::renderFont.setPixelSize(11);

    setZoom(100);

    //Refresh
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
}
UiRender::~UiRender() {
    delete ui;
}
void UiRender::changeEvent(QEvent *e) {
    QGLWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


//Textures
bool UiRender::loadTexture(UiRenderTexture *texture, bool gl) {
    if(gl) {
        if(texture->filename.exists()) {
            glEnable(GL_TEXTURE_2D);
            glGenTextures(1, &(texture->texture));
            glBindTexture(GL_TEXTURE_2D, texture->texture);
            QImage tex = QGLWidget::convertToGLFormat(QImage(texture->filename.absoluteFilePath()));
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glDisable(GL_TEXTURE_2D);
            texture->loaded = true;
            Global::textures->update();
            return true;
        }
    }
    else {
        Global::textures->insert(texture->name, texture);
        Global::textures->update();
        return true;
    }
    return false;
}
bool UiRender::removeTexture(const QString &name) {
    if(Global::textures->contains(name)) {
        delete Global::textures->value(name);
        Global::textures->remove(name);
        return true;
    }
    Global::textures->update();
    return false;
}

void UiRender::capture(qreal scaleFactor) {
    if(scaleFactor <= 0) {
#ifdef FFMPEG_INSTALLED
        //Encoder
        renderSize = QSize(800, 600);
        resize(renderSize);

        if(videoEncoder.isOk()) {
            timer->stop();
            qDebug("Fermeture de la video : %d", videoEncoder.close());
            timer->start(1000./50.);
        }
        else {
            setInterval(1000./25.);
            qDebug("Creation de la video : %d", videoEncoder.createFile("_test.avi", renderSize.width(), renderSize.height(), 5000000, 20, 25));
        }
#else
        if(capturedFramesStart) {
            capturedFramesStart = false;
            //Sauvegarde
#ifdef QT4
            QString basePath = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation) + "/IanniX_Capture_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "/";
#else
            QString basePath = QStandardPaths::DesktopLocation + "/IanniX_Capture_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + "/");
#endif
            QDir().mkpath(basePath);
            quint16 index = 0;
            foreach(const QImage &capturedFrame, capturedFrames)
                capturedFrame.save(basePath + tr("Image_%1.png").arg(index++, 5, 10, QChar('0')));
            capturedFrames.clear();
        }
        else {
            capturedFrames.clear();
            capturedFramesStart = true;
        }
#endif
    }
    else
        captureFrame(scaleFactor);
}
bool UiRender::captureFrame(qreal scaleFactor, const QString &filename) {
    renderSize = size() * scaleFactor;
    Global::forceLists         = true;
    Global::forceTexture       = true;
    Global::forceFrustumInInit = true;

    if(filename.isEmpty()) {
        QPixmap picture = renderPixmap(renderSize.width(), renderSize.height());
        if(picture.isNull()) {
            picture = QPixmap::fromImage(grabFrameBuffer(false));
            (new UiMessageBox())->display(tr("Graphical card error"), tr("Due to hardware issue, the high resolution snapshot creation failed.\nA classical snapshot has been saved on your desktop."), QDialogButtonBox::Ok);
        }
#ifdef QT4
        picture.save(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation) + "/IanniX_Capture_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + ".png");
#else
        picture.save(QStandardPaths::DesktopLocation + "/"IanniX_Capture_" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss") + ".png");
#endif
    } else {
        QDir().mkpath(QFileInfo(filename).absoluteDir().absolutePath());
        renderPixmap(renderSize.width(), renderSize.height()).save(filename);
    }
    Global::forceLists         = false;
    Global::forceTexture       = false;
    Global::forceFrustumInInit = false;
    return true;
}

void UiRender::centerOn(const NxPoint & center, bool force) {
    Global::axisCenterDest = -center;
    if(force)
        Global::axisCenter = Global::axisCenterDest;
    setZoom();
}

void UiRender::rotateTo(const NxPoint & rotation, bool force) {
    Global::rotationDest = rotation;
    if(force)
        Global::rotation = Global::rotationDest;
    setZoom();
}

void UiRender::setPerformanceMode(bool _performanceMode) {
    performanceMode = _performanceMode;
    if(performanceMode) {
        setParent(0);
        setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        move(pos());
        resize(size());
        show();
        //activateWindow();
        //raise();
    }
    else {
        //activateWindow();
        //raise();
    }
}

//Initialize event
void UiRender::initializeGL() {
    //OpenGL options
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT,  GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT,            GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT,             GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT,          GL_NICEST);

    //Force resize
    //resizeGL();
    Application::current->readyToStart();
}

//Resize event
void UiRender::resizeGL(int width, int height) {
    //Set viewport
    glViewport(0, 0, (GLint)width, (GLint)height);

    if(Global::forceFrustumInInit)
        setFrustum();
}

void UiRender::setFrustum() {
    qreal width  = renderSize.width();
    qreal height = renderSize.height();
    //Calculate area
    Global::axisArea = NxRect(NxPoint(), NxSize(10, 10));
    if(width > height) {
        if(Global::axisArea.width() > -Global::axisArea.height())
            Global::axisArea.setHeight(-Global::axisArea.width() * height/width);
        else
            Global::axisArea.setWidth(-Global::axisArea.height() * width/height);
    }
    else {
        if(Global::axisArea.width() > -Global::axisArea.height())
            Global::axisArea.setHeight(-Global::axisArea.width() * height/width);
        else
            Global::axisArea.setWidth(-Global::axisArea.height() * width/height);
    }
    Global::axisArea.setWidth(Global::axisArea.width()   * Global::zoomLinear);
    Global::axisArea.setHeight(Global::axisArea.height() * Global::zoomLinear);
    Global::axisArea.translate(-NxPoint(Global::axisArea.size().width()/2, Global::axisArea.size().height()/2));
    Global::axisArea.translate(-Global::axisCenter);

    //Set axis
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(Global::axisArea.left(), Global::axisArea.right(), Global::axisArea.bottom(), Global::axisArea.top(), 50, 650.0);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

//Paint event
void UiRender::paintGL() {
    QMapIterator<QString, UiRenderTexture*> textureIterator(*Global::textures);
    while (textureIterator.hasNext()) {
        textureIterator.next();
        if((!textureIterator.value()->loaded) || (Global::forceTexture))
            loadTexture(textureIterator.value(), true);
    }

    //Intertial system
    Global::axisCenter = Global::axisCenter + (Global::axisCenterDest - Global::axisCenter) / 3;
    Global::zoomLinear = Global::zoomLinear + (Global::zoomLinearDest - Global::zoomLinear) / 3;
    Global::rotation = Global::rotation + (Global::rotationDest - Global::rotation) / 6;
    //if(qAbs(UiRenderOptions::rotation.z() - UiRenderOptions::rotationDest.z()) > 360)
    //    UiRenderOptions::rotation.setZ(UiRenderOptions::rotationDest.z());
    translation = translation + (translationDest - translation) / 3;
    scale = scale + (scaleDest - scale) / 3;

    //Object sizes
    Global::objectSize = 0.15;
    if(Global::triggerAutosize)
        Global::objectSize *= 0.5*Global::zoomLinear;

    if(!Global::forceFrustumInInit) {
        renderSize = size();
        setFrustum();
    }

    //Clear
    qglClearColor(Global::colors->value(Global::colorsPrefix() + "_empty"));
    glClear(GL_COLOR_BUFFER_BIT);

    //Translation
    Global::axisArea.translate(Global::axisCenter);

    //Start drawing
    glPushMatrix();

    //First operations
    glTranslatef(0.0, 0.0, -150);

    if((Global::followId > 0) && (document) && (document->objects.contains(Global::followId)) && (document->objects.value(Global::followId)->getType() == ObjectsTypeCursor)) {
        NxCursor *object = (NxCursor*)document->objects.value(Global::followId);
        //rotationDest.setX(-object->getCurrentAngleRoll());
        //rotationDest.setY(-82 - object->getCurrentAnglePitch());
        Global::rotationDest.setZ(-object->getCurrentAngle().z() + 90);
        Global::rotation.setZ(Global::rotationDest.z());
        translationDest = -object->getCurrentPos();
        //scaleDest = 1 * 5;
    }
    glRotatef(Global::rotation.y(), 1, 0, 0);
    glRotatef(Global::rotation.x(), 0, 1, 0);
    glRotatef(Global::rotation.z(), 0, 0, 1);
    glScalef(scale, scale, scale);
    glTranslatef(translation.x(), translation.y(), translation.z());

    if((Global::rotationDest.x() == 0) && (Global::rotationDest.y() == 0) && (Global::rotationDest.z() == 0))
        Global::allowSelection = true;
    else
        Global::allowSelection = false;

    //Start measure
    Transport::perfOpenGLRefreshTime += renderMeasure.elapsed() / 1000.0F;
    Transport::perfOpenGLCounterTime++;
    renderMeasure.start();


    if(document) {
        //Background
        paintBackground();

        //Paint axis
        paintAxisGrid();

        //Paint selection
        paintSelection();

        //Draw objects
        //Browse documents
        foreach(NxGroup *group, document->groups) {
            if(((!Application::current->isGroupSoloActive) && (group->isNotMuted())) || ((Application::current->isGroupSoloActive) && (group->isSolo())))
                Global::paintThisGroup = true;
            else
                Global::paintThisGroup = false;

            //Browse active/inactive objects
            for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
                //Browse all types of objects
                for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                    //Browse objects
                    foreach(NxObject *object, group->objects[activityIterator][typeIterator]) {
                        //Draw the object
                        if(!isRemoving) {
                            bool oldPaintThisGroup = Global::paintThisGroup;
                            if(!(((!Application::current->isObjectSoloActive) && (object->isNotMuted())) || ((Application::current->isObjectSoloActive) && (object->isSolo()))))
                                Global::paintThisGroup = false;
                            object->paint();
                            Global::paintThisGroup = oldPaintThisGroup;
                        }
                        else
                            break;
                    }
                }
            }
        }
        isRemoving = false;
#ifdef KINECT_INSTALLED
        if(Application::current->kinect)
            Application::current->kinect->paint();
#endif
    }
    glPopMatrix();

#ifdef FFMPEG_INSTALLED
    if(videoEncoder.isOk())
        qDebug("%d encode", videoEncoder.encodeImage(grabFrameBuffer()));
#endif

#ifdef SYPHON_INSTALLED
    if(!interfaceSyphon->serverInit) {
        makeCurrent();
        interfaceSyphon->createSyphonServer();
    }
    if(interfaceSyphon->serverEnable) {
        glEnable(GL_TEXTURE_2D);
        if(!interfaceSyphon->serverTexture) {
            glGenTextures(1, &interfaceSyphon->serverTexture);
        }
        glBindTexture(GL_TEXTURE_2D, interfaceSyphon->serverTexture);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, renderSize.width(), renderSize.height(), 0);
        interfaceSyphon->publishTexture(GL_TEXTURE_2D, renderSize.width(), renderSize.height());
        glDisable(GL_TEXTURE_2D);
    }
#endif

    if((performanceMode) && (Application::current->getPerformancePreview())) {
        glEnable(GL_TEXTURE_2D);
        if(!renderPreviewTextureInit) {
            glGenTextures(1, &renderPreviewTexture);
            renderPreviewTextureInit = true;
        }
        glBindTexture(GL_TEXTURE_2D, renderPreviewTexture);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, renderSize.width(), renderSize.height(), 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glDisable(GL_TEXTURE_2D);
        Application::current->getRenderPreview()->paintPreview(this, renderPreviewTexture, renderSize);
    }

    if(capturedFramesStart)
        capturedFrames << grabFrameBuffer();
}


//Draw background
void UiRender::paintBackground() {
    if(Global::textures->contains("background")) {
        UiRenderTexture *texture = Global::textures->value("background");
        if((texture) && (texture->loaded) && (texture->mapping.width() != 0) && (texture->mapping.height() != 0)) {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture->texture);
            glBegin(GL_QUADS);
            qglColor(Global::colors->value(Global::colorsPrefix() + "_background"));
            glLineWidth(1);
            glTexCoord2d(0, 0); glVertex3f(texture->mapping.left() , texture->mapping.bottom(), 0);
            glTexCoord2d(1, 0); glVertex3f(texture->mapping.right(), texture->mapping.bottom(), 0);
            glTexCoord2d(1, 1); glVertex3f(texture->mapping.right(), texture->mapping.top(), 0);
            glTexCoord2d(0, 1); glVertex3f(texture->mapping.left() , texture->mapping.top(), 0);
            glEnd();
            glDisable(GL_TEXTURE_2D);
        }
    }
}


//Draw grid axis
void UiRender::paintAxisGrid() {
    if(Global::paintAxisGrid) {
        //Draw axis
        Global::axisArea.translate(-Global::axisCenter);

        for(qreal x = 0 ; x < ceil(Global::axisArea.right()) ; x += Global::axisGrid) {
            if((x == 0) && (Global::paintAxisGrid)) {
                if(Global::mouseSnapX)
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_axisSnap"));
                else
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_axis"));
                glLineWidth(2);
            }
            else {
                if(Global::mouseSnapX)
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_gridSnap"));
                else
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_grid"));
                glLineWidth(1);
            }
            glBegin(GL_LINES);
            glVertex3f(x, Global::axisArea.bottom(), 0);
            glVertex3f(x, Global::axisArea.top(), 0);
            glEnd();
        }
        for(qreal x = 0 ; x > floor(Global::axisArea.left()) ; x -= Global::axisGrid) {
            if((x == 0) && (Global::paintAxisGrid)) {
                if(Global::mouseSnapX)
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_axisSnap"));
                else
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_axis"));
                glLineWidth(2);
            }
            else {
                if(Global::mouseSnapX)
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_gridSnap"));
                else
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_grid"));
                glLineWidth(1);
            }
            glBegin(GL_LINES);
            glVertex3f(x, Global::axisArea.bottom(), 0);
            glVertex3f(x, Global::axisArea.top(), 0);
            glEnd();
        }
        for(qreal y = 0 ; y < ceil(Global::axisArea.top()) ; y += Global::axisGrid) {
            if((y == 0) && (Global::paintAxisGrid)) {
                if(Global::mouseSnapY)
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_axisSnap"));
                else
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_axis"));
                glLineWidth(2);
            }
            else {
                if(Global::mouseSnapY)
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_gridSnap"));
                else
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_grid"));
                glLineWidth(1);
            }
            glBegin(GL_LINES);
            glVertex3f(Global::axisArea.left(), y, 0);
            glVertex3f(Global::axisArea.right(), y, 0);
            glEnd();
        }
        for(qreal y = 0 ; y > floor(Global::axisArea.bottom()) ; y -= Global::axisGrid) {
            if((y == 0) && (Global::paintAxisGrid)) {
                if(Global::mouseSnapY)
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_axisSnap"));
                else
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_axis"));
                glLineWidth(2);
            }
            else {
                if(Global::mouseSnapY)
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_gridSnap"));
                else
                    qglColor(Global::colors->value(Global::colorsPrefix() + "_grid"));
                glLineWidth(1);
            }
            glBegin(GL_LINES);
            glVertex3f(Global::axisArea.left(), y, 0);
            glVertex3f(Global::axisArea.right(), y, 0);
            glEnd();
        }

        Global::axisArea.translate(Global::axisCenter);
    }
}

//Draw selection
void UiRender::paintSelection() {
    //Axis color
    qglColor(Global::colors->value(Global::colorsPrefix() + "_selection"));
    glLineWidth(1);

    //Draw axis
    glBegin(GL_QUADS);
    glVertex3f(Global::selectionArea.left(),  Global::selectionArea.top(), 0);
    glVertex3f(Global::selectionArea.right(), Global::selectionArea.top(), 0);
    glVertex3f(Global::selectionArea.right(), Global::selectionArea.bottom(), 0);
    glVertex3f(Global::selectionArea.left(),  Global::selectionArea.bottom(), 0);
    glVertex3f(Global::selectionArea.left(),  Global::selectionArea.top(), 0);
    glEnd();
}


void UiRender::wheelEvent(QWheelEvent *event) {
    bool mouse3D = event->modifiers() & Qt::AltModifier;

    //Zoom calculation
    if(mouse3D) {
        scaleDest = qMax((qreal)0, scale - (qreal)event->delta() / 150.0F);
        //refresh();
    }
    else if(event->modifiers() & Qt::ShiftModifier) Application::current->execute(QString("%1 %2").arg(COMMAND_ZOOM).arg(Global::zoomValue - (qreal)event->delta() / 3.0F), ExecuteSourceGui);
    else                                            Application::current->execute(QString("%1 %2").arg(COMMAND_ZOOM).arg(Global::zoomValue - (qreal)event->delta() / 15.0F), ExecuteSourceGui);
}
void UiRender::mousePressEvent(QMouseEvent *event) {
    //Save state when pressed
    mousePressedRawPos = NxPoint(event->pos().x(), event->pos().y());
    //Mouse position
    mousePressedAreaPosNoCenter = NxPoint((event->pos().x() - (qreal)size().width()/2) / (qreal)size().width() * Global::axisArea.width(), (event->pos().y() - (qreal)size().height()/2) / (qreal)size().height() * Global::axisArea.height());
    mousePressedAreaPos = mousePressedAreaPosNoCenter - Global::axisCenter;
    if(Global::mouseSnapX) {
        mousePressedAreaPosNoCenter.setX(qRound(mousePressedAreaPosNoCenter.x() / Global::axisGrid) * Global::axisGrid);
        mousePressedAreaPos.setX(qRound(mousePressedAreaPos.x() / Global::axisGrid) * Global::axisGrid);
    }
    if(Global::mouseSnapY) {
        mousePressedAreaPosNoCenter.setY(qRound(mousePressedAreaPosNoCenter.y() / Global::axisGrid) * Global::axisGrid);
        mousePressedAreaPos.setY(qRound(mousePressedAreaPos.y() / Global::axisGrid) * Global::axisGrid);
    }

    mousePressed = true;
    mousePressedAxisCenter = Global::axisCenter;
    mouseCommand = (event->modifiers() & Qt::ControlModifier);
    mouseShift = (event->modifiers() & Qt::ShiftModifier);
    rotationDrag = Global::rotation;
    translationDrag = translation;

    if(cursor().shape() == Qt::BlankCursor)
        return;

    //Start area selection
    if((Global::editing) && (Global::allowSelection)) {
        foreach(NxObject *selected, selection)
            selected->setSelected(false);
        selection.clear();
        //selectedHover->setSelected(true);   /// select this one
        //selectionAdd(selectedHover);
        if(Global::editingMode == EditingModeFree) {
            //emit(editingStart(mousePressedAreaPos));
            if(Global::editingFirstPoint)
                emit(editingStart(mousePressedAreaPos));
            else
                emit(editingMove(mousePressedAreaPos, true));
        }
        else if(Global::editingMode == EditingModePoint) {
            if(Global::editingFirstPoint)
                emit(editingStart(mousePressedAreaPos));
            else
                emit(editingMove(mousePressedAreaPos, true));
        }
        else if(Global::editingMode == EditingModeTriggers)
            emit(editingStart(mousePressedAreaPos));
        else if(Global::editingMode == EditingModeCircle)
            emit(editingStart(mousePressedAreaPos));
        Global::editingFirstPoint = false;
    }
    /*
    else if(!Global::allowSelection) {
        foreach(NxObject *selected, selection)
            selected->setSelected(false);
        selection.clear();
        if(selectedHover) {
            selectedHover->setSelectedHover(false);
            selectedHover = 0;
        }
    }
    */
    else {
        if(mouseShift) {
            Global::selectionArea.setTopLeft(mousePressedAreaPos);
            Global::selectionArea.setBottomRight(mousePressedAreaPos);
            if(cursor().shape() != Qt::BlankCursor)
                setCursor(Qt::CrossCursor);
        } else if (selectedHover) {
            if (!selectedHover->getSelected()) {
                foreach(NxObject *selected, selection)
                    selected->setSelected(false);
                selection.clear();
                selectedHover->setSelected(true);
                selectionAdd(selectedHover);
            }
        }
        else if((!selectedHover) && (cursor().shape() != Qt::BlankCursor))
            setCursor(Qt::ClosedHandCursor);
    }
}
void UiRender::mouseReleaseEvent(QMouseEvent *event) {
    //Edition
    if((Global::editing) && (Global::allowSelection) && (cursor().shape() != Qt::BlankCursor)) {
        /*
        if(editingMode == EditingModeFree) {
            emit(editingStop());
            editing = false;
        }
        */
    }
    else if((cursor().shape() != Qt::BlankCursor) && (Global::allowSelection)) {
        //Copy area selection
        foreach(NxObject *selected, selectionRect)
            selectionAdd(selected);
        selectionRect.clear();

        //End of drag
        foreach(NxObject* object, selection)
            object->dragStop();
        if(selectedHover)
            selectedHover->dragStop();

        emit(selectionChanged());

        //Simple clic
        if(mousePressedRawPos == NxPoint(event->pos().x(), event->pos().y())) {
            if(selectedHover) {
                //Click on an object
                if(!mouseShift)
                    selectionClear();

                //Invert selection
                if(selectedHover->getSelected()) {
                    selectedHover->setSelected(false);
                    selection.removeOne(selectedHover);
                }
                else
                    selectionAdd(selectedHover);
            }
            else if((!selectedHover) && (!mouseShift))
                //Click on the workspace
                selectionClear();
        }
    }

    //Release states
    mousePressed = false;
    mouseShift = false;
    mouseObjectDrag = false;
    Global::selectionArea.setSize(NxSize(0, 0));
    if((cursor().shape() != Qt::BlankCursor) && !((Global::editing) && ((Global::editingMode == EditingModeFree) || (Global::editingMode == EditingModePoint) || (Global::editingMode == EditingModeTriggers) || (Global::editingMode == EditingModeCircle)))) {
        if(mouseShift)
            setCursor(Qt::CrossCursor);
        else
            setCursor(Qt::OpenHandCursor);
    }
}
void UiRender::mouseMoveEvent(QMouseEvent *event) {
    //Mouse position
    bool mouse3D = event->modifiers() & Qt::AltModifier;
    NxPoint mousePosNoCenter = NxPoint((event->pos().x() - (qreal)size().width()/2) / (qreal)size().width() * Global::axisArea.width(), (event->pos().y() - (qreal)size().height()/2) / (qreal)size().height() * Global::axisArea.height());
    NxPoint mousePos = mousePosNoCenter - Global::axisCenter, mousePosBackup = mousePos;
    NxPoint deltaMouseRaw = NxPoint(event->pos().x(), event->pos().y()) - mousePressedRawPos;

    if(Global::mouseSnapX)  mousePos.setX(qRound(mousePos.x() / Global::axisGrid) * Global::axisGrid);
    if(Global::mouseSnapY)  mousePos.setY(qRound(mousePos.y() / Global::axisGrid) * Global::axisGrid);
    bool noSelection = true;
    emit(mousePosChanged(mousePos));

    if((Global::editing) && (cursor().shape() != Qt::BlankCursor) && (Global::allowSelection)) {
        if((mousePressed) && (Global::editingMode == EditingModeFree))
            emit(editingMove(mousePos, true));
        else if((!Global::editingFirstPoint) && ((Global::editingMode == EditingModeFree) || (Global::editingMode == EditingModePoint))){
            emit(editingMove(mousePos, false));
        }
    }
    else {
        //Cursor
        if((cursor().shape() != Qt::BlankCursor) && (Global::allowSelection)) {
            if((mouseShift) && (mousePressed))              setCursor(Qt::CrossCursor);
            else if((selectedHover) && (!mousePressed))     setCursor(Qt::PointingHandCursor);
            else if((!selectedHover) && (mousePressed))     setCursor(Qt::ClosedHandCursor);
            else                                            setCursor(Qt::OpenHandCursor);
        }

        //Mouse pressed
        if(mousePressed) {
            if(mouse3D) {
                if(mouseShift)  translationDest = translationDrag + 10 * NxPoint(deltaMouseRaw.x() / (qreal)size().width(), deltaMouseRaw.y() / (qreal)size().height());
                else {
                    NxPoint newRotation = rotationDrag + 360 * NxPoint(0, deltaMouseRaw.y() / (qreal)size().height(), deltaMouseRaw.x() / (qreal)size().width());
                    Application::current->execute(QString("%1 %2 %3 %4").arg(COMMAND_ROTATE).arg(newRotation.x()).arg(newRotation.y()).arg(newRotation.z()), ExecuteSourceGui);
                }
            }
            else if((mouseShift) && (Global::allowSelection) && (cursor().shape() != Qt::BlankCursor)) {
                Global::selectionArea.setBottomRight(mousePos);
            }
            else if((!Global::allowLockPos) && (Global::allowSelection) && ((selection.contains(selectedHover)) || (selectedHover) || (mouseObjectDrag)) && (!mouseCommand) && (cursor().shape() != Qt::BlankCursor)) {
                if(!mouseObjectDrag) {
                    mouseObjectDrag = true;
                    Application::current->pushSnapshot();

                    foreach(NxObject* object, selection)
                        object->dragStart(mousePos, selection.count() > 1);
                }
                NxPoint dragTranslation = mousePos - mousePressedAreaPos;
                if(selectedHover) {
                    if(Global::mouseSnapX)  dragTranslation.setX(qRound((selectedHover->getPosDrag().x() + dragTranslation.x()) / Global::axisGrid) * Global::axisGrid - selectedHover->getPosDrag().x());
                    if(Global::mouseSnapY)  dragTranslation.setY(qRound((selectedHover->getPosDrag().y() + dragTranslation.y()) / Global::axisGrid) * Global::axisGrid - selectedHover->getPosDrag().y());
                }
                foreach(NxObject* object, selection)
                    object->drag(dragTranslation, mousePos, selection.count() > 1);
            }
            else if(!mouseObjectDrag) {
                //New center
                NxPoint newCenter = -(mousePressedAxisCenter + NxPoint((mousePosNoCenter - mousePressedAreaPosNoCenter).x(), (mousePosNoCenter - mousePressedAreaPosNoCenter).y()));
                Application::current->execute(QString("%1 %2 %3").arg(COMMAND_CENTER).arg(newCenter.x()).arg(newCenter.y()), ExecuteSourceGui);
            }
        }

        mousePos = mousePosBackup;
        if((document) && (cursor().shape() != Qt::BlankCursor) && (Global::allowSelection) && (!Global::allowLockPos)) {
            UiRenderSelection eligibleSelection;

            //Browse documents
            foreach(NxGroup *group, document->groups) {
                //Is groups visible ?
                if((((!Application::current->isGroupSoloActive) && (group->isNotMuted())) || ((Application::current->isGroupSoloActive) && (group->isSolo())))) {
                    //Browse active/inactive objects
                    for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {
                        //Browse all types of objects
                        for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {
                            //Are objects visible ?
                            if(((typeIterator == ObjectsTypeCursor) && (Global::allowSelectionCursors)) || ((typeIterator == ObjectsTypeCurve) && (Global::allowSelectionCurves)) || ((typeIterator == ObjectsTypeTrigger) && (Global::allowSelectionTriggers))) {
                                //Browse objects
                                foreach(NxObject *object, group->objects[activityIterator][typeIterator]) {
                                    //Is Z visible ?
                                    if(((!Application::current->isObjectSoloActive) && (object->isNotMuted())) || ((Application::current->isObjectSoloActive) && (object->isSolo()))) {
                                        //Check selection
                                        if(object->isMouseHover(mousePos)) {
                                            if(object->getType() == ObjectsTypeCurve)
                                                eligibleSelection.prepend(object);
                                            else
                                                eligibleSelection.append(object);
                                        }

                                        //Add the object to selection if click+shift
                                        if((mouseShift) || (mouseCommand)) {
                                            NxRect objectBoundingRect = object->getBoundingRect();
                                            if(objectBoundingRect.width() == 0)  objectBoundingRect.setWidth(0.001);
                                            if(objectBoundingRect.height() == 0) objectBoundingRect.setHeight(0.001);
                                            if(Global::selectionArea.intersects(objectBoundingRect)) {
                                                selectionRect.append(object);
                                                object->setSelected(true);
                                            }
                                            else {
                                                selectionRect.removeOne(object);
                                                if(!selection.contains(object))
                                                    object->setSelected(false);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            foreach(NxObject *object, eligibleSelection) {
                bool selected = false;
                if(object->getType() == ObjectsTypeCurve) {
                    NxCurve *curve = (NxCurve*)object;
                    if(curve->isMouseHover(mousePos)) {
                        selected = true;
                        if(curve->getSelected()) {
                            qreal squareSize = (0.15 * Global::zoomLinear) / 2;
                            curve->isOnPathPoint(NxRect(mousePos - NxPoint(squareSize, squareSize, squareSize) - curve->getPos(), mousePos + NxPoint(squareSize, squareSize, squareSize) - curve->getPos()));
                        }
                    }
                }
                else if(object->isMouseHover(mousePos))
                    selected = true;

                //Add the object to selection
                if((selected) && (!mousePressed)) {
                    if((selectedHover) && (selectedHover != object))
                        selectedHover->setSelectedHover(false);
                    selectedHover = object;
                    selectedHover->setSelectedHover(true);
                    emit(selectionChanged());
                    noSelection = false;
                }
            }
            if((noSelection) && (selectedHover) && ((!mousePressed))) {
                selectedHover->setSelectedHover(false);
                selectedHover = 0;
            }
        }
    }

    if(((selectedHover) && (selectedHover->getType() == ObjectsTypeCurve)) || ((Global::editing) && ((Global::editingMode == EditingModeFree) || (Global::editingMode == EditingModePoint) || (Global::editingMode == EditingModeCircle))))
        changeStatus(curveStatusTip);
    else if((selectedHover) && (selectedHover->getType() == ObjectsTypeCursor))
        changeStatus(cursorStatusTip);
    else if(((selectedHover) && (selectedHover->getType() == ObjectsTypeTrigger)) || ((Global::editing) && (Global::editingMode == EditingModeTriggers)))
        changeStatus(triggerStatusTip);
    else
        changeStatus(defaultStatusTip);
}
void UiRender::changeStatus(const QString &_statusTip) {
    if(_statusTip != statusTip()) {
        setStatusTip(_statusTip);
        UiHelp::statusHelp(this);
    }
}

void UiRender::mouseDoubleClickEvent(QMouseEvent *event) {
    bool mouse3D      = event->modifiers() & Qt::AltModifier;
    bool mouseControl = event->modifiers() & Qt::ControlModifier;
    bool mouseShift   = event->modifiers() & Qt::ShiftModifier;

    if(mouse3D) {
        scaleDest = 3;
        Application::current->execute(QString("%1 0 0 0").arg(COMMAND_ROTATE), ExecuteSourceGui);
        translationDest = NxPoint();
        //refresh();
    }
    else {
        if(cursor().shape() == Qt::BlankCursor)
            return;

        else if((Global::editing) && (Global::allowSelection)) {
            emit(editingStop());
            Global::editing = false;
        }
        else if((selectedHover) && (event->modifiers() & Qt::ShiftModifier) && (selectedHover->getType() == ObjectsTypeCurve)) {
            bool ok = false;
            NxCurve *curve = (NxCurve*)selectedHover;
            quint16 nbPoints = (new UiMessageBox())->getDouble(tr("IanniX Curve Resample"), tr("Number of points:"), QPixmap(":/infos/res_info_curve.png"), 50, 0, 32767, 1, 0, "", &ok);
            if(ok) {
                Application::current->pushSnapshot();
                curve->resample(nbPoints);
            }
        }
        else if(selectedHover) {
            if((Global::allowSelection) && (selectedHover->getType() == ObjectsTypeCurve)) {
                NxCurve *curve = (NxCurve*)selectedHover;
                curve->addMousePointAt(mousePressedAreaPos, mouseControl);
            }
            else if(mouseShift)
                Application::current->execute(QString("%1 %2").arg(COMMAND_TRIG).arg(selectedHover->getId()), ExecuteSourceGui);
            else if((selectedHover->getType() == ObjectsTypeTrigger) || (selectedHover->getType() == ObjectsTypeCursor))
                Application::current->openMessageEditor();
        }
    }
}

void UiRender::keyPressEvent(QKeyEvent *event) {
    qreal translationUnit = 0.1;

    if((event->modifiers() & Qt::ShiftModifier) == Qt::ShiftModifier) {
        translationUnit = 1;
        //setCursor(Qt::CrossCursor);
    }

    NxPoint translation;
    if(event->key() == Qt::Key_Left)
        translation += NxPoint(translationUnit, 0);
    else if(event->key() == Qt::Key_Right)
        translation += NxPoint(-translationUnit, 0);
    else if(event->key() == Qt::Key_Up)
        translation += NxPoint(0, -translationUnit);
    else if(event->key() == Qt::Key_Down)
        translation += NxPoint(0, translationUnit);

    if(event->key() == Qt::Key_Escape) {
        emit(escFullscreen());
        emit(editingStop());
    }
    else if(event->key() == Qt::Key_Escape) {
        emit(editingStop());
        Global::editing = false;
    }

    if((selection.count() > 0) && ((translation.x() != 0) || (translation.y() != 0))) {
        Application::current->pushSnapshot();
        Application::current->execute(QString("%1 selection %2 %3 %4").arg(COMMAND_POS_TRANSLATE).arg(-translation.x()).arg(-translation.y()).arg(-translation.z()), ExecuteSourceGui);
        emit(selectionChanged());
    }
    else {
        NxPoint newCenter = -(Global::axisCenterDest + translation);
        if(newCenter != -Global::axisCenterDest)
            Application::current->execute(QString("%1 %2 %3").arg(COMMAND_CENTER).arg(newCenter.x()).arg(newCenter.y()), ExecuteSourceGui);
    }
}
bool UiRender::event(QEvent *event) {
    switch (event->type()) {
    case QEvent::Gesture: {
        QGestureEvent *gestureEvent = (QGestureEvent*)event;
        QList<QGesture*> gestures = gestureEvent->activeGestures();
        foreach(const QGesture *gesture, gestures) {
            if(gesture->gestureType() == Qt::PinchGesture) {
                QPinchGesture *pinch = (QPinchGesture*)gesture;
                if(pinch->state() == Qt::GestureStarted)
                    pinchValue = Global::zoomValue;
                setZoom(pinchValue * 1.0F / pinch->scaleFactor());
            }
        }
        return true;
    }
        break;
    default:
        break;
    }
    return QGLWidget::event(event);
}
void UiRender::dragEnterEvent(QDragEnterEvent *event) {
    const QMimeData* mimeData = event->mimeData();
    bool ok = false;
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        for(int i = 0; i < urlList.size() && i < 32; ++i) {
            QString filename = urlList.at(i).toLocalFile();
            if(filename.toLower().endsWith("svg"))
                ok = true;
            else if((filename.toLower().endsWith("png")) || (filename.toLower().endsWith("jpg")) || (filename.toLower().endsWith("jpeg")))
                ok = true;
        }
    }
    else if(!mimeData->text().isEmpty())
        ok = true;
    if(ok)
        event->acceptProposedAction();
}
void UiRender::dropEvent(QDropEvent *event) {
    const QMimeData* mimeData = event->mimeData();
    bool ok = false;
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        for(int i = 0; i < urlList.size() && i < 32; ++i) {
            QString filename = urlList.at(i).toLocalFile();
            if(filename.toLower().endsWith("svg")) {
                ok = true;
                actionImportSVG(filename);
            }
            else if((filename.toLower().endsWith("png")) || (filename.toLower().endsWith("jpg")) || (filename.toLower().endsWith("jpeg"))) {
                actionImportBackground(filename);
            }
        }
    }
    else if(!mimeData->text().isEmpty()) {
        ok = true;
        actionImportText("", mimeData->text());
    }
    if(ok)
        event->acceptProposedAction();
}

void UiRender::selectionClear(bool hoverAussi) {
    //Clear selection
    foreach(NxObject *selected, selection)
        selected->setSelected(false);
    foreach(NxObject *selected, selectionRect)
        selected->setSelected(false);
    selection.clear();
    if(hoverAussi) {
        if(selectedHover)
            selectedHover->setSelectedHover(false);
        selectedHover = 0;
    }
    emit(selectionChanged());
}
void UiRender::selectionAdd(NxObject *object) {
    if(object) {
        object->setSelected(true);
        if(!selection.contains(object))
            selection.append(object);
        emit(selectionChanged());
    }
}

void UiRender::setZoom() {
    Global::zoomLinearDest = qMax((qreal)0.01, Global::zoomValue / 100.F);
    emit(mouseZoomChanged(100.0F / Global::zoomLinearDest));
    Global::zoomLinearDest *= 1.3;
}
void UiRender::setZoom(qreal axisZoom) {
    Global::zoomValue = qMax((qreal)0, axisZoom);
    setZoom();
}
void UiRender::zoomIn() {
    setZoom(Global::zoomValue - 5);
}
void UiRender::zoomOut() {
    setZoom(Global::zoomValue + 5);
}
void UiRender::zoomInitial() {
    setZoom(100);
}




void UiRender::actionDuplicate() {
    Application::current->pushSnapshot();
    emit(actionRouteCopy());
    emit(actionRoutePaste());
}

void UiRender::actionCut() {
    Application::current->pushSnapshot();
    emit(actionRouteCopy());
    QStringList commands;
    foreach(NxObject *object, selection)
        commands << QString(COMMAND_REMOVE) + " " + QString::number(object->getId()) + COMMAND_END;
    foreach(const QString & command, commands)
        Application::current->execute(command, ExecuteSourceCopyPaste);
}

void UiRender::actionSelect_all() {
    if(document) {
        selectionClear();

        //Browse documents
        foreach(NxGroup *group, document->groups) {
            //Is groups visible ?
            if((((!Application::current->isGroupSoloActive) && (group->isNotMuted())) || ((Application::current->isGroupSoloActive) && (group->isSolo())))) {

                //Browse active/inactive objects
                for(quint16 activityIterator = 0 ; activityIterator < ObjectsActivityLenght ; activityIterator++) {

                    //Browse all types of objects
                    for(quint16 typeIterator = 0 ; typeIterator < ObjectsTypeLength ; typeIterator++) {

                        //Are objects visible ?
                        if(((typeIterator == ObjectsTypeCursor) && (Global::allowSelectionCursors)) || ((typeIterator == ObjectsTypeCurve) && (Global::allowSelectionCurves)) || ((typeIterator == ObjectsTypeTrigger) && (Global::allowSelectionTriggers))) {
                            //Browse objects
                            foreach(NxObject *object, group->objects[activityIterator][typeIterator]) {
                                //Is Z visible ?
                                if(((!Application::current->isObjectSoloActive) && (object->isNotMuted())) || ((Application::current->isObjectSoloActive) && (object->isSolo()))) {

                                    //Add the object to selection
                                    selectionAdd(object);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void UiRender::actionDelete() {
    Application::current->pushSnapshot();
    QStringList commands;
    if(selection.count() == Application::current->getCount()) {
        Application::current->execute(COMMAND_CLEAR, ExecuteSourceGui);
        selectionClear();
        selectedHover = 0;
    }
    else {
        foreach(NxObject *object, selection)
            commands << QString(COMMAND_REMOVE) + " " + QString::number(object->getId());
        selectionClear();
        selectedHover = 0;
        foreach(const QString & command, commands)
            Application::current->execute(command, ExecuteSourceGui);
    }
}

void UiRender::arrangeObjects(NxObject *objet, const NxPoint &pt) {
    Application::current->execute(QString("%1 %2 %3 %4 %5").arg(COMMAND_POS).arg(objet->getId()).arg(pt.x()).arg(pt.y()).arg(pt.z()), ExecuteSourceGui);
}
void UiRender::arrangeObjects(quint16 type) {
    qreal top = -99999999, left = 99999999, bottom = 99999999, right = -99999999;
    qreal dtop = -99999999, dleft = 99999999, dbottom = 99999999, dright = -99999999;
    qreal nbObj = 0;

    Application::current->pushSnapshot();

    //Browse objects
    foreach(const NxObject *object, selection) {
        if(object->getType() == ObjectsTypeCurve) {
            top    = qMax(top,    qMax(object->getBoundingRect().top(),  object->getBoundingRect().bottom()));
            left   = qMin(left,   qMin(object->getBoundingRect().left(), object->getBoundingRect().right()));
            bottom = qMin(bottom, qMin(object->getBoundingRect().top(),  object->getBoundingRect().bottom()));
            right  = qMax(right,  qMax(object->getBoundingRect().left(), object->getBoundingRect().right()));
            dtop    = qMax(dtop,    object->getBoundingRect().center().y());
            dleft   = qMin(dleft,   object->getBoundingRect().center().x());
            dbottom = qMin(dbottom, object->getBoundingRect().center().y());
            dright  = qMax(dright,  object->getBoundingRect().center().x());
            nbObj++;
        }
        else if(object->getType() == ObjectsTypeTrigger) {
            top    = qMax(top,    object->getPos().y());
            left   = qMin(left,   object->getPos().x());
            bottom = qMin(bottom, object->getPos().y());
            right  = qMax(right,  object->getPos().x());
            dtop    = qMax(dtop,    object->getPos().y());
            dleft   = qMin(dleft,   object->getPos().x());
            dbottom = qMin(dbottom, object->getPos().y());
            dright  = qMax(dright,  object->getPos().x());
            nbObj++;
        }
    }
    qreal width = (right-left)/2;
    qreal center = left + width;
    qreal height = (top-bottom)/2;
    qreal middle = bottom + height;

    if(type == 0) {
        //Top
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve)
                arrangeObjects(object, NxPoint(object->getPos().x(), object->getPos().y() + top-qMax(object->getBoundingRect().top(), object->getBoundingRect().bottom()), object->getPos().z()));
            else if(object->getType() == ObjectsTypeTrigger)
                arrangeObjects(object, NxPoint(object->getPos().x(), top, object->getPos().z()));
    }
    else if(type == 1) {
        //Left
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve)
                arrangeObjects(object, NxPoint(object->getPos().x() + left-qMin(object->getBoundingRect().left(), object->getBoundingRect().right()), object->getPos().y(), object->getPos().z()));
            else if(object->getType() == ObjectsTypeTrigger)
                arrangeObjects(object, NxPoint(left, object->getPos().y(), object->getPos().z()));
    }
    else if(type == 2) {
        //Bottom
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve)
                arrangeObjects(object, NxPoint(object->getPos().x(), object->getPos().y() + bottom-qMin(object->getBoundingRect().top(), object->getBoundingRect().bottom()), object->getPos().z()));
            else if(object->getType() == ObjectsTypeTrigger)
                arrangeObjects(object, NxPoint(object->getPos().x(), bottom, object->getPos().z()));
    }
    else if(type == 3) {
        //Right
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve)
                arrangeObjects(object, NxPoint(object->getPos().x() + right-qMax(object->getBoundingRect().left(), object->getBoundingRect().right()), object->getPos().y(), object->getPos().z()));
            else if(object->getType() == ObjectsTypeTrigger)
                arrangeObjects(object, NxPoint(right, object->getPos().y(), object->getPos().z()));
    }
    else if(type == 4) {
        //Middle
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve)
                arrangeObjects(object, NxPoint(object->getPos().x(), object->getPos().y() + middle-object->getBoundingRect().center().y(), object->getPos().z()));
            else if(object->getType() == ObjectsTypeTrigger)
                arrangeObjects(object, NxPoint(object->getPos().x(), middle, object->getPos().z()));
    }
    else if(type == 5) {
        //Center
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve)
                arrangeObjects(object, NxPoint(object->getPos().x() + middle-object->getBoundingRect().center().x(), object->getPos().y(), object->getPos().z()));
            else if(object->getType() == ObjectsTypeTrigger)
                arrangeObjects(object, NxPoint(center, object->getPos().y(), object->getPos().z()));
    }
    else if((type == 6) && (nbObj > 1)) {
        //Distrib H
        qreal dHStep = qAbs(dright-dleft) / (nbObj-1);
        nbObj = 0;
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve) {
                arrangeObjects(object, NxPoint(object->getPos().x() + (dleft + nbObj * dHStep)-object->getBoundingRect().center().x(), object->getPos().y(), object->getPos().z()));
                nbObj++;
            }
            else if(object->getType() == ObjectsTypeTrigger) {
                arrangeObjects(object, NxPoint(dleft + nbObj * dHStep, object->getPos().y(), object->getPos().z()));
                nbObj++;
            }
    }
    else if((type == 7) && (nbObj > 1)) {
        //Distrib V
        qreal dVStep = qAbs(dtop-dbottom) / (nbObj-1);
        nbObj = 0;
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve) {
                arrangeObjects(object, NxPoint(object->getPos().x(), object->getPos().y() + (dbottom + nbObj * dVStep)-object->getBoundingRect().center().y(), object->getPos().z()));
                nbObj++;
            }
            else if(object->getType() == ObjectsTypeTrigger) {
                arrangeObjects(object, NxPoint(object->getPos().x(), dbottom + nbObj * dVStep, object->getPos().z()));
                nbObj++;
            }
    }
    else if(type == 8) {
        //Distrib Circle
        qreal dAngle = 2 * M_PI / nbObj;
        nbObj = 0;
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve) {
                arrangeObjects(object, NxPoint(object->getPos().x() + (center + qMax(width,height)*qCos(dAngle * nbObj))-object->getBoundingRect().center().x(), object->getPos().y() + (middle + qMax(width,height)*qSin(dAngle * nbObj))-object->getBoundingRect().center().y(), object->getPos().z()));
                nbObj++;
            }
            else if(object->getType() == ObjectsTypeTrigger) {
                arrangeObjects(object, NxPoint(center + qMax(width,height)*qCos(dAngle * nbObj), middle + qMax(width,height)*qSin(dAngle * nbObj), object->getPos().z()));
                nbObj++;
            }
    }
    else if(type == 9) {
        //Distrib Ellipse
        qreal dAngle = 2 * M_PI / nbObj;
        nbObj = 0;
        foreach(NxObject *object, selection)
            if(object->getType() == ObjectsTypeCurve) {
                arrangeObjects(object, NxPoint(object->getPos().x() + (center + width*qCos(dAngle * nbObj))-object->getBoundingRect().center().x(), object->getPos().y() + (middle + height*qSin(dAngle * nbObj))-object->getBoundingRect().center().y(), object->getPos().z()));
                nbObj++;
            }
            else if(object->getType() == ObjectsTypeTrigger) {
                arrangeObjects(object, NxPoint(center + width*qCos(dAngle * nbObj), middle + height*qSin(dAngle * nbObj), object->getPos().z()));
                nbObj++;
            }
    }

}
