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

#include "common.hpp"
#include "config.hpp"
#include "keyboard.hpp"
#include "screenCommon.hpp"

extern std::unique_ptr<Config> config;
int layoutMode = 0;
bool caps = false, enter = false;
int shift = 0;

bool keyTouch(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))	return true;
	else	return false;
}

Structs::Key LayoutABC[] = {
	{"A", 6, 42}, {"B", 41, 42}, {"C", 76, 42}, {"D", 111, 42}, {"E", 146, 42}, {"F", 181, 42}, {"G", 216, 42}, {"H", 251, 42},
	{"I", 6, 90}, {"J", 41, 90}, {"K", 76, 90}, {"L", 111, 90}, {"M", 146, 90}, {"N", 181, 90}, {"O", 216, 90}, {"P", 251, 90}, {"Q", 286, 90},
	{"R", 6, 138}, {"S", 41, 138}, {"T", 76, 138}, {"U", 111, 138}, {"V", 146, 138}, {"W", 181, 138}, {"X", 216, 138}, {"Y", 251, 138}, {"Z", 286, 138}
};
Structs::Key Layoutabc[] = {
	{"a", 6, 42}, {"b", 41, 42}, {"c", 76, 42}, {"d", 111, 42}, {"e", 146, 42}, {"f", 181, 42}, {"g", 216, 42}, {"h", 251, 42},
	{"i", 6, 90}, {"j", 41, 90}, {"k", 76, 90}, {"l", 111, 90}, {"m", 146, 90}, {"n", 181, 90}, {"o", 216, 90}, {"p", 251, 90}, {"q", 286, 90},
	{"r", 6, 138}, {"s", 41, 138}, {"t", 76, 138}, {"u", 111, 138}, {"v", 146, 138}, {"w", 181, 138}, {"x", 216, 138}, {"y", 251, 138}, {"z", 286, 138}
};
// TODO.
Structs::Key LayoutSign[] = {
	{"0", 6, 42}, {"1", 41, 42}, {"2", 76, 42}, {"3", 111, 42}, {"4", 146, 42}, {"5", 181, 42}, {"6", 216, 42}, {"7", 251, 42},
	{"8", 6, 90}, {"9", 41, 90}, {"/", 76, 90}, {"\\", 111, 90}, {".", 146, 90}, {",", 181, 90}, {":", 216, 90}, {";", 251, 90}, {")", 286, 90},
	{"(", 6, 138}, {"+", 41, 138}, {"-", 76, 138}, {"!", 111, 138}, {">", 146, 138}, {"<", 181, 138}, {"?", 216, 138}, {"[", 251, 138}, {"]", 286, 138}
};

Structs::Key specialStuff[] = {
	{"\uE071", 286, 42}, // Delet.
	{" ", 70, 185}, // Space.
	{"\uE056", 270, 185}, // Enter.
	{"", 30, 185}, // Mode switch.
};

Structs::Key NumpadStruct[] = {
	{"1", 10, 30},
	{"2", 90, 30},
	{"3", 170, 30},
	{"B", 250, 30},
	{"4", 10, 100},
	{"5", 90, 100},
	{"6", 170, 100},
	{"0", 250, 100},
	{"7", 10, 170},
	{"8", 90, 170},
	{"9", 170, 170},
	{"E", 250, 170},
};
Structs::ButtonPos Numbers [] = {
	{10, 30, 60, 50}, // 1
	{90, 30, 60, 50}, // 2
	{170, 30, 60, 50}, // 3
	{250, 30, 60, 50}, // Backspace.
	{10, 100, 60, 50},
	{90, 100, 60, 50},
	{170, 100, 60, 50},
	{250, 100, 60, 50}, // 0.
	{10, 170, 60, 50},
	{90, 170, 60, 50},
	{170, 170, 60, 50},
	{250, 170, 60, 50}, // Enter.
};

