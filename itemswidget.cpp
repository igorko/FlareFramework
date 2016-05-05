#include "itemswidget.h"
#include "ui_itemswidget.h"

#include <QTextBlock>
#include <QMessageBox>
#include <QDir>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QGraphicsPixmapItem>

#include "EditorItemManager.h"
#include "API/Stats.h"
#include "API/AnimationSet.h"
#include "API/Animation.h"

#include "iconselector.h"

ItemsWidget::ItemsWidget(QScrollArea *parent) :
    QScrollArea(parent),
    ui(new Ui::ItemsWidget),
    items(NULL),
    itemsEdited(false),
    editedStyle("background-color:#66FF99;"),
    invalidStyle("background-color:#FF3333;")
{
    ui->setupUi(this);
    ui->iconPasteLabel->hide();
    setupConnections();
}

ItemsWidget::~ItemsWidget()
{
    delete items;
}

void ItemsWidget::saveItems(const QString &path)
{
    QString filename = path + QDir::separator() + "items" + QDir::separator() + "items.txt";
    if (items != NULL) items->save(filename.toUtf8().constData());

    filename = path + QDir::separator() + "images" + QDir::separator() + "icons" + QDir::separator() + "icons.png";
    ui->iconsView->saveIcons(filename);

    setItemsAreEdited(false);
}

void ItemsWidget::loadItems(const std::string &path)
{
    items = new EditorItemManager(path);
    for (unsigned i = 0; i<items->items.size(); i++)
    {
        if (items->items[i].name != "")
        {
            QListWidgetItem* item = new QListWidgetItem(qString(items->items[i].name));
            item->setData(Qt::UserRole, i);
            ui->itemsList->addItem(item);

        }
    }
    ui->itemTypeCB->clear();
    ui->itemTypeCB->addItem("");
    for (unsigned i = 0; i<items->item_types.size(); i++)
    {
        ui->itemTypeCB->addItem(qString(items->item_types[i].name), qString(items->item_types[i].id));
    }
    checkComboBoxForError(ui->itemTypeCB, "items/types.txt is missing or incorrect. Copy it from base mod.");

    ui->itemQualityCB->clear();
    ui->itemQualityCB->addItem("");
    for (unsigned i = 0; i<items->item_qualities.size(); i++)
    {
        ui->itemQualityCB->addItem(qString(items->item_qualities[i].id));
    }
    checkComboBoxForError(ui->itemTypeCB, "items/qualities.txt is missing or incorrect. Copy it from base mod.");

    ui->equipList->clear();
    for (unsigned i = 0; i<items->EQUIP_FLAGS.size(); i++)
    {
        ui->equipList->addItem(qString(items->EQUIP_FLAGS[i].id));
    }
    checkComboBoxForError(ui->equipList, "engine/equip_flags.txt is missing or incorrect. Copy it from base mod.");

    ui->slotsList->clear();
    for (unsigned i = 0; i<items->slot_type.size(); i++)
    {
        ui->slotsList->addItem(qString(items->slot_type[i]));
    }
    checkComboBoxForError(ui->slotsList, "menus/inventory.txt is missing or incorrect. Copy it from base mod.");

    ui->bonusList->clear();
    for (unsigned i = 0; i<items->ELEMENTS.size(); i++)
    {
        ui->bonusList->addItem(qString(items->ELEMENTS[i].id) + "_resist");
    }
    checkComboBoxForError(ui->bonusList, "engine/elements.txt is missing or incorrect. Copy it from base mod.");

    ui->bonusList->addItem("speed");
    ui->bonusList->addItem("physical");
    ui->bonusList->addItem("mental");
    ui->bonusList->addItem("offense");
    ui->bonusList->addItem("defense");
    for (unsigned i = 0; i<STAT_COUNT; i++)
    {
        ui->bonusList->addItem(qString(STAT_KEY[i]));
    }

    ui->stepSoundList->clear();
    ui->stepSoundList->addItem("");
    for (unsigned int i = 0; i<items->step_def.size(); i++)
    {
        ui->stepSoundList->addItem(qString(items->step_def[i].id));
    }
    checkComboBoxForError(ui->stepSoundList, "items/step_sounds.txt is missing or incorrect. Copy it from base mod.");

    ui->classList->clear();
    ui->classList->addItem("");
    for (unsigned i = 0; i<items->HERO_CLASSES.size(); i++)
    {
        ui->classList->addItem(qString(items->HERO_CLASSES[i].name));
    }
    ui->pushBtn->setEnabled(false);

    collectFileLists(path);
    ui->iconsView->init(qString(path));

    clearBtn();
}

