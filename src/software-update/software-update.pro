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

SOURCES += softwareupdate.cpp \
           Core\updatechecker.cpp \
           Core\filedownloader.cpp \
           Core\updatedownloader.cpp \
           Windows\updatewindow.cpp \
           Windows\downloadwindow.cpp

HEADERS += softwareupdate.h \
           software-update_global.h \
           Core\updatechecker.h \
           Core\filedownloader.h \
           Core\updatedownloader.h \
           Windows\updatewindow.h \
           Windows\downloadwindow.h \
           structs.h

FORMS += Windows\downloadwindow.ui \
         Windows\updatewindow.ui

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
