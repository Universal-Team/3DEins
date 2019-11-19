/*
*   This file is part of 3DEins
*   Copyright (C) 2019 VoltZ
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

#define TotalCards 54

void Test::Draw(void) const {
	Gui::DrawTop();
	Gui::DrawString(165, 2, 0.9f, WHITE, "3DEins");
	Gui::DrawSelectedCard(currentCard, 170, 80);
	Gui::DrawBottom();

	// Player Statistics Rectangles.
	Gui::Draw_Rect(0, 40+(0*57), 320, 45, C2D_Color32(130, 0, 0, 180));
	Gui::Draw_Rect(0, 40+(1*57), 320, 45, C2D_Color32(130, 0, 0, 180));
	Gui::Draw_Rect(0, 40+(2*57), 320, 45, C2D_Color32(130, 0, 0, 180));

	if (CardGetter::isBlue(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(0*57), 0.7f, WHITE, "This is a Blue card.", 320);
	} else if (CardGetter::isGreen(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(0*57), 0.7f, WHITE, "This is a Green Card.", 320);
	} else if (CardGetter::isRed(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(0*57), 0.7f, WHITE, "This is a Red Card.", 320);
	} else if (CardGetter::isYellow(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(0*57), 0.7f, WHITE, "This is a Yellow Card.", 320);
	} else {
		Gui::DrawStringCentered(0, 50+(0*57), 0.7f, WHITE, "This is a special Card.", 320);
	}

	if (CardGetter::isNumberCard(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(1*57), 0.7f, WHITE, "This is a Number card.", 320);
	} else if (CardGetter::isPlus2(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(1*57), 0.7f, WHITE, "This is a Plus2 card.", 320);
	} else if (CardGetter::isReturn(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(1*57), 0.7f, WHITE, "This is a Return card.", 320);
	} else if (CardGetter::isExpose(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(1*57), 0.7f, WHITE, "This is a expose card.", 320);
	} else if (CardGetter::isWish(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(1*57), 0.7f, WHITE, "This is a Wish card.", 320);
	} else if (CardGetter::isPlus4(currentCard) == true) {
		Gui::DrawStringCentered(0, 50+(1*57), 0.7f, WHITE, "This is a Plus4 card.", 320);
	} else {
		Gui::DrawStringCentered(0, 50+(1*57), 0.7f, WHITE, "This is a blank card.", 320);
	}
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