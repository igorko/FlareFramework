#include "itemshandler.h"

#include <QDir>
#include <QTextBlock>
#include <QLineEdit>
#include <QSpinBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "iconchooser.h"
#include "ui_iconchooser.h"

#include "iconselector.h"

#include "elementslist.h"
#include "ui_elementslist.h"

#include "lootanimationwidget.h"
#include "ui_lootanimationwidget.h"

#include "controlframe.h"
#include "ui_controlframe.h"

#include "combobox.h"
#include "ui_combobox.h"

#include "EditorItemManager.h"
#include "API/Stats.h"
#include "API/AnimationSet.h"
#include "API/Animation.h"

#include "lineedit.h"
#include "spinbox.h"
#include "doublespinbox.h"
#include "checkbox.h"
#include "iconchooser.h"
#include "stringlistwidget.h"
#include "lootanimationwidget.h"
#include "twospinbox.h"
#include "twostringlists.h"

ItemsHandler::ItemsHandler(MainWindow * _mainWindow, QObject *parent) :
    QObject(parent),
    mainWindow(_mainWindow),
    itemsLayout(NULL),
    items(NULL),
    itemsEdited(false),
    editedStyle("background-color:#66FF99;"),
    invalidStyle("background-color:#FF3333;")
{
    QScrollArea * itemsTab = dynamic_cast<QScrollArea *>(mainWindow->ui->tabWidget->widget(mainWindow->predefinedNameTypeElements[ITEMS]));
    itemsLayout = dynamic_cast<QGridLayout *>(itemsTab->widget()->layout());
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconPasteLabel->hide();
            break;
        }
    }
    setupConnections();
}

ItemsHandler::~ItemsHandler()
{
    delete items;
}

void ItemsHandler::saveItems(const QString &path)
{
    QString filename = path + QDir::separator() + "items" + QDir::separator() + "items.txt";
    if (items != NULL) items->save(filename.toUtf8().constData());

    filename = path + QDir::separator() + "images" + QDir::separator() + "icons" + QDir::separator() + "icons.png";
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconsView->saveIcons(filename);
            break;
        }
    }

    setItemsAreEdited(false);
}

