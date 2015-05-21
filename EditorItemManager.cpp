/*
Copyright © 2012-2015 Igor Paliychuk

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
 * class EditorItemManager
 */

#include "EditorItemManager.h"
#include "API/UtilsParsing.h"


EditorItemManager::EditorItemManager(const std::string& modpath) {
	items = std::vector<Item>();

	loadItems(modpath + "items/items.txt", false);
	if (!items.empty()) shrinkItems();
	else items.resize(1);

	loadTypes(modpath + "items/types.txt", false);
}

EditorItemManager::~EditorItemManager()
{}

/**
 * Shrinks the items vector to the absolute needed size.
 *
 * While loading the items, the item vector grows dynamically. To have
 * no much time overhead for reallocating the vector, a new reallocation
 * is twice as large as the needed item id, which means in the worst case
 * the item vector was reallocated for loading the last element, so the
 * vector is twice as large as needed. This memory is definitly not used,
 * so we can free it.
 */
void EditorItemManager::shrinkItems() {
	unsigned i = items.size() - 1;
	while (items[i].name == "")
		i--;

	items.resize(i + 1);
}

/**
 * Save a specific items file
 *
 * @param filename The full path and name of the file to save
 */
void EditorItemManager::save(const std::string& filename) {

	std::ofstream outfile;

	outfile.open(filename.c_str(), std::ios::out);

	if (outfile.is_open()) {
		for (unsigned i = 1;i<items.size();i++) {

			if (items[i].name == "") continue;

			outfile << "[item]" << "\n";

			outfile << "id=" << i << "\n";

			outfile << "name=" << items[i].name << "\n";

			if (items[i].flavor != "")
				outfile << "flavor=" << items[i].flavor << "\n";

			if (items[i].level > 0)
				outfile << "level=" << items[i].level << "\n";

			if (items[i].icon >= 0)
				outfile << "icon=" << items[i].icon << "\n";

			if (items[i].book != "")
				outfile << "book=" << items[i].book << "\n";

			if (items[i].quality != ITEM_QUALITY_NORMAL) {

				std::string  quality = "";
				if (items[i].quality == ITEM_QUALITY_LOW)
					quality = "low";
				else if (items[i].quality == ITEM_QUALITY_HIGH)
					quality = "high";
				else if (items[i].quality == ITEM_QUALITY_EPIC)
					quality = "epic";

				outfile << "quality=" << quality << "\n";
			}

			outfile << "item_type=" << items[i].type << "\n";

			if (items[i].equip_flags.size() > 0)
			{
				outfile << "equip_flags=";
				for (unsigned k = 0;k < items[i].equip_flags.size(); k++) {
					outfile << items[i].equip_flags[k];

					if (items[i].equip_flags.size() > 1 && k != items[i].equip_flags.size() - 1)
						outfile << ",";
				}
				outfile << "\n";
			}

			if (items[i].dmg_melee_min > 0 || items[i].dmg_melee_max > 0)
				outfile << "dmg_melee=" << items[i].dmg_melee_min << "," << items[i].dmg_melee_max << "\n";

			if (items[i].dmg_ranged_min > 0 || items[i].dmg_ranged_max > 0)
				outfile << "dmg_ranged=" << items[i].dmg_ranged_min << "," << items[i].dmg_ranged_max << "\n";

			if (items[i].dmg_ment_min > 0 || items[i].dmg_ment_max > 0)
				outfile << "dmg_ment=" << items[i].dmg_ment_min << "," << items[i].dmg_ment_max << "\n";

			if (items[i].abs_min > 0 || items[i].abs_max > 0) {
				if (items[i].abs_min == items[i].abs_max)
					outfile << "abs=" << items[i].abs_min << "\n";
				else
					outfile << "abs=" << items[i].abs_min << "," << items[i].abs_max << "\n";
			}

			for (unsigned k = 0;k < items[i].req_stat.size(); k++) {
				if (items[i].req_stat[k] == REQUIRES_PHYS)
					outfile << "requires_stat=physical," << items[i].req_val[k] << "\n";
				else if (items[i].req_stat[k] == REQUIRES_MENT)
					outfile << "requires_stat=mental," << items[i].req_val[k] << "\n";
				else if (items[i].req_stat[k] == REQUIRES_OFF)
					outfile << "requires_stat=offense," << items[i].req_val[k] << "\n";
				else if (items[i].req_stat[k] == REQUIRES_DEF)
					outfile << "requires_stat=defense," << items[i].req_val[k] << "\n";
			}

			if (items[i].requires_class != "")
				outfile << "requires_class=" << items[i].requires_class << "\n";

			// UNIMPLEMENTED: bonus
			//outfile << "bonus=" << "\n";

			if (items[i].sfx != "")
				outfile << "soundfx=" << items[i].sfx << "\n";

			if (items[i].gfx != "")
				outfile << "gfx=" << items[i].gfx << "\n";

			for (unsigned k = 0;k < items[i].loot_animation.size(); k++) {
				outfile << "loot_animation=" << items[i].loot_animation[k].name;

				if (items[i].loot_animation[k].low != 0)
					outfile << "," << items[i].loot_animation[k].low;
				if (items[i].loot_animation[k].high != 0)
					outfile << "," << items[i].loot_animation[k].high;

				outfile << "\n";
			}

			if (items[i].power > 0)
				outfile << "power=" << items[i].power << "\n";

			for (unsigned k = 0;k < items[i].replace_power.size(); k++) {
				outfile << "replace_power=" << items[i].replace_power[k].x << "," << items[i].replace_power[k].y << "\n";
			}

			if (items[i].power_desc != "")
				outfile << "power_desc=" << items[i].power_desc << "\n";

			if (items[i].price > 0)
				outfile << "price=" << items[i].price << "\n";

			if (items[i].price_sell > 0)
			   outfile << "price_sell=" << items[i].price_sell << "\n";

			if (items[i].max_quantity > 1)
				outfile << "max_quantity=" << items[i].max_quantity << "\n";

			if (items[i].pickup_status != "")
				outfile << "pickup_status=" << items[i].pickup_status << "\n";

			if (items[i].stepfx != "")
				outfile << "stepfx=" << items[i].stepfx << "\n";

			if (items[i].disable_slots.size() > 0)
			{
				outfile << "disable_slots=";
				for (unsigned k = 0;k < items[i].disable_slots.size(); k++) {
					outfile << items[i].disable_slots[k];

					if (items[i].disable_slots.size() > 1 && k != items[i].disable_slots.size() - 1)
						outfile << ",";
				}
				outfile << "\n";
			}

			outfile << std::endl;
		}
		if (outfile.bad()) fprintf(stderr, "Unable to save the file. No write access or disk is full!\n");
		outfile.close();
	}

}