void ItemsWidget::clearItemsList()
{
    ui->itemsList->clear();
    setItemsAreEdited(false);
    delete items;
    items = NULL;
}

bool ItemsWidget::itemsAreEdited()
{
    return itemsEdited;
}

void ItemsWidget::setItemsAreEdited(bool state)
{
    if (state)
        emit itemsWereEdited();
    else
        emit itemsNotEdited();
    itemsEdited = state;
}

void ItemsWidget::addNewItem()
{
	items->items.resize(items->items.size() + 1);
    int index = items->items.size() - 1;
    items->items[index].name = "newItem";

    QListWidgetItem* item = new QListWidgetItem("newItem");
    item->setData(Qt::UserRole, index);
    ui->itemsList->addItem(item);
}

void ItemsWidget::clearBtn()
{
    ui->itemName->clear();
	ui->itemName->setText("ItemName");
    ui->itemFlavor->clear();
    ui->itemBook->clear();
	ui->pickupStatus->clear();
	ui->powerDesc->clear();
    ui->replacePowerFrom->clear();
    ui->replacePowerTo->clear();
    ui->disableSlots->clear();
    ui->equipFlags->clear();
    ui->bonusName->clear();
    ui->bonusValue->clear();

    // comboBoxes
    ui->itemQualityCB->setCurrentIndex(0);
    ui->itemTypeCB->setCurrentIndex(0);
    ui->classList->setCurrentIndex(0);

    ui->sfxCb->setCurrentIndex(0);
    ui->lootAnimList->setCurrentIndex(0);
    ui->stepSoundList->setCurrentIndex(0);
    ui->equipAnimList->setCurrentIndex(0);

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

    ui->iconsView->setActiveIcon(0);
}

