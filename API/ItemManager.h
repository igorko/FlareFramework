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

class Item {
public:
	std::string name;     // item name displayed on long and short tool tips
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

	int getSellPrice();

	Item()
		: name("")
		, flavor("")
		, level(0)
		, set(0)
		, quality("")
		, type("other")
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
	std::string getItemType(std::string _type);
	void addUnknownItem(int id);
	bool requirementsMet(const StatBlock *stats, int item);

	std::vector<Item> items;
	std::vector<ItemType> item_types;
	std::vector<ItemSet> item_sets;
	std::vector<ItemQuality> item_qualities;
};

#endif
