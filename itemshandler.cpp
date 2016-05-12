#include "itemshandler.h"

#include <QDir>
#include <QTextBlock>
#include <QLineEdit>
#include <QSpinBox>
#include <QMetaProperty>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "iconchooser.h"
#include "ui_iconchooser.h"

#include "elementslist.h"
#include "ui_elementslist.h"

#include "lootanimationwidget.h"
#include "ui_lootanimationwidget.h"

#include "controlframe.h"
#include "ui_controlframe.h"

#include "combobox.h"
#include "ui_combobox.h"

#include "stringlistwidget.h"
#include "ui_stringlistwidget.h"

#include "comboboxkeyvaluelist.h"
#include "ui_comboboxkeyvaluelist.h"

#include "lineedit.h"
#include "ui_lineedit.h"

#include "spinbox.h"
#include "ui_spinbox.h"

#include "twospinbox.h"
#include "ui_twospinbox.h"

#include "checkbox.h"
#include "ui_checkbox.h"

#include "twostringlists.h"
#include "ui_twostringlists.h"

#include "EditorItemManager.h"
#include "API/Stats.h"
#include "API/AnimationSet.h"
#include "API/Animation.h"

#include "doublespinbox.h"

#include "iconselector.h"
#include "lootanimationwidget.h"

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
    for (int i = 0; i<items->items.size(); i++)
    {
        if (items->items[i]->name != "")
        {
            QListWidgetItem* item = new QListWidgetItem(qString(items->items[i]->name));
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
        else if (QString(widget->metaObject()->className()) == "StringListWidget")
        {
            if (widget->accessibleName() == "equip_flags")
            {
                for (unsigned i = 0; i<items->EQUIP_FLAGS.size(); i++)
                {
                    dynamic_cast<StringListWidget*>(widget)->ui->selector->addItem(qString(items->EQUIP_FLAGS[i].id));
                }
                checkComboBoxForError(dynamic_cast<StringListWidget*>(widget)->ui->selector,
                    "engine/equip_flags.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (widget->accessibleName() == "disable_slots")
            {
                for (unsigned i = 0; i<items->slot_type.size(); i++)
                {
                    dynamic_cast<StringListWidget*>(widget)->ui->selector->addItem(qString(items->slot_type[i]));
                }
                checkComboBoxForError(dynamic_cast<StringListWidget*>(widget)->ui->selector,
                    "menus/inventory.txt is missing or incorrect. Copy it from base mod.");
            }
        }
        else if (QString(widget->metaObject()->className()) == "ComboBoxKeyValueList")
        {
            ComboBoxKeyValueList * listWidget = dynamic_cast<ComboBoxKeyValueList*>(widget);
            if (listWidget->accessibleName() == "bonus")
            {
                for (unsigned i = 0; i<items->ELEMENTS.size(); i++)
                {
                    listWidget->ui->list->addItem(qString(items->ELEMENTS[i].id) + "_resist");
                }

                listWidget->ui->list->addItem("speed");
                listWidget->ui->list->addItem("physical");
                listWidget->ui->list->addItem("mental");
                listWidget->ui->list->addItem("offense");
                listWidget->ui->list->addItem("defense");
                for (unsigned i = 0; i<STAT_COUNT; i++)
                {
                    listWidget->ui->list->addItem(qString(STAT_KEY[i]));
                }
                checkComboBoxForError(listWidget->ui->list,
                    "engine/elements.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (listWidget->accessibleName() == "requires_stat")
            {
                listWidget->ui->list->addItem("physical");
                listWidget->ui->list->addItem("mental");
                listWidget->ui->list->addItem("offense");
                listWidget->ui->list->addItem("defense");
            }
        }
    }

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
    items->items[index]->name = "newItem";

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
    int index = -1;
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        if (widget->accessibleName() == "elementslist")
        {
            index = dynamic_cast<ElementsList*>(widget)->ui->itemsList->currentItem()->data(Qt::UserRole).toInt();
            break;
        }
    }
    Item * item = items->items[index];

    const QMetaObject* metaObject = item->metaObject();
    for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
    {
        QString propertyName = QString::fromLatin1(metaObject->property(i).name());

        for (int i = 0; i < itemsLayout->count(); i++)
        {
            QWidget * widget = itemsLayout->itemAt(i)->widget();
            if (widget == NULL)
            {
                continue;
            }
            if (widget->accessibleName() == propertyName)
            {
                if (QString(widget->metaObject()->className()) == "LineEdit")
                {
                    item->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<LineEdit*>(widget)->ui->lineEdit->text());
                }
                else if (QString(widget->metaObject()->className()) == "SpinBox")
                {
                    item->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<SpinBox*>(widget)->ui->spinBox->value());
                }
                else if (QString(widget->metaObject()->className()) == "CheckBox")
                {
                    item->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<CheckBox*>(widget)->ui->checkBox->isChecked());
                }
                else if (QString(widget->metaObject()->className()) == "TwoStringLists")
                {
                    QTextDocument* from = dynamic_cast<TwoStringLists*>(widget)->ui->edit_1->document();
                    QTextDocument* to   = dynamic_cast<TwoStringLists*>(widget)->ui->edit_2->document();

                    QList<QVariant> values;
                    for (int i = 0; i < from->lineCount(); i++)
                    {
                        if (from->findBlockByLineNumber(i).text().isEmpty() || to->findBlockByLineNumber(i).text().isEmpty())
                            break;
                        QStringList list;
                        list << from->findBlockByLineNumber(i).text() << to->findBlockByLineNumber(i).text();
                        values.append(list);
                    }
                    item->setProperty(propertyName.toStdString().c_str(), values);
                }
                else if (QString(widget->metaObject()->className()) == "StringListWidget")
                {
                    QTextDocument* list = dynamic_cast<StringListWidget*>(widget)->ui->list->document();

                    QList<QVariant> values;
                    for (int i = 0; i < list->lineCount(); i++)
                    {
                        if (list->findBlockByLineNumber(i).text().isEmpty())
                            break;
                        values.append(list->findBlockByLineNumber(i).text());
                    }
                    item->setProperty(propertyName.toStdString().c_str(), values);
                }
                else if (QString(widget->metaObject()->className()) == "ComboBoxKeyValueList")
                {
                    QTextDocument* keysList = dynamic_cast<ComboBoxKeyValueList*>(widget)->ui->keys->document();
                    QTextDocument* valuesList = dynamic_cast<ComboBoxKeyValueList*>(widget)->ui->values->document();
                    //item->bonus.clear();

                    for (int i = 0; i < keysList->lineCount(); i++)
                    {
                        if (keysList->findBlockByLineNumber(i).text().isEmpty() || valuesList->findBlockByLineNumber(i).text().isEmpty())
                            continue;
                        /*
                        item->bonus.push_back(BonusData());

                        QString bonus_str = bonusName->findBlockByLineNumber(i).text();

                        if (bonus_str == "speed") {
                            item->bonus.back().is_speed = true;
                        }
                        else if (bonus_str == "physical") {
                            item->bonus.back().base_index = 0;
                        }
                        else if (bonus_str == "mental") {
                            item->bonus.back().base_index = 1;
                        }
                        else if (bonus_str == "offense") {
                            item->bonus.back().base_index = 2;
                        }
                        else if (bonus_str == "defense") {
                            item->bonus.back().base_index = 3;
                        }

                        for (unsigned k=0; k<items->ELEMENTS.size(); ++k) {
                            if (bonus_str == qString(items->ELEMENTS[k].id) + "_resist")
                            {
                                item->bonus.back().resist_index = k;
                                break;
                            }
                        }
                        for (unsigned k=0; k<STAT_COUNT; ++k) {
                            if (bonus_str == qString(STAT_KEY[k])) {
                                item->bonus.back().stat_index = (STAT)k;
                                break;
                            }
                        }

                        item->bonus.back().value = valuesList->findBlockByLineNumber(i).text().toInt();
                        */
                    }
                    /*
                    // requires stat
                    item->req_stat.clear();
                    item->req_val.clear();

                    if (ui->reqPhys->value() > 0)
                    {
                        item->req_stat.push_back(REQUIRES_PHYS);
                        item->req_val.push_back(ui->reqPhys->value());
                    }
                    if (ui->reqMent->value() > 0)
                    {
                        item->req_stat.push_back(REQUIRES_MENT);
                        item->req_val.push_back(ui->reqMent->value());
                    }
                    if (ui->reqOff->value() > 0)
                    {
                        item->req_stat.push_back(REQUIRES_OFF);
                        item->req_val.push_back(ui->reqOff->value());
                    }
                    if (ui->reqDef->value() > 0)
                    {
                        item->req_stat.push_back(REQUIRES_DEF);
                        item->req_val.push_back(ui->reqDef->value());
                    }
                    */
                }
/*
                // Loot
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
*/
                else if (QString(widget->metaObject()->className()) == "ComboBox")
                {
                    item->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<ComboBox*>(widget)->ui->comboBox->currentText());

                    //items->items[index].type  = stdString(ui->itemTypeCB->itemData(ui->itemTypeCB->currentIndex()).toString());
                    //items->items[index].sfx = std::string("soundfx/inventory/") + stdString(ui->sfxCb->currentText());
                }
                else if (QString(widget->metaObject()->className()) == "IconChooser")
                {
                    item->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<IconChooser*>(widget)->ui->iconsView->getActiveIcon());
                }
            }
            else if (widget->accessibleName() + "_min" == propertyName)
            {
                if (QString(widget->metaObject()->className()) == "TwoSpinBox")
                {
                    item->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<TwoSpinBox*>(widget)->ui->spinBox->value());
                }
            }
            else if (widget->accessibleName() + "_max" == propertyName)
            {
                if (QString(widget->metaObject()->className()) == "TwoSpinBox")
                {
                    item->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<TwoSpinBox*>(widget)->ui->spinBox_2->value());
                }
            }
        }
    }

    //Update ListBox
    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        if (widget->accessibleName() == "elementslist")
        {
            dynamic_cast<ElementsList*>(widget)->ui->itemsList->currentItem()->setData(Qt::DisplayRole, qString(item->name));
            break;
        }
    }
    setItemsAreEdited(true);
}

