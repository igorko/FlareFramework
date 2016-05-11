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
#include "API/Stats.h"

EditorItemManager::EditorItemManager(const std::string& modpath)
{
    items = QVector<Item*>();
    setStatNames();
    loadMiscTypes();
    loadItems(modpath + "items/items.txt", false);
    if (!items.empty()) shrinkItems();
    else items.resize(1);

    loadTypes(modpath + "items/types.txt", false);
    loadQualities(modpath + "items/qualities.txt", false);
}

EditorItemManager::~EditorItemManager()
{}

/**
 * This method is a collection of misc code parts that are taken from flare-engine.
 */

void EditorItemManager::loadMiscTypes()
{
    FileParser infile;
    // @CLASS MenuInventory|Description of menus/inventory.txt
    if (infile.open("menus/inventory.txt")) {
        while(infile.next()) {
            // @ATTR equipment_slot|x (integer), y (integer), size (integer), slot_type (string)|Position and item type of an equipment slot.
            if(infile.key == "equipment_slot") {
                Rect area;
                Point pos;

                pos.x = area.x = popFirstInt(infile.val);
                pos.y = area.y = popFirstInt(infile.val);
                area.w = area.h = popFirstInt(infile.val);

                slot_type.push_back(popFirstString(infile.val));
            }
        }
        infile.close();
    }

    // @CLASS Settings: Elements|Description of engine/elements.txt
    if (infile.open("engine/elements.txt")) {
        while (infile.next()) {
            if (infile.new_section) {
                if (infile.section == "element") {
                    // check if the previous element and remove it if there is no identifier
                    if (!ELEMENTS.empty() && ELEMENTS.back().id == "") {
                        ELEMENTS.pop_back();
                    }
                    ELEMENTS.resize(ELEMENTS.size()+1);
                }
            }

            if (ELEMENTS.empty() || infile.section != "element")
                continue;

            // @ATTR element.id|string|An identifier for this element.
            if (infile.key == "id") ELEMENTS.back().id = infile.val;
            // @ATTR element.name|string|The displayed name of this element.
            else if (infile.key == "name") ELEMENTS.back().name = infile.val;

            else infile.error("Settings: '%s' is not a valid key.", infile.key.c_str());
        }
        infile.close();

        // check if the last element and remove it if there is no identifier
        if (!ELEMENTS.empty() && ELEMENTS.back().id == "") {
            ELEMENTS.pop_back();
        }
    }

    // @CLASS Settings: Equip flags|Description of engine/equip_flags.txt
    if (infile.open("engine/equip_flags.txt")) {
        while (infile.next()) {
            if (infile.new_section) {
                if (infile.section == "flag") {
                    // check if the previous flag and remove it if there is no identifier
                    if (!EQUIP_FLAGS.empty() && EQUIP_FLAGS.back().id == "") {
                        EQUIP_FLAGS.pop_back();
                    }
                    EQUIP_FLAGS.resize(EQUIP_FLAGS.size()+1);
                }
            }

            if (EQUIP_FLAGS.empty() || infile.section != "flag")
                continue;

            // @ATTR flag.id|string|An identifier for this equip flag.
            if (infile.key == "id") EQUIP_FLAGS.back().id = infile.val;
            // @ATTR flag.name|string|The displayed name of this equip flag.
            else if (infile.key == "name") EQUIP_FLAGS.back().name = infile.val;

            else infile.error("Settings: '%s' is not a valid key.", infile.key.c_str());
        }
        infile.close();

        // check if the last flag and remove it if there is no identifier
        if (!EQUIP_FLAGS.empty() && EQUIP_FLAGS.back().id == "") {
            EQUIP_FLAGS.pop_back();
        }
    }

    // @CLASS Settings: Classes|Description of engine/classes.txt
    if (infile.open("engine/classes.txt")) {
        while (infile.next()) {
            if (infile.new_section) {
                if (infile.section == "class") {
                    // check if the previous class and remove it if there is no name
                    if (!HERO_CLASSES.empty() && HERO_CLASSES.back().name == "") {
                        HERO_CLASSES.pop_back();
                    }
                    HERO_CLASSES.resize(HERO_CLASSES.size()+1);
                }
            }

            if (HERO_CLASSES.empty() || infile.section != "class")
                continue;

            if (!HERO_CLASSES.empty()) {
                // @ATTR name|string|The displayed name of this class.
                if (infile.key == "name") HERO_CLASSES.back().name = infile.val;
                // @ATTR description|string|A description of this class.
                else if (infile.key == "description") HERO_CLASSES.back().description = infile.val;
                // @ATTR currency|integer|The amount of currency this class will start with.
                else if (infile.key == "currency") HERO_CLASSES.back().currency = toInt(infile.val);
                // @ATTR equipment|item (integer), ...|A list of items that are equipped when starting with this class.
                else if (infile.key == "equipment") HERO_CLASSES.back().equipment = infile.val;
                // @ATTR physical|integer|Class starts with this physical stat.
                else if (infile.key == "physical") HERO_CLASSES.back().physical = toInt(infile.val);
                // @ATTR mental|integer|Class starts with this mental stat.
                else if (infile.key == "mental") HERO_CLASSES.back().mental = toInt(infile.val);
                // @ATTR offense|integer|Class starts with this offense stat.
                else if (infile.key == "offense") HERO_CLASSES.back().offense = toInt(infile.val);
                // @ATTR defense|integer|Class starts with this defense stat.
                else if (infile.key == "defense") HERO_CLASSES.back().defense = toInt(infile.val);

                else if (infile.key == "powers") {
                    // @ATTR powers|power (integer), ...|A list of powers that are unlocked when starting this class.
                    std::string power;
                    while ( (power = infile.nextValue()) != "") {
                        HERO_CLASSES.back().powers.push_back(toInt(power));
                    }
                }
                else if (infile.key == "campaign") {
                    // @ATTR campaign|status (string), ...|A list of campaign statuses that are set when starting this class.
                    std::string status;
                    while ( (status = infile.nextValue()) != "") {
                        HERO_CLASSES.back().statuses.push_back(status);
                    }
                }
                // @ATTR power_tree|string|Power tree that will be loaded by MenuPowers
                else if (infile.key == "power_tree") HERO_CLASSES.back().power_tree = infile.val;

                else infile.error("Settings: '%s' is not a valid key.", infile.key.c_str());
            }
        }
        infile.close();

        // check if the last class and remove it if there is no name
        if (!HERO_CLASSES.empty() && HERO_CLASSES.back().name == "") {
            HERO_CLASSES.pop_back();
        }
    }

    // load foot-step definitions
    // @CLASS Avatar: Step sounds|Description of items/step_sounds.txt
    if (infile.open("items/step_sounds.txt", true, "")) {
        while (infile.next()) {
            if (infile.key == "id") {
                // @ATTR id|string|An identifier name for a set of step sounds.
                step_def.push_back(Step_sfx());
                step_def.back().id = infile.val;
            }

            if (step_def.empty()) continue;

            if (infile.key == "step") {
                // @ATTR step|string|Filename of a step sound effect.
                step_def.back().steps.push_back(infile.val);
            }
        }
        infile.close();
    }
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
    while (items[i]->name == "")
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
        for (int i = 1;i<items.size();i++) {

            if (items[i]->name == "") continue;

            outfile << "[item]" << "\n";

            outfile << "id=" << i << "\n";

            outfile << "name=" << items[i]->name.toStdString() << "\n";

            if (items[i]->flavor != "")
                outfile << "flavor=" << items[i]->flavor.toStdString() << "\n";

            if (items[i]->level > 0)
                outfile << "level=" << items[i]->level << "\n";

            if (items[i]->icon >= 0)
                outfile << "icon=" << items[i]->icon << "\n";

            if (items[i]->book != "")
                outfile << "book=" << items[i]->book.toStdString() << "\n";

            if (items[i]->quality != "") {
                outfile << "quality=" << items[i]->quality.toStdString() << "\n";
            }

            outfile << "item_type=" << items[i]->type.toStdString() << "\n";

            if (items[i]->equip_flags.size() > 0)
            {
                outfile << "equip_flags=";
                for (int k = 0;k < items[i]->equip_flags.size(); k++) {
                    outfile << items[i]->equip_flags[k].toStdString();

                    if (items[i]->equip_flags.size() > 1 && k != items[i]->equip_flags.size() - 1)
                        outfile << ",";
                }
                outfile << "\n";
            }

            if (items[i]->dmg_melee_min > 0 || items[i]->dmg_melee_max > 0)
                outfile << "dmg_melee=" << items[i]->dmg_melee_min << "," << items[i]->dmg_melee_max << "\n";

            if (items[i]->dmg_ranged_min > 0 || items[i]->dmg_ranged_max > 0)
                outfile << "dmg_ranged=" << items[i]->dmg_ranged_min << "," << items[i]->dmg_ranged_max << "\n";

            if (items[i]->dmg_ment_min > 0 || items[i]->dmg_ment_max > 0)
                outfile << "dmg_ment=" << items[i]->dmg_ment_min << "," << items[i]->dmg_ment_max << "\n";

            if (items[i]->abs_min > 0 || items[i]->abs_max > 0) {
                if (items[i]->abs_min == items[i]->abs_max)
                    outfile << "abs=" << items[i]->abs_min << "\n";
                else
                    outfile << "abs=" << items[i]->abs_min << "," << items[i]->abs_max << "\n";
            }

            for (int k = 0;k < items[i]->req_stat.size(); k++) {
                if (items[i]->req_stat[k] == REQUIRES_PHYS)
                    outfile << "requires_stat=physical," << items[i]->req_val[k] << "\n";
                else if (items[i]->req_stat[k] == REQUIRES_MENT)
                    outfile << "requires_stat=mental," << items[i]->req_val[k] << "\n";
                else if (items[i]->req_stat[k] == REQUIRES_OFF)
                    outfile << "requires_stat=offense," << items[i]->req_val[k] << "\n";
                else if (items[i]->req_stat[k] == REQUIRES_DEF)
                    outfile << "requires_stat=defense," << items[i]->req_val[k] << "\n";
            }

            if (items[i]->requires_class != "")
                outfile << "requires_class=" << items[i]->requires_class.toStdString() << "\n";

            for (int k = 0;k < items[i]->bonus.size(); k++) {
                std::string bonus_str;
                if (items[i]->bonus[k].stat_index != -1)
                {
                    bonus_str = STAT_KEY[items[i]->bonus[k].stat_index];
                }
                else if (items[i]->bonus[k].is_speed)
                {
                    bonus_str = "speed";
                }
                else if (items[i]->bonus[k].resist_index != -1)
                {
                    bonus_str = ELEMENTS[items[i]->bonus[k].resist_index].id + "_resist";
                }
                else if (items[i]->bonus[k].base_index != -1)
                {
                    if (items[i]->bonus[k].base_index == 0)
                        bonus_str = "physical";
                    else if (items[i]->bonus[k].base_index == 1)
                       bonus_str = "mental";
                    else if (items[i]->bonus[k].base_index == 2)
                        bonus_str = "offense";
                    else if (items[i]->bonus[k].base_index == 3)
                        bonus_str = "defense";
                }
                outfile << "bonus=" << bonus_str << "," << items[i]->bonus[k].value << "\n";
            }

            if (items[i]->sfx != "")
                outfile << "soundfx=" << items[i]->sfx.toStdString() << "\n";

            if (items[i]->gfx != "")
                outfile << "gfx=" << items[i]->gfx.toStdString() << "\n";

            for (int k = 0;k < items[i]->loot_animation.size(); k++) {
                outfile << "loot_animation=" << items[i]->loot_animation[k].name;

                if (items[i]->loot_animation[k].low != 0)
                    outfile << "," << items[i]->loot_animation[k].low;
                if (items[i]->loot_animation[k].high != 0)
                    outfile << "," << items[i]->loot_animation[k].high;

                outfile << "\n";
            }

            if (items[i]->power > 0)
                outfile << "power=" << items[i]->power << "\n";

            for (int k = 0;k < items[i]->replace_power.size(); k++) {
                outfile << "replace_power=" << items[i]->replace_power[k].x() << "," << items[i]->replace_power[k].y() << "\n";
            }

            if (items[i]->power_desc != "")
                outfile << "power_desc=" << items[i]->power_desc.toStdString() << "\n";

            if (items[i]->price > 0)
                outfile << "price=" << items[i]->price << "\n";

            if (items[i]->price_sell > 0)
               outfile << "price_sell=" << items[i]->price_sell << "\n";

            if (items[i]->max_quantity > 1)
                outfile << "max_quantity=" << items[i]->max_quantity << "\n";

            if (items[i]->pickup_status != "")
                outfile << "pickup_status=" << items[i]->pickup_status.toStdString() << "\n";

            if (items[i]->stepfx != "")
                outfile << "stepfx=" << items[i]->stepfx.toStdString() << "\n";

            if (items[i]->disable_slots.size() > 0)
            {
                outfile << "disable_slots=";
                for (int k = 0;k < items[i]->disable_slots.size(); k++) {
                    outfile << items[i]->disable_slots[k].toStdString();

                    if (items[i]->disable_slots.size() > 1 && k != items[i]->disable_slots.size() - 1)
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
