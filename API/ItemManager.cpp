/*
Copyright © 2011-2012 Clint Bellanger
Copyright © 2012 Igor Paliychuk
Copyright © 2012 Stefan Beller
Copyright © 2013-2014 Henrik Andersson
Copyright © 2013 Kurt Rinnert
Copyright © 2012-2016 Justin Jacobs

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

#include "CommonIncludes.h"
#include "FileParser.h"
#include "ItemManager.h"
#ifndef EDITOR
#include "Settings.h"
#include "SharedResources.h"
#include "SharedGameResources.h"
#include "StatBlock.h"
#endif
#include "Stats.h"
#include "UtilsFileSystem.h"
#include "UtilsParsing.h"
#ifndef EDITOR
#include "WidgetLabel.h"
#endif

#include <cassert>
#include <climits>
#include <cstring>

bool compareItemStack(const ItemStack &stack1, const ItemStack &stack2) {
	return stack1.item < stack2.item;
}

ItemManager::ItemManager()
#ifndef EDITOR
    : color_normal(font->getColor("widget_normal"))
    , color_bonus(font->getColor("item_bonus"))
    , color_penalty(font->getColor("item_penalty"))
    , color_requirements_not_met(font->getColor("requirements_not_met"))
    , color_flavor(font->getColor("item_flavor")) {
    // NB: 20 is arbitrary picked number, but it looks like good start.
    items.reserve(20);
    item_sets.reserve(5);

    loadAll();
}
#else
{}
#endif

/**
 * Load all items files in all mods
 */
void ItemManager::loadAll() {

	// load each items.txt file. Individual item IDs can be overwritten with mods.
	this->loadItems("items/items.txt");
	this->loadTypes("items/types.txt");
	this->loadSets("items/sets.txt");
	this->loadQualities("items/qualities.txt");

	/*
	 * Shrinks the items vector to the absolute needed size.
	 *
	 * While loading the items, the item vector grows dynamically. To have
	 * no much time overhead for reallocating the vector, a new reallocation
	 * is twice as large as the needed item id, which means in the worst case
	 * the item vector was reallocated for loading the last element, so the
	 * vector is twice as large as needed. This memory is definitly not used,
	 * so we can free it.
	 */
	if (items.capacity() != items.size())
		items.swap(items);
	if (item_sets.capacity() != item_sets.size())
		item_sets.swap(item_sets);

	// do we need to print these messages?
	if (items.empty()) logInfo("ItemManager: No items were found.");
	if (item_sets.empty()) logInfo("ItemManager: No item sets were found.");
}

/**
 * Load a specific items file
 *
 * @param filename The (full) path and name of the file to load
 */
