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
#include "config.hpp"
#include "credits.hpp"
#include "gameScreen.hpp"
#include "mainMenu.hpp"
#include "rulesScreen.hpp"
#include "saveData.hpp"

extern std::unique_ptr<SaveData> savedata;
extern std::unique_ptr<Config> config;
extern bool exiting;
extern bool buttonTouch(touchPosition touch, ButtonStruct button);

MainMenu::MainMenu() { }

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, config->textColor(), "Welcome " + savedata->playerName() + " - " + std::to_string(savedata->playerID()) + "!");
	GFX::DrawBottom();
	for (int i = 0; i < 4; i++) {
		GFX::Button(mainButtons[i]);
		if (Selection == i) {
			GFX::DrawButtonSelector(mainButtons[i].X, mainButtons[i].Y);
		}
	}
}


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_TOUCH) {
		if (buttonTouch(touch, mainButtons[0])) {
			Gui::setScreen(std::make_unique<GameScreen>());
		} else if (buttonTouch(touch, mainButtons[1])) {
			Gui::setScreen(std::make_unique<ColorChanger>());
		} else if (buttonTouch(touch, mainButtons[2])) {
			Gui::setScreen(std::make_unique<Credits>());
		} else if (buttonTouch(touch, mainButtons[3])) {
			Gui::setScreen(std::make_unique<RulesScreen>());
		}
	}

	if (hDown & KEY_A) {
		switch (Selection) {
			case 0:
				Gui::setScreen(std::make_unique<GameScreen>());
				break;
			case 1:
				Gui::setScreen(std::make_unique<ColorChanger>());
				break;
			case 2:
				Gui::setScreen(std::make_unique<Credits>());
				break;
			case 3:
				Gui::setScreen(std::make_unique<RulesScreen>());
				break;
		}
	}

	if (hDown & KEY_UP) {
		if (Selection > 1)	Selection -= 2;
	} else if (hDown & KEY_DOWN) {
		if(Selection < 3 && Selection != 2 && Selection != 3)	Selection += 2;
	} else if (hDown & KEY_LEFT) {
		if (Selection%2) Selection--;
	} else if (hDown & KEY_RIGHT) {
		if (!(Selection%2)) Selection++;
	}

	if (hDown & KEY_START) {
		exiting = true;
	}
}