void ItemsWidget::pushBtn()
{
    int index = ui->itemsList->currentItem()->data(Qt::UserRole).toInt();

    // TextEdits
    items->items[index].name = stdString(ui->itemName->text());
    items->items[index].flavor = stdString(ui->itemFlavor->text());
    items->items[index].pickup_status = stdString(ui->pickupStatus->text());
    items->items[index].power_desc = stdString(ui->powerDesc->text());
    items->items[index].book = stdString(ui->itemBook->text());

    QTextDocument* docFrom = ui->replacePowerFrom->document();
    QTextDocument* docTo   = ui->replacePowerTo->document();
    items->items[index].replace_power.clear();

    for (int i = 0; i < docFrom->lineCount(); i++)
    {
        if (docFrom->findBlockByLineNumber(i).text().isEmpty() || docTo->findBlockByLineNumber(i).text().isEmpty())
            continue;
        items->items[index].replace_power.push_back(Point(
                                                        docFrom->findBlockByLineNumber(i).text().toInt(),
                                                        docTo->findBlockByLineNumber(i).text().toInt()));
    }

    QTextDocument* disabledSlots = ui->disableSlots->document();
    items->items[index].disable_slots.clear();

    for (int i = 0; i < disabledSlots->lineCount(); i++)
    {
        if (disabledSlots->findBlockByLineNumber(i).text().isEmpty())
            continue;
        items->items[index].disable_slots.push_back(stdString(disabledSlots->findBlockByLineNumber(i).text()));
    }

    QTextDocument* equipFlags = ui->equipFlags->document();
    items->items[index].equip_flags.clear();

    for (int i = 0; i < equipFlags->lineCount(); i++)
    {
        if (equipFlags->findBlockByLineNumber(i).text().isEmpty())
            continue;
        items->items[index].equip_flags.push_back(stdString(equipFlags->findBlockByLineNumber(i).text()));
    }

    QTextDocument* loot = ui->animations->document();
    QTextDocument* lootMin = ui->animationMin->document();
    QTextDocument* lootmax = ui->animationMax->document();
    items->items[index].loot_animation.clear();

    for (int i = 0; i < loot->lineCount(); i++)
    {
        if (loot->findBlockByLineNumber(i).text().isEmpty())
            continue;
        items->items[index].loot_animation.push_back(LootAnimation());

        items->items[index].loot_animation.back().name = stdString(loot->findBlockByLineNumber(i).text());
        items->items[index].loot_animation.back().low  = lootMin->findBlockByLineNumber(i).text().toInt();
        items->items[index].loot_animation.back().high = lootmax->findBlockByLineNumber(i).text().toInt();
    }

    QTextDocument* bonusName    = ui->bonusName->document();
    QTextDocument* bonusValue   = ui->bonusValue->document();
    items->items[index].bonus.clear();

    for (int i = 0; i < bonusName->lineCount(); i++)
    {
        if (bonusName->findBlockByLineNumber(i).text().isEmpty() || bonusValue->findBlockByLineNumber(i).text().isEmpty())
            continue;
        items->items[index].bonus.push_back(BonusData());

        QString bonus_str = bonusName->findBlockByLineNumber(i).text();

        if (bonus_str == "speed") {
            items->items[index].bonus.back().is_speed = true;
        }
        else if (bonus_str == "physical") {
            items->items[index].bonus.back().base_index = 0;
        }
        else if (bonus_str == "mental") {
            items->items[index].bonus.back().base_index = 1;
        }
        else if (bonus_str == "offense") {
            items->items[index].bonus.back().base_index = 2;
        }
        else if (bonus_str == "defense") {
            items->items[index].bonus.back().base_index = 3;
        }

        for (unsigned k=0; k<items->ELEMENTS.size(); ++k) {
            if (bonus_str == qString(items->ELEMENTS[k].id) + "_resist")
            {
                items->items[index].bonus.back().resist_index = k;
                break;
            }
        }
        for (unsigned k=0; k<STAT_COUNT; ++k) {
            if (bonus_str == qString(STAT_KEY[k])) {
                items->items[index].bonus.back().stat_index = (STAT)k;
                break;
            }
        }

        items->items[index].bonus.back().value = bonusValue->findBlockByLineNumber(i).text().toInt();
    }

    // comboBoxes
    items->items[index].type     = stdString(ui->itemTypeCB->itemData(ui->itemTypeCB->currentIndex()).toString());
    items->items[index].quality  = stdString(ui->itemQualityCB->currentText());
    items->items[index].requires_class = stdString(ui->classList->currentText());

    items->items[index].sfx    = std::string("soundfx/inventory/") + stdString(ui->sfxCb->currentText());
    items->items[index].gfx    = stdString(ui->equipAnimList->currentText());
    items->items[index].stepfx = stdString(ui->stepSoundList->currentText());

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

    if (ui->reqPhys->value() > 0)
    {
        items->items[index].req_stat.push_back(REQUIRES_PHYS);
        items->items[index].req_val.push_back(ui->reqPhys->value());
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

    items->items[index].icon = ui->iconsView->getActiveIcon();

    //Update ListBox
    ui->itemsList->currentItem()->setData(Qt::DisplayRole, ui->itemName->text());

    setItemsAreEdited(true);
}

void ItemsWidget::itemsList(QListWidgetItem *item)
{
    ui->pushBtn->setEnabled(true);
    int index = item->data(Qt::UserRole).toInt();

    // TextEdits
    ui->itemName->setText(qString(items->items[index].name));
    ui->pickupStatus->setText(qString(items->items[index].pickup_status));
    ui->powerDesc->setText(qString(items->items[index].power_desc));
    ui->itemFlavor->setText(qString(items->items[index].flavor));
    ui->itemBook->setText(qString(items->items[index].book));

    ui->replacePowerFrom->clear();
    ui->replacePowerTo->clear();
    for (unsigned int i = 0; i < items->items[index].replace_power.size(); i++)
    {
        ui->replacePowerFrom->appendPlainText(QString::number(items->items[index].replace_power[i].x));
        ui->replacePowerTo->appendPlainText(QString::number(items->items[index].replace_power[i].y));
    }

    ui->animations->clear();
    ui->animationMin->clear();
    ui->animationMax->clear();
    for (unsigned int i = 0; i < items->items[index].loot_animation.size(); i++)
    {
        ui->animations->appendPlainText(qString(items->items[index].loot_animation[i].name));
        ui->animationMin->appendPlainText(QString::number(items->items[index].loot_animation[i].low));
        ui->animationMax->appendPlainText(QString::number(items->items[index].loot_animation[i].high));
    }

    ui->disableSlots->clear();
    for (unsigned int i = 0; i < items->items[index].disable_slots.size(); i++)
    {
        ui->disableSlots->appendPlainText(qString(items->items[index].disable_slots[i]));
    }

    ui->equipFlags->clear();
    for (unsigned int i = 0; i < items->items[index].equip_flags.size(); i++)
    {
        ui->equipFlags->appendPlainText(qString(items->items[index].equip_flags[i]));
    }

    ui->bonusName->clear();
    ui->bonusValue->clear();
    for (unsigned int i = 0; i < items->items[index].bonus.size(); i++)
    {
        int stat_index     = items->items[index].bonus[i].stat_index;
        int base_index     = items->items[index].bonus[i].base_index;
        int resist_index   = items->items[index].bonus[i].resist_index;
        bool is_speed      = items->items[index].bonus[i].is_speed;

        if (stat_index != -1)
        {
            ui->bonusName->appendPlainText(qString(STAT_KEY[stat_index]));
        }
        else if (resist_index != -1)
        {
            ui->bonusName->appendPlainText(qString(items->ELEMENTS[resist_index].id) + "_resist");
        }
        else if (is_speed)
        {
            ui->bonusName->appendPlainText(QString("speed"));
        }
        else if (base_index != -1)
        {
            QString bonus_str;
            if (base_index == 0)
                bonus_str = "physical";
            else if (base_index == 1)
               bonus_str = "mental";
            else if (base_index == 2)
                bonus_str = "offense";
            else if (base_index == 3)
                bonus_str = "defense";

            ui->bonusName->appendPlainText(bonus_str);
        }
        ui->bonusValue->appendPlainText(QString::number(items->items[index].bonus[i].value));
    }

    // comboBoxes
    QString type = qString(items->items[index].type);
    ui->itemTypeCB->setCurrentIndex(-1);
    for (int i = 0; i < ui->itemTypeCB->count(); i++)
    {
        if (ui->itemTypeCB->itemData(i) == type)
        {
            ui->itemTypeCB->setCurrentIndex(i);
            break;
        }
    }
    QString quality = qString(items->items[index].quality);
    selectComboBoxItemByText(ui->itemQualityCB, quality);

    type = qString(items->items[index].requires_class);
    selectComboBoxItemByText(ui->classList, type);

    QString soundfx = qString(items->items[index].sfx);
    selectComboBoxItemByText(ui->sfxCb, QFileInfo(soundfx).fileName());

    QString stepfx = qString(items->items[index].stepfx);
    selectComboBoxItemByText(ui->stepSoundList, stepfx);

    QString gfx = qString(items->items[index].gfx);
    selectComboBoxItemByText(ui->equipAnimList, gfx);

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

    ui->reqPhys->setValue(0);
    ui->reqMent->setValue(0);
    ui->reqOff->setValue(0);
    ui->reqDef->setValue(0);
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

    ui->iconsView->setActiveIcon(items->items[index].icon);

    // load item animation if available
    if (ui->graphicsView->scene() != 0)
        ui->graphicsView->scene()->clear();
    if (items->items[index].loot_animation.size() > 0)
    {
        AnimationSet* animat = new AnimationSet(items->items[index].loot_animation[0].name);
        int count = animat->getAnimationFrames("power");
        /*
        QImage frame = *animat->sprite;

        QGraphicsItem *sprite = new QGraphicsPixmapItem(QPixmap::fromImage(frame));

        QTimeLine *timer = new QTimeLine(20000);
        timer->setFrameRange(0, count);

        QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
        animation->setItem(sprite);
        animation->setTimeLine(timer);
        */

        QGraphicsScene* scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);

        for (int i = 0; i < count; ++i)
        {
            QImage frame = animat->getAnimation("power")->getCurrentFrame(i);
            //QPointF pos = animat->getAnimation("power")->getFramePos(i);
            //animation->setPosAt(i / (float)count, pos);
            scene->addPixmap(QPixmap::fromImage(frame));
        }

        //QGraphicsScene* scene = new QGraphicsScene();
        //ui->graphicsView->setScene(scene);

        //timer->start();
    }

}

