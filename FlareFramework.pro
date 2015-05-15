#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T17:28:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlareFramework
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        EditorItemManager.cpp \
        API/FileParser.cpp \
        API/ItemManager.cpp \
        API/Utils.cpp \
        API/UtilsFileSystem.cpp \
        API/UtilsParsing.cpp \

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
