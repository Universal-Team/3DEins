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

extern bool touching(touchPosition touch, Structs::ButtonPos button);

// 4 Chars: StackZ, Carl, Isabel, Lea.
void CharSelection::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, WHITE, "3DEins - " + Lang::get("CHAR_SELECTION"), 320);
	GFX::DrawPlayer(-5, 35, 0, 0, state);
	GFX::DrawPlayer(95, 35, 0, 1, state);
	GFX::DrawPlayer(195, 35, 0, 2, state);
	GFX::DrawPlayer(295, 35, 0, 3, state);

	Gui::Draw_Rect(10, 160, 80, 30, C2D_Color32(200, 80, 0, 255));
	Gui::Draw_Rect(110, 160, 80, 30, C2D_Color32(200, 80, 0, 255));
	Gui::Draw_Rect(210, 160, 80, 30, C2D_Color32(200, 80, 0, 255));
	Gui::Draw_Rect(310, 160, 80, 30, C2D_Color32(200, 80, 0, 255));

	Gui::DrawString(25, 165, 0.7f, WHITE, "StackZ");
	Gui::DrawString(133, 165, 0.7f, WHITE, "Carl");
	Gui::DrawString(227, 165, 0.7f, WHITE, "Isabel");
	Gui::DrawString(332, 165, 0.7f, WHITE, "Lea");

	GFX::DrawSprite(sprites_pointer_idx, mainButtons[Selection].x+50, mainButtons[Selection].y+145);
	GFX::DrawBottom();
}

void CharSelection::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_R) {
		if (state < 4)	state++;
	}

	if (hDown & KEY_L) {
		if (state > 0)	state--;
	}

	if (hDown & KEY_RIGHT) {
		if (Selection < 3)	Selection++;
	}

	if (hDown & KEY_LEFT) {
		if (Selection > 0)	Selection--;
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("CHAR_SELECTION_INSTR"));
	}
}