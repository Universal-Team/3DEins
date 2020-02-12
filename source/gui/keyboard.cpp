#include "common.hpp"
#include "keyboard.hpp"
#include "structs.hpp"

#include <string>
#include <stdio.h>
#include <ctype.h>

extern C3D_RenderTarget* Top;
extern C3D_RenderTarget* Bottom;

bool caps = false, enter = false;
int shift = 0;

Structs::Key NumpadStruct[] = {
	{"1", 10, 30},
	{"2", 90, 30},
	{"3", 170, 30},

	{"4", 10, 100},
	{"5", 90, 100},
	{"6", 170, 100},

	{"7", 10, 170},
	{"8", 90, 170},
	{"9", 170, 170},

	{"0", 250, 100},

	{"E", 250, 170},

	{"B", 250, 30},
};
Structs::ButtonPos Numbers [] = {
	{10, 30, 60, 50}, // 1
	{90, 30, 60, 50}, // 2
	{170, 30, 60, 50}, // 3

	{10, 100, 60, 50},
	{90, 100, 60, 50},
	{170, 100, 60, 50},

	{10, 170, 60, 50},
	{90, 170, 60, 50},
	{170, 170, 60, 50},

	{250, 100, 60, 50}, // 0.

	{250, 170, 60, 50}, // Enter.

	{250, 30, 60, 50}, // Backspace.
};


Structs::Key HexStruct[] = {
	// Num struct.
	{"1", 70, 50},
	{"2", 110, 50},
	{"3", 150, 50},
	{"4", 190, 50},
	{"5", 230, 50},

	{"6", 70, 90},
	{"7", 110, 90},
	{"8", 150, 90},
	{"9", 190, 90},
	{"0", 230, 90},

	// Letter.
	{"A", 10, 10},
	{"B", 10, 50},
	{"C", 10, 90},
	{"D", 10, 130},
	{"E", 10, 170},
	{"F", 10, 210},
	// Special cases.
	{"x", 110, 150},
	{"B", 150, 150},
	{"E", 190, 150},
};

Structs::ButtonPos Hex [] = {
	{70, 50, 30, 20}, // 1.
	{110, 50, 30, 20}, // 2.
	{150, 50, 30, 20}, // 3.
	{190, 50, 30, 20}, // 4.
	{230, 50, 30, 20}, // 5.

	{70, 90, 30, 20}, // 6.
	{110, 90, 30, 20}, // 7.
	{150, 90, 30, 20}, // 8.
	{190, 90, 30, 20}, // 9.
	{230, 90, 30, 20}, // 0.

	{10, 10, 30, 20}, // A.
	{10, 50, 30, 20}, // B.
	{10, 90, 30, 20}, // C.
	{10, 130, 30, 20}, // D.
	{10, 170, 30, 20}, // E.
	{10, 210, 30, 20}, // F.

	{110, 150, 30, 20}, // x.
	{150, 150, 30, 20}, // Backspace.
	{190, 150, 30, 20}, // Enter.
};

extern bool touching(touchPosition touch, Structs::ButtonPos button);

void Input::DrawHex()
{
	for(uint i=0;i<(sizeof(HexStruct)/sizeof(HexStruct[0]));i++) {
		Gui::Draw_Rect(HexStruct[i].x, HexStruct[i].y, 30, 20, C2D_Color32(220, 60, 0, 200));
		char c[2] = {HexStruct[i].character[0]};
		Gui::DrawString(HexStruct[i].x+12, HexStruct[i].y+4, 0.5f, WHITE, c, 50);
	}
}

void Input::DrawNumpad()
{
	for(uint i=0;i<(sizeof(NumpadStruct)/sizeof(NumpadStruct[0]));i++) {
		Gui::Draw_Rect(NumpadStruct[i].x, NumpadStruct[i].y, 60, 50, C2D_Color32(220, 60, 0, 200));
		char c[2] = {NumpadStruct[i].character[0]};
		Gui::DrawString(NumpadStruct[i].x+25, NumpadStruct[i].y+15, 0.72f, WHITE, c, 50);
	}
}

int Input::getUint(int max, std::string Text) {
	std::string s = Input::Numpad(3, Text);
	if(s == "" || (atoi(s.c_str()) == 0 && s[0] != '0')) return -1;
	int i = atoi(s.c_str());
	if(i>max)	return 255;
	return i;
}

std::string Input::Numpad(std::string Text) { return Input::Numpad(-1, Text); }