void ItemsWidget::absorbMin(int arg1)
{
    markNotDefaultSpinBox(ui->absorbMin, arg1, 0);
}

void ItemsWidget::absorbMax(int arg1)
{
    markNotDefaultSpinBox(ui->absorbMax, arg1, 0);
}

void ItemsWidget::power(int arg1)
{
    markNotDefaultSpinBox(ui->power, arg1, 0);
}

void ItemsWidget::itemFlavor(const QString &arg1)
{
    markNotEmptyLineEdit(ui->itemFlavor, arg1);
}

void ItemsWidget::itemBook(const QString &arg1)
{
    markNotEmptyLineEdit(ui->itemBook, arg1);
}

void ItemsWidget::meleeMin(int arg1)
{
    markNotDefaultSpinBox(ui->meleeMin, arg1, 0);
}

void ItemsWidget::meleeMax(int arg1)
{
    markNotDefaultSpinBox(ui->meleeMax, arg1, 0);
}

void ItemsWidget::rangMin(int arg1)
{
    markNotDefaultSpinBox(ui->rangMin, arg1, 0);
}

void ItemsWidget::rangMax(int arg1)
{
    markNotDefaultSpinBox(ui->rangMax, arg1, 0);
}

void ItemsWidget::mentalMin(int arg1)
{
    markNotDefaultSpinBox(ui->mentalMin, arg1, 0);
}

