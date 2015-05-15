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


EditorItemManager::EditorItemManager(const std::string& filename) {
	items = vector<Item>();

	load(filename);
	if (!items.empty()) shrinkItems();
	else items.resize(1);
}

EditorItemManager::~EditorItemManager()
{}

/**
 * Load a specific items file
 *
 * @param filename The full path and name of the file to load
 */
void EditorItemManager::load(const std::string& filename) {
	FileParser infile;
	if (!infile.open(filename)) {
		fprintf(stderr, "Unable to open %s!\n", filename.c_str());
		return;
	}

	int id = 0;
	bool id_line = false;
	while (infile.next()) {
		if (infile.key == "id") {
			id_line = true;
			id = toInt(infile.val);
			if (id > 0 && id >= (int)items.size()) {
				// *2 to amortize the resizing to O(log(n)).
				items.resize((2*id) + 1);
			}
		} else id_line = false;

		if (id < 1) {
			if (id_line) fprintf(stderr, "Item index out of bounds 1-%d, skipping\n", INT_MAX);
			continue;
		}
		if (id_line) continue;

		if (infile.key == "name")
			items[id].name = infile.val;
		else if (infile.key == "level")
			items[id].level = toInt(infile.val);
		else if (infile.key == "icon") {
			items[id].icon_small = toInt(infile.nextValue());
			items[id].icon_large = toInt(infile.nextValue());
		}
		else if (infile.key == "quality") {
			if (infile.val == "low")
				items[id].quality = ITEM_QUALITY_LOW;
			else if (infile.val == "high")
				items[id].quality = ITEM_QUALITY_HIGH;
			else if (infile.val == "epic")
				items[id].quality = ITEM_QUALITY_EPIC;
		}
		else if (infile.key == "item_type") {
				items[id].type = infile.val;
		}
		else if (infile.key == "dmg_melee") {
			items[id].dmg_melee_min = toInt(infile.nextValue());
			if (infile.val.length() > 0)
				items[id].dmg_melee_max = toInt(infile.nextValue());
			else
				items[id].dmg_melee_max = items[id].dmg_melee_min;
		}
		else if (infile.key == "dmg_ranged") {
			items[id].dmg_ranged_min = toInt(infile.nextValue());
			if (infile.val.length() > 0)
				items[id].dmg_ranged_max = toInt(infile.nextValue());
			else
				items[id].dmg_ranged_max = items[id].dmg_ranged_min;
		}
		else if (infile.key == "dmg_ment") {
			items[id].dmg_ment_min = toInt(infile.nextValue());
			if (infile.val.length() > 0)
				items[id].dmg_ment_max = toInt(infile.nextValue());
			else
				items[id].dmg_ment_max = items[id].dmg_ment_min;
		}
		else if (infile.key == "abs") {
			items[id].abs_min = toInt(infile.nextValue());
			if (infile.val.length() > 0)
				items[id].abs_max = toInt(infile.nextValue());
			else
				items[id].abs_max = items[id].abs_min;
		}
		else if (infile.key == "req") {
			std::string s = infile.nextValue();
			if (s == "p")
				items[id].req_stat = REQUIRES_PHYS;
			else if (s == "m")
				items[id].req_stat = REQUIRES_MENT;
			else if (s == "o")
				items[id].req_stat = REQUIRES_OFF;
			else if (s == "d")
				items[id].req_stat = REQUIRES_DEF;
			items[id].req_val = toInt(infile.nextValue());
		}
		else if (infile.key == "bonus") {
			items[id].bonus_stat.push_back(infile.nextValue());
			items[id].bonus_val.push_back(toInt(infile.nextValue()));
		}
		else if (infile.key == "sfx") {
			if (infile.val == "book")
				items[id].sfx = SFX_BOOK;
			else if (infile.val == "cloth")
				items[id].sfx = SFX_CLOTH;
			else if (infile.val == "coins")
				items[id].sfx = SFX_COINS;
			else if (infile.val == "gem")
				items[id].sfx = SFX_GEM;
			else if (infile.val == "leather")
				items[id].sfx = SFX_LEATHER;
			else if (infile.val == "metal")
				items[id].sfx = SFX_METAL;
			else if (infile.val == "page")
				items[id].sfx = SFX_PAGE;
			else if (infile.val == "maille")
				items[id].sfx = SFX_MAILLE;
			else if (infile.val == "object")
				items[id].sfx = SFX_OBJECT;
			else if (infile.val == "heavy")
				items[id].sfx = SFX_HEAVY;
			else if (infile.val == "wood")
				items[id].sfx = SFX_WOOD;
			else if (infile.val == "potion")
				items[id].sfx = SFX_POTION;
		}
		else if (infile.key == "gfx")
			items[id].gfx = infile.val;
		else if (infile.key == "loot_animation")
			items[id].loot_animation = infile.val;
		else if (infile.key == "power") {
			if (toInt(infile.val) > 0) {
				items[id].power = toInt(infile.val);
			}
			else fprintf(stderr, "Power index inside item %d definition out of bounds 1-%d, skipping item\n", id, INT_MAX);
		}
		else if (infile.key == "power_mod")
			items[id].power_mod = toInt(infile.val);
		else if (infile.key == "power_desc")
			items[id].power_desc = infile.val;
		else if (infile.key == "price")
			items[id].price = toInt(infile.val);
		else if (infile.key == "price_sell")
			items[id].price_sell = toInt(infile.val);
		else if (infile.key == "max_quantity")
			items[id].max_quantity = toInt(infile.val);
		else if (infile.key == "rand_loot")
			items[id].rand_loot = toInt(infile.val);
		else if (infile.key == "rand_vendor")
			items[id].rand_vendor = toInt(infile.val);
		else if (infile.key == "pickup_status")
			items[id].pickup_status = infile.val;
		else if (infile.key == "stepfx")
			items[id].stepfx = infile.val;
		else if (infile.key == "class") {
			string classname = infile.nextValue();
			while (classname != "") {
				items[id].classname.push_back(classname);
				classname = infile.nextValue();
			}
		}

	}
	infile.close();
}

