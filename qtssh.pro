TEMPLATE = app
TARGET = qtssh
DEPENDPATH += . src
INCLUDEPATH += . src

# Input
HEADERS += src/kssh.h
FORMS += src/qtsshdialog.ui
SOURCES += src/kssh.cpp src/main.cpp src/qtsshdialog.cpp
