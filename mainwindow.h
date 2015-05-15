#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

class EditorItemManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addNewItem_clicked();

    void on_clearBtn_clicked();

    void on_itemClose_clicked();

    void on_actionClose_Mod_triggered();

    void on_pushBtn_clicked();

    void on_itemsList_itemClicked(QListWidgetItem *item);

    void on_actionAdd_Item_triggered();

    void on_actionSave_Mod_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionOpen_Mod_triggered();

    void on_actionNew_Mod_triggered();

private:
    Ui::MainWindow *ui;

    QString modPath;
    QString modName;
    void setMenusEnabled(bool state);
    void ToDo();
    void CloseAll();
    bool newMod;
    EditorItemManager * items;

};

#endif // MAINWINDOW_H
