/*
*   This file is part of 3DEins
*   Copyright (C) 2019-2020 Universal-Team
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

#include "common.hpp"
#include "config.hpp"
#include "fileBrowse.hpp"
#include "overlay.hpp"
#include <dirent.h>
#include <unistd.h>

extern bool iconTouch(touchPosition touch, Structs::ButtonPos button);
extern std::unique_ptr<Config> config;

// Draw the Top (File) browse.
static void DrawTop(uint Selection, std::vector<DirEntry> dirContents) {
	std::string sets;
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));

	GFX::DrawFileBrowseBG();
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), Lang::get("SELECT_SET"), 390);

	for (uint i = (Selection < 5) ? 0 : Selection - 5; i < dirContents.size() && i < ((Selection < 5) ? 6 : Selection + 1); i++) {
		if (i == Selection) {
			sets += "> " + dirContents[i].name + "\n\n";
		} else {
			sets += dirContents[i].name + "\n\n";
		}
	}

	for (uint i = 0; i < ((dirContents.size() < 6) ? 6-dirContents.size() : 0); i++) {
		sets += "\n\n";
	}

	Gui::DrawString(26, 32, 0.53f, config->textColor(), sets, 360);
	Gui::DrawStringCentered(0, 215, 0.6f, config->textColor(), Lang::get("REFRESH"), 390);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}

static void DrawBottom() {
	GFX::DrawFileBrowseBG(false);
	Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), Lang::get("X_DEFAULT_SET"), 390);
	C3D_FrameEnd(0);
}

std::string Overlays::SelectSet() {
	s32 selectedSet = 0;
	std::vector<DirEntry> dirContents;
	bool dirChanged = false;

	// Initial dir change.
	dirContents.clear();
	chdir("sdmc:/3ds/3DEins/sets/");
	std::vector<DirEntry> dirContentsTemp;
	getDirectoryContents(dirContentsTemp, {""});
	for(uint i = 0; i < dirContentsTemp.size(); i++) {
		dirContents.push_back(dirContentsTemp[i]);
	}

	while (1) {
		// Screen draw part.
		DrawTop(selectedSet, dirContents);
		DrawBottom();

		// The input part.
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hRepeat = hidKeysDownRepeat();

		// if directory changed -> Refresh it.
		if (dirChanged) {
			dirContents.clear();
			std::vector<DirEntry> dirContentsTemp;
			getDirectoryContents(dirContentsTemp, {""});
			for(uint i = 0; i < dirContentsTemp.size(); i++) {
				dirContents.push_back(dirContentsTemp[i]);
			}

			dirChanged = false;
		}

		if (hDown & KEY_A) {
			if (dirContents[selectedSet].isDirectory) {
				char path[PATH_MAX];
				getcwd(path, PATH_MAX);
				std::string output = path + dirContents[selectedSet].name;
				return output;
			}
		}

		if (hRepeat & KEY_UP) {
			if (selectedSet > 0) {
				selectedSet--;
			}
		}
		
		if (hRepeat & KEY_DOWN) {
			if ((uint)selectedSet < dirContents.size()-1) {
				selectedSet++;
			}
		}
		
		if (hDown & KEY_B) {
			if (Msg::promptMsg(Lang::get("CANCEL_SELECTION"))) {
				return "";
			}
		}

		if (hDown & KEY_X) {
			return "3DEINS_DEFAULT_ROMFS";
		}
		
		if (hDown & KEY_START) {
			dirChanged = true;
		}
	}
}