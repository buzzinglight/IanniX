#-------------------------------------------------
#
# Project created by QtCreator 2011-01-12T16:56:24
#
#-------------------------------------------------

QT_VERSION = $$[QT_VERSION]
message($$[QT_VERSION])
contains(QT_VERSION, "^4.*") {
    message("IanniX For QT4")
    DEFINES += QT4
    QT      += core gui opengl network script xml
} else {
    message("IanniX For QT5 (very experimental)")
    DEFINES += QT5
    QT      += widgets core gui opengl network script xml
}
macx {
    contains(QT_VERSION, "4.7.0") {
        message("IanniX for Mac 32bits")
        DEFINES += IANNIX_32
        CONFIG  += x86 x86_64
    }
    else {
        DEFINES += IANNIX_64
        CONFIG  += x86_64
        message("IanniX for Mac 64bits")
    }
}
!macx {
    DEFINES += IANNIX_64
    DEFINES += IANNIX_32
    CONFIG  += x86 x86_64
}

TARGET    = IanniX
TEMPLATE  = app

HEADERS  += iannix.h   iannixapp.h   iannix_spec.h  iannix_cmd.h
SOURCES  += iannix.cpp iannixapp.cpp iannix_spec.cpp
HEADERS  += misc/help.h   misc/application.h   misc/options.h
SOURCES  += misc/help.cpp misc/application.cpp misc/options.cpp

HEADERS  += messages/messagemanagerlogmini.h   messages/messagemanagerlog.h   messages/messagemanager.h   messages/message.h   messages/messagemanagerloginterface.h
SOURCES  += messages/messagemanagerlogmini.cpp messages/messagemanagerlog.cpp messages/messagemanager.cpp messages/message.cpp
FORMS    += messages/messagemanagerlogmini.ui  messages/messagemanagerlog.ui

HEADERS  += transport/transport.h   transport/uitimer.h   transport/uiabout.h   transport/uieditor.h
SOURCES  += transport/transport.cpp transport/uitimer.cpp transport/uiabout.cpp transport/uieditor.cpp
FORMS    += transport/transport.ui  transport/uitimer.ui  transport/uiabout.ui  transport/uieditor.ui

HEADERS  += render/uirender.h   render/uirenderpreview.h   render/uirenderoptions.h  
SOURCES  += render/uirender.cpp render/uirenderpreview.cpp render/uirenderoptions.cpp
FORMS    += render/uirender.ui

HEADERS  += geometry/nxpoint.h   geometry/nxrect.h   geometry/nxsize.h   geometry/nxline.h   geometry/nxpolygon.h   geometry/nxeasing.h
SOURCES  += geometry/nxpoint.cpp geometry/nxrect.cpp geometry/nxsize.cpp geometry/nxline.cpp geometry/nxpolygon.cpp geometry/nxeasing.cpp
HEADERS  += geometry/qmuparser/muParser.h   geometry/qmuparser/muParserBase.h   geometry/qmuparser/muParserBytecode.h   geometry/qmuparser/muParserCallback.h   geometry/qmuparser/muParserError.h   geometry/qmuparser/muParserTokenReader.h   geometry/qmuparser/muParserDef.h   geometry/qmuparser/muParserFixes.h   geometry/qmuparser/muParserStack.h   geometry/qmuparser/muParserToken.h
SOURCES  += geometry/qmuparser/muParser.cpp geometry/qmuparser/muParserBase.cpp geometry/qmuparser/muParserBytecode.cpp geometry/qmuparser/muParserCallback.cpp geometry/qmuparser/muParserError.cpp geometry/qmuparser/muParserTokenReader.cpp

HEADERS  += objects/nxdocument.h   objects/nxtrigger.h   objects/nxgroup.h   objects/nxcurve.h   objects/nxcursor.h   objects/nxobject.h  
SOURCES  += objects/nxdocument.cpp objects/nxtrigger.cpp objects/nxgroup.cpp objects/nxcurve.cpp objects/nxcursor.cpp objects/nxobject.cpp

HEADERS  += gui/uiinspector.h   gui/uiview.h   gui/uisplash.h   gui/uihelp.h   gui/uimessagebox.h
SOURCES  += gui/uiinspector.cpp gui/uiview.cpp gui/uisplash.cpp gui/uihelp.cpp gui/uimessagebox.cpp
FORMS    += gui/uiinspector.ui  gui/uiview.ui  gui/uisplash.ui  gui/uihelp.ui  gui/uimessagebox.ui
HEADERS  += gui/qjsedit/jsedit.h
SOURCES  += gui/qjsedit/jsedit.cpp
SOURCES  += items/uitreeview.cpp items/uitreeviewwidget.cpp items/uitreedelegate.cpp items/uifileitem.cpp items/uicoloritem.cpp items/uipathpointsitem.cpp items/uitextureitem.cpp
HEADERS  += items/uitreeview.h   items/uitreeviewwidget.h   items/uitreedelegate.h   items/uifileitem.h   items/uicoloritem.h   items/uipathpointsitem.h   items/uitextureitem.h
FORMS    += items/uitreeview.ui

