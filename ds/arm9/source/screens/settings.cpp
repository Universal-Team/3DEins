/*
*   This file is part of DSEins
*   Copyright (C) 2019-2021 Universal-Team
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
#include "selector.hpp"
#include "settings.hpp"

extern std::unique_ptr<Selector> selector;
extern bool Buttontouching(ButtonStruct button);

void Settings::Draw(void) const {
	Gui::DrawTop(true);
	printTextCentered("DSEins - " + Lang::get("UI_SETTINGS"), 0, 1, true, true);
	Gui::DrawBottom(true);

	for (int i = 0; i < 1; i++) {
		Gui::DrawButton(this->buttonPos[i]);
	}
}

void Settings::Logic(u16 hDown, touchPosition touch) {
	if (doUpdate) {
		selector->move(this->buttonPos[this->selection].x, this->buttonPos[this->selection].y);
		selector->update();
	}

	if (hDown & KEY_A) {
		Gui::setScreen(std::make_unique<LangSelection>());
		selector->resize(20, 20); // Resize to the other size.
		doUpdate = true;
		Gui::DrawScreen();
	}

	if (hDown & KEY_TOUCH) {
		if (Buttontouching(this->buttonPos[0])) {
			Gui::setScreen(std::make_unique<LangSelection>());
			selector->resize(20, 20); // Resize to the other size.
			doUpdate = true;
			Gui::DrawScreen();
		}
	}

	if (hDown & KEY_B) {
		doUpdate = true;
		Gui::screenBack();
		Gui::DrawScreen();
		return;
	}
}