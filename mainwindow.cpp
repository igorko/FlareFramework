#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include "EditorItemManager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMenusEnabled(false);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(2, false);
    modPath = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMenusEnabled(bool state)
{
    auto actions = menuBar()->actions();
    actions.at(1)->menu()->actions().at(0)->setEnabled(state);
    actions.at(1)->menu()->actions().at(1)->setEnabled(state);

    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(0)->setEnabled(state);
    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(1)->setEnabled(state);
    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(2)->setEnabled(state);
    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(3)->setEnabled(state);
    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(4)->setEnabled(state);
    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(5)->setEnabled(state);
    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(6)->setEnabled(state);
    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(7)->setEnabled(state);
    actions.at(2)->menu()->actions().at(0)->menu()->actions().at(8)->setEnabled(state);

    actions.at(2)->menu()->actions().at(1)->menu()->actions().at(0)->setEnabled(state);
    actions.at(2)->menu()->actions().at(1)->menu()->actions().at(1)->setEnabled(state);
    actions.at(2)->menu()->actions().at(1)->menu()->actions().at(2)->setEnabled(state);

    actions.at(3)->menu()->actions().at(0)->setEnabled(state);
    actions.at(3)->menu()->actions().at(1)->setEnabled(state);

    actions.at(5)->menu()->actions().at(0)->setEnabled(state);
}

void MainWindow::on_addNewItem_clicked()
{
    items->items.resize(items->items.size() + 1);
    //ui->itemsList->addItem("");
}

void MainWindow::on_clearBtn_clicked()
{
    ui->itemName->clear();
    ui->itemName->setText("ItemName");
    ui->ClassEdit->clear();
    ui->bonus->clear();
    ui->bonusVal->clear();
    ui->pickupStatus->clear();
    ui->powerDesc->clear();

    ui->itemTypeCB->clear();
    ui->requiresType->clear();
    ui->itemQualityCB->clear();
    ui->sfxCb->clear();
    ui->itemLvlSpin->clear();
    ui->sellPrice->clear();
    ui->absorbMax->clear();
    ui->absorbMin->clear();

    ui->maxQuantity->clear();
    ui->maxLootSpb->clear();
    ui->maxVendorSpb->clear();
    ui->meleeMin->clear();
    ui->meleeMax->clear();
    ui->mentalMin->clear();
    ui->mentalMax->clear();
    ui->power->clear();
    ui->powerMod->clear();
    ui->price->clear();
    ui->rangMin->clear();
    ui->rangMax->clear();
    ui->requiresValue->clear();
}

void MainWindow::on_itemClose_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabEnabled(1, false);
}

void MainWindow::on_actionClose_Mod_triggered()
{
    if (modPath == "") return;
    //wxMessageDialog saveQuestion(this, wxT("Save mod before closing?"), wxT("Save mod"), wxYES_DEFAULT|wxYES_NO|wxCANCEL|wxICON_INFORMATION);
    //int answer = saveQuestion.ShowModal();
    //if (answer == wxID_YES)
    //{
        QString filename = modPath + "/" + "items" + "/" + "items.txt";
        std::string path = filename.toAscii();
        items->save(path);
        // ToDo
    //}
    //else if (answer == wxID_CANCEL)
    //{
        return;
    //}
    modName = "";
    modPath = "";
    setMenusEnabled(false);
    /*
    MenuItemOpen->Enable(true);
    MenuItemCreate->Enable(true);
    */

    CloseAll();
}

void MainWindow::CloseAll()
{
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabEnabled(1, false);
    delete items;
    ui->itemsList->clear();
    //ToDo
}

