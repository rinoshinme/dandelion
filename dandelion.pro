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
    views/histview.cpp

HEADERS  += \
    views/imageview.h \
    windows/logindlg.h \
    views/histview.h \
    image/timage.h \
    dandelion.h

FORMS    +=
