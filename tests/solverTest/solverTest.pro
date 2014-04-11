#-------------------------------------------------
#
# Project created by QtCreator 2013-11-16T12:56:31
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_solvertest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app

INCLUDEPATH += "../../core"

SOURCES += tst_solvertest.cpp \
    ../../core/board/board.cpp \
    ../../core/solver/visitednode.cpp \
    ../../core/solver/step.cpp \
    solvertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    solvertest.h
