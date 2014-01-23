# -------------------------------------------------
# Project created by QtCreator 2013-12-06T12:28:49
# -------------------------------------------------
QT += core \
    gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
TARGET = Route
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    widgets.cpp \
    downloader.cpp \
    meineView.cpp \
    Wegfindung.cpp \
    Knoten.cpp \
    meineSzene.cpp \
    funktionen.cpp
HEADERS += mainwindow.h \
    widgets.h \
    downloader.h \
    meineView.h \
    Timer.h \
    Wegfindung.h \
    Knoten.h \
    meineSzene.h \
    funktionen.h
