#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T20:46:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = poe-qt-regex-editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    autopricemanagerdialog.cpp \
    autopricemanager.cpp \
    autopriceitem.cpp

HEADERS  += mainwindow.h \
    autopricemanagerdialog.h \
    autopricemanager.h \
    autopriceitem.h

FORMS    += mainwindow.ui \
    autopricemanagerdialog.ui
