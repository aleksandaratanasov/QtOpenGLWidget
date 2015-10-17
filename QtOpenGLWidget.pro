#-------------------------------------------------
#
# Project created by QtCreator 2015-10-17T16:14:48
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

//QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
CONFIG += release

TARGET = QtOpenGLWidget
#TEMPLATE = app
TEMPLATE = lib


SOURCES += \
        main.cpp \
        qtopenglwidget.cpp \
        openglcontainer.cpp

HEADERS  += \
        qtopenglwidget.hpp \
        openglcontainer.hpp

FORMS    += qtopenglwidget.ui

LIBS     += -lglut -lGL -lGLU
