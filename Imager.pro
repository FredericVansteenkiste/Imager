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
    HMI/WidgetManipColor/CStateMouse.cpp \
    HMI/WidgetManipColor/CStateMouse/CSubStateMouseDefault.cpp \
    HMI/WidgetManipColor/CStateMouse/CSubStateMousePen.cpp \
    HMI/WidgetManipColor/CStateMouse/CSubStateMousePipette.cpp \
    HMI/WidgetManipColor/WidgetManipColor.cpp \
    HMI/WidgetManipColor/CStateMouse/CSubStateMouse.cpp \
    HMI/WidgetManipColor/WidgetEditColor.cpp \
    HMI/WidgetManipColor/WidgetEditComponentColor.cpp \
    HMI/WidgetPalette/WidgetPaletteElement.cpp \
    HMI/WidgetPalette/WidgetPalette.cpp \
    CExceptionMessagerie/CExceptionMessagerie.cpp

HEADERS += \
    HMI/MainWindow.h \
    HMI/SubWindow.h \
    HMI/WidgetManipImage/WidgetManipImage.h \
    HMI/WidgetManipImage/ImageScene.h \
    HMI/WidgetManipImage/ImageView.h \
    HMI/WidgetManipImage/GraphicsPixmapItem.h \
    HMI/MdiArea.h \
    CStateMachine/CStateMachine.h \
    HMI/WidgetManipColor/CStateMouse.h \
    HMI/WidgetManipColor/CStateMouse/CSubStateMouseDefault.h \
    HMI/WidgetManipColor/CStateMouse/CSubStateMousePen.h \
    HMI/WidgetManipColor/CStateMouse/CSubStateMousePipette.h \
    HMI/WidgetManipColor/WidgetManipColor.h \
    HMI/WidgetManipColor/CStateMouse/CSubStateMouse.h \
    HMI/WidgetManipColor/WidgetEditColor.h \
    HMI/WidgetManipColor/WidgetEditComponentColor.h \
    global.h \
    HMI/WidgetPalette/WidgetPaletteElement.h \
    HMI/WidgetPalette/WidgetPalette.h \
    CExceptionMessagerie/CExceptionMessagerie.h

RESOURCES += \
    Imager.qrc

OTHER_FILES +=

CONFIG += c++11

RC_ICONS = Icones/application.ico

QMAKE_CXXFLAGS += -Wall

DISTFILES +=
