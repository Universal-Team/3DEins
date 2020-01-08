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

#include "gui/gui.hpp"

#include "screens/test.hpp"

#include "utils/cardHelper.hpp"

#define TotalCards 14
extern C2D_SpriteSheet cards;

void Test::Draw(void) const {
	Gui::DrawTop();
	Gui::DrawString(165, 2, 0.9f, WHITE, "3DEins");
	Gui::DrawSelectedCard(currentCard, 170, 80, 1);

	C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 15), 10, 85, 0.5f, NULL, 0.8, 0.8);
	Gui::DrawString(15, 100, 0.7f, BLACK, std::to_string(player2Cards));

	C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 15), 350, 85, 0.5f, NULL, 0.8, 0.8);
	Gui::DrawString(355, 100, 0.7f, BLACK, std::to_string(player3Cards));


	Gui::DrawBottom();

	Gui::DrawCard(Card1, 15, 160, 1, 0.8, 0.8);
	Gui::DrawCard(Card2, 65, 160, 2, 0.8, 0.8);
	Gui::DrawCard(Card3, 115, 160, 3, 0.8, 0.8);
	Gui::DrawCard(Card4, 165, 160, 4, 0.8, 0.8);
	Gui::DrawCard(Card5, 215, 160, 3, 0.8, 0.8);
	Gui::DrawCard(Card6, 265, 160, 2, 0.8, 0.8);
}

// Randomize all cards.
Test::Test() {
	Card1 = rand() % 14 + 0;
	Card2 = rand() % 14 + 0;
	Card3 = rand() % 14 + 0;
	Card4 = rand() % 14 + 0;
	Card5 = rand() % 14 + 0;
	Card6 = rand() % 14 + 0;
}

void Test::Logic(u32 hDown, u32 hHeld, touchPosition touch) {

	if (hDown & KEY_RIGHT) {
		if (currentCard < TotalCards) {
			currentCard++;
		}
	}

	if (hDown & KEY_LEFT ) {
		if (currentCard > 0) {
			currentCard--;
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}
}