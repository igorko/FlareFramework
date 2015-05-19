#include "itemswidget.h"
#include "ui_itemswidget.h"

#include "EditorItemManager.h"

ItemsWidget::ItemsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemsWidget),
    items(NULL)
{
    ui->setupUi(this);
}

ItemsWidget::~ItemsWidget()
{
    delete items;
}

void ItemsWidget::saveItems(const std::string &path)
{
    if (items != NULL) items->save(path);
}

void ItemsWidget::loadItems(const std::string &path)
{
    items = new EditorItemManager(path);
}

void ItemsWidget::on_addNewItem_clicked()
{
	items->items.resize(items->items.size() + 1);
	//ui->itemsList->addItem("");
}

void ItemsWidget::on_clearBtn_clicked()
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

void ItemsWidget::on_pushBtn_clicked()
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

void ItemsWidget::on_itemsList_itemClicked(QListWidgetItem *item)
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
