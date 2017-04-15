#-------------------------------------------------
#
# Project created by QtCreator 2016-12-21T19:57:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Imager
TEMPLATE = app


SOURCES += main.cpp \
    HMI/MainWindow.cpp \
    HMI/SubWindow.cpp \
    HMI/DisplayImage.cpp

HEADERS += \
    HMI/MainWindow.h \
    HMI/SubWindow.h \
    HMI/DisplayImage.h

RESOURCES += \
    Imager.qrc

OTHER_FILES +=

CONFIG += c++11

RC_ICONS = HMI/Icones/application.ico

DISTFILES +=