void ItemManager::loadItems(const std::string& filename, bool locateFileName) {
	FileParser infile;

	// @CLASS ItemManager: Items|Description about the class and it usage, items/items.txt...
	if (!infile.open(filename, locateFileName))
		return;

	// used to clear vectors when overriding items
	bool clear_req_stat = true;
	bool clear_bonus = true;
	bool clear_loot_anim = true;
	bool clear_replace_power = true;

	int id = 0;
	bool id_line = false;
	while (infile.next()) {
		if (infile.key == "id") {
			// @ATTR id|item_id|An uniq id of the item used as reference from other classes.
			id_line = true;
			id = toInt(infile.val);
			addUnknownItem(id);

			clear_req_stat = true;
			clear_bonus = true;
			clear_loot_anim = true;
			clear_replace_power = true;
		}
		else id_line = false;

		if (id < 1) {
			if (id_line) infile.error("ItemManager: Item index out of bounds 1-%d, skipping item.", INT_MAX);
			continue;
		}
		if (id_line) continue;

		assert(items.size() > std::size_t(id));

		if (infile.key == "name") {
			// @ATTR name|string|Item name displayed on long and short tooltips.
#ifndef EDITOR
            items[id]->name = msg->get(infile.val);
#else
            items[id]->name = infile.val;
#endif
            items[id]->has_name = true;
		}
		else if (infile.key == "flavor")
			// @ATTR flavor|string|A description of the item.
#ifndef EDITOR
            items[id]->flavor = msg->get(infile.val);
#else
            items[id]->flavor = infile.val;
#endif
		else if (infile.key == "level")
			// @ATTR level|int|The item's level. Has no gameplay impact. (Deprecated?)
            items[id]->level = toInt(infile.val);
		else if (infile.key == "icon") {
			// @ATTR icon|icon_id|An id for the icon to display for this item.
            items[id]->icon = toInt(infile.nextValue());
		}
		else if (infile.key == "book") {
			// @ATTR book|filename|A book file to open when this item is activated.
            items[id]->book = infile.val;
		}
		else if (infile.key == "quality") {
			// @ATTR quality|predefined_string|Item quality matching an id in items/qualities.txt
            items[id]->quality = infile.val;
		}
		else if (infile.key == "item_type") {
			// @ATTR item_type|predefined_string|Equipment slot matching an id in items/types.txt
            items[id]->type = infile.val;
		}
		else if (infile.key == "equip_flags") {
			// @ATTR equip_flags|list(predefined_string)|A comma separated list of flags to set when this item is equipped. See engine/equip_flags.txt.
            items[id]->equip_flags.clear();
			std::string flag = popFirstString(infile.val);

			while (flag != "") {
                items[id]->equip_flags.push_back(flag);
				flag = popFirstString(infile.val);
			}
		}
		else if (infile.key == "dmg_melee") {
			// @ATTR dmg_melee|int, int : Min, Max|Defines the item melee damage, if only min is specified the melee damage is fixed.
            items[id]->dmg_melee_min = toInt(infile.nextValue());
			if (infile.val.length() > 0)
                items[id]->dmg_melee_max = toInt(infile.nextValue());
			else
                items[id]->dmg_melee_max = items[id]->dmg_melee_min;
		}
		else if (infile.key == "dmg_ranged") {
			// @ATTR dmg_ranged|int, int : Min, Max|Defines the item ranged damage, if only min is specified the ranged damage is fixed.
            items[id]->dmg_ranged_min = toInt(infile.nextValue());
			if (infile.val.length() > 0)
                items[id]->dmg_ranged_max = toInt(infile.nextValue());
			else
                items[id]->dmg_ranged_max = items[id]->dmg_ranged_min;
		}
		else if (infile.key == "dmg_ment") {
			// @ATTR dmg_ment|int, int : Min, Max|Defines the item mental damage, if only min is specified the ranged damage is fixed.
            items[id]->dmg_ment_min = toInt(infile.nextValue());
			if (infile.val.length() > 0)
                items[id]->dmg_ment_max = toInt(infile.nextValue());
			else
                items[id]->dmg_ment_max = items[id]->dmg_ment_min;
		}
		else if (infile.key == "abs") {
			// @ATTR abs|int, int : Min, Max|Defines the item absorb value, if only min is specified the absorb value is fixed.
            items[id]->abs_min = toInt(infile.nextValue());
			if (infile.val.length() > 0)
                items[id]->abs_max = toInt(infile.nextValue());
			else
                items[id]->abs_max = items[id]->abs_min;
		}
		else if (infile.key == "requires_level") {
			// @ATTR requires_level|int|The hero's level must match or exceed this value in order to equip this item.
            items[id]->requires_level = toInt(infile.val);
		}
		else if (infile.key == "requires_stat") {
			// @ATTR requires_stat|repeatable(["physical", "mental", "offense", "defense"], int) : Primary stat name, Value|Make item require specific stat level ex. requires_stat=physical,6 will require hero to have level 6 in physical stats
			if (clear_req_stat) {
                items[id]->req_stat.clear();
                items[id]->req_val.clear();
				clear_req_stat = false;
			}
			std::string s = infile.nextValue();
			if (s == "physical")
                items[id]->req_stat.push_back(REQUIRES_PHYS);
			else if (s == "mental")
                items[id]->req_stat.push_back(REQUIRES_MENT);
			else if (s == "offense")
                items[id]->req_stat.push_back(REQUIRES_OFF);
			else if (s == "defense")
                items[id]->req_stat.push_back(REQUIRES_DEF);
			else
				infile.error("%s unrecognized at; requires_stat must be one of [physical:mental:offense:defense]", s.c_str());
            items[id]->req_val.push_back(toInt(infile.nextValue()));
		}
		else if (infile.key == "requires_class") {
			// @ATTR requires_class|predefined_string|The hero's base class (engine/classes.txt) must match for this item to be equipped.
            items[id]->requires_class = infile.val;
		}
		else if (infile.key == "bonus") {
			// @ATTR bonus|repeatable(predefined_string, int) : Stat name, Value|Adds a bonus to the item by stat name, example: bonus=hp, 50
			if (clear_bonus) {
                items[id]->bonus.clear();
				clear_bonus = false;
			}
			BonusData bdata;
			parseBonus(bdata, infile);
            items[id]->bonus.push_back(bdata);
		}
		else if (infile.key == "soundfx") {
			// @ATTR soundfx|filename|Sound effect filename to play for the specific item.
            items[id]->sfx = infile.val;
#ifndef EDITOR
            items[id].sfx_id = snd->load(items[id].sfx, "ItemManager");
#endif
		}
		else if (infile.key == "gfx")
			// @ATTR gfx|filename|Filename of an animation set to display when the item is equipped.
            items[id]->gfx = infile.val;
		else if (infile.key == "loot_animation") {
			// @ATTR loot_animation|repeatable(filename, int, int) : Loot image, Min quantity, Max quantity|Specifies the loot animation file for the item. The max quantity, or both quantity values, may be omitted.
			if (clear_loot_anim) {
                items[id]->loot_animation.clear();
				clear_loot_anim = false;
			}
			LootAnimation la;
			la.name = popFirstString(infile.val);
			la.low = popFirstInt(infile.val);
			la.high = popFirstInt(infile.val);
            items[id]->loot_animation.push_back(la);
		}
		else if (infile.key == "power") {
			// @ATTR power|power_id|Adds a specific power to the item which makes it usable as a power and can be placed in action bar.
			if (toInt(infile.val) > 0)
                items[id]->power = toInt(infile.val);
			else
				infile.error("ItemManager: Power index out of bounds 1-%d, skipping power.", INT_MAX);
		}
		else if (infile.key == "replace_power") {
			// @ATTR replace_power|repeatable(int, int) : Old power, New power|Replaces the old power id with the new power id in the action bar when equipped.
			if (clear_replace_power) {
                items[id]->replace_power.clear();
				clear_replace_power = false;
			}
			Point power_ids = toPoint(infile.val);
            items[id]->replace_power.push_back(power_ids);
		}
		else if (infile.key == "power_desc")
			// @ATTR power_desc|string|A string describing the additional power.
#ifndef EDITOR
            items[id]->power_desc = msg->get(infile.val);
#else
            items[id]->power_desc = infile.val;
#endif
		else if (infile.key == "price")
			// @ATTR price|int|The amount of currency the item costs, if set to 0 the item cannot be sold.
            items[id]->price = toInt(infile.val);
		else if (infile.key == "price_per_level")
			// @ATTR price_per_level|int|Additional price for each player level above 1
            items[id]->price_per_level = toInt(infile.val);
		else if (infile.key == "price_sell")
			// @ATTR price_sell|int|The amount of currency the item is sold for, if set to 0 the sell prices is prices*vendor_ratio.
            items[id]->price_sell = toInt(infile.val);
		else if (infile.key == "max_quantity")
			// @ATTR max_quantity|int|Max item count per stack.
            items[id]->max_quantity = toInt(infile.val);
		else if (infile.key == "pickup_status")
			// @ATTR pickup_status|string|Set a campaign status when item is picked up, this is used for quest items.
            items[id]->pickup_status = infile.val;
		else if (infile.key == "stepfx")
			// @ATTR stepfx|predefined_string|Sound effect when walking, this applies only to armors.
            items[id]->stepfx = infile.val;
		else if (infile.key == "disable_slots") {
			// @ATTR disable_slots|list(predefined_string)|A comma separated list of equip slot types to disable when this item is equipped.
            items[id]->disable_slots.clear();
			std::string slot_type = popFirstString(infile.val);

			while (slot_type != "") {
                items[id]->disable_slots.push_back(slot_type);
				slot_type = popFirstString(infile.val);
			}
		}
		else if (infile.key == "quest_item") {
			// @ATTR quest_item|bool|If true, this item is a quest item and can not be dropped, stashed, or sold.
            items[id]->quest_item = toBool(infile.val);
		}
		else {
			infile.error("ItemManager: '%s' is not a valid key.", infile.key.c_str());
		}

	}
	infile.close();
}

