#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:27:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = switchbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmswitchbutton.cpp
SOURCES     += switchbutton.cpp

HEADERS     += frmswitchbutton.h
HEADERS     += switchbutton.h

FORMS       += frmswitchbutton.ui
