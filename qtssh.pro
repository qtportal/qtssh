QT       += core gui

TEMPLATE = app
TARGET = qtssh
DEPENDPATH += . src
INCLUDEPATH += . src

FORMS = src/qtsshdialog.ui

# Input
HEADERS +=  src/qtssh.h  \
            src/qtfilechooser.h \
            src/qtconfig.h \
            src/processharness.h

SOURCES +=  src/qtssh.cpp \
            src/main.cpp \
            src/qtfilechooser.cpp \
            src/qtconfig.cpp \
            src/processharness.cpp