void ItemsWidget::mentalMax(int arg1)
{
    markNotDefaultSpinBox(ui->mentalMax, arg1, 0);
}

void ItemsWidget::replacePowerFrom()
{
    markNotEmptyPlainTextEdit(ui->replacePowerFrom);
}

void ItemsWidget::replacePowerTo()
{
    markNotEmptyPlainTextEdit(ui->replacePowerTo);
}

void ItemsWidget::disableSlots()
{
    markNotEmptyPlainTextEdit(ui->disableSlots);
}

void ItemsWidget::reqPhys(int arg1)
{
    markNotDefaultSpinBox(ui->reqPhys, arg1, 0);
}

void ItemsWidget::reqMent(int arg1)
{
    markNotDefaultSpinBox(ui->reqMent, arg1, 0);
}

void ItemsWidget::reqOff(int arg1)
{
    markNotDefaultSpinBox(ui->reqOff, arg1, 0);
}

void ItemsWidget::reqDef(int arg1)
{
    markNotDefaultSpinBox(ui->reqDef, arg1, 0);
}

void ItemsWidget::price(int arg1)
{
    markNotDefaultSpinBox(ui->price, arg1, 0);
}

void ItemsWidget::sellPrice(int arg1)
{
    markNotDefaultSpinBox(ui->sellPrice, arg1, 0);
}

void ItemsWidget::maxQuantity(int arg1)
{
    markNotDefaultSpinBox(ui->maxQuantity, arg1, 1);
}

void ItemsWidget::pickupStatus(const QString &arg1)
{
    markNotEmptyLineEdit(ui->pickupStatus, arg1);
}

void ItemsWidget::powerDesc(const QString &arg1)
{
    markNotEmptyLineEdit(ui->powerDesc, arg1);
}

void ItemsWidget::itemName(const QString &arg1)
{
    if (arg1 != "")
    {
        ui->itemName->setStyleSheet("");
        ui->itemName->setToolTip("");
    }
    else
    {
        ui->itemName->setStyleSheet(invalidStyle);
        ui->itemName->setToolTip("Item name should be not empty");
    }
}

void ItemsWidget::equipFlags()
{
    markNotEmptyPlainTextEdit(ui->equipFlags);
}

void ItemsWidget::bonusName()
{
    markNotEmptyPlainTextEdit(ui->bonusName);
}

void ItemsWidget::bonusValue()
{
    markNotEmptyPlainTextEdit(ui->bonusValue);
}

void ItemsWidget::addDisableSlot()
{
    ui->disableSlots->appendPlainText(ui->slotsList->currentText());
}

void ItemsWidget::addEquipFlag()
{
    ui->equipFlags->appendPlainText(ui->equipList->currentText());
}

void ItemsWidget::addBonus()
{
    ui->bonusName->appendPlainText(ui->bonusList->currentText());
}