void Keyboard::Draw(int selection) {
	for (uint i = 0; i < (sizeof(LayoutABC)/sizeof(LayoutABC[0])); i++) {
		if (i == (uint)selection) {
			C2D_DrawRectSolid(LayoutABC[i].x, LayoutABC[i].y, 0.5f, 30, 40, config->bgColor() & C2D_Color32(255, 255, 255, 200));
		} else {
			C2D_DrawRectSolid(LayoutABC[i].x, LayoutABC[i].y, 0.5f, 30, 40, config->barColor() & C2D_Color32(255, 255, 255, 200));
		}

		if (layoutMode == 0) {
			char c[2] = {LayoutABC[i].character[0]};
			Gui::DrawString(LayoutABC[i].x+5+(10-(Gui::GetStringWidth(0.55, c)/2)), LayoutABC[i].y+10+(10-(Gui::GetStringHeight(0.55, c)/2)), 0.55, config->textColor(), c);
		} else if (layoutMode == 1) {
			char c[2] = {Layoutabc[i].character[0]};
			Gui::DrawString(Layoutabc[i].x+5+(10-(Gui::GetStringWidth(0.50, c)/2)), Layoutabc[i].y+10+(10-(Gui::GetStringHeight(0.50, c)/2)), 0.50, config->textColor(), c);
		} else if (layoutMode == 2) {
			char c[2] = {LayoutSign[i].character[0]};
			Gui::DrawString(LayoutSign[i].x+5+(10-(Gui::GetStringWidth(0.50, c)/2)), LayoutSign[i].y+10+(10-(Gui::GetStringHeight(0.50, c)/2)), 0.50, config->textColor(), c);
		}
	}

	C2D_DrawRectSolid(specialStuff[0].x, specialStuff[0].y, 0.5f, 30, 40, config->barColor() & C2D_Color32(255, 255, 255, 200));
	Gui::DrawString(specialStuff[0].x+5+(10-(Gui::GetStringWidth(0.50, specialStuff[0].character)/2)), specialStuff[0].y+10+(10-(Gui::GetStringHeight(0.50, specialStuff[0].character)/2)), 0.50, config->textColor(), specialStuff[0].character);
	C2D_DrawRectSolid(specialStuff[1].x, specialStuff[1].y, 0.5f, 180, 20, config->barColor() & C2D_Color32(255, 255, 255, 200));
	C2D_DrawRectSolid(specialStuff[2].x, specialStuff[2].y, 0.5f, 30, 20, config->barColor() & C2D_Color32(255, 255, 255, 200));
	Gui::DrawString(specialStuff[2].x+5+(10-(Gui::GetStringWidth(0.50, specialStuff[2].character)/2)), specialStuff[2].y+(10-(Gui::GetStringHeight(0.50, specialStuff[2].character)/2)), 0.50, config->textColor(), specialStuff[2].character);
	C2D_DrawRectSolid(specialStuff[3].x, specialStuff[3].y, 0.5f, 30, 20, config->barColor() & C2D_Color32(255, 255, 255, 200));
}

void Keyboard::DrawNumpad(int selection) {
	for(uint i = 0; i < (sizeof(NumpadStruct)/sizeof(NumpadStruct[0])); i++) {
		if (i == (uint)selection) {
			Gui::Draw_Rect(NumpadStruct[i].x, NumpadStruct[i].y, 60, 50, config->bgColor());
		} else {
			Gui::Draw_Rect(NumpadStruct[i].x, NumpadStruct[i].y, 60, 50, config->barColor());
		}

		char c[2] = {NumpadStruct[i].character[0]};
		Gui::DrawString(NumpadStruct[i].x+25, NumpadStruct[i].y+15, 0.72f, config->textColor(), c, 50);
	}
}

int Keyboard::getUint(int max, std::string Text) {
	std::string s = Keyboard::Numpad(3, Text);
	if (s == "" || (atoi(s.c_str()) == 0 && s[0] != '0')) return -1;
	int i = atoi(s.c_str());
	if (i>max)	return 255;
	return i;
}

