#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T11:30:42
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HKProduceManagent
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    cameradialog.cpp \
    dialogtutksearch.cpp \
    qtutk/qtutkclient.cpp \
    qtutk/qtutkavreadframethread.cpp \
    qtutk/qtutkavreadaudiodatathread.cpp \
    tools.cpp \
    qtutk/qtutkavsendaudiofilethread.cpp \
    qtutk/ch264decoder.cpp

HEADERS  += mainwindow.h \
    AVIOCTRLDEFs.h \
    cameradialog.h \
    dialogtutksearch.h \
    qtutk/qtutkclient.h \
    qtutk/qtutkavreadframethread.h \
    qtutk/qtutkavreadaudiodatathread.h \
    AVFRAMEINFO.h \
    tools.h \
    qtutk/qtutkavsendaudiofilethread.h \
    qtutk/ch264decoder.h

FORMS    += mainwindow.ui \
    cameradialog.ui \
    dialogtutksearch.ui

unix: LIBS += -L$$PWD/libs/tutk/Linux/x86/  -lAVAPIs -lIOTCAPIs
unix: LIBS += -L/opt/ffmpeg-2.6.9/host/lib -lswscale -lavutil -lavdevice -lavformat -lswresample -lavcodec -ldl

INCLUDEPATH += $$PWD/Include
DEPENDPATH += $$PWD/Include

INCLUDEPATH += /opt/ffmpeg-3.3.4/

win32: LIBS += -L$$PWD/libs/tutk/Windows/Win32/ -lAVAPIs -lIOTCAPIs

DISTFILES +=

RESOURCES += \
    hkrcc.qrc
