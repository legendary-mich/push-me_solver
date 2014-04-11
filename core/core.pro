TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    board/board.cpp \
    board/boardeditor.cpp \
    solver/visitednode.cpp \
    solver/step.cpp \
    solver/solver.cpp \
    board/boardbase.cpp \
    helpers/services.cpp

HEADERS += \
    board/boardbase.h \
    board/board.h \
    board/blocks.h \
    board/boardeditor.h \
    helpers/intVector.h \
    helpers/moveDescription.h \
    solver/visitednode.h \
    solver/step.h \
    solver/solver.h \
    helpers/services.h

