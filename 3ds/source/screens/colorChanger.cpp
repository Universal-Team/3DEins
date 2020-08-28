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

#include "colorChanger.hpp"
#include "colorHelper.hpp"
#include "config.hpp"
#include "keyboard.hpp"
#include "overlay.hpp"

extern std::unique_ptr<Config> config;

extern bool touching(Structs::ButtonPos button);

/* Draw a preview of the color. */
void ColorChanger::DrawPreview(void) const {
	if (this->colorMode == 0) {
		GFX::DrawCardSelector(120, 65, 1.5, 1.5);
	} else if (this->colorMode == 1) {
		Gui::Draw_Rect(130, 120, 150, 40, config->buttonColor());
	}
}

void ColorChanger::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, config->textColor(), "3DEins - " + Lang::get("COLOR_SETTINGS"), 390);
	DrawPreview();
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	GFX::DrawBottom();

	Gui::Draw_Rect(buttons[0].x, buttons[0].y, 95, 41, C2D_Color32(255, 0, 0, 255));
	Gui::Draw_Rect(buttons[1].x, buttons[1].y, 95, 41, C2D_Color32(0, 255, 0, 255));
	Gui::Draw_Rect(buttons[2].x, buttons[2].y, 95, 41, C2D_Color32(0, 0, 255, 255));

	if (this->colorMode == 0) {
		Gui::DrawStringCentered(0, 60, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("SELECTOR_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->selectorColor(), 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->selectorColor(), 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->selectorColor(), 0).c_str(), 400);

	} else if (this->colorMode == 1) {
		Gui::DrawStringCentered(0, 60, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("BUTTON_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->buttonColor(), 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->buttonColor(), 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->buttonColor(), 0).c_str(), 400);

	} else if (this->colorMode == 2) {
		Gui::DrawStringCentered(0, 60, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("BAR_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->barColor(), 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->barColor(), 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->barColor(), 0).c_str(), 400);

	} else if (this->colorMode == 3) {
		Gui::DrawStringCentered(0, 60, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("BG_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->bgColor(), 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->bgColor(), 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->bgColor(), 0).c_str(), 400);

	} else if (this->colorMode == 4) {
		Gui::DrawStringCentered(0, 60, 0.7f, C2D_Color32(255, 255, 255, 255), Lang::get("TEXT_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->textColor(), 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->textColor(), 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, C2D_Color32(255, 255, 255, 255), ColorHelper::getColorName(config->textColor(), 0).c_str(), 400);
	}

	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}

void ColorChanger::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	int red;
	int green;
	int blue;

	if (hDown & KEY_B) {
		Gui::screenBack(true);
		return;
	}

	if (hDown & KEY_LEFT) {
		if (this->colorMode > 0) this->colorMode--;
	}

	if (hDown & KEY_RIGHT) {
		if (this->colorMode < 4) this->colorMode++;
	}

	if (hDown & KEY_A) {
		switch(this->colorMode) {
			case 0:
				config->selectorColor(Overlays::SelectRGB(config->selectorColor()));
				break;
			case 1:
				config->buttonColor(Overlays::SelectRGB(config->buttonColor()));
				break;
			case 2:
				config->barColor(Overlays::SelectRGB(config->barColor()));
				break;
			case 3:
				config->bgColor(Overlays::SelectRGB(config->bgColor()));
				break;
			case 4:
				config->textColor(Overlays::SelectRGB(config->textColor()));
				break;
		}
	}

	if (hDown & KEY_TOUCH) {
		if (touching(buttons[0])) {
			int temp = Keyboard::getUint(255, Lang::get("ENTER_RED_RGB"));
			if (temp != -1) {
				red = temp;
				if (this->colorMode == 0) {
					config->selectorColor(RGBA8(red, ColorHelper::getColorValue(config->selectorColor(), 1), ColorHelper::getColorValue(config->selectorColor(), 0), 255));
				} else if (this->colorMode == 1) {
					config->buttonColor(RGBA8(red, ColorHelper::getColorValue(config->buttonColor(), 1), ColorHelper::getColorValue(config->buttonColor(), 0), 255));
				} else if (this->colorMode == 2) {
					config->barColor(RGBA8(red, ColorHelper::getColorValue(config->barColor(), 1), ColorHelper::getColorValue(config->barColor(), 0), 255));
				} else if (this->colorMode == 3) {
					config->bgColor(RGBA8(red, ColorHelper::getColorValue(config->bgColor(), 1), ColorHelper::getColorValue(config->bgColor(), 0), 255));
				} else if (this->colorMode == 4) {
					config->textColor(RGBA8(red, ColorHelper::getColorValue(config->textColor(), 1), ColorHelper::getColorValue(config->textColor(), 0), 255));
				}
			}

		} else if (touching(buttons[1])) {
			int temp = Keyboard::getUint(255, Lang::get("ENTER_GREEN_RGB"));
			if (temp != -1) {
				green = temp;
				if (this->colorMode == 0) {
					config->selectorColor(RGBA8(ColorHelper::getColorValue(config->selectorColor(), 2), green, ColorHelper::getColorValue(config->selectorColor(), 0), 255));
				} else if (this->colorMode == 1) {
					config->buttonColor(RGBA8(ColorHelper::getColorValue(config->buttonColor(), 2), green, ColorHelper::getColorValue(config->buttonColor(), 0), 255));
				} else if (this->colorMode == 2) {
					config->barColor(RGBA8(ColorHelper::getColorValue(config->barColor(), 2), green, ColorHelper::getColorValue(config->barColor(), 0), 255));
				} else if (this->colorMode == 3) {
					config->bgColor(RGBA8(ColorHelper::getColorValue(config->bgColor(), 2), green, ColorHelper::getColorValue(config->bgColor(), 0), 255));
				} else if (this->colorMode == 4) {
					config->textColor(RGBA8(ColorHelper::getColorValue(config->textColor(), 2), green, ColorHelper::getColorValue(config->textColor(), 0), 255));
				}
			}
			
		} else if (touching(buttons[2])) {
			int temp = Keyboard::getUint(255, Lang::get("ENTER_BLUE_RGB"));
			if (temp != -1) {
				blue = temp;
				if (this->colorMode == 0) {
					config->selectorColor(RGBA8(ColorHelper::getColorValue(config->selectorColor(), 2), ColorHelper::getColorValue(config->selectorColor(), 1), blue, 255));
				} else if (this->colorMode == 1) {
					config->buttonColor(RGBA8(ColorHelper::getColorValue(config->buttonColor(), 2), ColorHelper::getColorValue(config->buttonColor(), 1), blue, 255));
				} else if (this->colorMode == 2) {
					config->barColor(RGBA8(ColorHelper::getColorValue(config->barColor(), 2), ColorHelper::getColorValue(config->barColor(), 1), blue, 255));
				} else if (this->colorMode == 3) {
					config->bgColor(RGBA8(ColorHelper::getColorValue(config->bgColor(), 2), ColorHelper::getColorValue(config->bgColor(), 1), blue, 255));
				} else if (this->colorMode == 4) {
					config->textColor(RGBA8(ColorHelper::getColorValue(config->textColor(), 2), ColorHelper::getColorValue(config->textColor(), 1), blue, 255));
				}
			}
		}
	}
}