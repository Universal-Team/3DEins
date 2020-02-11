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
#include "charSelection.hpp"
#include "credits.hpp"
#include "langSelection.hpp"
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
	Gui::DrawString(100, 0, 0.9f, WHITE, "3DEins - " + Lang::get("MAINMENU"));
	GFX::DrawCard(Card1, 40, 65, Color1, 1.5, 1.5);
	GFX::DrawCard(Card2, 160, 65, Color2, 1.5, 1.5);
	GFX::DrawCard(Card3, 280, 65, Color3, 1.5, 1.5);

	GFX::DrawBottom();
	for (int i = 0; i < 4; i++) {
		Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, C2D_Color32(170, 60, 0, 200));
		if (Selection == i) {
			GFX::DrawSprite(sprites_pointer_idx, mainButtons[i].x+130, mainButtons[i].y+25);
		}
	}

	Gui::DrawStringCentered(-80, mainButtons[0].y+12, 0.6f, WHITE, Lang::get("NEW_GAME"), 130);
	Gui::DrawStringCentered(80, mainButtons[1].y+12, 0.6f, WHITE, Lang::get("CARD_COLORS"), 130);
	Gui::DrawStringCentered(-80, mainButtons[2].y+12, 0.6f, WHITE, Lang::get("CREDITS"), 130);
	Gui::DrawStringCentered(80, mainButtons[3].y+12, 0.6f, WHITE, Lang::get("LANGUAGE"), 130);
}


void MainMenu::Logic(u32 hDown, u32 hHeld, touchPosition touch) {

	if (hDown & KEY_TOUCH) {
		if (touching(touch, mainButtons[0])) {
			if (Msg::promptMsg2(Lang::get("NEW_GAME_PROMPT"))) {
				Gui::setScreen(std::make_unique<Test>());
			}
		} else if (touching(touch, mainButtons[1])) {
			Gui::setScreen(std::make_unique<ColorCard>());
		} else if (touching(touch, mainButtons[2])) {
			Gui::setScreen(std::make_unique<Credits>());
		} else if (touching(touch, mainButtons[3])) {
			Gui::setScreen(std::make_unique<LangSelection>());
		}
	}


	if (hDown & KEY_A) {
		if (Selection == 0) {
			if (Msg::promptMsg2(Lang::get("NEW_GAME_PROMPT"))) {
				Gui::setScreen(std::make_unique<Test>());
			}
		} else if (Selection == 1) {
			Gui::setScreen(std::make_unique<ColorCard>());
		} else if (Selection == 2) {
			Gui::setScreen(std::make_unique<Credits>());
		} else if (Selection == 3) {
			Gui::setScreen(std::make_unique<LangSelection>());
		}
	}

	if(hDown & KEY_UP) {
		if(Selection > 1)	Selection -= 2;
	} else if(hDown & KEY_DOWN) {
		if(Selection < 3 && Selection != 2 && Selection != 3)	Selection += 2;
	} else if (hDown & KEY_LEFT) {
		if (Selection%2) Selection--;
	} else if (hDown & KEY_RIGHT) {
		if (!(Selection%2)) Selection++;
	}

	if (hDown & KEY_START) {
		exiting = true;
	}

	if (hDown & KEY_Y) {
		Gui::setScreen(std::make_unique<CharSelection>());
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("MAINMENU_INSTRUCTIONS"));
	}
}