void ItemsHandler::loadItems(const std::string &path)
{
    items = new EditorItemManager(path);
    for (unsigned i = 0; i<items->items.size(); i++)
    {
        if (items->items[i].name != "")
        {
            QListWidgetItem* item = new QListWidgetItem(qString(items->items[i].name));
            item->setData(Qt::UserRole, i);
            for (int i = 0; i < itemsLayout->count(); i++)
            {
                QWidget * widget = itemsLayout->itemAt(i)->widget();

                if (widget && widget->accessibleName() == "elementslist")
                {
                    dynamic_cast<ElementsList*>(widget)->ui->itemsList->addItem(item);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget == NULL)
        {
            continue;
        }
        if (QString(widget->metaObject()->className()) == "ComboBox")
        {
            dynamic_cast<ComboBox*>(widget)->clear();
            dynamic_cast<ComboBox*>(widget)->addItem("");

            if (widget->accessibleName() == "item_type")
            {
                for (unsigned i = 0; i<items->item_types.size(); i++)
                {
                    dynamic_cast<ComboBox*>(widget)->ui->comboBox->addItem(qString(items->item_types[i].name), qString(items->item_types[i].id));
                }
                checkComboBoxForError(dynamic_cast<ComboBox*>(widget)->ui->comboBox,
                    "items/types.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (widget->accessibleName() == "quality")
            {
                for (unsigned i = 0; i<items->item_qualities.size(); i++)
                {
                    dynamic_cast<ComboBox*>(widget)->ui->comboBox->addItem(qString(items->item_qualities[i].id));
                }
                checkComboBoxForError(dynamic_cast<ComboBox*>(widget)->ui->comboBox,
                    "items/qualities.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (widget->accessibleName() == "stepfx")
            {
                for (unsigned int i = 0; i<items->step_def.size(); i++)
                {
                    dynamic_cast<ComboBox*>(widget)->ui->comboBox->addItem(qString(items->step_def[i].id));
                }
                checkComboBoxForError(dynamic_cast<ComboBox*>(widget)->ui->comboBox,
                    "items/step_sounds.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (widget->accessibleName() == "requires_class")
            {
                for (unsigned i = 0; i<items->HERO_CLASSES.size(); i++)
                {
                    dynamic_cast<ComboBox*>(widget)->ui->comboBox->addItem(qString(items->HERO_CLASSES[i].name));
                }
                checkComboBoxForError(dynamic_cast<ComboBox*>(widget)->ui->comboBox,
                    "engine/classes.txt is missing or incorrect. Copy it from base mod.");
            }
        }
    }
    /*
    for (unsigned i = 0; i<items->EQUIP_FLAGS.size(); i++)
    {
        ui->equipList->addItem(qString(items->EQUIP_FLAGS[i].id));
    }

    for (unsigned i = 0; i<items->slot_type.size(); i++)
    {
        ui->slotsList->addItem(qString(items->slot_type[i]));
    }

    for (unsigned i = 0; i<items->ELEMENTS.size(); i++)
    {
        ui->bonusList->addItem(qString(items->ELEMENTS[i].id) + "_resist");
    }

    ui->bonusList->addItem("speed");
    ui->bonusList->addItem("physical");
    ui->bonusList->addItem("mental");
    ui->bonusList->addItem("offense");
    ui->bonusList->addItem("defense");
    for (unsigned i = 0; i<STAT_COUNT; i++)
    {
        ui->bonusList->addItem(qString(STAT_KEY[i]));
    }

    checkComboBoxForError(ui->equipList, "engine/equip_flags.txt is missing or incorrect. Copy it from base mod.");
    checkComboBoxForError(ui->slotsList, "menus/inventory.txt is missing or incorrect. Copy it from base mod.");
    checkComboBoxForError(ui->bonusList, "engine/elements.txt is missing or incorrect. Copy it from base mod.");
    */

    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "controlframe")
        {
            dynamic_cast<ControlFrame*>(widget)->ui->pushBtn->setEnabled(false);
            break;
        }
    }

    collectFileLists(path);
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconsView->init(qString(path));
            break;
        }
    }

    clearBtn();
}

void ItemsHandler::clearItemsList()
{
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "elementslist")
        {
            dynamic_cast<ElementsList*>(widget)->ui->itemsList->clear();
            break;
        }
    }
    setItemsAreEdited(false);
    delete items;
    items = NULL;
}

bool ItemsHandler::itemsAreEdited()
{
    return itemsEdited;
}

void ItemsHandler::setItemsAreEdited(bool state)
{
    if (state)
        emit itemsWereEdited();
    else
        emit itemsNotEdited();
    itemsEdited = state;
}

void ItemsHandler::addNewItem()
{
	items->items.resize(items->items.size() + 1);
    int index = items->items.size() - 1;
    items->items[index].name = "newItem";

    QListWidgetItem* item = new QListWidgetItem("newItem");
    item->setData(Qt::UserRole, index);
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "elementslist")
        {
            dynamic_cast<ElementsList*>(widget)->ui->itemsList->addItem(item);
            break;
        }
    }
}

