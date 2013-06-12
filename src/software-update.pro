#-------------------------------------------------
#
# Project created by QtCreator 2013-04-13T16:36:31
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++0x

TARGET = software-update
TEMPLATE = lib

DEFINES += SOFTWAREUPDATE_LIBRARY

SOURCES += sul_softwareupdate.cpp \
           sul_updatechecker.cpp \
           sul_filedownloader.cpp \
           sul_updatewindow.cpp \
           sul_downloadwindow.cpp

HEADERS += sul_softwareupdate.h \
           software-update_global.h \
           sul_updatechecker.h \
           sul_filedownloader.h \
           sul_updatewindow.h \
           sul_downloadwindow.h \
           sul_structs.h

FORMS += sul_downloadwindow.ui \
         sul_updatewindow.ui

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
