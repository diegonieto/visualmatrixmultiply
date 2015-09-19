#-------------------------------------------------
#
# Project created by QtCreator 2015-09-11T18:41:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Matrix_multiply
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    Matrix.hpp \
    Point.hpp \
    NumericMatrix.hpp

FORMS    += mainwindow.ui