void ItemsHandler::clearBtn()
{
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        QString name = QString(widget->metaObject()->className());
        if (name == "ComboBox")
        {
            dynamic_cast<ComboBox*>(widget)->setCurrentIndex(0);
        }
        else if (name == "SpinBox")
        {
            dynamic_cast<SpinBox*>(widget)->setValue(0);
        }
        else if (name == "DoubleSpinBox")
        {
            dynamic_cast<DoubleSpinBox*>(widget)->setValue(0.0);
        }
        else if (name == "LineEdit")
        {
            dynamic_cast<LineEdit*>(widget)->clear();
        }
        else if (name == "StringListWidget")
        {
            dynamic_cast<StringListWidget*>(widget)->clear();
        }
        else if (name == "TwoSpinBox")
        {
            dynamic_cast<TwoSpinBox*>(widget)->setValue1(0);
            dynamic_cast<TwoSpinBox*>(widget)->setValue2(0);
        }
        else if (name == "TwoStringLists")
        {
            dynamic_cast<TwoStringLists*>(widget)->clear();
        }
        else if (name == "LootAnimationWidget")
        {
            dynamic_cast<LootAnimationWidget*>(widget)->clear();
        }
        else if (name == "IconChooser")
        {
            dynamic_cast<IconChooser*>(widget)->setActiveIcon(0);
        }
        else if (name == "CheckBox")
        {
            dynamic_cast<CheckBox*>(widget)->setChecked(false);
        }
    }
}

void ItemsHandler::pushBtn()
{
    /*
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
    */
    setItemsAreEdited(true);
}

