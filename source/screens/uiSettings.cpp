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

#include "colorChanger.hpp"
#include "gameSettings.hpp"
#include "langSelection.hpp"
#include "setChanger.hpp"
#include "uiSettings.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

void UISettings::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.7f, Config::Text, "3DEins - " + Lang::get("UI_SETTINGS"), 400);
	GFX::DrawBottom();
	for (int i = 0; i < 4; i++) {
		Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, Config::Button);
		if (subSelection == i) {
			GFX::DrawButtonSelector(mainButtons[i].x, mainButtons[i].y);
		}
	}
	Gui::DrawStringCentered(-80, mainButtons[0].y+12, 0.6f, Config::Text, Lang::get("COLORS"), 130);
	Gui::DrawStringCentered(80, mainButtons[1].y+12, 0.6f, Config::Text, Lang::get("LANGUAGE"), 130);
	Gui::DrawStringCentered(-80, mainButtons[2].y+12, 0.6f, Config::Text, Lang::get("CARDSETS"), 130);
	Gui::DrawStringCentered(80, mainButtons[3].y+12, 0.6f, Config::Text, Lang::get("GAME_SETTINGS"), 130);
}

void UISettings::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_TOUCH) {
		if (touching(touch, mainButtons[0])) {
			Gui::setScreen(std::make_unique<ColorChanger>());
		} else if (touching(touch, mainButtons[1])) {
			Gui::setScreen(std::make_unique<LangSelection>());
		} else if (touching(touch, mainButtons[2])) {
			Gui::setScreen(std::make_unique<SetChanger>());
		} else if (touching(touch, mainButtons[3])) {
			Gui::setScreen(std::make_unique<GameSettings>());
		}
	}

	if (hDown & KEY_A) {
		switch (subSelection) {
			case 0:
				Gui::setScreen(std::make_unique<ColorChanger>());
				break;
			case 1:
				Gui::setScreen(std::make_unique<LangSelection>());
				break;
			case 2:
				Gui::setScreen(std::make_unique<SetChanger>());
				break;
			case 3:
				Gui::setScreen(std::make_unique<GameSettings>());
				break;
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if(hDown & KEY_UP) {
		if(subSelection > 1)	subSelection -= 2;
	} else if(hDown & KEY_DOWN) {
		if(subSelection < 3 && subSelection != 2 && subSelection != 3)	subSelection += 2;
	} else if (hDown & KEY_LEFT) {
		if (subSelection%2) subSelection--;
	} else if (hDown & KEY_RIGHT) {
		if (!(subSelection%2)) subSelection++;
	}
}