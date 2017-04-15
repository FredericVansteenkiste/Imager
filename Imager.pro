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
    HMI/WidgetManipImage/WidgetManipImage.cpp \
    HMI/WidgetManipImage/ImageScene.cpp \
    HMI/WidgetManipImage/ImageView.cpp

HEADERS += \
    HMI/MainWindow.h \
    HMI/SubWindow.h \
    HMI/WidgetManipImage/WidgetManipImage.h \
    HMI/WidgetManipImage/ImageScene.h \
    HMI/WidgetManipImage/ImageView.h

RESOURCES += \
    Imager.qrc

OTHER_FILES +=

CONFIG += c++11

RC_ICONS = HMI/Icones/application.ico

DISTFILES +=
