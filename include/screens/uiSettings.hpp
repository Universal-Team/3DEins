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

#ifndef UISETTINGS_HPP
#define UISETTINGS_HPP

#include "common.hpp"
#include "fileBrowse.hpp"
#include "structs.hpp"

#include <vector>

class UISettings : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	UISettings();
private:
	int Mode = 0; // Sub Menu.

	/*	Sub Menu 0.	*/
	std::vector<Structs::ButtonPos> mainButtons = {
		{90, 40, 140, 40}, // Colors.
		{90, 100, 140, 40}, // Language.
		{90, 160, 140, 40}, // Card Style Change.
	};
	int subSelection = 0;
	void DrawSubMenu(void) const;
	void SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch);

	/*	Colors 1.	*/
	void DrawColor(void) const;
	void ColorLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void DrawPreview(void) const;
	int colorMode = 0;
	std::vector<Structs::ButtonPos> buttons = {
		{10, 85, 95, 41},
		{115, 85, 95, 41},
		{220, 85, 95, 41},
	};

	/*	Language 2.	*/
	void DrawLanguage(void) const;
	void LanguageLogic(u32 hDown, u32 hHeld, touchPosition touch);
	int selectedLang = 0;
	std::vector<Structs::ButtonPos> langBlocks = {
		{37, 32, 20, 20},
		{37, 72, 20, 20},
		{37, 112, 20, 20},
		{37, 152, 20, 20},
		{37, 188, 20, 20},
		{177, 32, 20, 20},
		{177, 72, 20, 20},
		{177, 112, 20, 20},
		{177, 152, 20, 20},
		{177, 188, 20, 20},
	};

	/*	Card Style Change 3.	*/
	void DrawCardScreen(void) const;
	void CardLogic(u32 hDown, u32 hHeld, touchPosition touch);
	bool checkForValidate(std::string file);
	Result loadSet(std::string folder);
	uint selectedSheet = 0;
	int keyRepeatDelay = 0;
	mutable bool dirChanged = true;
	std::vector<DirEntry> dirContents;
};

#endif