/*
Copyright © 2011-2012 Clint Bellanger
Copyright © 2012 Igor Paliychuk
Copyright © 2013 Henrik Andersson
Copyright © 2013 Kurt Rinnert

This file is part of FLARE.

FLARE is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

FLARE is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
FLARE.  If not, see http://www.gnu.org/licenses/
*/

/**
 * class ItemManager
 */

#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "CommonIncludes.h"
#include "FileParser.h"
#ifndef EDITOR
#include "TooltipData.h"
#else
#include "Utils.h"

#include <QObject>
#include <QVector>
#include <QMetaType>
#include <QPair>
#include <QStringList>

class Element {
public:
	std::string id;
	std::string name;
};

class EquipFlag {
public:
	std::string id;
	std::string name;
};

class HeroClass {
public:
	std::string name;
	std::string description;
	int currency;
	std::string equipment;
	int physical;
	int mental;
	int offense;
	int defense;
	std::vector<int> powers;
	std::vector<std::string> statuses;
	std::string power_tree;

	HeroClass()
		: name("")
		, description("")
		, currency(0)
		, equipment("")
		, physical(0)
		, mental(0)
		, offense(0)
		, defense(0)
		, power_tree("") {
	}
};

class Step_sfx {
public:
	std::string id;
	std::vector<std::string> steps;
};

#endif

#include <stdint.h>

#define VENDOR_BUY 0
#define VENDOR_SELL 1
#define PLAYER_INV 2

class StatBlock;

const int REQUIRES_PHYS = 0;
const int REQUIRES_MENT = 1;
const int REQUIRES_OFF = 2;
const int REQUIRES_DEF = 3;

class LootAnimation {
public:
	std::string name;
	int low;
	int high;
	LootAnimation()
		: name("")
		, low(0)
		, high(0) {
	}
};

class BonusData {
public:
	int stat_index; // Stats.h
	int resist_index; // engine/elements.txt
	int base_index; // physical, mental, offense, defense
	bool is_speed;
	int value;
	BonusData()
		: stat_index(-1)
		, resist_index(-1)
		, base_index(-1)
		, is_speed(false)
		, value(0) {
	}
};

class Set_bonus : public BonusData {
public:
	int requirement;
	Set_bonus()
		: BonusData()
		, requirement(0) {
	}
};

class ItemQuality {
public:
	std::string id;
	std::string name;
#ifndef EDITOR
	Color color;
#endif
	ItemQuality()
		: id("")
		, name("")
#ifndef EDITOR
		, color(255,255,255) {
	}
#else
	{}
#endif
};

#ifndef EDITOR
class Item {
private:
	std::string name;     // item name displayed on long and short tool tips
	friend class ItemManager;
#else
class Item : public QObject {
    Q_OBJECT

private:
    Q_DISABLE_COPY(Item)

public:

    std::string name;     // item name displayed on long and short tool tips
#endif

public:
    std::string flavor;   // optional flavor text describing the item
    int level;            // rough estimate of quality, used in the loot algorithm
    int set;              // item can be attached to item set
    std::string quality;  // should match an id from items/qualities.txt
    std::string type;     // equipment slot or base item type
    std::vector<std::string> equip_flags;   // common values include: melee, ranged, mental, shield
    int icon;             // icon index on small pixel sheet
    std::string book;     // book file location
    int dmg_melee_min;    // minimum damage amount (melee)
    int dmg_melee_max;    // maximum damage amount (melee)
    int dmg_ranged_min;   // minimum damage amount (ranged)
    int dmg_ranged_max;   // maximum damage amount (ranged)
    int dmg_ment_min;     // minimum damage amount (mental)
    int dmg_ment_max;     // maximum damage amount (mental)
    int abs_min;          // minimum absorb amount
    int abs_max;          // maximum absorb amount
    std::vector<int> req_stat;         // physical, mental, offense, defense
    std::vector<int> req_val;          // 1-5 (used with req_stat)
    std::string requires_class;
    std::vector<BonusData> bonus;   // stat to increase/decrease e.g. hp, accuracy, speed
    std::string sfx;           // the item sound when it hits the floor or inventory, etc
#ifndef EDITOR
	SoundManager::SoundID sfx_id;
#endif
    std::string gfx;           // the sprite layer shown when this item is equipped
    std::vector<LootAnimation> loot_animation;// the flying loot animation for this item
    int power;            // this item can be dragged to the action bar and used as a power
    std::vector<Point> replace_power;        // alter powers when this item is equipped. Power id 'x' is replaced with id 'y'
    std::string power_desc;    // shows up in green text on the tooltip
    int price;            // if price = 0 the item cannot be sold
    int price_sell;       // if price_sell = 0, the sell price is price*vendor_ratio
    int max_quantity;     // max count per stack
    std::string pickup_status; // when this item is picked up, set a campaign state (usually for quest items)
    std::string stepfx;        // sound effect played when walking (armors only)
    std::vector<std::string> disable_slots; // if this item is equipped, it will disable slots that match the types in the list

#if EDITOR

public:
    Q_PROPERTY(QString name READ getName WRITE setName)