std::string Keyboard::Numpad(uint maxLength, std::string Text) {
	int hDown;
	touchPosition touch;
	std::string string;
	int keyDownDelay = 10, cursorBlink = 20, selection = 0;
	enter = false;
	while(1) {
		do {
			C3D_FrameEnd(0);
			Gui::clearTextBufs();
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
			C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
			GFX::DrawTop();
			Gui::DrawStringCentered(0, 2, 0.7f, config->textColor(), Text, 400);
			Gui::DrawString(180, 217, 0.8, config->textColor(), (string+(cursorBlink-- > 0 ? "_" : "")).c_str(), 380);
			if (cursorBlink < -20)	cursorBlink = 20;
			Gui::ScreenDraw(Bottom);
			Gui::Draw_Rect(0, 0, 320, 240, config->bgColor());
			DrawNumpad(selection);
			scanKeys();
			hDown = keysDown();

			if (keyDownDelay > 0) {
				keyDownDelay--;
			} else if (keyDownDelay == 0) {
				keyDownDelay--;
			}
		} while(!hDown);
		keyDownDelay = 10;

		if (hDown & KEY_RIGHT) {
			if (selection < 4)	selection++;
			else if (selection > 3 && selection < 8)	selection++;
			else if (selection > 7 && selection < 11)	selection++;
		}

		if (hDown & KEY_DOWN) {
			if (selection < 4)	selection += 4;
			else if (selection > 3 && selection < 8)	selection += 4;
		}

		if (hDown & KEY_UP) {
			if (selection > 7)	selection -= 4;
			else if (selection < 8 && selection > 3)	selection -= 4;
		}

		if (hDown & KEY_LEFT) {
			if (selection > 7)	selection--;
			else if (selection < 8 && selection > 3)	selection--;
			else if (selection < 4 && selection > 0)	selection--;
		}

		if (hDown & KEY_A) {
			if (string.length() < maxLength) {
				switch(selection) {
					case 0:
						string += "1";
						break;
					case 1:
						string += "2";
						break;
					case 2:
						string += "3";
						break;
					case 4:
						string += "4";
						break;
					case 5:
						string += "5";
						break;
					case 6:
						string += "6";
						break;
					case 7:
						string += "0";
						break;
					case 8:
						string += "7";
						break;
					case 9:
						string += "8";
						break;
					case 10:
						string += "9";
						break;
				}
			}

			if (selection == 3) {
				if (string.length() > 0)	string = string.substr(0, string.length()-1);
			} else if (selection == 11) {	enter = true; }
		}

		if (hDown & KEY_B) {
			if (string.length() > 0)	string = string.substr(0, string.length()-1);
		}

		if (hDown & KEY_TOUCH) {
			touchRead(&touch);
			if (string.length() < maxLength) {
				if (keyTouch(touch, Numbers[0])) {
					string += "1";
				} else if (keyTouch(touch, Numbers[1])) {
					string += "2";
				} else if (keyTouch(touch, Numbers[2])) {
					string += "3";
				} else if (keyTouch(touch, Numbers[4])) {
					string += "4";
				} else if (keyTouch(touch, Numbers[5])) {
					string += "5";
				} else if (keyTouch(touch, Numbers[6])) {
					string += "6";
				} else if (keyTouch(touch, Numbers[7])) {
					string += "0";
				} else if (keyTouch(touch, Numbers[8])) {
					string += "7";
				} else if (keyTouch(touch, Numbers[9])) {
					string += "8";
				} else if (keyTouch(touch, Numbers[10])) {
					string += "9";
				}
			}

			if (keyTouch(touch, Numbers[3])) {
				if (string.length() > 0)	string = string.substr(0, string.length()-1);
			} else if (keyTouch(touch, Numbers[11])) {
				enter = true;
			}
		}

		if (hDown & KEY_START || enter) {
			break;
		}
	}

	return string;
	enter = false;
}

