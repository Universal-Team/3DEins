/*
*   This file is part of DSEins
*   Copyright (C) 2019-2021 Universal-Team
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
#include "selector.hpp"
#include "structs.hpp"

#include <nds.h>

extern bool doUpdate;
extern std::unique_ptr<Selector> selector;
extern touchPosition touch;

const std::vector<ButtonStruct> colorPos = {
	{ 30, 45, 80, 40, "COLOR_RED", CARD_COLOR_RED, true }, // Red.
	{ 130, 45, 80, 40, "COLOR_BLUE", CARD_COLOR_BLUE, true }, // Blue.
	{ 30, 105, 80, 40, "COLOR_YELLOW", CARD_COLOR_YELLOW, true }, // Yellow.
	{ 130, 105, 80, 40, "COLOR_GREEN", CARD_COLOR_GREEN, true } // Green.
};

extern bool Buttontouching(ButtonStruct button);

/* Select a Color. */
CardColor _DSEins_Helper::selectColor() {
	int selection = 0;

	selector->show();
	selector->resize(80, 40);
	selector->move(colorPos[selection].x, colorPos[selection].y);
	doUpdate = true;
	selector->update();

	Gui::clearScreen(true, true);
	Gui::clearScreen(false, true);
	Gui::DrawTop(true);
	printTextCentered(Lang::get("SELECT_COLOR"), 0, 2, true, true);

	for (int i = 0; i < 4; i++) {
		Gui::DrawButton(colorPos[i], TextColor::white);
	}

	while(1) {
		if (doUpdate) {
			selector->move(colorPos[selection].x, colorPos[selection].y);
			selector->update();
		}

		/* The input part. */
		swiWaitForVBlank();
		scanKeys();
		touchRead(&touch);

		if (keysDown() & KEY_UP) {
			if (selection == 2) {
				selection -= 2;
				doUpdate = true;

			} else if (selection == 3) {
				selection -= 2;
				doUpdate = true;
			}

		}

		if (keysDown() & KEY_DOWN) {
			if (selection == 0) {
				selection += 2;
				doUpdate = true;

			} else if (selection == 1) {
				selection += 2;
				doUpdate = true;
			}
		}

		if (keysDown() & KEY_LEFT) {
			if (selection > 0) {
				selection--;
				doUpdate = true;
			}
		}

		if (keysDown() & KEY_RIGHT) {
			if (selection < 3) {
				selection++;
				doUpdate = true;
			}
		}

		if (keysDown() & KEY_A) {
			selector->hide();
			selector->resize(60, 90);
			doUpdate = true;
			selector->update();

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
			if (Buttontouching(colorPos[0])) {
				selector->hide();
				selector->resize(60, 90);
				doUpdate = true;
				selector->update();
				return CardColor::COLOR_RED;

			} else if (Buttontouching(colorPos[1])) {
				selector->hide();
				selector->resize(60, 90);
				doUpdate = true;
				selector->update();
				return CardColor::COLOR_BLUE;

			} else if (Buttontouching(colorPos[2])) {
				selector->hide();
				selector->resize(60, 90);
				doUpdate = true;
				selector->update();
				return CardColor::COLOR_YELLOW;

			} else if (Buttontouching(colorPos[3])) {
				selector->hide();
				selector->resize(60, 90);
				doUpdate = true;
				selector->update();
				return CardColor::COLOR_GREEN;
			}
		}
	}

	/* Redraw. */
	Gui::DrawScreen();
}