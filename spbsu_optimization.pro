#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T15:07:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spbsu_optimization
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    AREA.cpp \
    FUNC.cpp \
    OPTIMISATION.cpp \
    RNG.cpp \
    STOP.cpp \
    qtDRAWER.cpp \
    FUNCTION_FIELD.cpp

HEADERS  += mainwindow.h \
    AREA.h \
    FUNC.h \
    OPTIMISATION.h \
    RNG.h \
    STOP.h \
    qtDRAWER.h \
    FUNCTION_FIELD.h

FORMS    += mainwindow.ui
