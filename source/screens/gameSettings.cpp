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

#include "gameSettings.hpp"
#include "keyboard.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

void GameSettings::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, Config::Text, "3DEins - " + Lang::get("GAME_SETTINGS"), 320);
	GFX::DrawBottom();
	Gui::Draw_Rect(buttons[0].x, buttons[0].y, 95, 41, Config::Button);
	// Settings Pages.
	if (gamePage == 0) {
		Gui::DrawStringCentered(0, 60, 0.7f, Config::Text, Lang::get("ALLOW_BRUH_CARD"), 320);
		if (Config::allowBruh) {
			Gui::DrawString(140, 98, 0.7f, Config::Text, Lang::get("YES"), 400);
		} else {
			Gui::DrawString(140, 98, 0.7f, Config::Text, Lang::get("NO"), 400);
		}
	} else if (gamePage == 1) {
		Gui::DrawStringCentered(0, 60, 0.7f, Config::Text, Lang::get("POINTS_TO_WIN"), 320);
		Gui::DrawString(140, 98, 0.7f, Config::Text, std::to_string(Config::POINTS), 400);
	}
}

void GameSettings::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_R || hDown & KEY_RIGHT) {
		if (gamePage < 1)	gamePage++;
	}

	if (hDown & KEY_L || hDown & KEY_LEFT) {
		if (gamePage > 0)	gamePage--;
	}

	if (hDown & KEY_TOUCH) {
		if (touching(touch, buttons[0])) {
			if (gamePage == 0) {
				if (Config::allowBruh)	Config::allowBruh = false;
				else				Config::allowBruh = true;
			} else if (gamePage == 1) {
				std::string temp = Input::Numpad(Lang::get("ENTER_POINTS_TO_WIN"));
				Config::POINTS = atoi(temp.c_str());
			}
		}
	}
}