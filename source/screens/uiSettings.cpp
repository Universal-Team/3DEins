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

#include "colorHelper.hpp"
#include "keyboard.hpp"
#include "uiSettings.hpp"

extern C2D_SpriteSheet cards;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

// Draw a preview of the color.
void UISettings::DrawPreview(void) const {
	if (colorMode == 0) {
		C2D_DrawRectSolid(122, 67, 0.5f, 54*1.5-5, 80*1.5-5, Config::Red);
		C2D_DrawRectSolid(242, 67, 0.5f, 54*1-5, 80*1-5, Config::Red);
	} else if (colorMode == 1) {
		C2D_DrawRectSolid(122, 67, 0.5f, 54*1.5-5, 80*1.5-5, Config::Blue);
		C2D_DrawRectSolid(242, 67, 0.5f, 54*1-5, 80*1-5, Config::Blue);
	} else if (colorMode == 2) {
		C2D_DrawRectSolid(122, 67, 0.5f, 54*1.5-5, 80*1.5-5, Config::Yellow);
		C2D_DrawRectSolid(242, 67, 0.5f, 54*1-5, 80*1-5, Config::Yellow);
	} else if (colorMode == 3) {
		C2D_DrawRectSolid(122, 67, 0.5f, 54*1.5-5, 80*1.5-5, Config::Green);
		C2D_DrawRectSolid(242, 67, 0.5f, 54*1-5, 80*1-5, Config::Green);
	} else if (colorMode == 4) {
		GFX::DrawCardSelector(120, 65, 1.5, 1.5);
	} else if (colorMode == 5) {
		Gui::Draw_Rect(130, 120, 150, 40, Config::Button);
	}

	if (colorMode < 4) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, cardSelection), 120, 65, 0.5f, NULL, 1.5, 1.5);
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, cardSelection), 240, 65, 0.5f, NULL);
	}
}


void UISettings::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, Config::Text, "3DEins - " + Lang::get("UI_SETTINGS"), 320);
	DrawPreview();
	GFX::DrawBottom();

	Gui::Draw_Rect(buttons[0].x, buttons[0].y, 95, 41, C2D_Color32(255, 0, 0, 255));
	Gui::Draw_Rect(buttons[1].x, buttons[1].y, 95, 41, C2D_Color32(0, 255, 0, 255));
	Gui::Draw_Rect(buttons[2].x, buttons[2].y, 95, 41, C2D_Color32(0, 0, 255, 255));

	if (colorMode == 0) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("CARD_RED"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Red, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Red, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Red, 0).c_str(), 400);
	} else if (colorMode == 1) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("CARD_BLUE"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Blue, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Blue, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Blue, 0).c_str(), 400);
	} else if (colorMode == 2) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("CARD_YELLOW"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Yellow, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Yellow, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Yellow, 0).c_str(), 400);
	} else if (colorMode == 3) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("CARD_GREEN"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Green, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Green, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Green, 0).c_str(), 400);
	} else if (colorMode == 4) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("SELECTOR_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Selector, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Selector, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Selector, 0).c_str(), 400);
	} else if (colorMode == 5) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("BUTTON_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Button, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Button, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Button, 0).c_str(), 400);
	} else if (colorMode == 6) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("BAR_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Bar, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Bar, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Bar, 0).c_str(), 400);
	} else if (colorMode == 7) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("BG_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::BG, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::BG, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::BG, 0).c_str(), 400);
	} else if (colorMode == 8) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("TEXT_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Text, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Text, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Text, 0).c_str(), 400);
	}
}

