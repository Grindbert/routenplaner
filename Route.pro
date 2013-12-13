#-------------------------------------------------
#
# Project created by QtCreator 2013-12-06T12:28:49
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Route
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widgets.cpp \
    downloader.cpp

HEADERS  += mainwindow.h \
    widgets.h \
    downloader.h
