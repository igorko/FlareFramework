#include "itemshandler.h"

#include <QDir>
#include <QTextBlock>
#include <QLineEdit>
#include <QSpinBox>
#include <QMetaProperty>
#include <QScrollArea>
#include <QListWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "checkbox.h"
#include "combobox.h"
#include "comboboxkeyvaluelist.h"
#include "doublespinbox.h"
#include "lineedit.h"
#include "spinbox.h"
#include "stringlistwidget.h"
#include "twospinbox.h"
#include "twostringlists.h"

#include "EditorItemManager.h"
#include "API/AnimationSet.h"
#include "API/Animation.h"

#include "controlframe.h"
#include "ui_controlframe.h"

#include "elementslist.h"
#include "ui_elementslist.h"

#include "iconchooser.h"
#include "ui_iconchooser.h"

#include "iconselector.h"
#include "lootanimationwidget.h"

#include "lootanimationwidget.h"
#include "ui_lootanimationwidget.h"

ItemsHandler::ItemsHandler(MainWindow * _mainWindow, int tabIndex, QObject *parent) :
    EntityHandler(_mainWindow, parent),
    items(NULL)
{
    QScrollArea * itemsTab = dynamic_cast<QScrollArea *>(mainWindow->ui->tabWidget->widget(tabIndex));
    entityLayout = dynamic_cast<QGridLayout *>(itemsTab->widget()->layout());
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

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

void ItemsHandler::saveEntityList(const QString &itemsFilePath)
{
    if (items != NULL) items->save(itemsFilePath.toUtf8().constData());

    QString entityPath = "items/items.txt";
    QString iconsFilePath = itemsFilePath.left(itemsFilePath.size() - entityPath.size())
            + "images" + QDir::separator() + "icons" + QDir::separator() + "icons.png";
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconsView->saveIcons(iconsFilePath);
            break;
        }
    }

    setEntityEdited(false);
}

