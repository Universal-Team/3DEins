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

#include "colorCard.hpp"
#include "credits.hpp"
#include "keyboard.hpp"
#include "mainMenu.hpp"
#include "test.hpp"

extern bool exiting;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

MainMenu::MainMenu() {
	// Randomize carts. ;P
	Card1 = CardType(rand() % MAXCARDTYPE + 0);
	Color1 = CardColor(rand() % MAXCOLOR + 0);

	Card2 = CardType(rand() % MAXCARDTYPE + 0);
	Color2 = CardColor(rand() % MAXCOLOR + 0);

	Card3 = CardType(rand() % MAXCARDTYPE + 0);
	Color3 = CardColor(rand() % MAXCOLOR + 0);
}

void MainMenu::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawString(100, 0, 0.9f, WHITE, "3DEins - MainMenu");
	GFX::DrawCard(Card1, 40, 65, Color1, 1.5, 1.5);
	GFX::DrawCard(Card2, 160, 65, Color2, 1.5, 1.5);
	GFX::DrawCard(Card3, 280, 65, Color3, 1.5, 1.5);

	GFX::DrawBottom();
	for (int i = 0; i < 3; i++) {
		Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, C2D_Color32(170, 60, 0, 200));
		if (Selection == i) {
			Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, C2D_Color32(220, 60, 0, 200));
		}
	}
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.8, "New Game"))/2-80+17.5, 0.8, WHITE, "New Game", 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.8, "Card Colors"))/2-20+17.5, 0.8, WHITE, "Card Colors", 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.8, "Credits"))/2+75-17.5, 0.8, WHITE, "Credits", 130, 25);
}


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {

	if (hDown & KEY_TOUCH) {
		if (touching(touch, mainButtons[0])) {
			if (Msg::promptMsg2("Would you like to start a new game?\n3DEins isn't fully implemented right now.")) {
				Gui::setScreen(std::make_unique<Test>());
			}
		} else if (touching(touch, mainButtons[1])) {
			Gui::setScreen(std::make_unique<ColorCard>());
		} else if (touching(touch, mainButtons[2])) {
			Gui::setScreen(std::make_unique<Credits>());
		}
	}


	if (hDown & KEY_A) {
		if (Selection == 0) {
			if (Msg::promptMsg2("Would you like to start a new game?\n3DEins isn't fully implemented right now.")) {
				Gui::setScreen(std::make_unique<Test>());
			}
		} else if (Selection == 1) {
			Gui::setScreen(std::make_unique<ColorCard>());
		} else if (Selection == 2) {
			Gui::setScreen(std::make_unique<Credits>());
		}
	}

	if (hDown & KEY_DOWN) {
		if (Selection < 3)	Selection++;
	}

	if (hDown & KEY_UP) {
		if (Selection > 0)	Selection--;
	}

	if (hDown & KEY_START) {
		exiting = true;
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox("START: Exit the App.\n\uE000: Select");
	}
}