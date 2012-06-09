#-------------------------------------------------
#
# Project created by QtCreator 2011-01-12T16:56:24
#
#-------------------------------------------------

QT                      += core gui opengl network script xml

TARGET                   =  IanniX
TEMPLATE                 =  app
CONFIG                  +=  x86 x86_64

false {
    CONFIG              -= x86
    unix:DEFINES        += KINECT_INSTALLED
    unix:SOURCES        += qkinect/QKinect.cpp extkinectmanager.cpp
    unix:HEADERS        += qkinect/QKinect.h extkinectmanager.h
    unix:LIBS           += -lfreenect
    unix:INCLUDEPATH    += /usr/local/include/libfreenect
}

debug:DEFINES           += __RTMIDI_DEBUG__

SOURCES                 += iannix.cpp \
                           uitransport.cpp \
                           uirender.cpp \
                           uiinspector.cpp \
                           uiview.cpp \
                           nxobject.cpp \
                           nxdocument.cpp \
                           nxtrigger.cpp \
                           nxgroup.cpp \
                           nxcurve.cpp \
                           nxcursor.cpp \
                           extoscmanager.cpp \
                           extscriptmanager.cpp \
                           extscriptvariableask.cpp \
                           uisplash.cpp \
                           uiabout.cpp \
                           extoscpatternask.cpp \
                           exttcpmanager.cpp \
                           extudpmanager.cpp \
                           exthttpmanager.cpp \
                           extserialmanager.cpp \
                           iannixapp.cpp \
                           qextserialport/qextserialport.cpp \
                           qrtmidi/RtMidi.cpp \
                           extmidimanager.cpp \
                           qjsedit/jsedit.cpp \
                           uieditor.cpp \
                           nxpoint.cpp \
                           nxrect.cpp \
                           nxsize.cpp \
                           nxpolygon.cpp \
                           nxline.cpp \
                           extoscpatterneditor.cpp \
                           nxeasing.cpp \
                           nxcpu.cpp

HEADERS                 += iannix.h \
                           uitransport.h \
                           uirender.h \
                           uiinspector.h \
                           uirenderoptions.h \
                           uiview.h \
                           nxobject.h \
                           nxobjectfactoryinterface.h \
                           nxdocument.h \
                           nxtrigger.h \
                           nxgroup.h \
                           nxcurve.h \
                           nxcursor.h \
                           extoscmanager.h \
                           extscriptmanager.h \
                           extscriptvariableask.h \
                           uisplash.h \
                           uiabout.h \
                           extoscpatternask.h \
                           exttcpmanager.h \
                           extudpmanager.h \
                           exthttpmanager.h \
                           extserialmanager.h \
                           extmessage.h \
                           iannixapp.h \
                           qextserialport/qextserialport.h \
                           qextserialport/qextserialenumerator.h \
                           qextserialport/qextserialport_global.h \
                           qrtmidi/RtMidi.h \
                           qrtmidi/RtError.h \
                           extmidimanager.h \
                           qjsedit/jsedit.h \
                           uieditor.h \
                           iannix_spec.h \
                           iannix_cmd.h \
                           nxpoint.h \
                           nxrect.h \
                           nxsize.h \
                           nxline.h \
                           nxpolygon.h \
                           extoscpatterneditor.h \
                           nxeasing.h \
                           nxcpu.h

FORMS                   += uitransport.ui \
                           uirender.ui \
                           uiinspector.ui \
                           uiview.ui \
                           extscriptvariableask.ui \
                           uisplash.ui \
                           uiabout.ui \
                           extoscpatternask.ui \
                           uieditor.ui \
                           extoscpatterneditor.ui

TRANSLATIONS             = iannix_fr.ts

RESOURCES               += IanniX.qrc

macx {
    ICON                 = icon.icns
    QMAKE_INFO_PLIST     = Info.plist

    BUNDLE_RES.files     = icon_green.icns icon_orange.icns
    BUNDLE_RES.path      = Contents/Resources
    QMAKE_BUNDLE_DATA   += BUNDLE_RES
}
win32 {
    DEFINES             += __WINDOWS_MM__
    LIBS                += -lwinmm -lsetupapi
    RC_FILE              = icon.rc
    SOURCES             += qextserialport/win_qextserialport.cpp qextserialport/qextserialenumerator_win.cpp
    DEFINES             += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
}
linux* {
    DEFINES             += __LINUX_ALSASEQ__
    DEFINES             += AVOID_TIMESTAMPING
    LIBS                += -lasound
    PKGCONFIG           += alsa
}
macx {
    DEFINES             += __MACOSX_CORE__
    LIBS                += -framework CoreMidi -framework CoreAudio -framework CoreFoundation -framework IOKit -framework Carbon
    SOURCES             += qextserialport/qextserialenumerator_osx.cpp
}
unix:SOURCES            += qextserialport/posix_qextserialport.cpp
unix:!macx:SOURCES      += qextserialport/qextserialenumerator_unix.cpp


false {
    DEFINES             += SYPHON_ENABLE
    OBJECTIVE_SOURCES   += uirendersyphon.mm
    LIBS                += -framework Syphon
}
