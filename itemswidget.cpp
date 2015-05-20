#include "itemswidget.h"
#include "ui_itemswidget.h"

#include "EditorItemManager.h"

#include <QTextBlock>

ItemsWidget::ItemsWidget(QWidget *parent) :
    QWidget(parent),
    itemsEdited(false),
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
    ui->pushBtn->setEnabled(false);
}

void ItemsWidget::clearItemsList()
{
    itemsEdited = false;
    delete items;
    items = NULL;
}

void ItemsWidget::on_addNewItem_clicked()
{
	items->items.resize(items->items.size() + 1);
    int index = items->items.size() - 1;
    items->items[index].name = "newItem";

    QListWidgetItem* item = new QListWidgetItem("newItem");
    item->setData(Qt::UserRole, index);
    ui->itemsList->addItem(item);
}

void ItemsWidget::on_clearBtn_clicked()
{
    ui->itemName->clear();
	ui->itemName->setText("ItemName");
    ui->itemFlavor->clear();
    ui->itemBook->clear();
	ui->ClassEdit->clear();
	ui->pickupStatus->clear();
	ui->powerDesc->clear();
    ui->replacePowerFrom->clear();
    ui->replacePowerTo->clear();
    ui->disableSlots->clear();

    // comboBoxes
    ui->itemTypeCB->clear();
    ui->itemQualityCB->setCurrentIndex(1);
	ui->sfxCb->clear();

    // spinBoxes
    ui->itemLvlSpin->setValue(0);
    ui->price->setValue(0);
    ui->sellPrice->setValue(0);
    ui->absorbMax->setValue(0);
    ui->absorbMin->setValue(0);
    ui->maxQuantity->setValue(0);
    ui->meleeMin->setValue(0);
    ui->meleeMax->setValue(0);
    ui->mentalMin->setValue(0);
    ui->mentalMax->setValue(0);
    ui->power->setValue(0);
    ui->rangMin->setValue(0);
    ui->rangMax->setValue(0);
    ui->reqDef->setValue(0);
    ui->reqMent->setValue(0);
    ui->reqOff->setValue(0);
    ui->reqDef->setValue(0);

    //ui->bonus->clear();
    //ui->bonusVal->clear();
}

void ItemsWidget::on_pushBtn_clicked()
{
    int index = ui->itemsList->currentItem()->data(Qt::UserRole).toInt();

    // TextEdits
    items->items[index].name = ui->itemName->text().toAscii().constData();
    items->items[index].flavor = ui->itemFlavor->text().toAscii().constData();
    items->items[index].pickup_status = ui->pickupStatus->text().toAscii().constData();
    items->items[index].power_desc = ui->powerDesc->text().toAscii().constData();
    items->items[index].book = ui->itemBook->text().toAscii().constData();
    items->items[index].requires_class = ui->ClassEdit->text().toAscii().constData();

    QTextDocument* docFrom = ui->replacePowerFrom->document();
    QTextDocument* docTo   = ui->replacePowerTo->document();
    items->items[index].replace_power.clear();

    for (int i = 0; i < docFrom->lineCount(); i++)
    {
        items->items[index].replace_power.push_back(Point(
                                                        docFrom->findBlockByLineNumber(i).text().toInt(),
                                                        docTo->findBlockByLineNumber(i).text().toInt()));
    }

    QTextDocument* disabledSlots = ui->disableSlots->document();
    items->items[index].disable_slots.clear();

    for (int i = 0; i < disabledSlots->lineCount(); i++)
    {
        items->items[index].disable_slots.push_back(disabledSlots->findBlockByLineNumber(i).text().toAscii().constData());
    }

    // comboBoxes
    //items->items[index].type     = ui->itemTypeCB->currentIndex();
    items->items[index].quality  = ui->itemQualityCB->currentIndex();
    //items->items[index].sfx      = ui->sfxCb->currentIndex();

    // spinBoxes
    items->items[index].level        = ui->itemLvlSpin->value();
    items->items[index].price        = ui->price->value();
    items->items[index].price_sell   = ui->sellPrice->value();
    items->items[index].abs_max      = ui->absorbMax->value();
    items->items[index].abs_min      = ui->absorbMin->value();
    items->items[index].max_quantity = ui->maxQuantity->value();
    items->items[index].dmg_melee_min  = ui->meleeMin->value();
    items->items[index].dmg_melee_max  = ui->meleeMax->value();
    items->items[index].dmg_ment_max   = ui->mentalMin->value();
    items->items[index].dmg_ment_max   = ui->mentalMax->value();
    items->items[index].dmg_ranged_max = ui->rangMin->value();
    items->items[index].dmg_ranged_min = ui->rangMax->value();
    items->items[index].power          = ui->power->value();

    items->items[index].req_stat.clear();
    items->items[index].req_val.clear();

    if (ui->reqDef->value() > 0)
    {
        items->items[index].req_stat.push_back(REQUIRES_PHYS);
        items->items[index].req_val.push_back(ui->reqDef->value());
    }
    if (ui->reqMent->value() > 0)
    {
        items->items[index].req_stat.push_back(REQUIRES_MENT);
        items->items[index].req_val.push_back(ui->reqMent->value());
    }
    if (ui->reqOff->value() > 0)
    {
        items->items[index].req_stat.push_back(REQUIRES_OFF);
        items->items[index].req_val.push_back(ui->reqOff->value());
    }
    if (ui->reqDef->value() > 0)
    {
        items->items[index].req_stat.push_back(REQUIRES_DEF);
        items->items[index].req_val.push_back(ui->reqDef->value());
    }

    //Update ListBox
    ui->itemsList->currentItem()->setData(Qt::DisplayRole, ui->itemName->text());

    itemsEdited = true;
}