/**
 * Load a specific item types file
 *
 * @param filename The (full) path and name of the file to load
 */
void ItemManager::loadTypes(const std::string& filename, bool locateFileName) {
	FileParser infile;

	// @CLASS ItemManager: Types|Definition of a item types, items/types.txt...
	if (infile.open(filename, locateFileName)) {
		while (infile.next()) {
			if (infile.new_section) {
				if (infile.section == "type") {
					// check if the previous type and remove it if there is no identifier
					if (!item_types.empty() && item_types.back().id == "") {
						item_types.pop_back();
					}
					item_types.resize(item_types.size()+1);
				}
			}

			if (item_types.empty() || infile.section != "type")
				continue;

			// @ATTR type.id|string|Item type identifier.
			if (infile.key == "id")
				item_types.back().id = infile.val;
			// @ATTR type.name|string|Item type name.
			else if (infile.key == "name")
				item_types.back().name = infile.val;
			else
				infile.error("ItemManager: '%s' is not a valid key.", infile.key.c_str());
		}
		infile.close();

		// check if the last type and remove it if there is no identifier
		if (!item_types.empty() && item_types.back().id == "") {
			item_types.pop_back();
		}
	}
}

/**
 * Load a specific item qualities file
 *
 * @param filename The (full) path and name of the file to load
 */