HEADERS  += interfaces/interfacehttp.h   interfaces/interfacemidi.h   interfaces/interfaceosc.h   interfaces/interfaceserial.h   interfaces/interfacetcp.h   interfaces/interfaceudp.h   interfaces/interfacedirect.h   interfaces/interfacesyphon.h
SOURCES  += interfaces/interfacehttp.cpp interfaces/interfacemidi.cpp interfaces/interfaceosc.cpp interfaces/interfaceserial.cpp interfaces/interfacetcp.cpp interfaces/interfaceudp.cpp interfaces/interfacedirect.cpp
FORMS    += interfaces/interfacehttp.ui  interfaces/interfacemidi.ui  interfaces/interfaceosc.ui  interfaces/interfaceserial.ui  interfaces/interfacetcp.ui  interfaces/interfaceudp.ui  interfaces/interfacedirect.ui  interfaces/interfacesyphon.ui
HEADERS  += interfaces/extscriptvariableask.h   interfaces/extoscpatternask.h   interfaces/extoscpatterneditor.h
SOURCES  += interfaces/extscriptvariableask.cpp interfaces/extoscpatternask.cpp interfaces/extoscpatterneditor.cpp
FORMS    += interfaces/extscriptvariableask.ui  interfaces/extoscpatternask.ui  interfaces/extoscpatterneditor.ui

HEADERS  += interfaces/qextserialport/qextserialport.h   interfaces/qextserialport/qextserialenumerator.h   interfaces/qextserialport/qextserialport_global.h interfaces/qextserialport/qextserialport_p.h interfaces/qextserialport/qextserialenumerator_p.h
SOURCES  += interfaces/qextserialport/qextserialport.cpp interfaces/qextserialport/qextserialenumerator.cpp
HEADERS  += interfaces/qrtmidi/RtMidi.h   interfaces/qrtmidi/RtError.h
SOURCES  += interfaces/qrtmidi/RtMidi.cpp
debug:DEFINES += __RTMIDI_DEBUG__

#Syphon
macx {
    DEFINES           += SYPHON_INSTALLED
    OBJECTIVE_SOURCES += interfaces/interfacesyphon.mm
    LIBS              += -framework Cocoa -framework Syphon
}

#Kinect
false {
    DEFINES           += KINECT_INSTALLED
    CONFIG            -= x86
    unix:SOURCES      += interfaces/qkinect/QKinect.cpp extkinectmanager.cpp
    unix:HEADERS      += interfaces/qkinect/QKinect.h   extkinectmanager.h
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

    BUNDLE_RES.files     = icon_file.icns
    BUNDLE_RES.path      = Contents/Resources
    QMAKE_BUNDLE_DATA   += BUNDLE_RES
}


win32 {
    DEFINES             += __WINDOWS_MM__
    LIBS                += -lwinmm -lsetupapi #-ladvapi32 -luser32
    RC_FILE              = icon.rc
    SOURCES             += interfaces/qextserialport/qextserialport_win.cpp  interfaces/qextserialport/qextserialenumerator_win.cpp
    DEFINES             += WINVER=0x0501 # needed for mingw to pull in appropriate dbt business...probably a better way to do this
}
unix {
    SOURCES            += interfaces/qextserialport/qextserialport_unix.cpp
    linux* {
        SOURCES        += interfaces/qextserialport/qextserialenumerator_linux.cpp
    } else:macx {
        SOURCES        += interfaces/qextserialport/qextserialenumerator_osx.cpp
    } else {
        SOURCES        += interfaces/qextserialport/qextserialenumerator_unix.cpp
    }
}
linux* {
    DEFINES                  += __LINUX_ALSA__
    DEFINES                  += AVOID_TIMESTAMPING
    DEFINES                  += __linux__
    LIBS                     += -lasound
    PKGCONFIG                += alsa
    !qesp_linux_udev:DEFINES += QESP_NO_UDEV
    qesp_linux_udev: LIBS    += -ludev
}
macx {
    DEFINES             += __MACOSX_CORE__
    LIBS                += -framework CoreMidi -framework CoreAudio -framework CoreFoundation -framework IOKit -framework Carbon
}
