QT       += core gui

TEMPLATE = app
TARGET = qtssh
DEPENDPATH += . src
INCLUDEPATH += . src

# Input
HEADERS += src/qtssh.h src/qtfilechooser.h
FORMS = src/qtsshdialog.ui
SOURCES += src/qtssh.cpp src/main.cpp src/qtfilechooser.cpp