void ItemsWidget::collectFileLists(const std::string &path)
{
    ui->sfxCb->clear();
    ui->sfxCb->addItem("");

    ui->lootAnimList->clear();

    ui->equipAnimList->clear();
    ui->equipAnimList->addItem("");

    QString modPath = qString(path);
    QDir pathSfx(modPath + "soundfx" + QDir::separator() + "inventory");
    QStringList files = pathSfx.entryList(QDir::Files);
    ui->sfxCb->addItems(files);
    checkComboBoxForError(ui->sfxCb, "soundfx/inventory folder is empty. Place some sound files in it.");

    QDir pathLootAnim(modPath + "animations" + QDir::separator() + "loot");
    files = pathLootAnim.entryList(QDir::Files);
    ui->lootAnimList->addItems(files);
    checkComboBoxForError(ui->lootAnimList, "animations/loot folder is empty. Place some loot animation files in it.");

    QDir pathGfx(modPath + "animations" + QDir::separator() + "avatar" + QDir::separator() + "male");
    files = pathGfx.entryList(QDir::Files);
    for (int i = 0; i < files.size(); i++)
    {
        files[i].remove(files[i].size() - 4, 4);
    }
    ui->equipAnimList->addItems(files);
    checkComboBoxForError(ui->equipAnimList, "animations/avatar/male folder is empty. Place some equip animation files in it.");
}

QString ItemsWidget::qString(std::string value)
{

    return QString::fromUtf8(value.data(), value.size());
}

std::string ItemsWidget::stdString(QString value)
{
    return value.toUtf8().constData();
}

void ItemsWidget::checkComboBoxForError(QComboBox *widget, const QString &errorText)
{
    if (widget->count() == 0)
    {
        widget->setStyleSheet(invalidStyle);
        widget->setToolTip(errorText);
    }
    else
    {
        widget->setStyleSheet("");
        widget->setToolTip("");
    }
}

void ItemsWidget::markNotEmptyLineEdit(QLineEdit *widget, const QString& text)
{
    if (text != "")
    {
        widget->setStyleSheet(editedStyle);
    }
    else
    {
        widget->setStyleSheet("");
    }
}

void ItemsWidget::markNotEmptyPlainTextEdit(QPlainTextEdit *widget)
{
    QTextDocument* doc = widget->document();

    if (doc->lineCount() >= 1 && !doc->findBlockByLineNumber(0).text().isEmpty())
    {
        widget->setStyleSheet(editedStyle);
    }
    else
    {
        widget->setStyleSheet("");
    }
}

void ItemsWidget::selectComboBoxItemByText(QComboBox *widget, const QString &text)
{
    widget->setCurrentIndex(-1);
    for (int i = 0; i < widget->count(); i++)
    {
        if (widget->itemText(i) == text)
        {
            widget->setCurrentIndex(i);
            break;
        }
    }
}

