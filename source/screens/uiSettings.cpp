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

#include <unistd.h>

extern C2D_SpriteSheet cards;
extern bool touching(touchPosition touch, Structs::ButtonPos button);
extern bool isDay;

// Get current lang.
UISettings::UISettings() {
	if (isDay) {
		selectedLang = 0;
	} else {
		selectedLang = Config::lang;
	}
}

void UISettings::Draw(void) const {
	if (Mode == 0) {
		DrawSubMenu();
	} else if (Mode == 1) {
		DrawColor();
	} else if (Mode == 2) {
		DrawLanguage();
	} else if (Mode == 3) {
		DrawCardScreen();
	}
}

void UISettings::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (Mode == 0) {
		SubMenuLogic(hDown, hHeld, touch);
	} else if (Mode == 1) {
		ColorLogic(hDown, hHeld, touch);
	} else if (Mode == 2) {
		LanguageLogic(hDown, hHeld, touch);
	} else if (Mode == 3) {
		CardLogic(hDown, hHeld, touch);
	}
}

void UISettings::DrawSubMenu(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.7f, Config::Text, "3DEins - " + Lang::get("UI_SETTINGS"), 400);
	GFX::DrawBottom();
	for (int i = 0; i < 3; i++) {
		Gui::Draw_Rect(mainButtons[i].x, mainButtons[i].y, mainButtons[i].w, mainButtons[i].h, Config::Button);
		if (i == subSelection) {
			GFX::DrawButtonSelector(mainButtons[i].x, mainButtons[i].y);
		}
	}
	Gui::DrawStringCentered(0, mainButtons[0].y+10, 0.6f, Config::Text, Lang::get("COLORS"));
	Gui::DrawStringCentered(0, mainButtons[1].y+10, 0.6f, Config::Text, Lang::get("LANGUAGE"));
	Gui::DrawStringCentered(0, mainButtons[2].y+10, 0.6f, Config::Text, Lang::get("CARDSETS"));
}

void UISettings::SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_DOWN) {
		if (subSelection < 2)	subSelection++;
	}
	if (hDown & KEY_UP) {
		if (subSelection > 0)	subSelection--;
	}

	if (hDown & KEY_A) {
		switch (subSelection) {
			case 0:
				Mode = 1;
				break;
			case 1:
				Mode = 2;
				break;
			case 2:
				Mode = 3;
				break;
		}
	}

	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_TOUCH) {
		if (touching(touch, mainButtons[0])) {
			Mode = 1;
		} else if (touching(touch, mainButtons[1])) {
			Mode = 2;
		} else if (touching(touch, mainButtons[2])) {
			Mode = 3;
		}
	}
}

// Draw a preview of the color.
void UISettings::DrawPreview(void) const {
	if (colorMode == 0) {
		GFX::DrawCardSelector(120, 65, 1.5, 1.5);
	} else if (colorMode == 1) {
		Gui::Draw_Rect(130, 120, 150, 40, Config::Button);
	}
}

void UISettings::DrawColor(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, Config::Text, "3DEins - " + Lang::get("UI_SETTINGS"), 320);
	DrawPreview();
	GFX::DrawBottom();

	Gui::Draw_Rect(buttons[0].x, buttons[0].y, 95, 41, C2D_Color32(255, 0, 0, 255));
	Gui::Draw_Rect(buttons[1].x, buttons[1].y, 95, 41, C2D_Color32(0, 255, 0, 255));
	Gui::Draw_Rect(buttons[2].x, buttons[2].y, 95, 41, C2D_Color32(0, 0, 255, 255));

	if (colorMode == 0) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("SELECTOR_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Selector, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Selector, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Selector, 0).c_str(), 400);
	} else if (colorMode == 1) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("BUTTON_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Button, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Button, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Button, 0).c_str(), 400);
	} else if (colorMode == 2) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("BAR_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Bar, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Bar, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Bar, 0).c_str(), 400);
	} else if (colorMode == 3) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("BG_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::BG, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::BG, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::BG, 0).c_str(), 400);
	} else if (colorMode == 4) {
		Gui::DrawStringCentered(0, 60, 0.7f, WHITE, Lang::get("TEXT_COLOR"), 320);
		Gui::DrawString(40, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Text, 2).c_str(), 400);
		Gui::DrawString(140, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Text, 1).c_str(), 400);
		Gui::DrawString(245, 98, 0.7f, WHITE, ColorHelper::getColorName(Config::Text, 0).c_str(), 400);
	}
}

