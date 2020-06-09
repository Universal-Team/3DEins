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

#include "config.hpp"
#include "credits.hpp"

extern std::unique_ptr<Config> config;

extern bool touching(touchPosition touch, Structs::ButtonPos button);

void Credits::Draw(void) const {
	GFX::DrawTop(); // Draw the top screen.
	if (this->creditsPage == 0) {
		Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), "3DEins - " + Lang::get("CREDITS"), 400);
		Gui::DrawStringCentered(0, 30, 0.7f, config->textColor(), Lang::get("DEVELOPED_BY"), 390);
		Gui::DrawStringCentered(0, 50, 0.7f, config->textColor(), Lang::get("MAIN_DEV"), 390);
		GFX::DrawSprite(sprites_stackie_idx, 2, 80);
		GFX::DrawSprite(sprites_core_idx, 190, 105);
		std::string currentVersion = Lang::get("CURRENT_VERSION");
		currentVersion += V_STRING;
		Gui::DrawString(395-Gui::GetStringWidth(0.70f, currentVersion), 217, 0.70f, config->textColor(), currentVersion, 400);
	} else {
		Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 190));
		GFX::DrawSprite(sprites_discord_idx, 115, 35);
	}

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	GFX::DrawBottom();
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), Lang::get("GENERAL_CREDITS"), 310);
	Gui::DrawStringCentered(0, 30, 0.7f, config->textColor(), "Stack-Team", 310);
	Gui::DrawStringCentered(0, 60, 0.6f, config->textColor(), Lang::get("_3DEINS_CORE"), 310);
	Gui::DrawStringCentered(0, 100, 0.7f, config->textColor(), "Universal-Team", 310);
	Gui::DrawStringCentered(0, 130, 0.6f, config->textColor(), Lang::get("UNIVERSAL_CORE"), 310);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}


void Credits::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if ((hDown & KEY_L || hDown & KEY_LEFT)) {
		if (this->creditsPage == 1) {
			this->creditsPage = 0;
		}
	}

	if ((hDown & KEY_R || hDown & KEY_RIGHT)) {
		if (this->creditsPage == 0) {
			this->creditsPage = 1;
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack(true);
		return;
	}
}