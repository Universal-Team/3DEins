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
		Gui::DrawStringCentered(0, 0, 0.9f, Config::Text, "3DEins - " + Lang::get("CREDITS"), 400);
		Gui::DrawStringCentered(0, 30, 0.9f, Config::Text, Lang::get("DEVELOPED_BY"), 390);
		Gui::DrawStringCentered(0, 70, 0.9f, Config::Text, Lang::get("MAIN_DEV"), 390);
		GFX::DrawSprite(sprites_stackZ_idx, 120, 100);
		Gui::DrawString(395-Gui::GetStringWidth(0.7, Lang::get("CURRENT_VERSION") + V_STRING), 215, 0.7, Config::Text, Lang::get("CURRENT_VERSION") + V_STRING, 400);
		GFX::DrawBottom();

		// TODO.
		if (creditsPage == 1) {
			Gui::DrawStringCentered(0, -2, 0.7f, Config::Text, Lang::get("TRANSLATORS"), 320);
			Gui::DrawString(5, 30, 0.6f, Config::Text, "- _mapple²\n- antoine62\n- Pk11\n- StackZ\n- YoSoy");
			Gui::DrawString(180, 30, 0.6f, Config::Text, "Русский\nFrançais\n日本語\nDeutsch, English\nEspañol");
		} else if (creditsPage == 2) {
			Gui::DrawStringCentered(0, -2, 0.7f, Config::Text, "Universal-Team", 320);
			Gui::DrawStringCentered(0, 35, 0.7f, Config::Text, "DeadPhoenix");
			Gui::DrawStringCentered(0, 65, 0.7f, Config::Text, "Flame");
			Gui::DrawStringCentered(0, 95, 0.7f, Config::Text, "Pk11");
			Gui::DrawStringCentered(0, 125, 0.7f, Config::Text, "RocketRobz");
			Gui::DrawStringCentered(0, 155, 0.7f, Config::Text, "StackZ");
			Gui::DrawStringCentered(0, 185, 0.7f, Config::Text, "TotallyNotGuy");
		}
		Gui::DrawStringCentered(0, 217, 0.6f, Config::Text, discordText ? Lang::get("SHOW_QR") : Lang::get("LINK"), 310);
	 } else if (DisplayMode == 2) {
		qr_code();
	}
}

void Credits::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	Loop();
	if (DisplayMode == 1) {
		if (hHeld & KEY_SELECT) {
			Msg::HelperBox(Lang::get("CREDITS_INSTRUCTIONS"));
		}

		if (hDown & KEY_RIGHT) {
			if (creditsPage < 2)	creditsPage++;
		}

		if (hDown & KEY_LEFT) {
			if (creditsPage > 1)	creditsPage--;
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
			Msg::HelperBox(Lang::get("CREDITS_INSTRUCTIONS_2"));
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