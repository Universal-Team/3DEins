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

#include "_DSEins_Helper.hpp"
#include "gui.hpp"
#include "lang.hpp"
#include "structs.hpp"

#include <nds.h>

extern touchPosition touch;
std::vector<Structs::ButtonPos> colorPos = {
	{30, 45, 80, 40},   // Red.
	{130, 45, 80, 40},  // Blue.
	{30, 105, 80, 40},  // Yellow.
	{130, 105, 80, 40}  // Green.
};

extern bool touching(touchPosition touch, Structs::ButtonPos button);

// Select a Color.
CardColor _DSEins_Helper::selectColor() {
	int selection = 0;

	Gui::clearScreen(true, true);
	Gui::clearScreen(false, true);
	printTextCentered(Lang::get("SELECT_COLOR"), 0, 3, true, true);
	drawRectangle(colorPos[0].x, colorPos[0].y, colorPos[0].w, colorPos[0].h, CARD_COLOR_RED, false, true);
	drawRectangle(colorPos[1].x, colorPos[1].y, colorPos[1].w, colorPos[1].h, CARD_COLOR_BLUE, false, true);
	drawRectangle(colorPos[2].x, colorPos[2].y, colorPos[2].w, colorPos[2].h, CARD_COLOR_YELLOW, false, true);
	drawRectangle(colorPos[3].x, colorPos[3].y, colorPos[3].w, colorPos[3].h, CARD_COLOR_GREEN, false, true);
	drawOutline(colorPos[selection].x, colorPos[selection].y, colorPos[selection].w, colorPos[selection].h, WHITE, false, true);

	while(1) {
		// The input part.
		scanKeys();
		touchRead(&touch);

		if (keysDown() & KEY_UP) {
			if (selection == 2)	selection -= 2;
			else if (selection == 3)	selection -= 2;
		} else if (keysDown() & KEY_DOWN) {
			if (selection == 0)	selection += 2;
			else if (selection == 1)	selection += 2;
		}

		if (keysDown() & KEY_LEFT) {
			if (selection > 0)	selection--;
		} else if (keysDown() & KEY_RIGHT) {
			if (selection < 3)	selection++;
		}

		if (keysDown() & KEY_A) {
			if (selection == 0) {
				return CardColor::COLOR_RED;
			} else if (selection == 1) {
				return CardColor::COLOR_BLUE;
			} else if (selection == 2) {
				return CardColor::COLOR_YELLOW;
			} else if (selection == 3) {
				return CardColor::COLOR_GREEN;
			}
		}

		if (keysDown() & KEY_TOUCH) {
			if (touching(touch, colorPos[0])) {
				return CardColor::COLOR_RED;
			} else if (touching(touch, colorPos[1])) {
				return CardColor::COLOR_BLUE;
			} else if (touching(touch, colorPos[2])) {
				return CardColor::COLOR_YELLOW;
			} else if (touching(touch, colorPos[3])) {
				return CardColor::COLOR_GREEN;
			}
		}
	}

	// Redraw screen.
	Gui::DrawScreen();
}