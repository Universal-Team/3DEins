/*
*   This file is part of DSEins
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

#include "gameScreen.hpp"
#include "modeSelect.hpp"
#include "selector.hpp"

extern std::unique_ptr<Selector> selector;
extern bool Buttontouching(ButtonStruct button);
extern bool touching(touchPosition touch, Structs::ButtonPos button);

void ModeSelect::Draw(void) const {
	if (this->mode == 0) {
		this->DrawModeSelect();
	} else {
		this->DrawPlayerSelect();
	}
}

void ModeSelect::DrawModeSelect(void) const {
	Gui::DrawTop(true);
	printTextCentered(Lang::get("SELECT_GAME_MODE"), 0, 1, true, true);
	Gui::DrawBottom(true);

	for (int i = 0; i < 2; i++) {
		Gui::DrawButton(this->modeSelect[i]);
	}
}

void ModeSelect::DrawPlayerSelect(void) const {
	Gui::DrawTop(true);
	printTextCentered(Lang::get("SELECT_PLAYER_AMOUNT"), 0, 1, true, true);
	Gui::DrawBottom(true);

	Gui::DrawCard(CardType::NUMBER_2, CardColor::COLOR_RED, playerSelect[0].x, playerSelect[0].y, 1, 1, false, true);
	Gui::DrawCard(CardType::NUMBER_3, CardColor::COLOR_BLUE, playerSelect[1].x, playerSelect[1].y, 1, 1, false, true);
	Gui::DrawCard(CardType::NUMBER_4, CardColor::COLOR_GREEN, playerSelect[2].x, playerSelect[2].y, 1, 1, false, true);
}

void ModeSelect::Logic(u16 hDown, touchPosition touch) {
	if (this->mode == 0) {
		this->ModeLogic(hDown, touch);
	} else {
		this->PlayerLogic(hDown, touch);
	}
}

void ModeSelect::ModeLogic(u16 hDown, touchPosition touch) {
	if (doUpdate) {
		selector->move(this->modeSelect[this->modeSel].x, this->modeSelect[this->modeSel].y);
		selector->update();
	}

	if (hDown & KEY_DOWN) {
		if (this->modeSel == 0) {
			this->modeSel = 1;
			doUpdate = true;
		}
	}

	if (hDown & KEY_UP) {
		if (this->modeSel == 1) {
			this->modeSel = 0;
			doUpdate = true;
		}
	}

	if (hDown & KEY_TOUCH) {
		for (int i = 0; i < 2; i++) {
			if (Buttontouching(this->modeSelect[i])) {
				this->modeSel = i;
				this->mode = 1;
				selector->resize(60, 90);
				doUpdate = true;
				Gui::DrawScreen();
			}
		}
	}

	if (hDown & KEY_A) {
		this->mode = 1;
		selector->resize(60, 90);
		doUpdate = true;
		Gui::DrawScreen();
	}

	if (hDown & KEY_B) {
		Gui::screenBack();
		doUpdate = true;
		Gui::DrawScreen();
		return;
	}
}

void ModeSelect::PlayerLogic(u16 hDown, touchPosition touch) {
	if (doUpdate) {
		selector->move(this->playerSelect[this->playerSel].x, this->playerSelect[this->playerSel].y);
		selector->update();
	}

	if (hDown & KEY_LEFT) {
		if (this->playerSel > 0) {
			this->playerSel--;
			doUpdate = true;
		}
	}

	if (hDown & KEY_RIGHT) {
		if (this->playerSel < 2) {
			this->playerSel++;
			doUpdate = true;
		}
	}

	if (hDown & KEY_TOUCH) {
		for (int i = 0; i < 3; i++) {
			if (touching(touch, this->playerSelect[i])) {
				selector->hide();
				doUpdate = true;
				selector->update();

				this->playerSel = i;
				if (this->modeSel == 0) {
					Gui::setScreen(std::make_unique<GameScreen>(true, 2 + this->playerSel));
				} else {
					Gui::setScreen(std::make_unique<GameScreen>(false, 2 + this->playerSel));
				}

				Gui::DrawScreen();
			}
		}
	}

	if (hDown & KEY_A) {
		selector->hide();
		doUpdate = true;
		selector->update();
		if (this->modeSel == 0) {
			Gui::setScreen(std::make_unique<GameScreen>(true, 2 + this->playerSel));
		} else {
			Gui::setScreen(std::make_unique<GameScreen>(false, 2 + this->playerSel));
		}
		
		Gui::DrawScreen();
	}

	if (hDown & KEY_B) {
		this->mode = 0;
		selector->resize(80, 40);
		doUpdate = true;
		Gui::DrawScreen();
	}
}