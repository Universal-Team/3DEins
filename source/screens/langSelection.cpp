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

#include "langSelection.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

LangSelection::LangSelection() {
	selectedLang = Config::lang;
}

void LangSelection::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.7f, WHITE, Lang::get("SELECT_LANG"), 400);
	GFX::DrawBottom();

	for (int language = 0; language < 10; language++) {
		Gui::Draw_Rect(langBlocks[language].x, langBlocks[language].y, langBlocks[language].w, langBlocks[language].h, C2D_Color32(170, 60, 0, 200));
		if (Config::lang == language) {
			Gui::Draw_Rect(langBlocks[language].x, langBlocks[language].y, langBlocks[language].w, langBlocks[language].h, C2D_Color32(230, 60, 0, 200));
		}
	}

	Gui::DrawString(langBlocks[0].x+25, langBlocks[0].y, 0.7f, WHITE, "Bruh", 320);
	Gui::DrawString(langBlocks[1].x+25, langBlocks[1].y, 0.7f, WHITE, "Deutsch", 320);
	Gui::DrawString(langBlocks[2].x+25, langBlocks[2].y, 0.7f, WHITE, "English", 320);
	Gui::DrawString(langBlocks[3].x+25, langBlocks[3].y, 0.7f, WHITE, "Español", 320);
	Gui::DrawString(langBlocks[4].x+25, langBlocks[4].y, 0.7f, WHITE, "Français", 320);

	Gui::DrawString(langBlocks[5].x+25, langBlocks[5].y, 0.7f, WHITE, "Italiano", 320);
	Gui::DrawString(langBlocks[6].x+25, langBlocks[6].y, 0.7f, WHITE, "Lietuvių", 320);
	Gui::DrawString(langBlocks[7].x+25, langBlocks[7].y, 0.7f, WHITE, "Português", 320);
	Gui::DrawString(langBlocks[8].x+25, langBlocks[8].y, 0.7f, WHITE, "Русский", 320);
	Gui::DrawString(langBlocks[9].x+25, langBlocks[9].y, 0.7f, WHITE, "日本語", 320);
}

void LangSelection::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_TOUCH) {
		for (int language = 0; language < 10; language++) {
			if (touching(touch, langBlocks[language])) {
				selectedLang = language;
				Config::lang = language;
				Lang::load(Config::lang);
			}
		}
	}

	if (hDown & KEY_UP) {
		if(selectedLang > 0) {
			selectedLang--;
			Config::lang = selectedLang;
			Lang::load(Config::lang);
		}
	}

	if (hDown & KEY_DOWN) {
		if(selectedLang < 9) {
			selectedLang++;
			Config::lang = selectedLang;
			Lang::load(Config::lang);
		}
	}


	if (hDown & KEY_LEFT) {
		if (selectedLang > 4) {
			selectedLang -= 5;
			Config::lang = selectedLang;
			Lang::load(Config::lang);
		}
	}

	if (hDown & KEY_RIGHT) {
		if (selectedLang < 5) {
			selectedLang += 5;
			Config::lang = selectedLang;
			Lang::load(Config::lang);
		}
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("LANGUAGE_INSTRUCTIONS"));
	}
	
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}
}