void MainWindow::on_pushBtn_clicked()
{
    int index = 0;
    /*
    int index = ListBoxItems->GetSelection() + 1;
    items->items[index].name = TextCtrlItemName->GetLineText(0);
    items->items[index].pickup_status = TextCtrlItemPickup->GetLineText(0);
    items->items[index].power_desc = TextCtrlItemPowerDesc->GetLineText(0);

    std::string classlist = std::string(TextCtrlItemClass->GetLineText(0).mb_str());
    classlist = classlist + ',';
    std::string classname = eatFirstString(classlist, ',');
    items->items[index].classname.clear();
    while (classname != "") {
        items->items[index].classname.push_back(classname);
        classname = eatFirstString(classlist, ',');
    }

    std::string bonus_stat_list = std::string(TextCtrlitemBonus->GetLineText(0).mb_str());
    bonus_stat_list = bonus_stat_list + ',';
    std::string bonus_stat = eatFirstString(bonus_stat_list, ',');
    items->items[index].bonus_stat.clear();
    while (bonus_stat != "") {
        items->items[index].bonus_stat.push_back(bonus_stat);
        bonus_stat = eatFirstString(bonus_stat_list, ',');
    }

    std::string bonus_val_list = std::string(TextCtrlItemBonusVal->GetLineText(0).mb_str());
    bonus_val_list = bonus_val_list + ',';
    std::string bonus_val = eatFirstString(bonus_val_list, ',');
    items->items[index].bonus_val.clear();
    while (bonus_val != "") {
        items->items[index].bonus_val.push_back(toInt(bonus_val));
        bonus_val = eatFirstString(bonus_val_list, ',');
    }
    items->items[index].type = ComboBoxItemType->GetValue();

    items->items[index].req_stat = ComboBoxitemRequires->GetSelection();
    items->items[index].quality = ComboBoxItemQuality->GetSelection();
    items->items[index].sfx = ComboBoxItemSfx->GetSelection();

    items->items[index].level = SpinCtrlItemLevel->GetValue();
    items->items[index].price = SpinCtrlItemPrice->GetValue();
    items->items[index].price_sell = SpinCtrlItemSell->GetValue();
    items->items[index].abs_max = SpinCtrlItemAbsMax->GetValue();
    items->items[index].abs_min = SpinCtrlItemAbsMin->GetValue();
    items->items[index].max_quantity = SpinCtrlItemMaxQuan->GetValue();
    items->items[index].dmg_melee_max = SpinCtrlItemMelDmgMax->GetValue();
    items->items[index].dmg_melee_min = SpinCtrlItemMelDmgMin->GetValue();
    items->items[index].dmg_ment_max = SpinCtrlItemMentDmgMax->GetValue();
    items->items[index].dmg_ment_min = SpinCtrlItemMentDmgMin->GetValue();
    items->items[index].power = SpinCtrlItemPower->GetValue();
    items->items[index].power_mod = SpinCtrlItemPowerMod->GetValue();
    items->items[index].dmg_ranged_max = SpinCtrlItemRanDmgMax->GetValue();
    items->items[index].dmg_ranged_min = SpinCtrlItemRanDmgMin->GetValue();
    items->items[index].rand_loot = SpinCtrlItemRan_loot->GetValue();
    items->items[index].rand_vendor = SpinCtrlItemRan_ven->GetValue();
    items->items[index].req_val = SpinCtrlItemRequires->GetValue();

    //Update ListBox
    ListBoxItems->SetString(ListBoxItems->GetSelection(), items->items[index].name.c_str());
    */
}