std::string Input::Numpad(uint maxLength, std::string Text)
{
	int hDown;
	touchPosition touch;
	std::string string;
	int keyDownDelay = 10, cursorBlink = 20;
	enter = false;
	while(1) {
		do {
			C3D_FrameEnd(0);
			Gui::clearTextBufs();
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(Top, BLACK);
			C2D_TargetClear(Bottom, BLACK);
			GFX::DrawTop();
			Gui::DrawStringCentered(0, 2, 0.7f, WHITE, Text, 400);
			Gui::DrawString(180, 217, 0.8, WHITE, (string+(cursorBlink-- > 0 ? "_" : "")).c_str(), 380);
			if(cursorBlink < -20)	cursorBlink = 20;
			Gui::ScreenDraw(Bottom);
			Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(220, 60, 0, 200));
			DrawNumpad();
			scanKeys();
			hDown = keysDown();
			if(keyDownDelay > 0) {
				keyDownDelay--;
			} else if(keyDownDelay == 0) {
				keyDownDelay--;
			}
		} while(!hDown);
		if(keyDownDelay > 0) {
		}
		keyDownDelay = 10;

		if(hDown & KEY_TOUCH) {
			touchRead(&touch);
			if(string.length() < maxLength) {
				if (touching(touch, Numbers[0])) {
					string += "1";
				} else if (touching(touch, Numbers[1])) {
					string += "2";
				} else if (touching(touch, Numbers[2])) {
					string += "3";
				} else if (touching(touch, Numbers[3])) {
					string += "4";
				} else if (touching(touch, Numbers[4])) {
					string += "5";
				} else if (touching(touch, Numbers[5])) {
					string += "6";
				} else if (touching(touch, Numbers[6])) {
					string += "7";
				} else if (touching(touch, Numbers[7])) {
					string += "8";
				} else if (touching(touch, Numbers[8])) {
					string += "9";
				} else if (touching(touch, Numbers[9])) {
					string += "0";
				}
			}
		}

		if(hDown & KEY_B || touching(touch, Numbers[11])) {
			string = string.substr(0, string.length()-1);
		}

		if(hDown & KEY_START || touching(touch, Numbers[10]) || enter) {
			break;
		}
	}

	return string;
	enter = false;
}


std::string Input::getHex(int max, std::string Text)
{
	int hDown;
	touchPosition touch;
	std::string string;
	int keyDownDelay = 10, cursorBlink = 20;
	enter = false;
	while(1) {
		do {
			C3D_FrameEnd(0);
			Gui::clearTextBufs();
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(Top, BLACK);
			C2D_TargetClear(Bottom, BLACK);
			GFX::DrawTop();
			Gui::DrawStringCentered(0, 2, 0.7f, WHITE, Text, 400);
			Gui::DrawString(180, 217, 0.65, WHITE, (string+(cursorBlink-- > 0 ? "_" : "")).c_str(), 380);
			if(cursorBlink < -20)	cursorBlink = 20;
			Gui::ScreenDraw(Bottom);
			Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(220, 60, 0, 200));
			DrawHex();
			scanKeys();
			hDown = keysDown();
			if(keyDownDelay > 0) {
				keyDownDelay--;
			} else if(keyDownDelay == 0) {
				keyDownDelay--;
			}
		} while(!hDown);
		if(keyDownDelay > 0) {
		}
		keyDownDelay = 10;

		if(hDown & KEY_TOUCH) {
			touchRead(&touch);
			if((int)string.length() < max) {
				if (touching(touch, Hex[0])) {
					string += "1";
				} else if (touching(touch, Hex[1])) {
					string += "2";
				} else if (touching(touch, Hex[2])) {
					string += "3";
				} else if (touching(touch, Hex[3])) {
					string += "4";
				} else if (touching(touch, Hex[4])) {
					string += "5";
				} else if (touching(touch, Hex[5])) {
					string += "6";
				} else if (touching(touch, Hex[6])) {
					string += "7";
				} else if (touching(touch, Hex[7])) {
					string += "8";
				} else if (touching(touch, Hex[8])) {
					string += "9";
				} else if (touching(touch, Hex[9])) {
					string += "0";
				} else if (touching(touch, Hex[10])) {
					string += "A";
				} else if (touching(touch, Hex[11])) {
					string += "B";
				} else if (touching(touch, Hex[12])) {
					string += "C";
				} else if (touching(touch, Hex[13])) {
					string += "D";
				} else if (touching(touch, Hex[14])) {
					string += "E";
				} else if (touching(touch, Hex[15])) {
					string += "F";
				} else if (touching(touch, Hex[16])) {
					string += "x";
				}
			}
		}

		if(hDown & KEY_B || touching(touch, Hex[17])) {
			string = string.substr(0, string.length()-1);
		}

		if(hDown & KEY_START || touching(touch, Hex[18]) || enter) {
			break;
		}
	}

	return string;
	enter = false;
}