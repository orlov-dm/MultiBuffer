 #-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T13:43:09
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultiBuffer
TEMPLATE = app

win32 {
    LIBS += -L"C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\v7.1A\\Lib\\x64"
    LIBS += -lUser32
    LIBS += -lDwmapi
} else {
    QT += x11extras
    CONFIG    += link_pkgconfig
    PKGCONFIG += x11
    PKGCONFIG += xtst
}


SOURCES += main.cpp \
    core/multibuffer.cpp \
    core/nativeeventfilter.cpp \
    ui/historyform.cpp \
    models/historymodel.cpp \    
    core/eventfilterfactory.cpp

HEADERS  += includes/const.h \
    core/multibuffer.h \
    core/nativeeventfilter.h \
    ui/historyform.h \
    models/historymodel.h \    
    core/eventfilterfactory.h

FORMS    += ui/historyform.ui

win32 {
    SOURCES += core/wineventfilter.cpp
    HEADERS += core/wineventfilter.h
} else {
    SOURCES += core/linuxeventfilter.cpp
    HEADERS += core/linuxeventfilter.h
}

