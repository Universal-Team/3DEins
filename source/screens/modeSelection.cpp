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

#include "charSelection.hpp"
#include "modeSelection.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

// Player Amount is 2 by Initialize.
int playerAmount = 2;

void ModeSelection::Draw(void) const {
	if (Mode == 1) {
		DrawMode();
	} else {
		DrawPlayerAmount();
	}
}

void ModeSelection::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (Mode == 1) {
		MSelection(hDown, hHeld, touch);
	} else {
		PlayerSelection(hDown, hHeld, touch);
	}
}

void ModeSelection::DrawMode(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, WHITE, "3DEins - " + Lang::get("MODE_SELECTION"), 320);
	GFX::DrawBottom();
	for (int i = 0; i < 3; i++) {
		Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, C2D_Color32(170, 60, 0, 200));
		if (Selection == i) {
			GFX::DrawSprite(sprites_pointer_idx, mainButtons[i].x+130, mainButtons[i].y+25);
		}
	}
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("SINGLE_PLAYER")))/2-80+17.5, 0.6, WHITE, Lang::get("SINGLE_PLAYER"), 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("MULTI_PLAYER")))/2-20+17.5, 0.6, WHITE, Lang::get("MULTI_PLAYER"), 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("BACK")))/2+75-17.5, 0.6, WHITE, Lang::get("BACK"), 130, 25);
}

void ModeSelection::DrawPlayerAmount(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, WHITE, Lang::get("PLAYER_AMOUNT"), 320);
	GFX::DrawBottom();
	GFX::DrawCard(CardType::NUMBER_2, 20, 60, CardColor::RED, 1.4, 1.4);
	GFX::DrawCard(CardType::NUMBER_3, 120, 60, CardColor::BLUE, 1.4, 1.4);
	GFX::DrawCard(CardType::NUMBER_4, 220, 60, CardColor::YELLOW, 1.4, 1.4);
	GFX::DrawSprite(sprites_pointer_idx, 60 + ((amountSelection - 2) * 90), 100);
}

void ModeSelection::MSelection(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_DOWN) {
		if (Selection < 2)	Selection++;
	}
	if (hDown & KEY_UP) {
		if (Selection > 0)	Selection--;
	}

	if (hDown & KEY_A) {
		if (Selection == 0) {
			Msg::NotImplementedYet(); // Single player not done yet.
		} else if (Selection == 1) {
			Mode = 2;
		} else if (Selection == 2) {
			Gui::screenBack();
			return;
		}
	}
}

void ModeSelection::PlayerSelection(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_RIGHT) {
		if (amountSelection < 4)	amountSelection++;
	}
	if (hDown & KEY_LEFT) {
		if (amountSelection > 2)	amountSelection--;
	}

	if (hDown & KEY_B) {
		Mode = 1;
	}

	if (hDown & KEY_A) {
		playerAmount = amountSelection;
		Gui::setScreen(std::make_unique<CharSelection>());
	}
}