    QString getName() {return QString::fromStdString(name);}
    void setName(QString value) {name = value.toStdString();}

    Q_PROPERTY(QString flavor READ getFlavor WRITE setFlavor)

    QString getFlavor() {return QString::fromStdString(flavor);}
    void setFlavor(QString value) {flavor = value.toStdString();}

    Q_PROPERTY(int level READ getLevel WRITE setLevel)

    int getLevel() {return level;}
    void setLevel(int value) {level = value;}

    Q_PROPERTY(int set READ getSet WRITE setSet)

    int getSet() {return set;}
    void setSet(int value) {set = value;}

    Q_PROPERTY(QString quality READ getQuality WRITE setQuality)

    QString getQuality() {return QString::fromStdString(quality);}
    void setQuality(QString value) {quality = value.toStdString();}

    Q_PROPERTY(QString type READ getType WRITE setType)

    QString getType() {return QString::fromStdString(type);}
    void setType(QString value) {type = value.toStdString();}

    Q_PROPERTY(QList<QString> equip_flags READ getEquipFlags WRITE setEquipFlags)

    QList<QString> getEquipFlags()
    {
        QList<std::string> list = QList<std::string>::fromVector(QVector<std::string>::fromStdVector(equip_flags));
        QList<QString> result;
        for (int i = 0; i < list.size(); i++)
        {
            result.push_back(QString::fromStdString(list[i]));
        }
        return result;
    }
    void setEquipFlags(QList<QString> value)
    {
        equip_flags.clear();
        for (int i = 0; i < value.size(); i++)
        {
            equip_flags.push_back(value[i].toStdString());
        }
    }

    Q_PROPERTY(int icon READ getIcon WRITE setIcon)

    int getIcon() {return icon;}
    void setIcon(int value) {icon = value;}

    Q_PROPERTY(QString book READ getBook WRITE setBook)

    QString getBook() {return QString::fromStdString(book);}
    void setBook(QString value) {book = value.toStdString();}

    Q_PROPERTY(int dmg_melee_min READ getDmgMeleeMin WRITE setDmgMeleeMin)

    int getDmgMeleeMin() {return dmg_melee_min;}
    void setDmgMeleeMin(int value) {dmg_melee_min = value;}

    Q_PROPERTY(int dmg_melee_max READ getDmgMeleeMax WRITE setDmgMeleeMax)

    int getDmgMeleeMax() {return dmg_melee_max;}
    void setDmgMeleeMax(int value) {dmg_melee_max = value;}

    Q_PROPERTY(int dmg_ranged_min READ getDmgRangedMin WRITE setDmgRangedMin)

    int getDmgRangedMin() {return dmg_ranged_min;}
    void setDmgRangedMin(int value) {dmg_ranged_min = value;}

    Q_PROPERTY(int dmg_ranged_max READ getDmgRangedMax WRITE setDmgRangedMax)

    int getDmgRangedMax() {return dmg_ranged_max;}
    void setDmgRangedMax(int value) {dmg_ranged_max = value;}

    Q_PROPERTY(int dmg_ment_min READ getDmgMentMin WRITE setDmgMentMin)

    int getDmgMentMin() {return dmg_ment_min;}
    void setDmgMentMin(int value) {dmg_ment_min = value;}

    Q_PROPERTY(int dmg_ment_max READ getDmgMentMax WRITE setDmgMentMax)

