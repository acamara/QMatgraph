#-------------------------------------------------
#
# Project created by QtCreator 2012-08-27T21:22:08
#
#-------------------------------------------------

QT       += core gui
CONFIG   += qwt

TARGET   = QMatgraph
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
    interpreter/variablelist.cpp \
    interpreter/parser.cpp \
    interpreter/functions.cpp \
    interpreter/error.cpp

HEADERS   += mainwindow.h \
    interpreter/variablelist.h \
    interpreter/parser.h \
    interpreter/functions.h \
    interpreter/error.h \
    interpreter/constants.h

FORMS     += mainwindow.ui

RESOURCES += resources.qrc
