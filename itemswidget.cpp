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
    for (unsigned i = 1; i<items->items.size(); i++)
    {
        if (items->items[i].name != "")
        {
            QListWidgetItem* item = new QListWidgetItem(QString::fromAscii(items->items[i].name.data(), items->items[i].name.size()));
            item->setData(Qt::UserRole, i);
            ui->itemsList->addItem(item);

        }
    }
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

    // comboBoxes
    ui->itemTypeCB->clear();
	ui->requiresType->clear();
	ui->itemQualityCB->clear();
	ui->sfxCb->clear();

    // spinBoxes
    ui->itemLvlSpin->setValue(0);
    ui->price->setValue(0);
    ui->sellPrice->setValue(0);
    ui->absorbMax->setValue(0);
    ui->absorbMin->setValue(0);
    ui->maxQuantity->setValue(0);
    ui->maxLootSpb->setValue(0);
    ui->maxVendorSpb->setValue(0);
    ui->meleeMin->setValue(0);
    ui->meleeMax->setValue(0);
    ui->mentalMin->setValue(0);
    ui->mentalMax->setValue(0);
    ui->power->setValue(0);
    ui->powerMod->setValue(0);
    ui->rangMin->setValue(0);
    ui->rangMax->setValue(0);
    ui->requiresValue->setValue(0);
}

void ItemsWidget::on_pushBtn_clicked()
{
    int index = ui->itemsList->currentItem()->data(Qt::UserRole).toInt();

    // TextEdits
    items->items[index].name = ui->itemName->text().toAscii().constData();
    items->items[index].pickup_status = ui->pickupStatus->text().toAscii().constData();
    items->items[index].power_desc = ui->powerDesc->text().toAscii().constData();

    // comboBoxes
    items->items[index].type     = ui->itemTypeCB->currentIndex();
    items->items[index].quality  = ui->itemQualityCB->currentIndex();
    //items->items[index].sfx      = ui->sfxCb->currentIndex();

    // spinBoxes
    items->items[index].level        = ui->itemLvlSpin->value();
    items->items[index].price               = ui->price->value();
    items->items[index].price_sell   = ui->sellPrice->value();
    items->items[index].abs_max      = ui->absorbMax->value();
    items->items[index].abs_min      = ui->absorbMin->value();
    items->items[index].max_quantity = ui->maxQuantity->value();

    //ui->maxLootSpb->value();
    //ui->maxVendorSpb->value();

    items->items[index].dmg_melee_min  = ui->meleeMin->value();
    items->items[index].dmg_melee_max  = ui->meleeMax->value();
    items->items[index].dmg_ment_max   = ui->mentalMin->value();
    items->items[index].dmg_ment_max   = ui->mentalMax->value();
    items->items[index].dmg_ranged_max = ui->rangMin->value();
    items->items[index].dmg_ranged_min = ui->rangMax->value();

    items->items[index].power               = ui->power->value();
    //items->items[index].replace_power[0].y  = ui->powerMod->value();

    // mixed (pair) controls
    //items->items[index].req_stat[0]    = ui->requiresType->currentIndex();
    //items->items[index].req_val[0]     = ui->requiresValue->value();

    /*
	//Update ListBox
	ListBoxItems->SetString(ListBoxItems->GetSelection(), items->items[index].name.c_str());
	*/
}

void ItemsWidget::on_itemsList_itemClicked(QListWidgetItem *item)
{
    int index = item->data(Qt::UserRole).toInt();

    // TextEdits
    ui->itemName->setText(QString::fromAscii(items->items[index].name.data(), items->items[index].name.size()));
    ui->pickupStatus->setText(QString::fromAscii(items->items[index].pickup_status.data(), items->items[index].pickup_status.size()));
    ui->powerDesc->setText(QString::fromAscii(items->items[index].power_desc.data(), items->items[index].power_desc.size()));

    // comboBoxes
    //ui->itemTypeCB->setCurrentIndex(items->items[index].type);
    ui->itemQualityCB->setCurrentIndex(items->items[index].quality);
    //ui->sfxCb->setCurrentIndex(items->items[index].sfx);

    // spinBoxes
    ui->itemLvlSpin->setValue(items->items[index].level);
    ui->price->setValue(items->items[index].price);
    ui->sellPrice->setValue(items->items[index].price_sell);
    ui->absorbMax->setValue(items->items[index].abs_max);
    ui->absorbMin->setValue(items->items[index].abs_min);
    ui->maxQuantity->setValue(items->items[index].max_quantity);

    //ui->maxLootSpb->value();
    //ui->maxVendorSpb->value();

    ui->meleeMin->setValue(items->items[index].dmg_melee_min);
    ui->meleeMax->setValue(items->items[index].dmg_melee_max);
    ui->mentalMin->setValue(items->items[index].dmg_ment_max);
    ui->mentalMax->setValue(items->items[index].dmg_ment_max);
    ui->rangMin->setValue(items->items[index].dmg_ranged_max);
    ui->rangMax->setValue(items->items[index].dmg_ranged_min);

    ui->power->setValue(items->items[index].power);
    //ui->powerMod->setValue(items->items[index].replace_power[0].y);

    // mixed (pair) controls
    //ui->requiresType->setCurrentIndex(items->items[index].req_stat[0]);
    //ui->requiresValue->setValue(items->items[index].req_val[0]);
}
