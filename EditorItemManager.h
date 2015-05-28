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

#ifndef EDITOR_ITEM_MANAGER_H
#define EDITOR_ITEM_MANAGER_H

#include "API/ItemManager.h"

class EditorItemManager : public ItemManager {
public:

	EditorItemManager(const std::string& modpath);
	~EditorItemManager();
	
	void shrinkItems();

	void save(const std::string& filename);

    std::vector<std::string> slot_type;
    std::vector<Step_sfx> step_def;

private:
	void loadMiscTypes();
};

#endif
