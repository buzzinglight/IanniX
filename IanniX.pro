#-------------------------------------------------
#
# Project created by QtCreator 2011-01-12T16:56:24
#
#-------------------------------------------------

QT       += core gui opengl network script xml

TARGET    =  IanniX
TEMPLATE  =  app
CONFIG   +=  x86_64

SOURCES  += iannix.cpp iannixapp.cpp
HEADERS  += iannix.h   iannixapp.h   iannix_spec.h  iannix_cmd.h

SOURCES  += misc/nxcpu.cpp misc/help.cpp
HEADERS  += misc/nxcpu.h   misc/help.h

HEADERS  += geometry/nxpoint.h   geometry/nxrect.h   geometry/nxsize.h   geometry/nxline.h   geometry/nxpolygon.h   geometry/nxeasing.h
SOURCES  += geometry/nxpoint.cpp geometry/nxrect.cpp geometry/nxsize.cpp geometry/nxline.cpp geometry/nxpolygon.cpp geometry/nxeasing.cpp
HEADERS  += geometry/qmuparser/muParser.h   geometry/qmuparser/muParserBase.h   geometry/qmuparser/muParserBytecode.h   geometry/qmuparser/muParserCallback.h   geometry/qmuparser/muParserError.h   geometry/qmuparser/muParserTokenReader.h   geometry/qmuparser/muParserDef.h   geometry/qmuparser/muParserFixes.h   geometry/qmuparser/muParserStack.h   geometry/qmuparser/muParserToken.h
SOURCES  += geometry/qmuparser/muParser.cpp geometry/qmuparser/muParserBase.cpp geometry/qmuparser/muParserBytecode.cpp geometry/qmuparser/muParserCallback.cpp geometry/qmuparser/muParserError.cpp geometry/qmuparser/muParserTokenReader.cpp

HEADERS  += objects/nxdocument.h   objects/nxtrigger.h   objects/nxgroup.h   objects/nxcurve.h   objects/nxcursor.h   objects/nxobject.h   objects/nxobjectfactoryinterface.h
SOURCES  += objects/nxdocument.cpp objects/nxtrigger.cpp objects/nxgroup.cpp objects/nxcurve.cpp objects/nxcursor.cpp objects/nxobject.cpp

FORMS    += gui/uitransport.ui  gui/uirender.ui  gui/uiinspector.ui  gui/uiview.ui  gui/uisplash.ui  gui/uiabout.ui  gui/uieditor.ui  gui/uihelp.ui  gui/uitimer.ui  gui/uimessagebox.ui
HEADERS  += gui/uitransport.h   gui/uirender.h   gui/uiinspector.h   gui/uiview.h   gui/uisplash.h   gui/uiabout.h   gui/uieditor.h   gui/uihelp.h   gui/uitimer.h   gui/uimessagebox.h   gui/uirenderpreview.h   gui/uirenderoptions.h
SOURCES  += gui/uitransport.cpp gui/uirender.cpp gui/uiinspector.cpp gui/uiview.cpp gui/uisplash.cpp gui/uiabout.cpp gui/uieditor.cpp gui/uihelp.cpp gui/uitimer.cpp gui/uimessagebox.cpp gui/uirenderpreview.cpp
HEADERS  += gui/qjsedit/jsedit.h
SOURCES  += gui/qjsedit/jsedit.cpp

HEADERS  += interfaces/extmidimanager.h   interfaces/exttcpmanager.h   interfaces/extudpmanager.h   interfaces/exthttpmanager.h   interfaces/extserialmanager.h   interfaces/extoscmanager.h   interfaces/extscriptmanager.h   interfaces/extmessage.h
SOURCES  += interfaces/extmidimanager.cpp interfaces/exttcpmanager.cpp interfaces/extudpmanager.cpp interfaces/exthttpmanager.cpp interfaces/extserialmanager.cpp interfaces/extoscmanager.cpp interfaces/extscriptmanager.cpp interfaces/extmessage.cpp
HEADERS  += interfaces/extscriptvariableask.h   interfaces/extoscpatternask.h   interfaces/extoscpatterneditor.h
FORMS    += interfaces/extscriptvariableask.ui  interfaces/extoscpatternask.ui  interfaces/extoscpatterneditor.ui
SOURCES  += interfaces/extscriptvariableask.cpp interfaces/extoscpatternask.cpp interfaces/extoscpatterneditor.cpp

HEADERS  += interfaces/qextserialport/qextserialport.h   interfaces/qextserialport/qextserialenumerator.h interfaces/qextserialport/qextserialport_global.h
SOURCES  += interfaces/qextserialport/qextserialport.cpp
HEADERS  += interfaces/qrtmidi/RtMidi.h   interfaces/qrtmidi/RtError.h
SOURCES  += interfaces/qrtmidi/RtMidi.cpp
debug:DEFINES += __RTMIDI_DEBUG__


#Kinect
false {
    DEFINES           += KINECT_INSTALLED
    CONFIG            -= x86
    unix:SOURCES      += interfaces/qkinect/QKinect.cpp extkinectmanager.cpp
    unix:HEADERS      += interfaces/qkinect/QKinect.h extkinectmanager.h
    unix:LIBS         += -lfreenect
    unix:INCLUDEPATH  += /usr/local/include/libfreenect
}

#FFMPEG to record
false {
    DEFINES           += FFMPEG_INSTALLED
    CONFIG            -= x86
    INCLUDEPATH       += gui/qffmpeg
    SOURCES           += gui/qffmpeg/QVideoEncoder.cpp   gui/qffmpeg/QVideoDecoder.cpp
    HEADERS           += gui/qffmpeg/QVideoEncoder.h     gui/qffmpeg/QVideoDecoder.h
    unix:LIBS         +=-L/opt/local/lib -lavutil
    unix:LIBS         +=-L/opt/local/lib -lavcodec
    unix:LIBS         +=-L/opt/local/lib -lavformat
    unix:LIBS         +=-L/opt/local/lib -lswscale
    win32:DEFINES     += __STDC_CONSTANT_MACROS
}

#Syphon
macx {
    DEFINES           += SYPHON_INSTALLED
    OBJECTIVE_SOURCES += gui/uirendersyphon.mm
    HEADERS           += gui/uirendersyphon.h
    LIBS              += -framework Cocoa -framework Syphon
}

#Wacom & trackpads
false {
    DEFINES           += WACOM_INSTALLED
    OBJECTIVE_SOURCES += interfaces/extwacommanager.mm interfaces/qwacom/WacomTabletDriver.h  interfaces/qwacom/WacomTabletDriver.m
    HEADERS           += interfaces/extwacommanager.h
    LIBS              += -framework Cocoa
}

TRANSLATIONS             = Tools/Translation_fr_FR.ts

RESOURCES               += icons/IanniX.qrc

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
    SOURCES             += interfaces/qextserialport/win_qextserialport.cpp  interfaces/qextserialport/qextserialenumerator_win.cpp
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
    SOURCES             += interfaces/qextserialport/qextserialenumerator_osx.cpp
}
unix:SOURCES            += interfaces/qextserialport/posix_qextserialport.cpp
unix:!macx:SOURCES      += interfaces/qextserialport/qextserialenumerator_unix.cpp