void ItemManager::loadQualities(const std::string& filename, bool locateFileName) {
	FileParser infile;

	// @CLASS ItemManager: Qualities|Definition of a item qualities, items/types.txt...
	if (infile.open(filename, locateFileName)) {
		while (infile.next()) {
			if (infile.new_section) {
				if (infile.section == "quality") {
					// check if the previous quality and remove it if there is no identifier
					if (!item_qualities.empty() && item_qualities.back().id == "") {
						item_qualities.pop_back();
					}
					item_qualities.resize(item_qualities.size()+1);
				}
			}

			if (item_qualities.empty() || infile.section != "quality")
				continue;

			// @ATTR quality.id|string|Item quality identifier.
			if (infile.key == "id")
				item_qualities.back().id = infile.val;
			// @ATTR quality.name|string|Item quality name.
			else if (infile.key == "name")
				item_qualities.back().name = infile.val;
			// @ATTR quality.color|color|Item quality color.
			else if (infile.key == "color")
				item_qualities.back().color = toRGB(infile.val);
			else
				infile.error("ItemManager: '%s' is not a valid key.", infile.key.c_str());
		}
		infile.close();

		// check if the last quality and remove it if there is no identifier
		if (!item_qualities.empty() && item_qualities.back().id == "") {
			item_qualities.pop_back();
		}
	}
}

std::string ItemManager::getItemName(unsigned id) {
#ifndef EDITOR
	if (id >= items.size()) return msg->get("Unknown Item");

    if (!items[id].has_name)
		items[id].name = msg->get("Unknown Item");
#else
    return items[id]->name;
#endif
}

std::string ItemManager::getItemType(const std::string& _type) {
	for (unsigned i=0; i<item_types.size(); ++i) {
		if (item_types[i].id == _type)
			return item_types[i].name;
	}
	// If all else fails, return the original string
	return _type;
}

Color ItemManager::getItemColor(unsigned id) {
	if (id < 1 || id > items.size()) return color_normal;

    if (items[id]->set > 0) {
        return item_sets[items[id]->set].color;
	}
	else {
		for (unsigned i=0; i<item_qualities.size(); ++i) {
            if (item_qualities[i].id == items[id]->quality) {
				return item_qualities[i].color;
			}
		}
	}

	return color_normal;
}

