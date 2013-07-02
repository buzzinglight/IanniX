QT       -= gui
QT       += network

TARGET = zeroconf
TEMPLATE = lib

DEFINES += ZEROCONF_LIBRARY
SOURCES += servicebrowser.cpp mdnsderived.cpp embeddedLib.cpp nativeLib.cpp avahiLib.cpp
HEADERS += servicebrowser.h   mdnsderived.h   zeroconf_global.h dns_sd_types.h servicebrowser_p.h
win32{
    LIBS += -lws2_32
}


