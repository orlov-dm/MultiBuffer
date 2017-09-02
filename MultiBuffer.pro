 #-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T13:43:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultiBuffer
TEMPLATE = app

LIBS += -L"C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\v7.1A\\Lib\\x64"
LIBS += -lUser32
LIBS += -lDwmapi


SOURCES += main.cpp \
    core/multibuffer.cpp \
    core/nativeeventfilter.cpp \
    ui/historyform.cpp \
    models/historymodel.cpp

HEADERS  += includes/const.h \
    core/multibuffer.h \
    core/nativeeventfilter.h \
    ui/historyform.h \
    models/historymodel.h

FORMS    += ui/historyform.ui
