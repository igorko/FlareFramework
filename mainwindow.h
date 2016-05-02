#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include <QMap>

const int TAB_MAIN = 0;
const int TAB_ITEMS = 1;
const int TAB_POWERS = 2;
const int TAB_ENEMIES = 3;
const int TAB_NPCS = 4;
const int TAB_QUESTS = 5;

const int MENU_FILE = 0;
const int MENU_CREATURES = 1;
const int MENU_MENUS = 2;
const int MENU_STUFF = 3;
const int MENU_STORY = 5;

//key is property name, value is pair<type, description>
typedef QMap<QString, QPair<QString, QString> > NameTypeElementAttributes;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    static QString modPath;

public slots:
    void enableSaving();
    void disableSaving();

private slots:
    void itemClose();

    void Close_Mod();

    void Add_Item();

    void Save_Mod();

    void Quit();

    void About();

    void Open_Mod();

    void New_Mod();

private:
    Ui::MainWindow *ui;

    void disableAllTabsExceptIndex(int index);
    void setMenusEnabled(bool state);
    void setupConnections();
    void CloseAll();

    bool ParseAttributesXML();
    void ReadNameTypeElementAttributes(QString elementName);

private:
    bool newMod;
    QXmlStreamReader xml;
    QMap<QString, NameTypeElementAttributes> m_nameTypeElements;
    QMap<QString, QString> m_nameTypeElementDescriptions;
    QVector<QString> predefinedNameTypeElements;

};

#endif // MAINWINDOW_H
