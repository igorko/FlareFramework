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
    comboboxkeyvaluelist.cpp \
    entityhandler.cpp

HEADERS  += mainwindow.h \
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
    comboboxkeyvaluelist.h \
    API/Animation.h \
    API/AnimationSet.h \
    API/CommonIncludes.h \
    API/FileParser.h \
    API/ItemManager.h \
    API/Stats.h \
    API/Utils.h \
    API/UtilsFileSystem.h \
    API/UtilsParsing.h \
    entityhandler.h

FORMS    += mainwindow.ui \
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