void ItemManager::addUnknownItem(unsigned id) {
	if (id > 0) {
		size_t new_size = id+1;
		if (items.size() <= new_size)
			items.resize(new_size);
	}
}

/**
 * Load a specific item sets file
 *
 * @param filename The (full) path and name of the file to load
 */
void ItemManager::loadSets(const std::string& filename, bool locateFileName) {
	FileParser infile;

	// @CLASS ItemManager: Sets|Definition of a item sets, items/sets.txt...
	if (!infile.open(filename, locateFileName))
		return;

	bool clear_bonus = true;

	int id = 0;
	bool id_line;
	while (infile.next()) {
		if (infile.key == "id") {
			// @ATTR id|int|A uniq id for the item set.
			id_line = true;
			id = toInt(infile.val);

			if (id > 0) {
				size_t new_size = id+1;
				if (item_sets.size() <= new_size)
					item_sets.resize(new_size);
			}

			clear_bonus = true;
		}
		else id_line = false;

		if (id < 1) {
			if (id_line) infile.error("ItemManager: Item set index out of bounds 1-%d, skipping set.", INT_MAX);
			continue;
		}
		if (id_line) continue;

		assert(item_sets.size() > std::size_t(id));

		if (infile.key == "name") {
			// @ATTR name|string|Name of the item set.
#ifndef EDITOR
			item_sets[id].name = msg->get(infile.val);
#else
            item_sets[id].name = infile.val;
#endif
		}
		else if (infile.key == "items") {
			// @ATTR items|list(item_id)|List of item id's that is part of the set.
			item_sets[id].items.clear();
			std::string item_id = infile.nextValue();
			while (item_id != "") {
				int temp_id = toInt(item_id);
				if (temp_id > 0 && temp_id < static_cast<int>(items.size())) {
                    items[temp_id]->set = id;
					item_sets[id].items.push_back(temp_id);
				}
				else {
					const int maxsize = static_cast<int>(items.size()-1);
					infile.error("ItemManager: Item index out of bounds 1-%d, skipping item.", maxsize);
				}
				item_id = infile.nextValue();
			}
		}
		else if (infile.key == "color") {
			// @ATTR color|color|A specific of color for the set.
			item_sets[id].color = toRGB(infile.val);
		}
		else if (infile.key == "bonus") {
			// @ATTR bonus|repeatable(int, string, int) : Required set item count, Stat name, Value|Bonus to append to items in the set.
			if (clear_bonus) {
				item_sets[id].bonus.clear();
				clear_bonus = false;
			}
			Set_bonus bonus;
			bonus.requirement = toInt(infile.nextValue());
			parseBonus(bonus, infile);
			item_sets[id].bonus.push_back(bonus);
		}
		else {
			infile.error("ItemManager: '%s' is not a valid key.", infile.key.c_str());
		}
	}
	infile.close();
}

void ItemManager::parseBonus(BonusData& bdata, FileParser& infile) {
	std::string bonus_str = infile.nextValue();
	bdata.value = toInt(infile.nextValue());

	if (bonus_str == "speed") {
		bdata.is_speed = true;
		return;
	}

	for (unsigned i=0; i<STAT_COUNT; ++i) {
		if (bonus_str == STAT_KEY[i]) {
			bdata.stat_index = (STAT)i;
			return;
		}
	}

	for (unsigned i=0; i<ELEMENTS.size(); ++i) {
		if (bonus_str == ELEMENTS[i].id + "_resist") {
			bdata.resist_index = i;
			return;
		}
	}

	if (bonus_str == "physical") {
		bdata.base_index = 0;
		return;
	}
	else if (bonus_str == "mental") {
		bdata.base_index = 1;
		return;
	}
	else if (bonus_str == "offense") {
		bdata.base_index = 2;
		return;
	}
	else if (bonus_str == "defense") {
		bdata.base_index = 3;
		return;
	}

	infile.error("ItemManager: Unknown bonus type '%s'.", bonus_str.c_str());
}

