#-------------------------------------------------
#
# Project created by QtCreator 2019-05-31T13:47:07
#
#-------------------------------------------------
QT       += network
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IRcamera
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qReader.cpp \
    qRedis.cpp

HEADERS += \
        mainwindow.h \
    DeviceFunctionSupport.h \
    GD_MTC_ERROR_CODE.h \
    GD_MTC_SDK_API.h \
    IMAGE_MEASURE_input.h \
    MeasureCoreNet.h \
    MeasureCoreNet_StructBasic.h \
    MeasureCoreNet2.h \
    MeasureCoreNet2_Struct.h \
    MeasureCoreNetExpert.h \
    ParamMeasure.h \
    PlatformType.h \
    qReader.h \
    qRedis.h

FORMS += \
        mainwindow.ui

LIBS    +="C:/Users/LHM\Desktop/cameraUV/Windows/32/sdk/GFileAnalysis.lib"

LIBS    +="C:/Users/LHM\Desktop/cameraUV/Windows/32/sdk/MeasureCoreNet.lib"

DISTFILES += \
    GFileAnalysis.lib \
    MeasureCoreNet.lib \
    GFileAnalysis.dll \
    MeasureCoreNet.dll \
    MeasureCoreNet.cfg \
    arial.ttf
