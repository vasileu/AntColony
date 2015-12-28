#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T13:30:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AntsColony
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    graph.cpp \
    paintwidget.cpp \
    graphgenerator.cpp \
    graphpainter.cpp \
    pallette.cpp \
    antcolony.cpp \
    ant.cpp \
    geneticalgorithm.cpp \
    chromosome.cpp

HEADERS  += \
    mainwindow.h \
    graph.h \
    paintwidget.h \
    graphgenerator.h \
    graphpainter.h \
    pallette.h \
    antcolony.h \
    ant.h \
    geneticalgorithm.h \
    chromosome.h

FORMS    += \
    mainwindow.ui
