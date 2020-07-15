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
#include "overlay.hpp"
#include "structs.hpp"

extern std::unique_ptr<Config> config;
extern touchPosition touch;
const std::vector<Structs::ButtonPos> colorPos = {
	{10, 70, 140, 40}, // Red.
	{170, 70, 140, 40}, // Blue.
	{10, 145, 140, 40}, // Yellow.
	{170, 145, 140, 40}  // Green.
};

extern bool touching(Structs::ButtonPos button);

static void Draw(int selection) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
	GFX::DrawTop();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 190));
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.7f, Lang::get("SELECT_COLOR")))/2, 0.7f, config->textColor(), Lang::get("SELECT_COLOR"), 390, 70);
	GFX::DrawBottom();
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 190));
	Gui::Draw_Rect(10, 70, 140, 40, config->cardRed());
	Gui::Draw_Rect(170, 70, 140, 40, config->cardBlue());
	Gui::Draw_Rect(10, 145, 140, 40, config->cardYellow());
	Gui::Draw_Rect(170, 145, 140, 40, config->cardGreen());
	Gui::DrawStringCentered(10 - 160 + (140/2), 70 + (40/2) - 10, 0.6f, config->textColor(), Lang::get("COLOR_RED"), 140-17, 40-5);
	Gui::DrawStringCentered(170 - 160 + (140/2), 70 + (40/2) - 10, 0.6f, config->textColor(), Lang::get("COLOR_BLUE"), 140-17, 40-5);
	Gui::DrawStringCentered(10 - 160 + (140/2), 145 + (40/2) - 10, 0.6f, config->textColor(), Lang::get("COLOR_YELLOW"), 140-17, 40-5);
	Gui::DrawStringCentered(170 - 160 + (140/2), 145 + (40/2) - 10, 0.6f, config->textColor(), Lang::get("COLOR_GREEN"), 140-17, 40-5);
	GFX::DrawButtonSelector(colorPos[selection].x, colorPos[selection].y);
	C3D_FrameEnd(0);
}


CardColor Overlays::SelectCardColor() {
	int selection = 0;
	while(1) {
		Draw(selection);

		hidScanInput();
		hidTouchRead(&touch);

		if (hidKeysDown() & KEY_UP) {
			if (selection > 1) selection -= 2;
		}
		
		if (hidKeysDown() & KEY_DOWN) {
			if (selection < 2) selection += 2;
		}

		if (hidKeysDown() & KEY_LEFT) {
			if (selection > 0) selection--;
		}

		if (hidKeysDown() & KEY_RIGHT) {
			if (selection < 3) selection++;
		}

		if (hidKeysDown() & KEY_A) {
			switch(selection) {
				case 0:
					return CardColor::COLOR_RED;
				case 1:
					return CardColor::COLOR_BLUE;
				case 2:
					return CardColor::COLOR_YELLOW;
				case 3:
					return CardColor::COLOR_GREEN;
			}
		}

		if (hidKeysDown() & KEY_TOUCH) {
			if (touching(colorPos[0])) {
				return CardColor::COLOR_RED;
			} else if (touching(colorPos[1])) {
				return CardColor::COLOR_BLUE;
			} else if (touching(colorPos[2])) {
				return CardColor::COLOR_YELLOW;
			} else if (touching(colorPos[3])) {
				return CardColor::COLOR_GREEN;
			}
		}
	}
}