void ItemManager::getBonusString(std::stringstream& ss, BonusData* bdata) {
#ifndef EDITOR
	if (bdata->value > 0)
		ss << "+" << bdata->value;
	else
		ss << bdata->value;

	if (bdata->stat_index != -1) {
		if (STAT_PERCENT[bdata->stat_index])
			ss << "%";

		ss << " " << STAT_NAME[bdata->stat_index];
	}
	else if (bdata->resist_index != -1) {
		ss << "% " << msg->get("%s Resistance", ELEMENTS[bdata->resist_index].name.c_str());
	}
	else if (bdata->base_index != -1) {
		if (bdata->base_index == 0)
			ss << " " << msg->get("Physical");
		else if (bdata->base_index == 1)
			ss << " " << msg->get("Mental");
		else if (bdata->base_index == 2)
			ss << " " << msg->get("Offense");
		else if (bdata->base_index == 3)
			ss << " " << msg->get("Defense");
	}
#endif
}

void ItemManager::playSound(int item, const Point& pos) {
#ifndef EDITOR
	snd->play(items[item].sfx_id, GLOBAL_VIRTUAL_CHANNEL, pos, false);
#endif
}
#ifndef EDITOR
TooltipData ItemManager::getShortTooltip(ItemStack stack) {
	std::stringstream ss;
	TooltipData tip;

	if (stack.empty()) return tip;

	// name
	if (stack.quantity > 1) {
		ss << stack.quantity << " " << getItemName(stack.item);
	}
	else {
		ss << getItemName(stack.item);
	}
	tip.addText(ss.str(), getItemColor(stack.item));

	return tip;
}

/**
 * Create detailed tooltip showing all relevant item info
 */