void ItemsWidget::on_itemsList_itemClicked(QListWidgetItem *item)
{
    ui->pushBtn->setEnabled(true);
    int index = item->data(Qt::UserRole).toInt();

    // TextEdits
    ui->itemName->setText(QString::fromAscii(items->items[index].name.data(), items->items[index].name.size()));
    ui->pickupStatus->setText(QString::fromAscii(items->items[index].pickup_status.data(), items->items[index].pickup_status.size()));
    ui->powerDesc->setText(QString::fromAscii(items->items[index].power_desc.data(), items->items[index].power_desc.size()));
    ui->itemFlavor->setText(QString::fromAscii(items->items[index].flavor.data(), items->items[index].flavor.size()));
    ui->itemBook->setText(QString::fromAscii(items->items[index].book.data(), items->items[index].book.size()));
    ui->ClassEdit->setText(QString::fromAscii(items->items[index].requires_class.data(), items->items[index].requires_class.size()));

    ui->replacePowerFrom->clear();
    ui->replacePowerTo->clear();
    for (unsigned int i = 0; i < items->items[index].replace_power.size(); i++)
    {
        ui->replacePowerFrom->appendPlainText(QString::number(items->items[index].replace_power[i].x));
        ui->replacePowerTo->appendPlainText(QString::number(items->items[index].replace_power[i].y));
    }

    ui->disableSlots->clear();
    for (unsigned int i = 0; i < items->items[index].disable_slots.size(); i++)
    {
        ui->disableSlots->appendPlainText(QString::fromAscii(items->items[index].disable_slots[i].data(), items->items[index].disable_slots[i].size()));
    }

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
    ui->meleeMin->setValue(items->items[index].dmg_melee_min);
    ui->meleeMax->setValue(items->items[index].dmg_melee_max);
    ui->mentalMin->setValue(items->items[index].dmg_ment_max);
    ui->mentalMax->setValue(items->items[index].dmg_ment_max);
    ui->rangMin->setValue(items->items[index].dmg_ranged_max);
    ui->rangMax->setValue(items->items[index].dmg_ranged_min);
    ui->power->setValue(items->items[index].power);

    for (unsigned int i = 0; i < items->items[index].req_stat.size(); i++)
    {
        int value = items->items[index].req_val[i];

        if (items->items[index].req_stat[i] == REQUIRES_PHYS)
            ui->reqPhys->setValue(value);

        else if (items->items[index].req_stat[i] == REQUIRES_MENT)
            ui->reqMent->setValue(value);

        else if (items->items[index].req_stat[i] == REQUIRES_OFF)
            ui->reqOff->setValue(value);

        else if (items->items[index].req_stat[i] == REQUIRES_DEF)
            ui->reqDef->setValue(value);
    }
}