void UISettings::ColorLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	int red;
	int green;
	int blue;

	if (hDown & KEY_B) {
		Mode = 0;
	}

	if (hDown & KEY_LEFT) {
		if(colorMode > 0)	colorMode--;
	}

	if (hDown & KEY_RIGHT) {
		if(colorMode < 4)	colorMode++;
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
					Config::Selector = RGBA8(red, ColorHelper::getColorValue(Config::Selector, 1), ColorHelper::getColorValue(Config::Selector, 0), 255);
				} else if (colorMode == 1) {
					Config::Button = RGBA8(red, ColorHelper::getColorValue(Config::Button, 1), ColorHelper::getColorValue(Config::Button, 0), 200);
				} else if (colorMode == 2) {
					Config::Bar = RGBA8(red, ColorHelper::getColorValue(Config::Bar, 1), ColorHelper::getColorValue(Config::Bar, 0), 200);
				} else if (colorMode == 3) {
					Config::BG = RGBA8(red, ColorHelper::getColorValue(Config::BG, 1), ColorHelper::getColorValue(Config::BG, 0), 200);
				} else if (colorMode == 4) {
					Config::Text = RGBA8(red, ColorHelper::getColorValue(Config::Text, 1), ColorHelper::getColorValue(Config::Text, 0), 255);
				}
			}
		} else if (touching(touch, buttons[1])) {
			int temp = Input::getUint(255, Lang::get("ENTER_GREEN_RGB"));
			if(temp != -1) {
				green = temp;
				if (colorMode == 0) {
					Config::Selector = RGBA8(ColorHelper::getColorValue(Config::Selector, 2), green, ColorHelper::getColorValue(Config::Selector, 0), 255);
				} else if (colorMode == 1) {
					Config::Button = RGBA8(ColorHelper::getColorValue(Config::Button, 2), green, ColorHelper::getColorValue(Config::Button, 0), 200);
				} else if (colorMode == 2) {
					Config::Bar = RGBA8(ColorHelper::getColorValue(Config::Bar, 2), green, ColorHelper::getColorValue(Config::Bar, 0), 200);
				} else if (colorMode == 3) {
					Config::BG = RGBA8(ColorHelper::getColorValue(Config::BG, 2), green, ColorHelper::getColorValue(Config::BG, 0), 200);
				} else if (colorMode == 4) {
					Config::Text = RGBA8(ColorHelper::getColorValue(Config::Text, 2), green, ColorHelper::getColorValue(Config::Text, 0), 255);
				}
			}
		} else if (touching(touch, buttons[2])) {
			int temp = Input::getUint(255, Lang::get("ENTER_BLUE_RGB"));
			if(temp != -1) {
				blue = temp;
				if (colorMode == 0) {
					Config::Selector = RGBA8(ColorHelper::getColorValue(Config::Selector, 2), ColorHelper::getColorValue(Config::Selector, 1), blue, 255);
				} else if (colorMode == 1) {
					Config::Button = RGBA8(ColorHelper::getColorValue(Config::Button, 2), ColorHelper::getColorValue(Config::Button, 1), blue, 200);
				} else if (colorMode == 2) {
					Config::Bar = RGBA8(ColorHelper::getColorValue(Config::Bar, 2), ColorHelper::getColorValue(Config::Bar, 1), blue, 200);
				} else if (colorMode == 3) {
					Config::BG = RGBA8(ColorHelper::getColorValue(Config::BG, 2), ColorHelper::getColorValue(Config::BG, 1), blue, 200);
				} else if (colorMode == 4) {
					Config::Text = RGBA8(ColorHelper::getColorValue(Config::Text, 2), ColorHelper::getColorValue(Config::Text, 1), blue, 255);
				}
			}
		}
	}
}

void UISettings::DrawLanguage(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.7f, Config::Text, Lang::get("SELECT_LANG"), 400);
	GFX::DrawBottom();

	for (int language = 0; language < 10; language++) {
		Gui::Draw_Rect(langBlocks[language].x, langBlocks[language].y, langBlocks[language].w, langBlocks[language].h, Config::Button);
		if (Config::lang == language) {
			Gui::Draw_Rect(langBlocks[language].x, langBlocks[language].y, langBlocks[language].w, langBlocks[language].h, Config::Selector);
		}
	}

	Gui::DrawString(langBlocks[0].x+25, langBlocks[0].y, 0.7f, Config::Text, "Bruh", 320);
	Gui::DrawString(langBlocks[1].x+25, langBlocks[1].y, 0.7f, Config::Text, "Deutsch", 320);
	Gui::DrawString(langBlocks[2].x+25, langBlocks[2].y, 0.7f, Config::Text, "English", 320);
	Gui::DrawString(langBlocks[3].x+25, langBlocks[3].y, 0.7f, Config::Text, "Español", 320);
	Gui::DrawString(langBlocks[4].x+25, langBlocks[4].y, 0.7f, Config::Text, "Français", 320);

	Gui::DrawString(langBlocks[5].x+25, langBlocks[5].y, 0.7f, Config::Text, "Italiano", 320);
	Gui::DrawString(langBlocks[6].x+25, langBlocks[6].y, 0.7f, Config::Text, "Lietuvių", 320);
	Gui::DrawString(langBlocks[7].x+25, langBlocks[7].y, 0.7f, Config::Text, "Português", 320);
	Gui::DrawString(langBlocks[8].x+25, langBlocks[8].y, 0.7f, Config::Text, "Русский", 320);
	Gui::DrawString(langBlocks[9].x+25, langBlocks[9].y, 0.7f, Config::Text, "日本語", 320);
}