void ItemsHandler::loadEntityList(const std::string &path)
{
    items = new EditorItemManager(path, mainWindow->getClassTypes("Stats"));
    for (int i = 0; i<items->items.size(); i++)
    {
        if (items->items[i]->name != "")
        {
            QListWidgetItem* item = new QListWidgetItem(qString(items->items[i]->name));
            item->setData(Qt::UserRole, i);
            for (int i = 0; i < entityLayout->count(); i++)
            {
                QWidget * widget = entityLayout->itemAt(i)->widget();

                if (widget && widget->accessibleName() == "elementslist")
                {
                    dynamic_cast<ElementsList*>(widget)->ui->itemsList->addItem(item);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

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
                    dynamic_cast<ComboBox*>(widget)->addItem(qString(items->item_types[i].name), qString(items->item_types[i].id));
                }
                checkComboBoxForError(dynamic_cast<ComboBox*>(widget),
                    "items/types.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (widget->accessibleName() == "quality")
            {
                for (unsigned i = 0; i<items->item_qualities.size(); i++)
                {
                    dynamic_cast<ComboBox*>(widget)->addItem(qString(items->item_qualities[i].id));
                }
                checkComboBoxForError(dynamic_cast<ComboBox*>(widget),
                    "items/qualities.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (widget->accessibleName() == "stepfx")
            {
                for (unsigned int i = 0; i<items->step_def.size(); i++)
                {
                    dynamic_cast<ComboBox*>(widget)->addItem(qString(items->step_def[i].id));
                }
                checkComboBoxForError(dynamic_cast<ComboBox*>(widget),
                    "items/step_sounds.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (widget->accessibleName() == "requires_class")
            {
                for (unsigned i = 0; i<items->HERO_CLASSES.size(); i++)
                {
                    dynamic_cast<ComboBox*>(widget)->addItem(qString(items->HERO_CLASSES[i].name));
                }
                checkComboBoxForError(dynamic_cast<ComboBox*>(widget),
                    "engine/classes.txt is missing or incorrect. Copy it from base mod.");
            }
        }
        else if (QString(widget->metaObject()->className()) == "StringListWidget")
        {
            if (widget->accessibleName() == "equip_flags")
            {
                for (unsigned i = 0; i<items->EQUIP_FLAGS.size(); i++)
                {
                    dynamic_cast<StringListWidget*>(widget)->addItemToComboBox(qString(items->EQUIP_FLAGS[i].id));
                }
                checkComboBoxForError(dynamic_cast<StringListWidget*>(widget)->comboBox(),
                    "engine/equip_flags.txt is missing or incorrect. Copy it from base mod.");
            }
            else if (widget->accessibleName() == "disable_slots")
            {
                for (unsigned i = 0; i<items->slot_type.size(); i++)
                {
                    dynamic_cast<StringListWidget*>(widget)->addItemToComboBox(qString(items->slot_type[i]));
                }
                checkComboBoxForError(dynamic_cast<StringListWidget*>(widget)->comboBox(),
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
                    listWidget->comboBox()->addItem(qString(items->ELEMENTS[i].id) + "_resist");
                }

                listWidget->comboBox()->addItem("speed");
                listWidget->comboBox()->addItem("physical");
                listWidget->comboBox()->addItem("mental");
                listWidget->comboBox()->addItem("offense");
                listWidget->comboBox()->addItem("defense");
                for (unsigned i = 0; i < mainWindow->getClassTypes("Stats").size(); i++)
                {
                    listWidget->comboBox()->addItem(mainWindow->getClassTypes("Stats").at(i).first);
                }
                checkComboBoxForError(listWidget->comboBox(),
                    "engine/elements.txt is missing or incorrect. Copy it from base mod.");
            }
        }
    }

    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "controlframe")
        {
            dynamic_cast<ControlFrame*>(widget)->ui->pushBtn->setEnabled(false);
            break;
        }
    }

    collectFileLists(path);
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

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
    EntityHandler::clearItemsList();
    delete items;
    items = NULL;
}

void ItemsHandler::addNewItem()
{
	items->items.resize(items->items.size() + 1);
    int index = items->items.size() - 1;
    items->items[index] = new Item;
    items->items[index]->name = "newItem";

    QListWidgetItem* item = new QListWidgetItem("newItem");
    item->setData(Qt::UserRole, index);
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "elementslist")
        {
            dynamic_cast<ElementsList*>(widget)->ui->itemsList->addItem(item);
            break;
        }
    }
}

void ItemsHandler::clearBtn()
{
    EntityHandler::clearBtn();

    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        QString name = QString(widget->metaObject()->className());
        if (name == "LootAnimationWidget")
        {
            dynamic_cast<LootAnimationWidget*>(widget)->clear();
        }
        else if (name == "IconChooser")
        {
            dynamic_cast<IconChooser*>(widget)->setActiveIcon(0);
        }
    }
}

void ItemsHandler::pushBtn()
{
    int index = -1;
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
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
    entity = items->items[index];
    EntityHandler::pushBtn();

    const QMetaObject* metaObject = item->metaObject();
    for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
    {
        QString propertyName = QString::fromLatin1(metaObject->property(i).name());

        for (int i = 0; i < entityLayout->count(); i++)
        {
            QWidget * widget = entityLayout->itemAt(i)->widget();
            if (widget == NULL)
            {
                continue;
            }
            if (widget->accessibleName() == propertyName)
            {
                if (QString(widget->metaObject()->className()) == "LootAnimationWidget")
                {
                    LootAnimationWidget * lootWidget = dynamic_cast<LootAnimationWidget*>(widget);

                    QTextDocument* loot = lootWidget->ui->animations->document();
                    QTextDocument* lootMin = lootWidget->ui->animationMin->document();
                    QTextDocument* lootmax = lootWidget->ui->animationMax->document();
                    item->loot_animation.clear();

                    for (int i = 0; i < loot->lineCount(); i++)
                    {
                        if (loot->findBlockByLineNumber(i).text().isEmpty())
                            continue;
                        item->loot_animation.push_back(LootAnimation());

                        item->loot_animation.back().name = stdString(loot->findBlockByLineNumber(i).text());
                        item->loot_animation.back().low  = lootMin->findBlockByLineNumber(i).text().toInt();
                        item->loot_animation.back().high = lootmax->findBlockByLineNumber(i).text().toInt();
                    }
                }
                else if (QString(widget->metaObject()->className()) == "IconChooser")
                {
                    item->setProperty(propertyName.toStdString().c_str(),
                        dynamic_cast<IconChooser*>(widget)->ui->iconsView->getActiveIcon());
                }
            }
        }
    }

    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
        if (widget == NULL)
        {
            continue;
        }
        if (widget->accessibleName() == "elementslist")
        {
            dynamic_cast<ElementsList*>(widget)->ui->itemsList->currentItem()->setData(Qt::DisplayRole, qString(item->name));
        }
        else if (widget->accessibleName() == "item_type")
        {
            item->type = stdString(dynamic_cast<ComboBox*>(widget)->itemData(dynamic_cast<ComboBox*>(widget)->currentIndex()).toString());
        }
        else if (widget->accessibleName() == "soundfx")
        {
            item->sfx = std::string("soundfx/inventory/") + stdString(dynamic_cast<ComboBox*>(widget)->currentText());
        }
        else if (widget->accessibleName() == "bonus")
        {
            QTextDocument* keysList = dynamic_cast<ComboBoxKeyValueList*>(widget)->keys();
            QTextDocument* valuesList = dynamic_cast<ComboBoxKeyValueList*>(widget)->values();
            item->bonus.clear();

            for (int i = 0; i < keysList->lineCount(); i++)
            {
                if (keysList->findBlockByLineNumber(i).text().isEmpty() || valuesList->findBlockByLineNumber(i).text().isEmpty())
                    continue;

                item->bonus.push_back(BonusData());

                QString bonus_str = keysList->findBlockByLineNumber(i).text();

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
                for (unsigned k=0; k < mainWindow->getClassTypes("Stats").size(); ++k) {
                    if (bonus_str == mainWindow->getClassTypes("Stats").at(k).first) {
                        item->bonus.back().stat_index = k;
                        break;
                    }
                }
                item->bonus.back().value = valuesList->findBlockByLineNumber(i).text().toInt();
            }
        }
        else if (widget->accessibleName() == "requires_stat")
        {
            item->req_stat.clear();
            item->req_val.clear();

            QTextDocument* keysList = dynamic_cast<ComboBoxKeyValueList*>(widget)->keys();
            QTextDocument* valuesList = dynamic_cast<ComboBoxKeyValueList*>(widget)->values();

            for (int i = 0; i < keysList->lineCount(); i++)
            {
                if (keysList->findBlockByLineNumber(i).text().isEmpty() || valuesList->findBlockByLineNumber(i).text().isEmpty())
                    continue;

                QString stat = keysList->findBlockByLineNumber(i).text();
                QString val = valuesList->findBlockByLineNumber(i).text();
                if (val.toInt() > 0)
                {
                    if (stat == "physical")
                    {
                        item->req_stat.push_back(REQUIRES_PHYS);
                    }
                    else if (stat == "mental")
                    {
                        item->req_stat.push_back(REQUIRES_MENT);
                    }
                    else if (stat == "offense")
                    {
                        item->req_stat.push_back(REQUIRES_OFF);
                    }
                    else if (stat == "defense")
                    {
                        item->req_stat.push_back(REQUIRES_DEF);
                    }
                    item->req_val.push_back(val.toInt());
                }
            }
        }
    }
    entity = NULL;
}

