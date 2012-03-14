TEMPLATE = app
TARGET = qtssh
DEPENDPATH += . src
INCLUDEPATH += . src

# Input
HEADERS += src/kssh.h src/qtfilechooser.h
FORMS += src/qtsshdialog.ui
SOURCES += src/kssh.cpp src/main.cpp src/qtsshdialog.cpp src/qtfilechooser.cpp
