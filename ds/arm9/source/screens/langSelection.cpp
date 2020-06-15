/*
*   This file is part of DSEins
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
#include "langSelection.hpp"
#include "selector.hpp"

extern std::unique_ptr<Config> config;
extern std::unique_ptr<Selector> selector;

extern bool touching(touchPosition touch, Structs::ButtonPos);

LangSelection::LangSelection() { this->selectedLang = config->language(); }

void LangSelection::Draw(void) const {
	Gui::DrawTop(true);
	printTextCentered(Lang::get("SELECT_LANG"), 0, 1, true, true);
	Gui::DrawBottom(true);

	for (int language = 0; language < 10; language++) {
		drawRectangle(langBlocks[language].x, langBlocks[language].y, langBlocks[language].w, langBlocks[language].h, GRAY, false, true);
	}

	printText("Bruh", langBlocks[0].x+25, langBlocks[0].y+2, false, true);
	printText("Deutsch", langBlocks[1].x+25, langBlocks[1].y+2, false, true);
	printText("English", langBlocks[2].x+25, langBlocks[2].y+2, false, true);
	printText("Español", langBlocks[3].x+25, langBlocks[3].y+2, false, true);
	printText("Français", langBlocks[4].x+25, langBlocks[4].y+2, false, true);

	printText("Italiano", langBlocks[5].x+25, langBlocks[5].y+2, false, true);
	printText("Lietuvių", langBlocks[6].x+25, langBlocks[6].y+2, false, true);
	printText("Português", langBlocks[7].x+25, langBlocks[7].y+2, false, true);
	printText("Русский", langBlocks[8].x+25, langBlocks[8].y+2, false, true);
	printText("日本語", langBlocks[9].x+25, langBlocks[9].y+2, false, true);
}

void LangSelection::Logic(u16 hDown, touchPosition touch) {
	if (doUpdate) {
		selector->move(this->langBlocks[this->selectedLang].x, this->langBlocks[this->selectedLang].y);
		selector->update();
	}

	if (hDown & KEY_B) {
		selector->resize(80, 40);
		Gui::screenBack();
		doUpdate = true;
		Gui::DrawScreen();
		return;
	}

	if (hDown & KEY_TOUCH) {
		for(int language = 0; language < 10; language++) {
			if (touching(touch, langBlocks[language])) {
				this->selectedLang = language;
				config->language(this->selectedLang);
				Lang::load();
				doUpdate = true;
			}
		}
	}

	if (hDown & KEY_UP) {
		if (this->selectedLang > 0) {
			this->selectedLang--;
			config->language(this->selectedLang);
			Lang::load();
			doUpdate = true;
		}
	}

	if (hDown & KEY_DOWN) {
		if (this->selectedLang < 9) {
			this->selectedLang++;
			config->language(this->selectedLang);
			Lang::load();
			doUpdate = true;
		}
	}

	if (hDown & KEY_LEFT) {
		if (this->selectedLang > 4) {
			this->selectedLang -= 5;
			config->language(this->selectedLang);
			Lang::load();
			doUpdate = true;
		}
	}

	if (hDown & KEY_RIGHT) {
		if (this->selectedLang < 5) {
			this->selectedLang += 5;
			config->language(this->selectedLang);
			Lang::load();
			doUpdate = true;
		}
	}
}