#-------------------------------------------------
#
# Project created by QtCreator 2019-04-29T00:02:25
#
#-------------------------------------------------

QT       -= core gui

TARGET = longDigit
TEMPLATE = lib
CONFIG += staticlib

SOURCES += longdigit.cpp

HEADERS += longdigit.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