TooltipData ItemManager::getTooltip(ItemStack stack, StatBlock *stats, int context) {
	TooltipData tip;

	if (stack.empty()) return tip;

	Color color = getItemColor(stack.item);

	// name
	std::stringstream ss;
	if (stack.quantity == 1)
		ss << getItemName(stack.item);
	else
		ss << getItemName(stack.item) << " (" << stack.quantity << ")";
	tip.addText(ss.str(), color);

	// quest item
	if (items[stack.item].quest_item) {
		tip.addText(msg->get("Quest Item"), color_bonus);
	}

	// only show the name of the currency item
	if (stack.item == CURRENCY_ID)
		return tip;

	// flavor text
	if (items[stack.item].flavor != "") {
		tip.addText(substituteVarsInString(items[stack.item].flavor, pc), color_flavor);
	}

	// level
	if (items[stack.item].level != 0) {
		tip.addText(msg->get("Level %d", items[stack.item].level));
	}

	// type
	if (items[stack.item].type != "") {
		tip.addText(msg->get(getItemType(items[stack.item].type)));
	}

	// item quality text for colorblind users
	if (COLORBLIND && items[stack.item].quality != "") {
		color = color_normal;
		for (size_t i=0; i<item_qualities.size(); ++i) {
			if (item_qualities[i].id == items[stack.item].quality) {
				tip.addText(msg->get("Quality: %s", msg->get(item_qualities[i].name)), color);
				break;
			}
		}
	}

	// damage
	if (items[stack.item].dmg_melee_max > 0) {
		if (items[stack.item].dmg_melee_min < items[stack.item].dmg_melee_max)
			tip.addText(msg->get("Melee damage: %d-%d", items[stack.item].dmg_melee_min, items[stack.item].dmg_melee_max));
		else
			tip.addText(msg->get("Melee damage: %d", items[stack.item].dmg_melee_max));
	}
	if (items[stack.item].dmg_ranged_max > 0) {
		if (items[stack.item].dmg_ranged_min < items[stack.item].dmg_ranged_max)
			tip.addText(msg->get("Ranged damage: %d-%d", items[stack.item].dmg_ranged_min, items[stack.item].dmg_ranged_max));
		else
			tip.addText(msg->get("Ranged damage: %d", items[stack.item].dmg_ranged_max));
	}
	if (items[stack.item].dmg_ment_max > 0) {
		if (items[stack.item].dmg_ment_min < items[stack.item].dmg_ment_max)
			tip.addText(msg->get("Mental damage: %d-%d", items[stack.item].dmg_ment_min, items[stack.item].dmg_ment_max));
		else
			tip.addText(msg->get("Mental damage: %d", items[stack.item].dmg_ment_max));
	}

	// absorb
	if (items[stack.item].abs_max > 0) {
		if (items[stack.item].abs_min < items[stack.item].abs_max)
			tip.addText(msg->get("Absorb: %d-%d", items[stack.item].abs_min, items[stack.item].abs_max));
		else
			tip.addText(msg->get("Absorb: %d", items[stack.item].abs_max));
	}

	// bonuses
	unsigned bonus_counter = 0;
	while (bonus_counter < items[stack.item].bonus.size()) {
		ss.str("");

		BonusData* bdata = &items[stack.item].bonus[bonus_counter];

		if (bdata->is_speed) {
			ss << msg->get("%d%% Speed", bdata->value);
			if (bdata->value >= 100) color = color_bonus;
			else color = color_penalty;
		}
		else {
			if (bdata->value > 0) {
				color = color_bonus;
			}
			else {
				color = color_penalty;
			}

			getBonusString(ss, bdata);
		}

		tip.addText(ss.str(), color);
		bonus_counter++;
	}

	// power
	if (items[stack.item].power_desc != "") {
		tip.addText(items[stack.item].power_desc, color_bonus);
	}

	// level requirement
	if (items[stack.item].requires_level > 0) {
		if (stats->level < items[stack.item].requires_level) color = color_requirements_not_met;
		else color = color_normal;
		tip.addText(msg->get("Requires Level %d", items[stack.item].requires_level), color);
	}

	// base stat requirement
	for (unsigned i=0; i<items[stack.item].req_stat.size(); ++i) {
		if (items[stack.item].req_val[i] > 0) {
			if (items[stack.item].req_stat[i] == REQUIRES_PHYS) {
				if (stats->get_physical() < items[stack.item].req_val[i]) color = color_requirements_not_met;
				else color = color_normal;
				tip.addText(msg->get("Requires Physical %d", items[stack.item].req_val[i]), color);
			}
			else if (items[stack.item].req_stat[i] == REQUIRES_MENT) {
				if (stats->get_mental() < items[stack.item].req_val[i]) color = color_requirements_not_met;
				else color = color_normal;
				tip.addText(msg->get("Requires Mental %d", items[stack.item].req_val[i]), color);
			}
			else if (items[stack.item].req_stat[i] == REQUIRES_OFF) {
				if (stats->get_offense() < items[stack.item].req_val[i]) color = color_requirements_not_met;
				else color = color_normal;
				tip.addText(msg->get("Requires Offense %d", items[stack.item].req_val[i]), color);
			}
			else if (items[stack.item].req_stat[i] == REQUIRES_DEF) {
				if (stats->get_defense() < items[stack.item].req_val[i]) color = color_requirements_not_met;
				else color = color_normal;
				tip.addText(msg->get("Requires Defense %d", items[stack.item].req_val[i]), color);
			}
		}
	}

	// requires class
	if (items[stack.item].requires_class != "") {
		if (items[stack.item].requires_class != stats->character_class) color = color_requirements_not_met;
		else color = color_normal;
		tip.addText(msg->get("Requires Class: %s", msg->get(items[stack.item].requires_class)), color);
	}

	// buy or sell price
	if (items[stack.item].getPrice() > 0 && stack.item != CURRENCY_ID) {

		int price_per_unit;
		if (context == VENDOR_BUY) {
			price_per_unit = items[stack.item].getPrice();
			if (stats->currency < price_per_unit) color = color_requirements_not_met;
			else color = color_normal;
			if (items[stack.item].max_quantity <= 1)
				tip.addText(msg->get("Buy Price: %d %s", price_per_unit, CURRENCY), color);
			else
				tip.addText(msg->get("Buy Price: %d %s each", price_per_unit, CURRENCY), color);
		}
		else if (context == VENDOR_SELL) {
			price_per_unit = items[stack.item].getSellPrice();
			if (stats->currency < price_per_unit) color = color_requirements_not_met;
			else color = color_normal;
			if (items[stack.item].max_quantity <= 1)
				tip.addText(msg->get("Buy Price: %d %s", price_per_unit, CURRENCY), color);
			else
				tip.addText(msg->get("Buy Price: %d %s each", price_per_unit, CURRENCY), color);
		}
		else if (context == PLAYER_INV) {
			price_per_unit = items[stack.item].getSellPrice();
			if (price_per_unit == 0) price_per_unit = 1;
			if (items[stack.item].max_quantity <= 1)
				tip.addText(msg->get("Sell Price: %d %s", price_per_unit, CURRENCY));
			else
				tip.addText(msg->get("Sell Price: %d %s each", price_per_unit, CURRENCY));
		}
	}

	if (items[stack.item].set > 0) {
		// item set bonuses
		ItemSet set = item_sets[items[stack.item].set];
		bonus_counter = 0;

		tip.addText("\n" + msg->get("Set: ") + msg->get(item_sets[items[stack.item].set].name), set.color);

		while (bonus_counter < set.bonus.size()) {
			ss.str("");

			Set_bonus* bdata = &set.bonus[bonus_counter];

			ss << msg->get("%d items: ", bdata->requirement);

			if (bdata->is_speed) {
				ss << msg->get("%d%% Speed", bdata->value);
			}
			else {
				getBonusString(ss, bdata);
			}

			tip.addText(ss.str(), set.color);
			bonus_counter++;
		}
	}

	return tip;
}
#endif
/**
 * Check requirements on an item
 */
