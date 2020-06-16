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

#include "config.hpp"
#include "credits.hpp"
#include "mainMenu.hpp"
#include "modeSelect.hpp"
#include "rulesScreen.hpp"
#include "uiSettings.hpp"

extern std::unique_ptr<Config> config;
extern bool exiting;
extern bool buttonTouch(ButtonStruct button);

MainMenu::MainMenu() { }

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, config->textColor(), "3DEins - " + Lang::get("MAINMENU"));
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	GFX::DrawBottom();
	for (int i = 0; i < 4; i++) {
		GFX::Button(mainButtons[i]);
	}

	GFX::DrawButtonSelector(mainButtons[this->Selection].X, mainButtons[this->Selection].Y);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_TOUCH) {
		if (buttonTouch(mainButtons[0])) {
			if (Msg::promptMsg(Lang::get("NEW_GAME_PROMPT"))) {
				Gui::setScreen(std::make_unique<ModeSelect>(), true, true);
			}
		} else if (buttonTouch(mainButtons[1])) {
			Gui::setScreen(std::make_unique<UISettings>(), true, true);
		} else if (buttonTouch(mainButtons[2])) {
			Gui::setScreen(std::make_unique<Credits>(), true, true);
		} else if (buttonTouch(mainButtons[3])) {
			Gui::setScreen(std::make_unique<RulesScreen>(), true, true);
		}
	}

	if (hDown & KEY_A) {
		switch (Selection) {
			case 0:
				if (Msg::promptMsg(Lang::get("NEW_GAME_PROMPT"))) {
					Gui::setScreen(std::make_unique<ModeSelect>(), true, true);
				}
				break;
			case 1:
				Gui::setScreen(std::make_unique<UISettings>(), true, true);
				break;
			case 2:
				Gui::setScreen(std::make_unique<Credits>(), true, true);
				break;
			case 3:
				Gui::setScreen(std::make_unique<RulesScreen>(), true, true);
				break;
		}
	}

	if (hDown & KEY_UP) {
		if (Selection > 1)	Selection -= 2;
	} else if (hDown & KEY_DOWN) {
		if(Selection < 3 && Selection != 2 && Selection != 3)	Selection += 2;
	} else if (hDown & KEY_LEFT) {
		if (Selection%2)	Selection--;
	} else if (hDown & KEY_RIGHT) {
		if (!(Selection%2))	Selection++;
	}

	if (hDown & KEY_START) {
		fadeout = true;
		fadecolor = 0;
		exiting = true;
	}
}