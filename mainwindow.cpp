#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMenusEnabled(false);
    disableAllTabsExceptIndex(0);
    modPath = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_itemClose_clicked()
{
    disableAllTabsExceptIndex(TAB_MAIN);
}

void MainWindow::disableAllTabsExceptIndex(int index)
{
    for (int i = 0; i < ui->tabWidget->count(); i++)
    {
        ui->tabWidget->setTabEnabled(i, false);
    }
    if (index >= 0 && index < ui->tabWidget->count())
    {
        ui->tabWidget->setTabEnabled(index, true);
        ui->tabWidget->setCurrentIndex(index);
    }
}

void MainWindow::setMenusEnabled(bool state)
{
    QList<QAction*> actions = menuBar()->actions();

    actions.at(MENU_FILE)->menu()->actions().at(0)->setEnabled(!state);
    actions.at(MENU_FILE)->menu()->actions().at(1)->setEnabled(!state);
    actions.at(MENU_FILE)->menu()->actions().at(2)->setEnabled(state);
    actions.at(MENU_FILE)->menu()->actions().at(3)->setEnabled(state);

    actions.at(MENU_CREATURES)->menu()->actions().at(0)->setEnabled(state);
    actions.at(MENU_CREATURES)->menu()->actions().at(1)->setEnabled(state);

    for (int i = 0; i < 9; i++)
    {
        actions.at(MENU_MENUS)->menu()->actions().at(0)->menu()->actions().at(i)->setEnabled(state);
    }

    actions.at(MENU_MENUS)->menu()->actions().at(1)->menu()->actions().at(0)->setEnabled(state);
    actions.at(MENU_MENUS)->menu()->actions().at(1)->menu()->actions().at(1)->setEnabled(state);
    actions.at(MENU_MENUS)->menu()->actions().at(1)->menu()->actions().at(2)->setEnabled(state);

    actions.at(MENU_STUFF)->menu()->actions().at(0)->setEnabled(state);
    actions.at(MENU_STUFF)->menu()->actions().at(1)->setEnabled(state);

    actions.at(MENU_STORY)->menu()->actions().at(0)->setEnabled(state);
}

void MainWindow::on_actionClose_Mod_triggered()
{
    if (modPath == "") return;
    if (ui->Items->itemsEdited)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Save mod", "Save mod before closing?", QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            QString filename = modPath + QDir::separator() + "items" + QDir::separator() + "items.txt";
            std::string path = filename.toUtf8().constData();
            ui->Items->saveItems(path);
        }
    }
    modPath = "";
    setMenusEnabled(false);
    ui->Items->clearItemsList();

    CloseAll();
}

void MainWindow::CloseAll()
{
    disableAllTabsExceptIndex(TAB_MAIN);
    //ToDo
}

void MainWindow::on_actionAdd_Item_triggered()
{
    disableAllTabsExceptIndex(TAB_ITEMS);

    if (!QDir(modPath + QDir::separator() + "items").exists())
        QDir().mkdir(modPath + QDir::separator() + "items");

    //QFile itemsFile(filepath);
    //if (!itemsFile.exists())
    //    itemsFile.Create();

    std::string path = (modPath + QDir::separator()).toUtf8().constData();
    ui->Items->loadItems(path);
}

void MainWindow::on_actionSave_Mod_triggered()
{
    QString filename = modPath + QDir::separator() + "items" + QDir::separator() + "items.txt";
    ui->Items->saveItems(filename.toUtf8().constData());
    //ToDo

}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QString msg = "FLARE Game Development Environment v0.1";
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setText(msg);
    msgBox->exec();
}

void MainWindow::on_actionOpen_Mod_triggered()
{
    newMod = false;
    QString path = QFileDialog::getExistingDirectory(this, QObject::tr("Select mod folder"));

    if (!path.isEmpty()){
        modPath = path;
        setMenusEnabled(true);
    }
}

void MainWindow::on_actionNew_Mod_triggered()
{
    newMod = true;
    QString path = QFileDialog::getExistingDirectory(this, QObject::tr("Select mod folder"));
    if (!path.isEmpty()){
        modPath = path;
        setMenusEnabled(true);
    }
}
