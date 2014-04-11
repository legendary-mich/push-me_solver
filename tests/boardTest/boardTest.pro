#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T13:21:04
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_boardtests
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11
TEMPLATE = app

INCLUDEPATH += "../../core"
SOURCES += tst_boardtest.cpp \
    ../../core/board/board.cpp \
    ../../core/board/boardbase.cpp \
    boardtest.cpp \
    helpers.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    helpers.h \
    boardtest.h

