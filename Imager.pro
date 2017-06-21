#-------------------------------------------------
#
# Project created by QtCreator 2016-12-21T19:57:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Imager
TEMPLATE = app

include(QtSingleCoreApplication/src/qtsingleapplication.pri)

SOURCES += main.cpp \
    HMI/MainWindow.cpp \
    HMI/SubWindow.cpp \
    HMI/WidgetManipImage/WidgetManipImage.cpp \
    HMI/WidgetManipImage/ImageScene.cpp \
    HMI/WidgetManipImage/ImageView.cpp \
    HMI/WidgetManipImage/GraphicsPixmapItem.cpp \
    HMI/MdiArea.cpp \
    CStateMachine/CStateMachine.cpp \
    HMI/WidgetManipColor/CStateMouse/CStateMouse.cpp \
    HMI/WidgetManipColor/CStateMouse/CState/CStateMouseDefault.cpp \
    HMI/WidgetManipColor/CStateMouse/CState/CStateMousePen.cpp \
    HMI/WidgetManipColor/CStateMouse/CState/CStateMousePipette.cpp \
    HMI/WidgetManipColor/WidgetManipColor.cpp \
    HMI/WidgetManipColor/CStateMouse/CState.cpp

HEADERS += \
    HMI/MainWindow.h \
    HMI/SubWindow.h \
    HMI/WidgetManipImage/WidgetManipImage.h \
    HMI/WidgetManipImage/ImageScene.h \
    HMI/WidgetManipImage/ImageView.h \
    HMI/WidgetManipImage/GraphicsPixmapItem.h \
    HMI/MdiArea.h \
    CStateMachine/CStateMachine.h \
    HMI/WidgetManipColor/CStateMouse/CStateMouse.h \
    HMI/WidgetManipColor/CStateMouse/CState/CStateMouseDefault.h \
    HMI/WidgetManipColor/CStateMouse/CState/CStateMousePen.h \
    HMI/WidgetManipColor/CStateMouse/CState/CStateMousePipette.h \
    HMI/WidgetManipColor/WidgetManipColor.h \
    HMI/WidgetManipColor/CStateMouse/CState.h

RESOURCES += \
    Imager.qrc

OTHER_FILES +=

CONFIG += c++11

RC_ICONS = HMI/Icones/application.ico

QMAKE_CXXFLAGS += -Wall #-Weffc++