void UISettings::LanguageLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (isDay != true) {
		if (hDown & KEY_TOUCH) {
			for (int language = 0; language < 10; language++) {
				if (touching(touch, langBlocks[language])) {
					selectedLang = language;
					Config::lang = language;
					Lang::load(Config::lang);
				}
			}
		}
	}

	if (isDay != true) {
		if (hDown & KEY_UP) {
			if(selectedLang > 0) {
				selectedLang--;
				Config::lang = selectedLang;
				Lang::load(Config::lang);
			}
		}

		if (hDown & KEY_DOWN) {
			if(selectedLang < 9) {
				selectedLang++;
				Config::lang = selectedLang;
				Lang::load(Config::lang);
			}
		}

		if (hDown & KEY_LEFT) {
			if (selectedLang > 4) {
				selectedLang -= 5;
				Config::lang = selectedLang;
				Lang::load(Config::lang);
			}
		}

		if (hDown & KEY_RIGHT) {
			if (selectedLang < 5) {
				selectedLang += 5;
				Config::lang = selectedLang;
				Lang::load(Config::lang);
			}
		}
	} else {
		// Of course make it disable again, we don't want to force someone to not able to play it.
		if (hDown & KEY_L && hDown & KEY_R) {
			isDay = false;
		}
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("LANGUAGE_INSTRUCTIONS"));
	}
	
	if (hDown & KEY_B) {
		Mode = 0;
	}
}

// TODO.
void UISettings::DrawCardScreen(void) const {
	GFX::DrawFileBrowseBG();
	Gui::DrawStringCentered(0, 0, 0.7f, Config::Text, "3DEins - " + Lang::get("CARDSETS"), 400);
	std::string dirs;
	for (uint i=(selectedSheet<5) ? 0 : selectedSheet-5;i<dirContents.size()&&i<((selectedSheet<5) ? 6 : selectedSheet+1);i++) {
		if (i == selectedSheet) {
			dirs += "> " + dirContents[i].name + "\n\n";
		} else {
			dirs += dirContents[i].name + "\n\n";
		}
	}
	for (uint i=0;i<((dirContents.size()<6) ? 6-dirContents.size() : 0);i++) {
		dirs += "\n\n";
	}
	Gui::DrawString(26, 32, 0.53f, Config::Text, dirs.c_str(), 360);
	Gui::DrawStringCentered(0, 215, 0.6f, Config::Text, Lang::get("REFRESH"), 390);
	GFX::DrawFileBrowseBG(false);
}

// TODO.
void UISettings::CardLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (keyRepeatDelay)	keyRepeatDelay--;

	if (dirChanged) {
		dirContents.clear();
		chdir("sdmc:/3ds/3DEins/sets/");
		std::vector<DirEntry> dirContentsTemp;
		getDirectoryContents(dirContentsTemp, {});
		for(uint i=0;i<dirContentsTemp.size();i++) {
			dirContents.push_back(dirContentsTemp[i]);
		}
		dirChanged = false;
	}
	// Refresh.
	if (hDown & KEY_START) {
		dirChanged = true;
	}

	if (hHeld & KEY_UP) {
		if (selectedSheet > 0 && !keyRepeatDelay) {
			selectedSheet--;
			keyRepeatDelay = 6;
		}
	} else if (hHeld & KEY_DOWN && !keyRepeatDelay) {
		if (selectedSheet < dirContents.size()-1) {
			selectedSheet++;
			keyRepeatDelay = 6;
		}
	}

	if (hDown & KEY_A) {
		if (dirContents.size() != 0) {
			std::string path = dirContents[selectedSheet].name;
			loadSet(path);
		}
	}

	if (hDown & KEY_B) {
		Mode = 0;
	}
}

// Check if Card Spritesheet even EXIST.
bool UISettings::checkForValidate(std::string file) {
	if(access(file.c_str(), F_OK) != -1 ) {
		return true;
	} else {
		return false;
	}
}

// Load Sheet. ;)
Result UISettings::loadSet(std::string folder) {
	if (checkForValidate(folder)) {
		if (checkForValidate(folder + "/Colors.json")) {
			if (checkForValidate(folder + "/cards.t3x")) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("LOADING_SET_PROMPT").c_str(), folder.c_str());
				if (Msg::promptMsg2(message)) {
					Gui::unloadSheet(cards);
					Msg::DisplayMsg(Lang::get("LOADING_SPRITESHEET"));
					Gui::loadSheet((folder + "/cards.t3x").c_str(), cards);
					Config::loadCardColors((folder + "/Colors.json").c_str());
				}
			} else {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("FILE_NOT_EXIST").c_str(), "cards.t3x");
				Msg::DisplayWaitMsg(message);
			}
		} else {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("FILE_NOT_EXIST").c_str(), "Colors.json");
			Msg::DisplayWaitMsg(message);
		}
	}
	return 0;
}