void ItemsHandler::selectElementFromList(QListWidgetItem *_item)
{
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
        if (widget && widget->accessibleName() == "item_type")
        {
            // FIXME: setting -1 crashes in some cases
            //dynamic_cast<ComboBox*>(widget)->setCurrentIndex(-1);
        }
    }

    int index = _item->data(Qt::UserRole).toInt();
    Item* item = items->items[index];
    entity = items->items[index];
    EntityHandler::selectElementFromList(_item);

    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
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
                int listSize = dynamic_cast<ComboBox*>(widget)->count();
                for (int i = 0; i < listSize; i++)
                {
                    if (dynamic_cast<ComboBox*>(widget)->itemData(i) == type)
                    {
                        dynamic_cast<ComboBox*>(widget)->setCurrentIndex(i);
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
            listWidget->clear();
            for (int i = 0; i < item->bonus.size(); i++)
            {
                int stat_index     = item->bonus[i].stat_index;
                int base_index     = item->bonus[i].base_index;
                int resist_index   = item->bonus[i].resist_index;
                bool is_speed      = item->bonus[i].is_speed;

                if (stat_index != -1)
                {
                    listWidget->appendKey(mainWindow->getClassTypes("Stats").at(stat_index).first);
                }
                else if (resist_index != -1)
                {
                    listWidget->appendKey(qString(items->ELEMENTS[resist_index].id) + "_resist");
                }
                else if (is_speed)
                {
                    listWidget->appendKey(QString("speed"));
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

                    listWidget->appendKey(bonus_str);
                }
                listWidget->appendValue(QString::number(item->bonus[i].value));
            }
        }
        else if (widget->accessibleName() == "requires_stat")
        {
            ComboBoxKeyValueList * listWidget = dynamic_cast<ComboBoxKeyValueList*>(widget);
            listWidget->clear();
            for (int i = 0; i < item->req_stat.size(); i++)
            {
                int value = item->req_val[i];
                listWidget->comboBox()->itemData(item->req_stat[i]).toString();
                listWidget->appendValue(QString::number(value));
            }
        }
    }
    entity = NULL;
}

void ItemsHandler::collectFileLists(const std::string &path)
{
    QString modPath = qString(path);
    QStringList files;

    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();
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

void ItemsHandler::setupConnections()
{
    EntityHandler::setupConnections();

    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "icon")
        {
            IconChooser * iconChooser = dynamic_cast<IconChooser*>(widget);
            connect(iconChooser->ui->assignIconBtn, SIGNAL(clicked()), SLOT(requestIconAdd()));
            connect(iconChooser->ui->iconsView, SIGNAL(iconPlaced()), SLOT(finishIconAdd()));
            connect(iconChooser->ui->iconsView, SIGNAL(iconSkipped()), SLOT(skipIconAdd()));
        }
    }
}

void ItemsHandler::finishIconAdd()
{
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

        if (widget && widget->accessibleName() == "icon")
        {
            dynamic_cast<IconChooser*>(widget)->ui->iconPasteLabel->hide();
            break;
        }
    }
    setEntityEdited(true);

}

void ItemsHandler::skipIconAdd()
{
    for (int i = 0; i < entityLayout->count(); i++)
    {
        QWidget * widget = entityLayout->itemAt(i)->widget();

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
        for (int i = 0; i < entityLayout->count(); i++)
        {
            QWidget * widget = entityLayout->itemAt(i)->widget();

            if (widget && widget->accessibleName() == "icon")
            {
                dynamic_cast<IconChooser*>(widget)->ui->iconPasteLabel->show();
                dynamic_cast<IconChooser*>(widget)->ui->iconsView->appendIcon(newIcon);
                break;
            }
        }
    }
}