void UISettings::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	int red;
	int green;
	int blue;

	if (hDown & KEY_B) {
		Config::save();
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_LEFT) {
		if(colorMode > 0)	colorMode--;
	}

	if (hDown & KEY_RIGHT) {
		if(colorMode < 8)	colorMode++;
	}

	if (hDown & KEY_R) {
		if (cardSelection < 14)	cardSelection++;
	}

	if (hDown & KEY_L) {
		if (cardSelection > 0)	cardSelection--;
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("CARD_COLOR_INSTRUCTIONS"));
	}

	if (hDown & KEY_TOUCH) {
		if (touching(touch, buttons[0])) {
			int temp = Input::getUint(255, Lang::get("ENTER_RED_RGB"));
			if(temp != -1) {
				red = temp;
				if (colorMode == 0) {
					Config::Red = RGBA8(red, ColorHelper::getColorValue(Config::Red, 1), ColorHelper::getColorValue(Config::Red, 0), 255);
				} else if (colorMode == 1) {
					Config::Blue = RGBA8(red, ColorHelper::getColorValue(Config::Blue, 1), ColorHelper::getColorValue(Config::Blue, 0), 255);
				} else if (colorMode == 2) {
					Config::Yellow = RGBA8(red, ColorHelper::getColorValue(Config::Yellow, 1), ColorHelper::getColorValue(Config::Yellow, 0), 255);
				} else if (colorMode == 3) {
					Config::Green = RGBA8(red, ColorHelper::getColorValue(Config::Green, 1), ColorHelper::getColorValue(Config::Green, 0), 255);
				} else if (colorMode == 4) {
					Config::Selector = RGBA8(red, ColorHelper::getColorValue(Config::Selector, 1), ColorHelper::getColorValue(Config::Selector, 0), 255);
				} else if (colorMode == 5) {
					Config::Button = RGBA8(red, ColorHelper::getColorValue(Config::Button, 1), ColorHelper::getColorValue(Config::Button, 0), 200);
				} else if (colorMode == 6) {
					Config::Bar = RGBA8(red, ColorHelper::getColorValue(Config::Bar, 1), ColorHelper::getColorValue(Config::Bar, 0), 200);
				} else if (colorMode == 7) {
					Config::BG = RGBA8(red, ColorHelper::getColorValue(Config::BG, 1), ColorHelper::getColorValue(Config::BG, 0), 200);
				} else if (colorMode == 8) {
					Config::Text = RGBA8(red, ColorHelper::getColorValue(Config::Text, 1), ColorHelper::getColorValue(Config::Text, 0), 255);
				}
			}
		} else if (touching(touch, buttons[1])) {
			int temp = Input::getUint(255, Lang::get("ENTER_GREEN_RGB"));
			if(temp != -1) {
				green = temp;
				if (colorMode == 0) {
					Config::Red = RGBA8(ColorHelper::getColorValue(Config::Red, 2), green, ColorHelper::getColorValue(Config::Red, 0), 255);
				} else if (colorMode == 1) {
					Config::Blue = RGBA8(ColorHelper::getColorValue(Config::Blue, 2), green, ColorHelper::getColorValue(Config::Blue, 0), 255);
				} else if (colorMode == 2) {
					Config::Yellow = RGBA8(ColorHelper::getColorValue(Config::Yellow, 2), green, ColorHelper::getColorValue(Config::Yellow, 0), 255);
				} else if (colorMode == 3) {
					Config::Green = RGBA8(ColorHelper::getColorValue(Config::Green, 2), green, ColorHelper::getColorValue(Config::Green, 0), 255);
				} else if (colorMode == 4) {
					Config::Selector = RGBA8(ColorHelper::getColorValue(Config::Selector, 2), green, ColorHelper::getColorValue(Config::Selector, 0), 255);
				} else if (colorMode == 5) {
					Config::Button = RGBA8(ColorHelper::getColorValue(Config::Button, 2), green, ColorHelper::getColorValue(Config::Button, 0), 200);
				} else if (colorMode == 6) {
					Config::Bar = RGBA8(ColorHelper::getColorValue(Config::Bar, 2), green, ColorHelper::getColorValue(Config::Bar, 0), 200);
				} else if (colorMode == 7) {
					Config::BG = RGBA8(ColorHelper::getColorValue(Config::BG, 2), green, ColorHelper::getColorValue(Config::BG, 0), 200);
				} else if (colorMode == 8) {
					Config::Text = RGBA8(ColorHelper::getColorValue(Config::Text, 2), green, ColorHelper::getColorValue(Config::Text, 0), 255);
				}
			}
		} else if (touching(touch, buttons[2])) {
			int temp = Input::getUint(255, Lang::get("ENTER_BLUE_RGB"));
			if(temp != -1) {
				blue = temp;
				if (colorMode == 0) {
					Config::Red = RGBA8(ColorHelper::getColorValue(Config::Red, 2), ColorHelper::getColorValue(Config::Red, 1), blue, 255);
				} else if (colorMode == 1) {
					Config::Blue = RGBA8(ColorHelper::getColorValue(Config::Blue, 2), ColorHelper::getColorValue(Config::Blue, 1), blue, 255);
				} else if (colorMode == 2) {
					Config::Yellow = RGBA8(ColorHelper::getColorValue(Config::Yellow, 2), ColorHelper::getColorValue(Config::Yellow, 1), blue, 255);
				} else if (colorMode == 3) {
					Config::Green = RGBA8(ColorHelper::getColorValue(Config::Green, 2), ColorHelper::getColorValue(Config::Green, 1), blue, 255);
				} else if (colorMode == 4) {
					Config::Selector = RGBA8(ColorHelper::getColorValue(Config::Selector, 2), ColorHelper::getColorValue(Config::Selector, 1), blue, 255);
				} else if (colorMode == 5) {
					Config::Button = RGBA8(ColorHelper::getColorValue(Config::Button, 2), ColorHelper::getColorValue(Config::Button, 1), blue, 200);
				} else if (colorMode == 6) {
					Config::Bar = RGBA8(ColorHelper::getColorValue(Config::Bar, 2), ColorHelper::getColorValue(Config::Bar, 1), blue, 200);
				} else if (colorMode == 7) {
					Config::BG = RGBA8(ColorHelper::getColorValue(Config::BG, 2), ColorHelper::getColorValue(Config::BG, 1), blue, 200);
				} else if (colorMode == 8) {
					Config::Text = RGBA8(ColorHelper::getColorValue(Config::Text, 2), ColorHelper::getColorValue(Config::Text, 1), blue, 255);
				}
			}
		}
	}
}