void MainWindow::on_itemsList_itemClicked(QListWidgetItem *item)
{
    /*
    int index = ListBoxItems->GetSelection() + 1;
    wxString temp0(items->items[index].name.c_str(), wxConvUTF8);
    TextCtrlItemName->Clear();
    TextCtrlItemName->AppendText(temp0);

    wxString temp2(items->items[index].pickup_status.c_str(), wxConvUTF8);
    TextCtrlItemPickup->Clear();
    TextCtrlItemPickup->AppendText(temp2);

    wxString temp3(items->items[index].power_desc.c_str(), wxConvUTF8);
    TextCtrlItemPowerDesc->Clear();
    TextCtrlItemPowerDesc->AppendText(temp3);

    TextCtrlItemClass->Clear();
    if (items->items[index].classname.size() > 0) {
        for (unsigned i = 0;i<items->items[index].classname.size()-1;i++) {
        wxString temp4(items->items[index].classname[i].c_str(), wxConvUTF8);
            TextCtrlItemClass->AppendText(temp4);
            TextCtrlItemClass->AppendText(",");
        }
        wxString temp4(items->items[index].classname.back().c_str(), wxConvUTF8);
        TextCtrlItemClass->AppendText(temp4);
    }

    TextCtrlitemBonus->Clear();
    if (items->items[index].bonus_stat.size() > 0) {
        for (unsigned i = 0;i<items->items[index].bonus_stat.size()-1;i++) {
        wxString temp5(items->items[index].bonus_stat[i].c_str(), wxConvUTF8);
            TextCtrlitemBonus->AppendText(temp5);
            TextCtrlitemBonus->AppendText(",");
        }
        wxString temp5(items->items[index].bonus_stat.back().c_str(), wxConvUTF8);
        TextCtrlitemBonus->AppendText(temp5);
    }

    TextCtrlItemBonusVal->Clear();
    if (items->items[index].bonus_val.size() > 0) {
        for (unsigned i = 0;i<items->items[index].bonus_val.size()-1;i++) {
        wxString temp6(wxString::Format(wxT("%i"),items->items[index].bonus_val[i]));
            TextCtrlItemBonusVal->AppendText(temp6);
            TextCtrlItemBonusVal->AppendText(",");
        }
        wxString temp6(wxString::Format(wxT("%i"),items->items[index].bonus_val.back()));
        TextCtrlItemBonusVal->AppendText(temp6);
    }

    wxString temp7(items->items[index].type.c_str(), wxConvUTF8);
    ComboBoxItemType->SetValue(temp7);
    ComboBoxitemRequires->SetSelection(items->items[index].req_stat);
    ComboBoxItemQuality->SetSelection(items->items[index].quality);
    ComboBoxItemSfx->SetSelection(items->items[index].sfx);

    SpinCtrlItemLevel->SetValue(items->items[index].level);
    SpinCtrlItemPrice->SetValue(items->items[index].price);
    SpinCtrlItemSell->SetValue(items->items[index].price_sell);
    SpinCtrlItemAbsMax->SetValue(items->items[index].abs_max);
    SpinCtrlItemAbsMin->SetValue(items->items[index].abs_min);
    SpinCtrlItemMaxQuan->SetValue(items->items[index].max_quantity);
    SpinCtrlItemMelDmgMax->SetValue(items->items[index].dmg_melee_max);
    SpinCtrlItemMelDmgMin->SetValue(items->items[index].dmg_melee_min);
    SpinCtrlItemMentDmgMax->SetValue(items->items[index].dmg_ment_max);
    SpinCtrlItemMentDmgMin->SetValue(items->items[index].dmg_ment_min);
    SpinCtrlItemPower->SetValue(items->items[index].power);
    SpinCtrlItemPowerMod->SetValue(items->items[index].power_mod);
    SpinCtrlItemRanDmgMax->SetValue(items->items[index].dmg_ranged_max);
    SpinCtrlItemRanDmgMin->SetValue(items->items[index].dmg_ranged_min);
    SpinCtrlItemRan_loot->SetValue(items->items[index].rand_loot);
    SpinCtrlItemRan_ven->SetValue(items->items[index].rand_vendor);
    SpinCtrlItemRequires->SetValue(items->items[index].req_val);
    */
}

void MainWindow::on_actionAdd_Item_triggered()
{
    ui->tabWidget->setTabEnabled(0, false);
    ui->tabWidget->setTabEnabled(1, true);
    ui->tabWidget->setCurrentIndex(1);
    /*
    if (!wxFileName::DirExists(modPath + wxT("/") + "items"))
        wxFileName::Mkdir(modPath + wxT("/") + "items");
    wxString filename = modPath + wxT("/") + "items" + wxT("/") + wxT("items.txt");

    wxTextFile itemsFile(filename);
    if (!itemsFile.Exists())
        itemsFile.Create();

    std::string path = std::string(filename.mb_str());
    items = new ItemManager(path);
    for (unsigned i = 1;i<items->items.size();i++) {
        ListBoxItems->Append(items->items[i].name.c_str());
    }
    */
}

void MainWindow::on_actionSave_Mod_triggered()
{
    QString filename = modPath + "/" + "items" + "/" + "items.txt";
    items->save(filename.toAscii().constData());
    //ToDo

}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QString msg = "FLARE Game Development Environment v0.1";
    auto msgBox = new QMessageBox(this);
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
        //MenuItemCreate->Enable(false);
        //MenuItemOpen->Enable(false);
    }
}

void MainWindow::on_actionNew_Mod_triggered()
{
    newMod = true;
    /*if (ModDirDialog->ShowModal() == wxID_OK){
        modPath = ModDirDialog->GetPath();
        modName = wxGetTextFromUser (wxT("Enter mod name"), wxT("Enter mod name"), wxT("new_mod"), NULL, wxDefaultCoord, wxDefaultCoord, true);
        modPath = modPath + wxT("/") + modName;
        if (!wxFileName::DirExists(modPath))
            wxFileName::Mkdir(modPath);
        EnableMenus();
        MenuItemCreate->Enable(false);
        MenuItemOpen->Enable(false);
    }*/
}
