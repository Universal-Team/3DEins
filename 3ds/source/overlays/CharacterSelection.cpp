/*
*   This file is part of 3DEins
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

#include "config.hpp"
#include "overlay.hpp"
#include "structs.hpp"

extern touchPosition touch;
extern std::unique_ptr<Config> config;

static void Draw(int page, int selection) {
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
	GFX::DrawTop();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 190));
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), Lang::get("SELECT_CHARACTER"), 390, 30);

	if (page == 1) {
		GFX::DrawPlayer(-5, 35, 1, 1, 0);
		GFX::DrawPlayer(95, 35, 1, 1, 1);
		GFX::DrawPlayer(195, 35, 1, 1, 2);
		GFX::DrawPlayer(295, 35, 1, 1, 3);
	} else if (page == 2) {
		GFX::DrawPlayer(-5, 35, 1, 1, 4);
		GFX::DrawPlayer(95, 35, 1, 1, 5);
		GFX::DrawPlayer(195, 35, 1, 1, 6);
		GFX::DrawPlayer(295, 35, 1, 1, 7);
	}

	Gui::Draw_Rect(10, 160, 80, 30, config->buttonColor());
	Gui::Draw_Rect(110, 160, 80, 30, config->buttonColor());
	Gui::Draw_Rect(210, 160, 80, 30, config->buttonColor());
	Gui::Draw_Rect(310, 160, 80, 30, config->buttonColor());

	if (page == 1) {
		GFX::DrawButtonSelector(10 + (selection * 100), 160, 1, 1, true);
	} else {
		GFX::DrawButtonSelector(10 + ((selection-4) * 100), 160, 1, 1, true);
	}

	GFX::DrawBottom();
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 190));
	C3D_FrameEnd(0);
}

/* Select an avatar. */
int Overlays::SelectAvatar(int oldAvatar) {
	int selection = 0;
	int page = 1;

	while(1) {
		Draw(page, selection);

		/* The input part. */
		hidScanInput();
		hidTouchRead(&touch);

		/* Page Switches. */
		if (hidKeysDown() & KEY_R) {
			if (page == 1) {
				page = 2;
				selection += 4;
			}
		}

		if (hidKeysDown() & KEY_L) {
			if (page == 2) {
				page = 1;
				selection -= 4;
			}
		}

		if (hidKeysDown() & KEY_RIGHT) {
			if (page == 1) {
				if (selection > 2) {
					selection++;
					page++;
				} else {
					selection++;
				}
			} else if (page == 2) {
				if (selection < 7) {
					selection++;
				}
			}
		}

		if (hidKeysDown() & KEY_LEFT) {
			if (page == 1) {
				if (selection > 0) {
					selection--;
				}
			} else if (page == 2) {
				if (selection < 5) {
					selection--;
					page--;
				} else {
					selection--;
				}
			}
		}

		if (hidKeysDown() & KEY_A) {
			return selection;
		}

		if (hidKeysDown() & KEY_B) {
			return oldAvatar;
		}
	}
}