void ItemsHandler::selectItem(QListWidgetItem *_item)
{
    clearBtn();

    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        //fixme crash
        /*if (widget && widget->accessibleName() == "item_type")
        {
            dynamic_cast<ComboBox*>(widget)->setCurrentIndex(-1);
        }
        else */if (widget && widget->accessibleName() == "controlframe")
        {
            dynamic_cast<ControlFrame*>(widget)->ui->pushBtn->setEnabled(true);
        }
    }

    int index = _item->data(Qt::UserRole).toInt();
    Item item = items->items[index];

    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        QString name = QString(widget->metaObject()->className());
        if (name == "LineEdit")
        {
            if (widget->accessibleName() == "name")
            {
                dynamic_cast<LineEdit*>(widget)->setText(qString(item.name));
            }
            else if (widget->accessibleName() == "pickup_status")
            {
                dynamic_cast<LineEdit*>(widget)->setText(qString(item.pickup_status));
            }
            else if (widget->accessibleName() == "power_desc")
            {
                dynamic_cast<LineEdit*>(widget)->setText(qString(item.power_desc));
            }
            else if (widget->accessibleName() == "flavor")
            {
                dynamic_cast<LineEdit*>(widget)->setText(qString(item.flavor));
            }
            else if (widget->accessibleName() == "book")
            {
                dynamic_cast<LineEdit*>(widget)->setText(qString(item.book));
            }
        }
        else if (name == "SpinBox")
        {
            if (widget->accessibleName() == "level")
            {
                dynamic_cast<SpinBox*>(widget)->setValue(item.level);
            }
            else if (widget->accessibleName() == "price")
            {
                dynamic_cast<SpinBox*>(widget)->setValue(item.price);
            }
            else if (widget->accessibleName() == "price_sell")
            {
                dynamic_cast<SpinBox*>(widget)->setValue(item.price_sell);
            }
            else if (widget->accessibleName() == "max_quantity")
            {
                dynamic_cast<SpinBox*>(widget)->setValue(item.max_quantity);
            }
            else if (widget->accessibleName() == "power")
            {
                dynamic_cast<SpinBox*>(widget)->setValue(item.power);
            }
        }
        else if (name == "TwoSpinBox")
        {
            if (widget->accessibleName() == "abs")
            {
                dynamic_cast<TwoSpinBox*>(widget)->setValue1(item.abs_min);
                dynamic_cast<TwoSpinBox*>(widget)->setValue2(item.abs_max);
            }
            else if (widget->accessibleName() == "dmg_melee")
            {
                dynamic_cast<TwoSpinBox*>(widget)->setValue1(item.dmg_melee_min);
                dynamic_cast<TwoSpinBox*>(widget)->setValue2(item.dmg_melee_max);
            }
            else if (widget->accessibleName() == "dmg_ment")
            {
                dynamic_cast<TwoSpinBox*>(widget)->setValue1(item.dmg_ment_min);
                dynamic_cast<TwoSpinBox*>(widget)->setValue2(item.dmg_ment_max);
            }
            else if (widget->accessibleName() == "dmg_ranged")
            {
                dynamic_cast<TwoSpinBox*>(widget)->setValue1(item.dmg_ranged_min);
                dynamic_cast<TwoSpinBox*>(widget)->setValue2(item.dmg_ranged_max);
            }
        }
        else if (widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconsView->setActiveIcon(item.icon);
        }
        else if (widget->accessibleName() == "loot_animation")
        {
            LootAnimationWidget * lootAnim = dynamic_cast<LootAnimationWidget*>(widget);

            QVector<QAnimation> animations_v;
            for (unsigned int i = 0; i < item.loot_animation.size(); i++)
            {
                QAnimation anm;
                anm.name = qString(item.loot_animation[i].name);
                anm.low = item.loot_animation[i].low;
                anm.high = item.loot_animation[i].high;
                animations_v.append(anm);
            }
            lootAnim->setValues(animations_v);

            // load item animation if available
            if (lootAnim->ui->graphicsView->scene() != 0)
                lootAnim->ui->graphicsView->scene()->clear();
            if (item.loot_animation.size() > 0)
            {
                AnimationSet* animat = new AnimationSet(items->items[index].loot_animation[0].name);
                int count = animat->getAnimationFrames("power");

                //QImage frame = *animat->sprite;

                //QGraphicsItem *sprite = new QGraphicsPixmapItem(QPixmap::fromImage(frame));

                //QTimeLine *timer = new QTimeLine(20000);
                //timer->setFrameRange(0, count);

                //QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
                //animation->setItem(sprite);
                //animation->setTimeLine(timer);

                QGraphicsScene* scene = new QGraphicsScene();
                lootAnim->ui->graphicsView->setScene(scene);

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
        else if (widget->accessibleName() == "replace_power")
        {
            QVector< QPair<QString, QString> > powers;
            for (unsigned int i = 0; i < item.replace_power.size(); i++)
            {
                powers.append(qMakePair(QString::number(item.replace_power[i].x),
                    QString::number(item.replace_power[i].y)));
            }
            dynamic_cast<TwoStringLists*>(widget)->setValues(powers);
        }
        else if (widget->accessibleName() == "disable_slots")
        {
            QVector<QString> values;
            for (unsigned int i = 0; i < item.disable_slots.size(); i++)
            {
                values.append(qString(item.disable_slots[i]));
            }
            dynamic_cast<StringListWidget*>(widget)->setValues(values);
        }
        else if (widget->accessibleName() == "equip_flags")
        {
            QVector<QString> values;
            for (unsigned int i = 0; i < item.equip_flags.size(); i++)
            {
                values.append(qString(item.equip_flags[i]));
            }
            dynamic_cast<StringListWidget*>(widget)->setValues(values);
        }
    }
    /*
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
    */
}

void ItemsHandler::collectFileLists(const std::string &path)
{
    QString modPath = qString(path);
    QStringList files;

    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        if (widget->accessibleName() == "soundfx")
        {
            QDir pathSfx(modPath + "soundfx" + QDir::separator() + "inventory");
            files = pathSfx.entryList(QDir::Files);
            dynamic_cast<ComboBox*>(widget)->addItems(files);

            checkComboBoxForError(dynamic_cast<ComboBox*>(widget),
                "soundfx/inventory folder is empty. Place some sound files in it.");
        }
        else if (widget->accessibleName() == "gfx")
        {
            QDir pathGfx(modPath + "animations" + QDir::separator() + "avatar" + QDir::separator() + "male");
            files = pathGfx.entryList(QDir::Files);
            for (int i = 0; i < files.size(); i++)
            {
                files[i].remove(files[i].size() - 4, 4);
            }
            dynamic_cast<ComboBox*>(widget)->addItems(files);
            checkComboBoxForError(dynamic_cast<ComboBox*>(widget),
                "animations/avatar/male folder is empty. Place some equip animation files in it.");

        }
        else if (widget->accessibleName() == "loot_animation")
        {
            QDir pathLootAnim(modPath + "animations" + QDir::separator() + "loot");
            files = pathLootAnim.entryList(QDir::Files);
            dynamic_cast<LootAnimationWidget*>(widget)->addItems(files);

            checkComboBoxForError(dynamic_cast<LootAnimationWidget*>(widget)->ui->lootAnimList,
                "animations/loot folder is empty. Place some loot animation files in it.");
        }
    }
}

