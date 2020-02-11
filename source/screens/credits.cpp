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

#include "credits.hpp"

extern bool touching(touchPosition touch, Structs::ButtonPos button);

void Credits::Draw(void) const {
	if (DisplayMode == 1) {
		GFX::DrawTop();
		Gui::DrawStringCentered(0, 0, 0.9f, WHITE, "3DEins - Credits", 400);
		Gui::DrawStringCentered(0, 30, 0.9f, WHITE, "Developed by: Universal-Team.", 390);
		Gui::DrawStringCentered(0, 70, 0.9f, WHITE, "Main Developer: StackZ", 390);
		GFX::DrawSprite(sprites_stackZ_idx, 120, 100);
		Gui::DrawString(395-Gui::GetStringWidth(0.7, V_STRING), 215, 0.7, WHITE, V_STRING, 400);
		GFX::DrawBottom();
		Gui::DrawStringCentered(0, 217, 0.6f, WHITE, discordText ? "Click here to show the QR Code." : "Join our Discord: https://discord.gg/KDJCfGF", 310);
	 } else if (DisplayMode == 2) {
		qr_code();
	}
}

void Credits::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	Loop();
	if (DisplayMode == 1) {
		if (hHeld & KEY_SELECT) {
			Msg::HelperBox("Touch the Bar for a QR Code to our discord.\n\uE001: Back");
		}

		if (hDown & KEY_B) {
			Gui::screenBack();
			return;
		}
		if (hDown & KEY_TOUCH) {
			if (touching(touch, touchPos[0])) {
				DisplayMode = 2;
			}
		}

	} else if (DisplayMode == 2) {
		if (hHeld & KEY_SELECT) {
			Msg::HelperBox("\uE001: Back");
		}

		if (hDown & KEY_B) {
			DisplayMode = 1;
		}
	}
}

void Credits::qr_code() const
{
	GFX::DrawTop();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 190));
	GFX::DrawSprite(sprites_discord_idx, 115, 35);
	GFX::DrawBottom();
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 190));
}

void Credits::Loop() {
	gspWaitForVBlank();
	if(delay > 0) {
		delay--;
	} else {
		delay = 120;
		discordText = !discordText;
	}
}