void ItemsWidget::setupConnections()
{
    connect(ui->addNewItem, SIGNAL(clicked()), SLOT(addNewItem()));

    connect(ui->clearBtn, SIGNAL(clicked()), SLOT(clearBtn()));

    connect(ui->pushBtn, SIGNAL(clicked()), SLOT(pushBtn()));

    connect(ui->itemsList, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(itemsList(QListWidgetItem*)));

    connect(ui->absorbMin, SIGNAL(valueChanged(int)), SLOT(absorbMin(int)));

    connect(ui->absorbMax, SIGNAL(valueChanged(int)), SLOT(absorbMax(int)));

    connect(ui->power, SIGNAL(valueChanged(int)), SLOT(power(int)));

    connect(ui->itemFlavor, SIGNAL(textChanged(const QString&)), SLOT(itemFlavor(const QString&)));

    connect(ui->itemBook, SIGNAL(textChanged(const QString&)), SLOT(itemBook(const QString&)));

    connect(ui->meleeMin, SIGNAL(valueChanged(int)), SLOT(meleeMin(int)));

    connect(ui->meleeMax, SIGNAL(valueChanged(int)), SLOT(meleeMax(int)));

    connect(ui->rangMin, SIGNAL(valueChanged(int)), SLOT(rangMin(int)));

    connect(ui->rangMax, SIGNAL(valueChanged(int)), SLOT(rangMax(int)));

    connect(ui->mentalMin, SIGNAL(valueChanged(int)), SLOT(mentalMin(int)));

    connect(ui->mentalMax, SIGNAL(valueChanged(int)), SLOT(mentalMax(int)));

    connect(ui->replacePowerFrom, SIGNAL(textChanged()), SLOT(replacePowerFrom()));

    connect(ui->replacePowerTo, SIGNAL(textChanged()), SLOT(replacePowerTo()));

    connect(ui->disableSlots, SIGNAL(textChanged()), SLOT(disableSlots()));

    connect(ui->reqPhys, SIGNAL(valueChanged(int)), SLOT(reqPhys(int)));

    connect(ui->reqMent, SIGNAL(valueChanged(int)), SLOT(reqMent(int)));

    connect(ui->reqOff, SIGNAL(valueChanged(int)), SLOT(reqOff(int)));

    connect(ui->reqDef, SIGNAL(valueChanged(int)), SLOT(reqDef(int)));

    connect(ui->price, SIGNAL(valueChanged(int)), SLOT(price(int)));

    connect(ui->sellPrice, SIGNAL(valueChanged(int)), SLOT(sellPrice(int)));

    connect(ui->maxQuantity, SIGNAL(valueChanged(int)), SLOT(maxQuantity(int)));

    connect(ui->pickupStatus, SIGNAL(textChanged(const QString&)), SLOT(pickupStatus(const QString&)));

    connect(ui->powerDesc, SIGNAL(textChanged(const QString&)), SLOT(powerDesc(const QString&)));

    connect(ui->itemName, SIGNAL(textChanged(const QString&)), SLOT(itemName(const QString&)));

    connect(ui->equipFlags, SIGNAL(textChanged()), SLOT(equipFlags()));

    connect(ui->bonusName, SIGNAL(textChanged()), SLOT(bonusName()));

    connect(ui->bonusValue, SIGNAL(textChanged()), SLOT(bonusValue()));

    connect(ui->addDisableSlot, SIGNAL(clicked()), SLOT(addDisableSlot()));

    connect(ui->addEquipFlag, SIGNAL(clicked()), SLOT(addEquipFlag()));

    connect(ui->addBonus, SIGNAL(clicked()), SLOT(addBonus()));

    connect(ui->lootAnimAdd, SIGNAL(clicked()), SLOT(lootAnimAdd()));

    connect(ui->animations, SIGNAL(textChanged()), SLOT(animations()));

    connect(ui->animationMin, SIGNAL(textChanged()), SLOT(animationMin()));

    connect(ui->animationMax, SIGNAL(textChanged()), SLOT(animationMax()));

    connect(ui->assignIconBtn, SIGNAL(clicked()), SLOT(requestIconAdd()));

    connect(ui->iconsView, SIGNAL(iconPlaced()), SLOT(finishIconAdd()));
    connect(ui->iconsView, SIGNAL(iconSkipped()), SLOT(skipIconAdd()));
}

void ItemsWidget::finishIconAdd()
{
    ui->iconPasteLabel->hide();
    setItemsAreEdited(true);

}

void ItemsWidget::skipIconAdd()
{
    ui->iconPasteLabel->hide();

}

void ItemsWidget::requestIconAdd()
{
    IconSelector* dialog = new IconSelector();
    int ret = dialog->exec();
    if (ret == QDialog::Accepted)
    {
        QImage newIcon = dialog->getSelection();
        ui->iconPasteLabel->show();
        ui->iconsView->appendIcon(newIcon);
    }
}

void ItemsWidget::markNotDefaultSpinBox(QSpinBox *widget, int value, int defaultValue)
{
    if (value != defaultValue)
    {
        widget->setStyleSheet(editedStyle);
    }
    else
    {
        widget->setStyleSheet("");
    }
}

void ItemsWidget::lootAnimAdd()
{
    ui->animations->appendPlainText(ui->lootAnimList->currentText());
}

void ItemsWidget::animations()
{
    markNotEmptyPlainTextEdit(ui->animations);
}

void ItemsWidget::animationMin()
{
    markNotEmptyPlainTextEdit(ui->animationMin);
}

void ItemsWidget::animationMax()
{
    markNotEmptyPlainTextEdit(ui->animationMax);
}