    int getDmgMentMax() {return dmg_ment_max;}
    void setDmgMentMax(int value) {dmg_ment_max = value;}

    Q_PROPERTY(int abs_min READ getAbsMin WRITE setAbsMin)

    int getAbsMin() {return abs_min;}
    void setAbsMin(int value) {abs_min = value;}

    Q_PROPERTY(int abs_max READ getAbsMax WRITE setAbsMax)

    int getAbsMax() {return abs_max;}
    void setAbsMax(int value) {abs_max = value;}

    Q_PROPERTY(QList<int> req_stat READ getReqStat WRITE setReqStat)

    QList<int> getReqStat() {return QList<int>::fromVector(QVector<int>::fromStdVector(req_stat));}
    void setReqStat(QList<int> value) {req_stat = value.toVector().toStdVector();}

    Q_PROPERTY(QList<int> req_val READ getReqVal WRITE setReqVal)

    QList<int> getReqVal() {return QList<int>::fromVector(QVector<int>::fromStdVector(req_val));}
    void setReqVal(QList<int> value) {req_val = value.toVector().toStdVector();}

    Q_PROPERTY(QString requires_class READ getRequiresClass WRITE setRequiresClass)

    QString getRequiresClass() {return QString::fromStdString(requires_class);}
    void setRequiresClass(QString value) {requires_class = value.toStdString();}

    //Q_PROPERTY(QList<BonusData> bonus READ getBonus WRITE setBonus)
    //QList<BonusData> getBonus() {return bonus;};
    //void setBonus(QList<BonusData> value) {bonus = value;};

    Q_PROPERTY(QString sfx READ getSfx WRITE setSfx)

    QString getSfx() {return QString::fromStdString(sfx);}
    void setSfx(QString value) {sfx = value.toStdString();}

    Q_PROPERTY(QString gfx READ getGfx WRITE setGfx)

    QString getGfx() {return QString::fromStdString(gfx);}
    void setGfx(QString value) {gfx = value.toStdString();}

    //Q_PROPERTY(QList<LootAnimation> loot_animation  READ getLootAnimation WRITE setLootAnimation)
    //QList<LootAnimation> getLootAnimation() {return loot_animation;};
    //void setLootAnimation(QList<LootAnimation> value) {loot_animation = value;};

    Q_PROPERTY(int power READ getPower WRITE setPower)

    int getPower() {return power;}
    void setPower(int value) {power = value;}

    Q_PROPERTY(QList<QStringList> replace_power READ getReplacePower WRITE setReplacePower)

    QList<QStringList> getReplacePower()
    {
        QList<Point> list = QList<Point>::fromVector(QVector<Point>::fromStdVector(replace_power));
        QList<QStringList> result;
        for (int i = 0; i < list.size(); i++)
        {
            QStringList tmp;
            tmp << QString::number(list[i].x) << QString::number(list[i].y);
            result.push_back(tmp);
        }
        return result;
    }
    void setReplacePower(QList<QStringList> value)
    {
        replace_power.clear();
        for (int i = 0; i < value.size(); i++)
        {
            replace_power.push_back(Point(value[i][0].toInt(), value[i][1].toInt()));
        }
    }

    Q_PROPERTY(QString power_desc READ getPowerDesc WRITE setPowerDesc)

    QString getPowerDesc() {return QString::fromStdString(power_desc);}
    void setPowerDesc(QString value) {power_desc = value.toStdString();}

    Q_PROPERTY(int price READ getPrice WRITE setPrice)

    int getPrice() {return price;}
    void setPrice(int value) {price = value;}

    Q_PROPERTY(int price_sell READ getPriceSell WRITE setPriceSell)

    int getPriceSell() {return price_sell;}
    void setPriceSell(int value) {price_sell = value;}

    Q_PROPERTY(int max_quantity READ getQuantity WRITE setQuantity)

    int getQuantity() {return max_quantity;}
    void setQuantity(int value) {max_quantity = value;}

    Q_PROPERTY(QString pickup_status READ getPickupStatus WRITE setPickupStatus)

    QString getPickupStatus() {return QString::fromStdString(pickup_status);}
    void setPickupStatus(QString value) {pickup_status = value.toStdString();}

    Q_PROPERTY(QString stepfx READ getStepFX WRITE setStepFX)