void ItemsHandler::selectItem(QListWidgetItem *_item)
{
    clearBtn();

    for (int i = 0; i < itemsLayout->count(); i++)
    {
        QWidget * widget = itemsLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "item_type")
        {
            dynamic_cast<ComboBox*>(widget)->setCurrentIndex(-1);
        }
        else if (widget && widget->accessibleName() == "controlframe")
        {
            dynamic_cast<ControlFrame*>(widget)->ui->pushBtn->setEnabled(true);
        }
    }

    int index = _item->data(Qt::UserRole).toInt();
    Item* item = items->items[index];

    const QMetaObject* metaObject = item->metaObject();
    for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
    {
        QString propertyName = QString::fromLatin1(metaObject->property(i).name());

        for (int i = 0; i < itemsLayout->count(); i++)
        {
            QWidget * widget = itemsLayout->itemAt(i)->widget();
            if (widget == NULL)
            {
                continue;
            }
            QString className = QString(widget->metaObject()->className());
            if (widget->accessibleName() == propertyName)
            {
                if (className == "LineEdit")
                {
                    dynamic_cast<LineEdit*>(widget)->ui->lineEdit->setText(item->property(propertyName.toStdString().c_str()).toString());
                }
                else if (className == "SpinBox")
                {
                    dynamic_cast<SpinBox*>(widget)->setValue(item->property(propertyName.toStdString().c_str()).toInt());
                }
                else if (className == "TwoSpinBox")
                {
                    if (propertyName.endsWith("_min"))
                    {
                        dynamic_cast<TwoSpinBox*>(widget)->setValue1(item->property(propertyName.toStdString().c_str()).toInt());
                    }
                    else if (propertyName.endsWith("_max"))
                    {
                        dynamic_cast<TwoSpinBox*>(widget)->setValue2(item->property(propertyName.toStdString().c_str()).toInt());
                    }
                }
                else if (className == "TwoStringLists")
                {
                    QList<QVariant> values = item->property(propertyName.toStdString().c_str()).toList();
                    QVector< QPair<QString,QString> > vector;
                    for(int i = 0; i < values.size(); i++)
                    {
                        vector.append(qMakePair(values[i].toStringList()[0], values[i].toStringList()[1]));
                    }
                    dynamic_cast<TwoStringLists*>(widget)->setValues(vector);
                }
                else if (className == "StringListWidget")
                {
                    QList<QVariant> values = item->property(propertyName.toStdString().c_str()).toList();
                    QVector<QString> vector;
                    for(int i = 0; i < values.size(); i++)
                    {
                        vector.append(values[i].toString());
                    }
                    dynamic_cast<StringListWidget*>(widget)->setValues(vector);
                }
                else if (className == "ComboBox")
                {
                    dynamic_cast<ComboBox*>(widget)->selectComboBoxItemByText(item->property(propertyName.toStdString().c_str()).toString());
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
        QString name = QString(widget->metaObject()->className());
        if (name == "ComboBox")
        {
            if (widget->accessibleName() == "item_type")
            {
                QString type = qString(item->type);
                int listSize = dynamic_cast<ComboBox*>(widget)->ui->comboBox->count();
                for (int i = 0; i < listSize; i++)
                {
                    if (dynamic_cast<ComboBox*>(widget)->ui->comboBox->itemData(i) == type)
                    {
                        dynamic_cast<ComboBox*>(widget)->ui->comboBox->setCurrentIndex(i);
                        break;
                    }
                }
            }
            else if (widget->accessibleName() == "soundfx")
            {
                QString soundfx = qString(item->sfx);
                dynamic_cast<ComboBox*>(widget)->selectComboBoxItemByText(QFileInfo(soundfx).fileName());
            }
        }
        else if (widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconsView->setActiveIcon(item->icon);
        }
        else if (widget->accessibleName() == "loot_animation")
        {
            LootAnimationWidget * lootAnim = dynamic_cast<LootAnimationWidget*>(widget);

            QVector<QAnimation> animations_v;
            for (int i = 0; i < item->loot_animation.size(); i++)
            {
                QAnimation anm;
                anm.name = qString(item->loot_animation[i].name);
                anm.low = item->loot_animation[i].low;
                anm.high = item->loot_animation[i].high;
                animations_v.append(anm);
            }
            lootAnim->setValues(animations_v);

            // load item animation if available
            if (lootAnim->ui->graphicsView->scene() != 0)
                lootAnim->ui->graphicsView->scene()->clear();
            if (item->loot_animation.size() > 0)
            {
                AnimationSet* animat = new AnimationSet(item->loot_animation[0].name);
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
        else if (widget->accessibleName() == "bonus")
        {
            ComboBoxKeyValueList * listWidget = dynamic_cast<ComboBoxKeyValueList*>(widget);
            listWidget->ui->keys->clear();
            listWidget->ui->values->clear();
            for (int i = 0; i < item->bonus.size(); i++)
            {
                int stat_index     = item->bonus[i].stat_index;
                int base_index     = item->bonus[i].base_index;
                int resist_index   = item->bonus[i].resist_index;
                bool is_speed      = item->bonus[i].is_speed;

                if (stat_index != -1)
                {
                    listWidget->ui->keys->appendPlainText(qString(STAT_KEY[stat_index]));
                }
                else if (resist_index != -1)
                {
                    listWidget->ui->keys->appendPlainText(qString(items->ELEMENTS[resist_index].id) + "_resist");
                }
                else if (is_speed)
                {
                    listWidget->ui->keys->appendPlainText(QString("speed"));
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

                    listWidget->ui->keys->appendPlainText(bonus_str);
                }
                listWidget->ui->values->appendPlainText(QString::number(item->bonus[i].value));
            }
        }
        else if (widget->accessibleName() == "requires_stat")
        {
            ComboBoxKeyValueList * listWidget = dynamic_cast<ComboBoxKeyValueList*>(widget);
            listWidget->ui->keys->clear();
            listWidget->ui->values->clear();
            for (int i = 0; i < item->req_stat.size(); i++)
            {
                int value = item->req_val[i];

                if (item->req_stat[i] == REQUIRES_PHYS)
                    listWidget->ui->keys->appendPlainText("physical");

                else if (item->req_stat[i] == REQUIRES_MENT)
                    listWidget->ui->keys->appendPlainText("mental");

                else if (item->req_stat[i] == REQUIRES_OFF)
                    listWidget->ui->keys->appendPlainText("offense");

                else if (item->req_stat[i] == REQUIRES_DEF)
                    listWidget->ui->keys->appendPlainText("defense");

                listWidget->ui->values->appendPlainText(QString::number(value));
            }
        }
    }
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
