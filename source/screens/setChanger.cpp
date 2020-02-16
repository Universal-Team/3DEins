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

#include "setChanger.hpp"

#include <unistd.h>

// For the sets.
extern C2D_SpriteSheet cards;
extern C2D_SpriteSheet characters;

// Load path.
SetChanger::SetChanger() {
	dirContents.clear();
	chdir("sdmc:/3ds/3DEins/sets/");
	std::vector<DirEntry> dirContentsTemp;
	getDirectoryContents(dirContentsTemp, {});
	for(uint i=0;i<dirContentsTemp.size();i++) {
		dirContents.push_back(dirContentsTemp[i]);
	}
}

void SetChanger::Draw(void) const {
	GFX::DrawFileBrowseBG();
	Gui::DrawStringCentered(0, 0, 0.7f, Config::Text, "3DEins - " + Lang::get("CARDSETS"), 400);
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
	Gui::DrawString(26, 32, 0.53f, Config::Text, dirs.c_str(), 360);
	Gui::DrawStringCentered(0, 215, 0.6f, Config::Text, Lang::get("REFRESH"), 390);
	GFX::DrawFileBrowseBG(false);
}

void SetChanger::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (keyRepeatDelay)	keyRepeatDelay--;

	if (dirChanged) {
		dirContents.clear();
		chdir("sdmc:/3ds/3DEins/sets/");
		std::vector<DirEntry> dirContentsTemp;
		getDirectoryContents(dirContentsTemp, {});
		for(uint i=0;i<dirContentsTemp.size();i++) {
			dirContents.push_back(dirContentsTemp[i]);
		}
		dirChanged = false;
	}

	// Refresh.
	if (hDown & KEY_START) {
		dirChanged = true;
	}

	if (hHeld & KEY_UP) {
		if (selectedSet > 0 && !keyRepeatDelay) {
			selectedSet--;
			keyRepeatDelay = 6;
		}
	} else if (hHeld & KEY_DOWN && !keyRepeatDelay) {
		if (selectedSet < dirContents.size()-1) {
			selectedSet++;
			keyRepeatDelay = 6;
		}
	}

	if (hDown & KEY_A) {
		if (dirContents.size() != 0) {
			std::string path = dirContents[selectedSet].name;
			loadSet(path);
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("REFRESH"));
	}
}

// Check if Files of the set exist.
bool SetChanger::checkForValidate(std::string file) {
	if(access(file.c_str(), F_OK) != -1 ) {
		return true;
	} else {
		return false;
	}
}

// Load Set. ;)
Result SetChanger::loadSet(std::string folder) {
	if (checkForValidate(folder)) {
		if (checkForValidate(folder + "/Set.json")) {
			if (checkForValidate(folder + "/cards.t3x")) {
				if (checkForValidate(folder + "/chars.t3x")) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("LOADING_SET_PROMPT").c_str(), folder.c_str());
					if (Msg::promptMsg2(message)) {
						// Unload.
						Gui::unloadSheet(cards);
						Gui::unloadSheet(characters);
						Msg::DisplayMsg(Lang::get("LOADING_SPRITESHEET"));
						// Load.
						Gui::loadSheet((folder + "/cards.t3x").c_str(), cards);
						Gui::loadSheet((folder + "/chars.t3x").c_str(), characters);
						Config::loadSet((folder + "/Set.json").c_str());
					}
				} else {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("FILE_NOT_EXIST").c_str(), "chars.t3x");
					Msg::DisplayWaitMsg(message);
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