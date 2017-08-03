#-------------------------------------------------
#
# Project created by QtCreator 2017-07-31T23:18:00
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rz_ribbon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fireswsclient.cpp \
    notificator.cpp

HEADERS  += mainwindow.h \
    fireswsclient.h \
    notificator.h

RESOURCES += \
    resources.qrc
