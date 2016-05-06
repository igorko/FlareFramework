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
    lineedit.cpp \
    doublespinbox.cpp \
    iconchooser.cpp \
    stringlistwidget.cpp \
    lootanimationwidget.cpp \
    twospinbox.cpp \
    twostringlists.cpp \
    combobox.cpp \
    elementslist.cpp \
    itemshandler.cpp \
    controlframe.cpp \
    comboboxkeyvaluelist.cpp

HEADERS  += mainwindow.h \
    itemswidget.h \
    iconview.h \
    iconwidget.h \
    iconselector.h \
    spinbox.h \
    checkbox.h \
    lineedit.h \
    doublespinbox.h \
    iconchooser.h \
    stringlistwidget.h \
    lootanimationwidget.h \
    twospinbox.h \
    twostringlists.h \
    combobox.h \
    elementslist.h \
    itemshandler.h \
    controlframe.h \
    comboboxkeyvaluelist.h

FORMS    += mainwindow.ui \
    itemswidget.ui \
    iconselector.ui \
    spinbox.ui \
    checkbox.ui \
    lineedit.ui \
    doublespinbox.ui \
    iconchooser.ui \
    stringlistwidget.ui \
    lootanimationwidget.ui \
    twospinbox.ui \
    twostringlists.ui \
    combobox.ui \
    elementslist.ui \
    controlframe.ui \
    comboboxkeyvaluelist.ui

DEFINES  += EDITOR
