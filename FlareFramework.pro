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
	API/Stats.cpp \
        API/Utils.cpp \
        API/UtilsFileSystem.cpp \
        API/UtilsParsing.cpp \
	API/Animation.cpp \
	API/AnimationSet.cpp \
    itemswidget.cpp \
    iconview.cpp \
    iconwidget.cpp \
    iconselector.cpp \
    spinbox.cpp \
    checkbox.cpp \
    lineedit.cpp

HEADERS  += mainwindow.h \
    itemswidget.h \
    iconview.h \
    iconwidget.h \
    iconselector.h \
    spinbox.h \
    checkbox.h \
    lineedit.h

FORMS    += mainwindow.ui \
    itemswidget.ui \
    iconselector.ui \
    spinbox.ui \
    checkbox.ui \
    lineedit.ui

DEFINES  += EDITOR
