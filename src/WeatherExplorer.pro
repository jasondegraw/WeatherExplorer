#-------------------------------------------------
#
# Project created by QtCreator 2013-10-26T00:13:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherExplorer
TEMPLATE = app

SOURCES += main.cpp\
        weatherexplorer.cpp \
    weatherdatamodel.cpp \
    weatherdatapoint.cpp \
    locationdialog.cpp

HEADERS  += weatherexplorer.h \
    weatherdatamodel.h \
    weatherdatapoint.h \
    locationdialog.h

RESOURCES += \
    resources.qrc

FORMS += \
    locationdialog.ui