std::string Keyboard::getString(uint maxLength, std::string Text, float inputTextSize) {
	int hDown;
	touchPosition touch;
	std::string string;
	int keyDownDelay = 10, cursorBlink = 20, selection = 0;
	caps = false, shift = 0, enter = false;
	while(1) {
		do {
			C3D_FrameEnd(0);
			Gui::clearTextBufs();
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			GFX::DrawTop();
			Gui::DrawString((400-Gui::GetStringWidth(0.8f, Text))/2, 2, 0.8f, config->textColor(), Text, 400);
			GFX::DrawBottom();
			Keyboard::Draw(selection);
			C2D_DrawRectSolid(0, 5, 0.5f, 320, 20, config->barColor() & C2D_Color32(200, 200, 200, 200));
			Gui::DrawString(2, 5, inputTextSize, config->textColor(), (string+(cursorBlink-- > 0 ? "_" : "")).c_str(), 316);
			if(cursorBlink < -20)	cursorBlink = 20;
			scanKeys();
			hDown = keysDown();
			if (keyDownDelay > 0) {
				keyDownDelay--;
			} else if (keyDownDelay == 0) {
				keyDownDelay--;
			}
		} while(!hDown);

		keyDownDelay = 10;

		if (hDown & KEY_R) {
			if (layoutMode < 2)	layoutMode++;
		} else if (hDown & KEY_L) {
			if (layoutMode > 0)	layoutMode--;
		}

		if (hDown & KEY_RIGHT) {
			if (selection < 8)	selection++;
			else if (selection > 7 && selection < 17)	selection++;
			else if (selection > 16 && selection < 25)	selection++;
		}

		if (hDown & KEY_DOWN) {
			if (selection < 8)	selection += 8;
			else if (selection > 7 && selection < 17)	selection += 9;
		}

		if (hDown & KEY_UP) {
			if (selection > 16)	selection -= 9;
			else if (selection < 16 && selection > 7)	selection -= 8;
		}

		if (hDown & KEY_LEFT) {
			if (selection > 16)	selection--;
			else if (selection < 17 && selection > 7)	selection--;
			else if (selection < 8 && selection > 0)	selection--;
		}

		// Enter a key.
		if (hDown & KEY_A) {
			if (string.length() < maxLength) {
				char c;
				switch(layoutMode) {
					case 0:
						c = LayoutABC[selection].character[0];
						string += c;
						break;
					case 1:
						c = Layoutabc[selection].character[0];
						string += c;
						break;
					case 2:
						c = LayoutSign[selection].character[0];
						string += c;
						break;
				}
			}
		}

		if (hDown & KEY_Y) {
			if (string.length() < maxLength) {
				string += " ";
			}
		}


		if (hDown & KEY_TOUCH) {
			touchRead(&touch);
			if (string.length() < maxLength) {
				if (layoutMode == 0) {
					// Check if a regular key was pressed
					for(uint i = 0; i < (sizeof(LayoutABC)/sizeof(LayoutABC[0])); i++) {
						if ((touch.px > LayoutABC[i].x && touch.px < LayoutABC[i].x+38) && (touch.py > LayoutABC[i].y && touch.py < LayoutABC[i].y+28)) {
							char c = LayoutABC[i].character[0];
							string += c;
							break;
						}
					}

				} else if (layoutMode == 1) {
					// Check if a regular key was pressed
					for(uint i = 0; i < (sizeof(Layoutabc)/sizeof(Layoutabc[0])); i++) {
						if ((touch.px > Layoutabc[i].x && touch.px < Layoutabc[i].x+38) && (touch.py > Layoutabc[i].y && touch.py < Layoutabc[i].y+28)) {
							char c = Layoutabc[i].character[0];
							string += c;
							break;
						}
					}
				} else if (layoutMode == 2) {
					// Check if a regular key was pressed
					for(uint i = 0; i < (sizeof(LayoutSign)/sizeof(LayoutSign[0])); i++) {
						if ((touch.px > LayoutSign[i].x && touch.px < LayoutSign[i].x+38) && (touch.py > LayoutSign[i].y && touch.py < LayoutSign[i].y+28)) {
							char c = LayoutSign[i].character[0];
							string += c;
							break;
						}
					}
				}
			}
			// Layout switch.
			if ((touch.px > specialStuff[3].x && touch.px < specialStuff[3].x+28) && (touch.py > specialStuff[3].y && touch.py < specialStuff[3].y+18)) {
				if (layoutMode == 0)	layoutMode = 1;
				else if (layoutMode == 1)	layoutMode = 2;
				else if (layoutMode == 2)	layoutMode = 0;
			}
			// Enter.
			if ((touch.px > specialStuff[2].x && touch.px < specialStuff[2].x+28) && (touch.py > specialStuff[2].y && touch.py < specialStuff[2].y+18)) {
				enter = true;
			}
			// Space.
			if ((touch.px > specialStuff[1].x && touch.px < specialStuff[1].x+178) && (touch.py > specialStuff[1].y && touch.py < specialStuff[1].y+18)) {
				if (string.length() < maxLength) {
					string += " ";
				}
			}
			// Remove.
			if ((touch.px > specialStuff[0].x && touch.px < specialStuff[0].x+38) && (touch.py > specialStuff[0].y && touch.py < specialStuff[0].y+28)) {
				if (string.length() != 0) {
					string = string.substr(0, string.length()-1);
				}
			}
		}

		if (hDown & KEY_B) {
			string = string.substr(0, string.length()-1);
		}

		if (hDown & KEY_START || enter) {
			layoutMode = 0; // Reset.
			break;
		}
	}
	return string;
}