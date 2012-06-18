true {
    unix:SOURCES     += QVideoEncoder.cpp   QVideoDecoder.cpp
    unix:HEADERS     += QVideoEncoder.h     QVideoDecoder.h
    unix:LIBS        +=-L/opt/local/lib -lavutil
    unix:LIBS        +=-L/opt/local/lib -lavcodec
    unix:LIBS        +=-L/opt/local/lib -lavformat
    unix:LIBS        +=-L/opt/local/lib -lswscale

    #INCLUDEPATH += QVideoEncoder
    #INCLUDEPATH += ../QTFFmpegWrapper

    win32 {
        DEFINES += __STDC_CONSTANT_MACROS
    }
}
