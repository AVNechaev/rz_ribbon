#-------------------------------------------------
#
# Project created by QtCreator 2017-07-31T23:18:00
#
#-------------------------------------------------

QT       += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rz_ribbon
TEMPLATE = app
VERSION = 1.2.15

SOURCES += main.cpp\        
    fireswsclient.cpp \
    notificator.cpp \
    ribbonapp.cpp \
    settingswindow.cpp \
    ribbonwnd.cpp \
    ribbonmodel.cpp \
    settings.cpp \
    logwriter.cpp

HEADERS  += fireswsclient.h \
    notificator.h \
    ribbonapp.h \
    settingswindow.h \
    ribbonwnd.h \
    firedata.h \
    ribbonmodel.h \
    settings.h \
    logwriter.h

RESOURCES += \
    resources.qrc

FORMS += \
    settingswindow.ui \
    ribbonwnd.ui

win32 {
    release {
        QMAKE_POST_LINK = $$shell_path($$_PRO_FILE_PWD_)\tools\zip.exe $$shell_path($$_PRO_FILE_PWD_)\releases\\$${TARGET}_$${VERSION}.zip $$shell_path($$OUT_PWD)\release\\$${TARGET}.exe
    }
}
