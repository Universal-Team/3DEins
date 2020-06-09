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

#include "config.hpp"
#include "setChanger.hpp"
#include <unistd.h>

extern std::unique_ptr<Config> config;
// For the sets.
extern C2D_SpriteSheet cards;

// Load path.
SetChanger::SetChanger() {
	this->dirContents.clear();
	chdir("sdmc:/3ds/3DEins/sets/");
	std::vector<DirEntry> dirContentsTemp;
	getDirectoryContents(dirContentsTemp, {});
	for(uint i=0;i<dirContentsTemp.size();i++) {
		this->dirContents.push_back(dirContentsTemp[i]);
	}

	if (this->dirContents.size() == 0)	this->isEmpty = true;
}

void SetChanger::Draw(void) const {
	if (!this->isEmpty) {
		GFX::DrawFileBrowseBG();
		Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), "3DEins - " + Lang::get("CARDSETS"), 400);

		std::string dirs;
		for (uint i=(selectedSet<5) ? 0 : selectedSet-5;i<dirContents.size()&&i<((selectedSet<5) ? 6 : selectedSet+1);i++) {
			if (i == selectedSet) {
				dirs += "> " + dirContents[i].name + "\n\n";
			} else {
				dirs += dirContents[i].name + "\n\n";
			}
		}

		for (uint i=0;i<((dirContents.size()<6) ? 6-dirContents.size() : 0);i++) {
			dirs += "\n\n";
		}

		Gui::DrawString(26, 32, 0.53f, config->textColor(), dirs.c_str(), 360);
		Gui::DrawStringCentered(0, 215, 0.6f, config->textColor(), Lang::get("REFRESH"), 390);
		if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
		GFX::DrawFileBrowseBG(false);
		if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	} else {
		GFX::DrawFileBrowseBG();
		Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), "3DEins - " + Lang::get("CARDSETS"), 400);
		Gui::DrawStringCentered(0, 215, 0.6f, config->textColor(), Lang::get("NO_CARD_SETS_FOUND"), 390);
		if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
		GFX::DrawFileBrowseBG(false);
		if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	}
}

void SetChanger::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->keyRepeatDelay)	this->keyRepeatDelay--;

	if (this->dirChanged) {
		this->dirContents.clear();
		chdir("sdmc:/3ds/3DEins/sets/");
		std::vector<DirEntry> dirContentsTemp;
		getDirectoryContents(dirContentsTemp, {});
		for(uint i=0;i<dirContentsTemp.size();i++) {
			this->dirContents.push_back(dirContentsTemp[i]);
		}

		this->dirChanged = false;
	}

	// Refresh.
	if (hDown & KEY_START) {
		this->dirChanged = true;
	}

	if (hHeld & KEY_UP) {
		if (this->selectedSet > 0 && !this->keyRepeatDelay) {
			this->selectedSet--;
			this->keyRepeatDelay = 6;
		}
	} else if (hHeld & KEY_DOWN && !this->keyRepeatDelay) {
		if (this->selectedSet < this->dirContents.size()-1) {
			this->selectedSet++;
			this->keyRepeatDelay = 6;
		}
	}

	if (hDown & KEY_A) {
		if (this->dirContents.size() != 0) {
			if (this->dirContents[selectedSet].isDirectory) {
				std::string path = this->dirContents[selectedSet].name;
				this->loadSet(path);
			}
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack(true);
		return;
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("REFRESH"));
	}
}

// Check if Files of the set exist.
bool SetChanger::checkForValidate(std::string file) {
	if (access(file.c_str(), F_OK) != -1 ) {
		return true;
	} else {
		return false;
	}
}

// Load a set.
Result SetChanger::loadSet(std::string folder) {
	if (this->checkForValidate(folder)) {
		if (this->checkForValidate(folder + "/Set.json")) {
			if (this->checkForValidate(folder + "/cards.t3x")) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("LOADING_SET_PROMPT").c_str(), folder.c_str());
				if (Msg::promptMsg2(message)) {
					// Unload.
					Gui::unloadSheet(cards);
					Msg::DisplayMsg(Lang::get("LOADING_SPRITESHEET"));

					// Load.
					Gui::loadSheet((folder + "/cards.t3x").c_str(), cards);
					config->loadCardSets(folder + "/Set.json");
				}
			} else {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("FILE_NOT_EXIST").c_str(), "cards.t3x");
				Msg::DisplayWaitMsg(message);
			}
		} else {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("FILE_NOT_EXIST").c_str(), "Set.json");
			Msg::DisplayWaitMsg(message);
		}
	}
	return 0;
}