bool ItemManager::requirementsMet(const StatBlock *stats, int item) {
#ifndef EDITOR
	if (!stats) return false;

	// level
    if (items[item].requires_level > 0 && stats->level < items[item].requires_level) {
		return false;
	}

	// base stats
    for (unsigned i=0; i < items[item].req_stat.size(); ++i) {
        if (items[item].req_stat[i] == REQUIRES_PHYS) {
            if (stats->get_physical() < items[item].req_val[i])
				return false;
		}
        if (items[item].req_stat[i] == REQUIRES_MENT) {
            if (stats->get_mental() < items[item].req_val[i])
				return false;
		}
        if (items[item].req_stat[i] == REQUIRES_OFF) {
            if (stats->get_offense() < items[item].req_val[i])
				return false;
		}
        if (items[item].req_stat[i] == REQUIRES_DEF) {
            if (stats->get_defense() < items[item].req_val[i])
				return false;
		}
	}

	// class
    if (items[item].requires_class != "" && items[item].requires_class != stats->character_class) {
		return false;
	}
#else
	// otherwise there is no requirement, so it is usable.
	return true;
#endif
}

ItemManager::~ItemManager() {
#ifdef EDITOR
    for (int i = 0; i < items.size(); i++)
    {
        delete items[i];
        items[i] = NULL;
    }
#endif
}

/**
 * Compare two item stack to be able to sorting them on their item_id in the vendors' stock
 */
bool ItemStack::operator > (const ItemStack &param) const {
	if (item == 0 && param.item > 0) {
		// Make the empty slots the last while sorting
		return true;
	}
	else if (item > 0 && param.item == 0) {
		// Make the empty slots the last while sorting
		return false;
	}
	else {
		return item > param.item;
	}
}

/**
 * Check if an item stack is empty and provide some error checking
 */
bool ItemStack::empty() {
	if (item != 0 && quantity > 0) {
		return false;
	}
	else if (item == 0 && quantity != 0) {
		logError("ItemStack: Item id is zero, but quantity is %d.", quantity);
		quantity = 0;
	}
	else if (item != 0 && quantity == 0) {
		logError("ItemStack: Item id is %d, but quantity is zero.", item);
		item = 0;
	}
	return true;
}

void ItemStack::clear() {
	item = 0;
	quantity = 0;
}

#ifndef EDITOR
int Item::getPrice() {
    return price + (price_per_level * (pc->stats.level - 1));
}

int Item::getSellPrice() {
    int new_price = 0;
    if (price_sell != 0)
        new_price = price_sell;
    else
        new_price = static_cast<int>(static_cast<float>(getPrice()) * VENDOR_RATIO);
    if (new_price == 0) new_price = 1;

    return new_price;
}
#endif
