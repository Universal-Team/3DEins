/*
*   This file is part of 3DEins
*   Copyright (C) 2019-2020 Universal-Team
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
#include "gameScreen.hpp"
#include "modeSelect.hpp"

extern std::unique_ptr<Config> config;
extern bool buttonTouch(ButtonStruct button);
extern bool touching(Structs::ButtonPos button);

void ModeSelect::Draw(void) const {
	if (this->mode == 0) {
		this->DrawModeSelect();
	} else {
		this->DrawPlayerSelect();
	}
}

void ModeSelect::DrawModeSelect(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.7f, config->textColor(), Lang::get("SELECT_GAME_MODE"), 390);
	GFX::DrawBottom();

	for (int i = 0; i < 2; i++) {
		GFX::Button(this->modeSelect[i]);
	}

	GFX::DrawButtonSelector(this->modeSelect[this->modeSel].X, this->modeSelect[this->modeSel].Y);
}

void ModeSelect::DrawPlayerSelect(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.7f, config->textColor(), Lang::get("SELECT_PLAYER_AMOUNT"));
	GFX::DrawBottom();

	GFX::DrawCard(CardType::NUMBER_2, this->playerSelect[0].x, this->playerSelect[0].y, CardColor::COLOR_RED, 1, 1);
	GFX::DrawCard(CardType::NUMBER_3, this->playerSelect[1].x, this->playerSelect[1].y, CardColor::COLOR_BLUE, 1, 1);
	GFX::DrawCard(CardType::NUMBER_4, this->playerSelect[2].x, this->playerSelect[2].y, CardColor::COLOR_GREEN, 1, 1);

	GFX::DrawCardSelector(this->playerSelect[this->playerSel].x, this->playerSelect[this->playerSel].y, 1, 1);
}

void ModeSelect::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->mode == 0) {
		this->ModeLogic(hDown, hHeld, touch);
	} else {
		this->PlayerLogic(hDown, hHeld, touch);
	}
}

void ModeSelect::ModeLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack(true);
		return;
	}

	if (hDown & KEY_DOWN) {
		if (this->modeSel == 0) this->modeSel = 1;
	}

	if (hDown & KEY_UP) {
		if (this->modeSel == 1) this->modeSel = 0;
	}

	if (hDown & KEY_TOUCH) {
		for (int i = 0; i < 2; i++) {
			if (buttonTouch(this->modeSelect[i])) {
				this->modeSel = i;
				this->mode = 1;
			}
		}
	}

	if (hDown & KEY_A) {
		this->mode = 1;
	}
}

void ModeSelect::PlayerLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		this->mode = 0;
	}

	if (hDown & KEY_RIGHT) {
		if (this->playerSel < 2) this->playerSel++;
	}

	if (hDown & KEY_LEFT) {
		if (this->playerSel > 0) this->playerSel--;
	}

	if (hDown & KEY_TOUCH) {
		for (int i = 0; i < 3; i++) {
			if (touching(this->playerSelect[i])) {
				this->playerSel = i;
				
				if (this->modeSel == 0) {
					Gui::setScreen(std::make_unique<GameScreen>(true, 2 + this->playerSel), true, true);
				} else {
					Gui::setScreen(std::make_unique<GameScreen>(false, 2 + this->playerSel), true, true);
				}
			}
		}
	}

	if (hDown & KEY_A) {
		if (this->modeSel == 0) {
			Gui::setScreen(std::make_unique<GameScreen>(true, 2 + this->playerSel), true, true);
		} else {
			Gui::setScreen(std::make_unique<GameScreen>(false, 2 + this->playerSel), true, true);
		}
	}
}