/*
*   This file is part of DSEins
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

#include "gameScreen.hpp"

extern bool exiting;

GameScreen::GameScreen() {
	this->currentGame = std::make_unique<Game>(this->playerAmount);
}

void GameScreen::Draw(void) const {
	Gui::DrawTop(true);
	Gui::DrawBottom(true);
	this->ShowCards();
}

// This is just raw Text for now.
void GameScreen::ShowCards(void) const {
	std::string cards;
	for (int i = 0; i < (int)this->currentGame->getSize(0); i++) {
		if (i == this->currentGame->cardIndex(0)) {
			cards += "> " + GameHelper::getTypeName(this->currentGame->getType(i, 0)) + " | " + GameHelper::getColorName(this->currentGame->getColor(i, 0)) + "\n";
		} else {
			cards += GameHelper::getTypeName(this->currentGame->getType(i, 0)) + " | " + GameHelper::getColorName(this->currentGame->getColor(i, 0)) + "\n";
		}
	}

	printText(cards, 5, 10, false, true);
}


void GameScreen::Logic(u16 hDown, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		Gui::DrawScreen();
		return;
	}

	if (hDown & KEY_DOWN) {
		if (this->currentGame->cardIndex(0) < this->currentGame->getSize(0) -1) {
			this->currentGame->cardIndex(this->currentGame->cardIndex(0) + 1, 0);
			Gui::DrawScreen();
		}
	}

	if (hDown & KEY_UP) {
		if (this->currentGame->cardIndex(0) > 0) {
			this->currentGame->cardIndex(this->currentGame->cardIndex(0) - 1, 0);
			Gui::DrawScreen();
		}
	}
}