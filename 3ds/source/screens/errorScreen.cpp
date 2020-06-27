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

#include "errorScreen.hpp"

extern bool exiting;

void ErrorScreen::Draw(void) const {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 30, C2D_Color32(220, 60, 0, 255));
	Gui::Draw_Rect(0, 30, 400, 180, C2D_Color32(220, 160, 0, 255));
	Gui::Draw_Rect(0, 210, 400, 30, C2D_Color32(220, 60, 0, 255));
	Gui::DrawStringCentered(0, 0, 0.8f, C2D_Color32(255, 255, 255, 255), "Failed to initialize the config class.", 400);
	Gui::DrawStringCentered(0, 215, 0.8f, C2D_Color32(255, 255, 255, 255), "Press START to exit.", 400);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 30, C2D_Color32(220, 60, 0, 255));
	Gui::Draw_Rect(0, 30, 320, 180, C2D_Color32(220, 160, 0, 255));
	Gui::Draw_Rect(0, 210, 320, 30, C2D_Color32(220, 60, 0, 255));
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}

void ErrorScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_START) {
		exiting = true;
	}
}