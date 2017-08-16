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
    fireswsclient.cpp \
    notificator.cpp \
    ribbonapp.cpp \
    settingswindow.cpp \
    ribbonwnd.cpp \
    ribbonmodel.cpp

HEADERS  += fireswsclient.h \
    notificator.h \
    ribbonapp.h \
    settingswindow.h \
    ribbonwnd.h \
    firedata.h \
    ribbonmodel.h \
    settings.h

RESOURCES += \
    resources.qrc

FORMS += \
    settingswindow.ui \
    ribbonwnd.ui
