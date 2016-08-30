#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T08:54:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    networkwrapper.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    networkwrapper.h

FORMS    += mainwindow.ui \
    dialog.ui




LIBS += -L$$PWD/../lib/native/ -lNetwork

INCLUDEPATH += $$PWD/../lib/native
INCLUDEPATH += $$PWD/../Network

DEPENDPATH += $$PWD/../lib/native
INCLUDEPATH += C:/boost_1_61_0/
DEPENDPATH += C:/boost_1_61_0/stage/lib/
QMAKE_LIBDIR += C:/boost_1_61_0/stage/lib/
//QMAKE_LIBDIR += $$PWD/../lib/native

PRE_TARGETDEPS += $$PWD/../lib/native/Network.lib
PRE_TARGETDEPS += C:/boost_1_61_0/stage/lib/libboost_system-vc140-mt-gd-1_61.lib