QString ItemsHandler::qString(std::string value)
{
    return QString::fromUtf8(value.data(), value.size());
}

std::string ItemsHandler::stdString(QString value)
{
    return value.toUtf8().constData();
}

QObject *ItemsHandler::CloseButton()
{
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "controlframe")
        {
            return dynamic_cast<ControlFrame*>(widget)->ui->itemClose;
        }
    }

    return NULL;
}

void ItemsHandler::checkComboBoxForError(ComboBox *widget, const QString &errorText)
{
    if (widget->ui->comboBox->count() == 0)
    {
        widget->ui->comboBox->setStyleSheet(invalidStyle);
        widget->ui->comboBox->setToolTip(errorText);
    }
    else
    {
        widget->ui->comboBox->setStyleSheet("");
        widget->ui->comboBox->setToolTip("");
    }
}

void ItemsHandler::checkComboBoxForError(QComboBox *widget, const QString &errorText)
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

void ItemsHandler::selectComboBoxItemByText(QComboBox *widget, const QString &text)
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

void ItemsHandler::setupConnections()
{
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "controlframe")
        {
            ControlFrame * controlFrame = dynamic_cast<ControlFrame*>(widget);
            connect(controlFrame->ui->addNewItem, SIGNAL(clicked()), SLOT(addNewItem()));
            connect(controlFrame->ui->clearBtn, SIGNAL(clicked()), SLOT(clearBtn()));
            connect(controlFrame->ui->pushBtn, SIGNAL(clicked()), SLOT(pushBtn()));
        }
        else if (widget && widget->accessibleName() == "icon")
        {
            IconChooser * iconChooser = dynamic_cast<IconChooser*>(widget);
            connect(iconChooser->ui->assignIconBtn, SIGNAL(clicked()), SLOT(requestIconAdd()));
            connect(iconChooser->ui->iconsView, SIGNAL(iconPlaced()), SLOT(finishIconAdd()));
            connect(iconChooser->ui->iconsView, SIGNAL(iconSkipped()), SLOT(skipIconAdd()));
        }
        else if (widget && widget->accessibleName() == "elementslist")
        {
            ElementsList * elementsList = dynamic_cast<ElementsList*>(widget);
            connect(elementsList->ui->itemsList, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(selectItem(QListWidgetItem*)));
        }
    }
}

void ItemsHandler::finishIconAdd()
{
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconPasteLabel->hide();
            break;
        }
    }
    setItemsAreEdited(true);

}

void ItemsHandler::skipIconAdd()
{
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconPasteLabel->hide();
            break;
        }
    }
}

void ItemsHandler::requestIconAdd()
{
    IconSelector* dialog = new IconSelector();
    int ret = dialog->exec();
    if (ret == QDialog::Accepted)
    {
        QImage newIcon = dialog->getSelection();
        for (int i = 0; i < itemsLayout->count(); i++)
        {
            QWidget * widget = itemsLayout->itemAt(i)->widget();

            if (widget && widget->accessibleName() == "icon")
            {
                dynamic_cast<IconChooser*>(widget)->ui->iconPasteLabel->show();
                dynamic_cast<IconChooser*>(widget)->ui->iconsView->appendIcon(newIcon);
                break;
            }
        }
    }
}
