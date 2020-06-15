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

#include "credits.hpp"
#include "selector.hpp"

extern std::unique_ptr<Selector> selector;

struct Translator {
	std::string Name;
	std::string Language;
};

const std::vector<Translator> TL = {
	{"_mapple²", "Русский"},
	{"antoine62", "Français"},
	{"Linuxcat", "Français"},
	{"Pk11", "日本語"},
	{"SuperSaiyajinStackZ", "Deutsch, English"},
	{"XxPhoenix1996xX", "Español"},
	{"YoSoy", "Español"}
};

// Load core graphic here on constructor call.
Credits::Credits() { this->core = loadImage("/graphics/core.gfx"); }


void Credits::Draw(void) const {
	Gui::DrawTop(true);
	printTextCentered("DSEins - " + Lang::get("CREDITS"), 0, 1, true, true);
	printTextCentered(Lang::get("DEVELOPED_BY"), 0, 25, true, true);
	printTextCentered(Lang::get("MAIN_DEV"), 0, 40, true, true);
	printText(Lang::get("CURRENT_VERSION") + VER_NUMBER, (250-getTextWidth(Lang::get("CURRENT_VERSION") + VER_NUMBER)), 175, true, true);
	drawImage(25, 60, this->core, true, true);
	Gui::DrawBottom(true);
	this->DrawBottom();
}

void Credits::DrawBottom(void) const {
	Gui::clearScreen(false, true); // Clear first!

	if (this->creditsPage == 0) {
		printTextCentered(Lang::get("GENERAL_CREDITS"), 0, 1, false, true);

		printTextCentered("SuperSaiyajinStackZ", 0, 30, false, true);
		printTextCenteredMaxW(Lang::get("_DSEINS_CORE"), 240, 1, 0, 45, false, true);
	} else if (this->creditsPage == 1) {
		printTextCentered(Lang::get("TRANSLATORS"), 0, 1, false, true);

		std::string tlText;
		for (int i = 0; i < (int)TL.size(); i++) {
			tlText += TL[i].Name + " - " + TL[i].Language + "\n";
		}

		printTextCentered(tlText, 0, 25, false, true);
	}
}

void Credits::Logic(u16 hDown, touchPosition touch) {
	if (hDown & KEY_B) {
		selector->show();
		doUpdate = true;
		Gui::screenBack();
		Gui::DrawScreen();
		return;
	}

	if (hDown & KEY_R) {
		if (this->creditsPage == 0) {
			this->creditsPage = 1;
			this->DrawBottom();
		}
	}

	if (hDown & KEY_L) {
		if (this->creditsPage == 1) {
			this->creditsPage = 0;
			this->DrawBottom();
		}
	}
}