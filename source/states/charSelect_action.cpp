/*
*   This file is part of 3DEins
*   Copyright (C) 2019-2020 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, StackZ, TotallyNotGuy
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "charSelect_action.hpp"
#include "config.hpp"
#include <vector>

extern std::unique_ptr<Config> config;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

void CharSelect_Action::DrawStateTop(void) const {
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), "Select a character you want.", 390, 30);
	if (this->page == 1) {
		GFX::DrawPlayer(-5, 35, 1, 1, 0);
		GFX::DrawPlayer(95, 35, 1, 1, 1);
		GFX::DrawPlayer(195, 35, 1, 1, 2);
		GFX::DrawPlayer(295, 35, 1, 1, 3);
	} else if (this->page == 2) {
		GFX::DrawPlayer(-5, 35, 1, 1, 4);
		GFX::DrawPlayer(95, 35, 1, 1, 5);
		GFX::DrawPlayer(195, 35, 1, 1, 6);
		GFX::DrawPlayer(295, 35, 1, 1, 7);
	}
}

void CharSelect_Action::DrawStateBottom(void) const {
}

void CharSelect_Action::StateLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	// Page Switches.
	if (hDown & KEY_R) {
		if (this->page == 1) {
			this->page = 2;
			this->selection += 4;
		}
	}
	if (hDown & KEY_L) {
		if (this->page == 2) {
			this->page = 1;
			this->selection -= 4;
		}
	}

	if (hDown & KEY_RIGHT) {
		if (this->page == 1) {
			if (this->selection > 2) {
				this->selection++;
				this->page++;
			} else {
				this->selection++;
			}
		} else if (this->page == 2) {
			if (this->selection < 7) {
				this->selection++;
			}
		}
	}

	if (hDown & KEY_LEFT) {
		if (this->page == 1) {
			if (this->selection > 0) {
				this->selection--;
			}
		} else if (this->page == 2) {
			if (this->selection < 5) {
				this->selection--;
				this->page--;
			} else {
				this->selection--;
			}
		}
	}

	if (hDown & KEY_A) {
		// Our Player variable which should be set.
		this->save->playerAvatar(this->selection);
		this->isUsed = false;
	}
}