void EditorItemManager::loadTypes(const std::string& filename) {
	FileParser infile;
	std::string type,description;
	type = description = "";

	if (infile.open(filename)) {
		while (infile.next()) {
			if (infile.key == "name") type = infile.val;
			else if (infile.key == "description") description = infile.val;

			if (type != "" && description != "") {
				item_types[type] = description;
				type = description = "";
			}
		}
		infile.close();
	} else fprintf(stderr, "Unable to open %s!\n", filename.c_str());
}


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

			outfile << "item_type=" << items[i].type << "\n";

			outfile << "level=" << items[i].level << "\n";
/*
			if (items[i].req_stat == REQUIRES_PHYS && items[i].req_val > 0)
				outfile << "req=p," << items[i].req_val << "\n";
			else if (items[i].req_stat == REQUIRES_MENT && items[i].req_val > 0)
				outfile << "req=m," << items[i].req_val << "\n";
			else if (items[i].req_stat == REQUIRES_OFF && items[i].req_val > 0)
				outfile << "req=o," << items[i].req_val << "\n";
			else if (items[i].req_stat == REQUIRES_DEF && items[i].req_val > 0)
				outfile << "req=d," << items[i].req_val << "\n";
*/
			if (items[i].dmg_melee_min > 0 || items[i].dmg_melee_max > 0)
				outfile << "dmg_melee=" << items[i].dmg_melee_min << "," << items[i].dmg_melee_max << "\n";

			if (items[i].dmg_ranged_min > 0 || items[i].dmg_ranged_max > 0)
				outfile << "dmg_ranged=" << items[i].dmg_ranged_min << "," << items[i].dmg_ranged_max << "\n";

			if (items[i].dmg_ment_min > 0 || items[i].dmg_ment_max > 0)
				outfile << "dmg_ment=" << items[i].dmg_ment_min << "," << items[i].dmg_ment_max << "\n";

			if (items[i].abs_min > 0 || items[i].abs_max > 0)
				outfile << "abs=" << items[i].abs_min << "," << items[i].abs_max << "\n";

			if (items[i].quality >= 0)
				outfile << "quality=" << items[i].quality << "\n";

			if (items[i].icon_small >= 0)
				outfile << "icon=" << items[i].icon_small << "\n";

			if (items[i].sfx >= 0)
				outfile << "sfx=" << items[i].sfx << "\n";

			if (items[i].gfx != "")
				outfile << "gfx=" << items[i].gfx << "\n";

			if (items[i].loot_animation != "")
				outfile << "loot_animation=" << items[i].loot_animation << "\n";

			if (items[i].power > 0)
				outfile << "power=" << items[i].power << "\n";

			if (items[i].power_desc != "")
				outfile << "power_desc=" << items[i].power_desc << "\n";

			if (items[i].power_mod > 0)
				outfile << "power_mod=" << items[i].power_mod << "\n";

			if (items[i].price > 0)
				outfile << "price=" << items[i].price << "\n";

			if (items[i].price_sell > 0)
			   outfile << "price_sell=" << items[i].price_sell << "\n";

			if (items[i].max_quantity > 1)
				outfile << "max_quantity=" << items[i].max_quantity << "\n";

			if (items[i].rand_vendor > 1)
				outfile << "rand_vendor=" << items[i].rand_vendor << "\n";

			if (items[i].rand_loot > 1)
				outfile << "rand_loot=" << items[i].rand_loot << "\n";

			if (items[i].classname.size() > 0) {
				outfile << "class=";
				for (unsigned k = 0;k<items[i].classname.size()-1;k++) {
					outfile << items[i].classname[k] << ",";
				}
				outfile << items[i].classname.back();
				outfile << "\n";
			}

			if (items[i].bonus_stat.size() != items[i].bonus_val.size()) {
				if (items[i].bonus_stat.size() > items[i].bonus_val.size())
					items[i].bonus_val.resize(items[i].bonus_stat.size());
				else
					items[i].bonus_stat.resize(items[i].bonus_val.size());
			}
			for (unsigned k = 0;k<items[i].bonus_stat.size();k++) {
				outfile << "bonus=" << items[i].bonus_stat[k] << "," << items[i].bonus_val[k] << "\n";
			}

			if (items[i].pickup_status != "")
				outfile << "pickup_status=" << items[i].pickup_status << "\n";

			if (items[i].stepfx != "")
				outfile << "stepfx=" << items[i].stepfx << "\n";

			outfile << std::endl;
		}

		if (outfile.bad()) fprintf(stderr, "Unable to save the file. No write access or disk is full!\n");
		outfile.close();
	}

}
