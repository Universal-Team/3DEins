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

/* Draw the Top (File) browse. */
static void DrawTop(uint Selection, std::vector<DirEntry> dirContents, const std::string Text) {
	std::string files;
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));

	GFX::DrawFileBrowseBG();
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), Text, 390);

	for (uint i = (Selection < 5) ? 0 : Selection - 5; i < dirContents.size() && i < ((Selection < 5) ? 6 : Selection + 1); i++) {
		if (i == Selection) {
			files += "> " + dirContents[i].name + "\n\n";
		} else {
			files += dirContents[i].name + "\n\n";
		}
	}

	for (uint i = 0; i < ((dirContents.size() < 6) ? 6-dirContents.size() : 0); i++) {
		files += "\n\n";
	}

	Gui::DrawString(26, 32, 0.53f, config->textColor(), files.c_str(), 360);
	Gui::DrawStringCentered(0, 215, 0.6f, config->textColor(), Lang::get("REFRESH"), 390);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}

static void DrawBottom(bool isDirBrowse = false) {
	GFX::DrawFileBrowseBG(false);
	if (isDirBrowse) Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), Lang::get("X_SELECT"), 390);
	C3D_FrameEnd(0);
}

std::string Overlays::SelectFile(const std::vector<std::string> fileType, const std::string initialPath, const std::string Text) {
	s32 selectedFile = 0;
	bool dirChanged = false;
	std::vector<DirEntry> dirContents;

	/* Initial dir change. */
	dirContents.clear();
	chdir(initialPath.c_str());
	std::vector<DirEntry> dirContentsTemp;
	getDirectoryContents(dirContentsTemp, fileType);
	for(uint i = 0; i < dirContentsTemp.size(); i++) {
		dirContents.push_back(dirContentsTemp[i]);
	}

	while (1) {
		/* Screen draw part. */
		DrawTop(selectedFile, dirContents, Text);
		DrawBottom();

		/* The input part. */
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hRepeat = hidKeysDownRepeat();

		/* if directory changed -> Refresh it. */
		if (dirChanged) {
			dirContents.clear();
			std::vector<DirEntry> dirContentsTemp;
			getDirectoryContents(dirContentsTemp, fileType);
			for(uint i = 0; i < dirContentsTemp.size(); i++) {
				dirContents.push_back(dirContentsTemp[i]);
			}

			dirChanged = false;
		}

		if (hDown & KEY_A) {
			if (dirContents[selectedFile].isDirectory) {
				chdir(dirContents[selectedFile].name.c_str());
				selectedFile = 0;
				dirChanged = true;
			} else {
				char path[PATH_MAX];
				getcwd(path, PATH_MAX);
				return path + dirContents[selectedFile].name;
			}
		}

		if (hRepeat & KEY_UP) {
			if (selectedFile > 0) {
				selectedFile--;
			}
		}
		
		if (hRepeat & KEY_DOWN) {
			if ((uint)selectedFile < dirContents.size()-1) {
				selectedFile++;
			}
		}
		
		if (hDown & KEY_B) {
			char path[PATH_MAX];
			getcwd(path, PATH_MAX);
			if (strcmp(path, "sdmc:/") == 0 || strcmp(path, "/") == 0) {
				if (Msg::promptMsg(Lang::get("CANCEL_SELECTION"))) {
					return "";
				}
			} else {
				chdir("..");
				selectedFile = 0;
				dirChanged = true;
			}
		}
		
		if (hDown & KEY_START) {
			dirChanged = true;
		}
	}
}

std::string Overlays::SelectDirectory(const std::string initialPath, const std::string Text) {
	s32 selectedDirectory = 0;
	bool dirChanged = false;
	std::vector<DirEntry> dirContents;

	/* Initial dir change. */
	dirContents.clear();
	chdir(initialPath.c_str());
	std::vector<DirEntry> dirContentsTemp;
	getDirectoryContents(dirContentsTemp, {""});
	for(uint i = 0; i < dirContentsTemp.size(); i++) {
		dirContents.push_back(dirContentsTemp[i]);
	}

	while (1) {
		/* Screen draw part. */
		DrawTop(selectedDirectory, dirContents, Text);
		DrawBottom(true);

		/* The input part. */
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hRepeat = hidKeysDownRepeat();

		/* if directory changed -> Refresh it. */
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
			if (dirContents[selectedDirectory].isDirectory) {
				chdir(dirContents[selectedDirectory].name.c_str());
				selectedDirectory = 0;
				dirChanged = true;
			}
		}

		if (hRepeat & KEY_UP) {
			if (selectedDirectory > 0) {
				selectedDirectory--;
			}
		}
		
		if (hRepeat & KEY_DOWN) {
			if ((uint)selectedDirectory < dirContents.size()-1) {
				selectedDirectory++;
			}
		}
		
		if (hDown & KEY_B) {
			char path[PATH_MAX];
			getcwd(path, PATH_MAX);
			if (strcmp(path, "sdmc:/") == 0 || strcmp(path, "/") == 0) {
				if (Msg::promptMsg(Lang::get("CANCEL_SELECTION"))) {
					return "";
				}
			} else {
				chdir("..");
				selectedDirectory = 0;
				dirChanged = true;
			}
		}
		
		if (hDown & KEY_START) {
			dirChanged = true;
		}

		if (hDown & KEY_X) {
			if (dirContents[selectedDirectory].isDirectory) {
				char path[PATH_MAX];
				getcwd(path, PATH_MAX);
				return path + dirContents[selectedDirectory].name;
			}
		}
	}
}