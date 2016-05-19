#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QMap>

#include "itemshandler.h"

const int TAB_MAIN = 0;
const int MENU_FILE = 0;

#define ITEM_TYPES      "ItemManager: Types"
#define ITEMS           "ItemManager: Items"
#define ITEM_QUALITIES  "ItemManager: Qualities"
#define ITEM_SETS       "ItemManager: Sets"
#define EFFECTS         "Effects"
#define POWERS          "Powers"
#define QUEST_LOG       "QuestLog"
#define CUTSCENE        "Cutscene"
#define NPC             "NPC"

//key is property name, value is pair<type, description>
typedef QMap<QString, QPair<QString, QString> > NameTypeElementAttributes;
//key is property name, value is description, vector used for ordering
typedef QVector< QPair<QString, QString> > NameElementAttributes;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void BuildUI();

    static QString modPath;

    Ui::MainWindow *ui;

    const NameElementAttributes & getClassTypes(QString className);

public slots:
    void enableSaving();
    void disableSaving();

private slots:
    void itemClose();

    void Close_Mod();

    void Add_Item();
    void loadTab(int index);

    void Save_Mod();

    void Quit();

    void About();

    void Open_Mod();

    void New_Mod();

private:
    void disableAllTabs();
    void enableAllTabs();
    void setMenusEnabled(bool state);
    void setupConnections();
    void CloseAll();

    bool ParseAttributesXML();
    void ReadNameTypeElementAttributes(QString elementName);
    void selectWidgetWithPredefinedString(QGridLayout *layout, int row, int column,
        QString widgetName, QString widgetDescription, QString attrType, QString valuesList);

private:
    bool newMod;
    QXmlStreamReader xml;
    //QMap<attribute_name, attribute_(type-description)>
    QMap<QString, NameTypeElementAttributes> m_classAttributes;
    //QMap<type_name, type_description>
    QMap<QString, NameElementAttributes> m_classTypes;

    QMap<QString, QString> m_classDescriptions;
    ItemsHandler * itemsHandler;

};

#endif // MAINWINDOW_H