    QString getStepFX() {return QString::fromStdString(stepfx);}
    void setStepFX(QString value) {stepfx = value.toStdString();}

    Q_PROPERTY(QList<QString> disable_slots READ getDisableSlots WRITE setDisableSlots)

    QList<QString> getDisableSlots()
    {
        QList<std::string> list = QList<std::string>::fromVector(QVector<std::string>::fromStdVector(disable_slots));
        QList<QString> result;
        for (int i = 0; i < list.size(); i++)
        {
            result.push_back(QString::fromStdString(list[i]));
        }
        return result;
    }
    void setDisableSlots(QList<QString> value)
    {
        disable_slots.clear();
        for (int i = 0; i < value.size(); i++)
        {
            disable_slots.push_back(value[i].toStdString());
        }
    }

#endif

public:
	int getSellPrice();
#ifndef EDITOR
	Item()
		: name("")
#else
	explicit Item(QObject * parent = NULL)
		: QObject(parent)
        , name("")
#endif
        , flavor("")
        , level(0)
        , set(0)
        , quality("")
        , type("")
        , icon(0)
        , dmg_melee_min(0)
        , dmg_melee_max(0)
        , dmg_ranged_min(0)
        , dmg_ranged_max(0)
        , dmg_ment_min(0)
        , dmg_ment_max(0)
        , abs_min(0)
		, abs_max(0)
        , requires_class("")
        , sfx("")
#ifndef EDITOR
		, sfx_id(0)
#endif
        , gfx("")
        , power(0)
        , power_desc("")
        , price(0)
        , price_sell(0)
        , max_quantity(1)
        , pickup_status("")
        , stepfx("") {
	}

	~Item() {
	}
};

class ItemSet {
public:
	std::string name;            // item set name displayed on long and short tool tips
	std::vector<int> items;      // items, included into set
	std::vector<Set_bonus> bonus;// vector with stats to increase/decrease
#ifndef EDITOR
	Color color;
#endif

	ItemSet()
		: name("") {
#ifndef EDITOR
		color.r = 255;
		color.g = 255;
		color.b = 255;
#endif
	}

	~ItemSet() {
	}
};

class ItemStack {
public:
	ItemStack()
		: item(0)
		, quantity(0) {
	}
	~ItemStack() {}
	int item;
	int quantity;
	bool operator > (const ItemStack &param) const;
	bool empty();
	void clear();
};

class ItemType {
public:
	ItemType()
		: id("")
		, name("") {
	}
	~ItemType() {}

	std::string id;
	std::string name;
};

class ItemManager {
protected:
	void loadItems(const std::string& filename, bool locateFileName = true);
	void loadTypes(const std::string& filename, bool locateFileName = true);
	void loadSets(const std::string& filename, bool locateFileName = true);
	void loadQualities(const std::string& filename, bool locateFileName = true);
private:
	void loadAll();
	void parseBonus(BonusData& bdata, FileParser& infile);
	void getBonusString(std::stringstream& ss, BonusData* bdata);

#ifndef EDITOR
	Color color_normal;
	Color color_low;
	Color color_high;
	Color color_epic;
	Color color_bonus;
	Color color_penalty;
	Color color_requirements_not_met;
	Color color_flavor;
#endif

public:
	ItemManager();
	~ItemManager();
	void playSound(int item, Point pos = Point(0,0));
#ifndef EDITOR
	TooltipData getTooltip(ItemStack stack, StatBlock *stats, int context);
	TooltipData getShortTooltip(ItemStack item);
#else
	std::vector<Element> ELEMENTS;
	std::vector<EquipFlag> EQUIP_FLAGS;
	std::vector<HeroClass> HERO_CLASSES;
#endif
	std::string getItemName(unsigned id);
	std::string getItemType(std::string _type);
	void addUnknownItem(unsigned id);
	bool requirementsMet(const StatBlock *stats, int item);

#ifndef EDITOR
	std::vector<Item> items;
#else
	QVector<Item*> items;
#endif
	std::vector<ItemType> item_types;
	std::vector<ItemSet> item_sets;
	std::vector<ItemQuality> item_qualities;
};

#include <QMetaType>

Q_DECLARE_METATYPE(Item*)

#endif
