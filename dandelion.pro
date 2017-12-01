#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T09:11:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dandelion
TEMPLATE = app

SOURCES += main.cpp\
    views/imageview.cpp \
    windows/logindlg.cpp \
    views/histview.cpp \
    views/waveview.cpp \
    views/timageview.cpp

HEADERS  += \
    views/imageview.h \
    windows/logindlg.h \
    views/histview.h \
    dandelion.h \
    views/waveview.h \
    structs/timage.h \
    views/timageview.h \
    structs/pixel.h

FORMS    +=
