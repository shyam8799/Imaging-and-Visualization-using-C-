#-------------------------------------------------
#
# Project created by QtCreator 2016-01-29T21:51:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ass3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mprvisualizer.cpp \
    cutplane.cpp \
    volume.cpp \
    transferfunction.cpp \
    formula.cpp \
    mhdhandler.cpp \
    detector.cpp \
    source.cpp \
    robot.cpp \
    solver.cpp \
    scanner.cpp \
    ontheflymatrix.cpp \
    csvfilereader.cpp \
    trajectorygenerator.cpp \
    directvolume.cpp

HEADERS  += mainwindow.h \
    mprvisualizer.h \
    cutplane.h \
    volume.h \
    transferfunction.h \
    formula.h \
    mhdhandler.h \
    ioutilities.h \
    detector.h \
    source.h \
    robot.h \
    solver.h \
    scanner.h \
    ontheflymatrix.h \
    csvfilereader.h \
    trajectorygenerator.h \
    directvolume.h

FORMS    += mainwindow.ui

CONFIG += c++11
