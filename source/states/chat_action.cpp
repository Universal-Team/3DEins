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

#include "chat_action.hpp"
#include "config.hpp"

#include <vector>

extern std::unique_ptr<Config> config;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

void Chat_Action::DrawStateTop(void) const {
	char message [100];
	snprintf(message, sizeof(message), Lang::get("CHATROOM_DETAILS").c_str(), cs->getChatName().c_str(), cs->getUserAmount());
	Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), message, 390);
	if (this->DisplayMode == 0) {
		this->DrawChatTop();
	} else {
		this->DrawMemberListTop();
	}
}

void Chat_Action::DrawChatTop(void) const {
	for(int i=0;i<3 && i<(int)cs->getChat().size();i++) {
		Gui::Draw_Rect(0, 40 + (i * 60), 400, 50, config->barColor());
		GFX::DrawChar(8 + cs->getChat()[screenPos + i].PS.avatar, 0, 38 + (60 * i));
		Gui::DrawString(60, 41 + (i * 60), 0.55f, config->textColor(), cs->getChat()[screenPos + i].PS.name + "#" + std::to_string(cs->getChat()[screenPos + i].PS.id) + "  #" + std::to_string(cs->getChat()[screenPos + i].messageCount), 400);
		Gui::DrawString(60, 60 + (i * 60), 0.5f, config->textColor(), cs->getChat()[screenPos + i].message, 400);
	}
	if (this->delay > 0) {
		char message [100];
		snprintf(message, sizeof(message), Lang::get("IS_TYPING").c_str(), cs->getName(0).c_str(), cs->getID(0));
		Gui::DrawStringCentered(0, 215, 0.5f, config->textColor(), message, 390);
	}
}

void Chat_Action::DrawMemberListTop(void) const {
	for(int i=0;i<3 && i<(int)cs->getUserAmount();i++) {
		if (memberPos + i == memberSelection) {
			Gui::Draw_Rect(0, 40 + (i * 60), 400, 50, config->selectorColor());
		} else {
			Gui::Draw_Rect(0, 40 + (i * 60), 400, 50, config->barColor());
		}
		GFX::DrawChar(8 + cs->getAvatar(memberPos + i), 0, 38 + (60 * i));
		Gui::DrawString(60, 41 + (i * 60), 0.55f, config->textColor(), cs->getName(memberPos + i) + "#" + std::to_string(cs->getID(memberPos + i)) + "  #" + std::to_string(memberPos + i + 1), 400);
		Gui::DrawString(60, 60 + (i * 60), 0.5f, config->textColor(), cs->getPhrase(memberPos + i), 400);
	}
}

void Chat_Action::DrawStateBottom(void) const {
	if (this->DisplayMode == 0) {
		this->DrawChatBottom();
	} else {
		this->DrawMemberListBottom();
	}
}

void Chat_Action::DrawChatBottom(void) const {
	// Our specific bar with Input shit.
	C2D_DrawRectSolid(0, 2, 0.5f, 320, 23, config->barColor() & C2D_Color32(200, 200, 200, 200));
	Gui::DrawString(2, 3, 0.40, config->textColor(), (this->tempString+(this->cursorBlink-- > 0 ? "_" : "")).c_str(), 316);

	for (uint i = 0; i < (sizeof(this->LayoutABC)/sizeof(this->LayoutABC[0])); i++) {
		if (i == (uint)this->keySelection) {
			C2D_DrawRectSolid(LayoutABC[i].x, LayoutABC[i].y, 0.5f, 30, 40, config->bgColor() & C2D_Color32(255, 255, 255, 200));
		} else {
			C2D_DrawRectSolid(this->LayoutABC[i].x, this->LayoutABC[i].y, 0.5f, 30, 40, config->barColor() & C2D_Color32(255, 255, 255, 200));
		}
		if (this->layout == 0) {
			char c[2] = {LayoutABC[i].character[0]};
			Gui::DrawString(LayoutABC[i].x+5+(10-(Gui::GetStringWidth(0.55, c)/2)), this->LayoutABC[i].y+10+(10-(Gui::GetStringHeight(0.55, c)/2)), 0.55, config->textColor(), c);
		} else if (this->layout == 1) {
			char c[2] = {Layoutabc[i].character[0]};
			Gui::DrawString(Layoutabc[i].x+5+(10-(Gui::GetStringWidth(0.50, c)/2)), this->Layoutabc[i].y+10+(10-(Gui::GetStringHeight(0.50, c)/2)), 0.50, config->textColor(), c);
		} else if (this->layout == 2) {
			char c[2] = {this->LayoutSign[i].character[0]};
			Gui::DrawString(this->LayoutSign[i].x+5+(10-(Gui::GetStringWidth(0.50, c)/2)), this->LayoutSign[i].y+10+(10-(Gui::GetStringHeight(0.50, c)/2)), 0.50, config->textColor(), c);
		}
	}
	C2D_DrawRectSolid(this->specialStuff[0].x, this->specialStuff[0].y, 0.5f, 30, 40, config->barColor() & C2D_Color32(255, 255, 255, 200));
	Gui::DrawString(this->specialStuff[0].x+5+(10-(Gui::GetStringWidth(0.50, this->specialStuff[0].character)/2)), this->specialStuff[0].y+10+(10-(Gui::GetStringHeight(0.50, this->specialStuff[0].character)/2)), 0.50, config->textColor(), this->specialStuff[0].character);
	C2D_DrawRectSolid(this->specialStuff[1].x, this->specialStuff[1].y, 0.5f, 180, 20, config->barColor() & C2D_Color32(255, 255, 255, 200));
	C2D_DrawRectSolid(this->specialStuff[2].x, this->specialStuff[2].y, 0.5f, 30, 20, config->barColor() & C2D_Color32(255, 255, 255, 200));
	Gui::DrawString(this->specialStuff[2].x+5+(10-(Gui::GetStringWidth(0.50, this->specialStuff[2].character)/2)), this->specialStuff[2].y+(10-(Gui::GetStringHeight(0.50, this->specialStuff[2].character)/2)), 0.50, config->textColor(), this->specialStuff[2].character);
	C2D_DrawRectSolid(this->specialStuff[3].x, this->specialStuff[3].y, 0.5f, 30, 20, config->barColor() & C2D_Color32(255, 255, 255, 200));
}

// No idea what should be displayed here.
void Chat_Action::DrawMemberListBottom(void) const { }

void Chat_Action::StateLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->DisplayMode == 0) {
		ChatLogic(hDown, hHeld, touch);
	} else {
		MemberListLogic(hDown, hHeld, touch);
	}
}

void Chat_Action::ChatLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	// Our delay for "<User> is typing..."
	if (this->delay > 0) {
		this->delay--;
	}

	if (this->keyDownDelay > 0) {
		this->keyDownDelay--;
	} else if (this->keyDownDelay == 0) {
		this->keyDownDelay--;
	}

	if (this->cursorBlink < -20)	this->cursorBlink = 20;

	if (hDown & KEY_START) {
		this->enter = true;
	}
	
	if (hDown & KEY_R) {
		if (this->layout < 2)	this->layout++;
	} else if (hDown & KEY_L) {
		if (this->layout > 0)	this->layout--;
	}

	if (hDown & KEY_RIGHT) {
		if (this->keySelection < 8)	this->keySelection++;
		else if (this->keySelection > 7 && this->keySelection < 17)	this->keySelection++;
		else if (this->keySelection > 16 && this->keySelection < 25)	this->keySelection++;
	}

	if (hDown & KEY_DOWN) {
		if (this->keySelection < 8)	this->keySelection += 8;
		else if (this->keySelection > 7 && this->keySelection < 17)	this->keySelection += 9;
	}

	if (hDown & KEY_UP) {
		if (this->keySelection > 16)	this->keySelection -= 9;
		else if (this->keySelection < 16 && this->keySelection > 7)	this->keySelection -= 8;
	}

	if (hDown & KEY_LEFT) {
		if (this->keySelection > 16)	this->keySelection--;
		else if (this->keySelection < 17 && this->keySelection > 7)	this->keySelection--;
		else if (this->keySelection < 8 && this->keySelection > 0)	this->keySelection--;
	}

	// Enter a key.
	if (hDown & KEY_A) {
		if (this->tempString.length() < 81) {
			char c;
			switch(this->layout) {
				case 0:
					c = LayoutABC[this->keySelection].character[0];
					this->tempString += c;
					break;
				case 1:
					c = Layoutabc[this->keySelection].character[0];
					this->tempString += c;
					break;
				case 2:
					c = LayoutSign[this->keySelection].character[0];
					this->tempString += c;
					break;
			}
			this->delay = 90;
		}
	}

	if (hDown & KEY_Y) {
		if (this->tempString.length() < 81) {
			this->tempString += " ";
			this->delay = 90;
		}
	}

	if (hDown & KEY_X) {
		if (this->tempString.length() > 0) {
			this->tempString = this->tempString.substr(0, this->tempString.length()-1);
			this->delay = 90;
		}
	}

//	if (this->keyDownDelay > 0) { }
//	this->keyDownDelay = 10;

	if (hDown & KEY_TOUCH) {
		if (this->tempString.length() < 81) {
			if (this->layout == 0) {
				// Check if a regular key was pressed
				for (uint i = 0; i < (sizeof(this->LayoutABC)/sizeof(this->LayoutABC[0])); i++) {
					if ((touch.px > this->LayoutABC[i].x && touch.px < this->LayoutABC[i].x+30) && (touch.py > this->LayoutABC[i].y && touch.py < this->LayoutABC[i].y+40)) {
						char c = this->LayoutABC[i].character[0];
						this->tempString += c;
						this->delay = 90;
						break;
					}
				}
			} else if (this->layout == 1) {
				// Check if a regular key was pressed
				for (uint i = 0; i < (sizeof(this->Layoutabc)/sizeof(this->Layoutabc[0])); i++) {
					if ((touch.px > this->Layoutabc[i].x && touch.px < this->Layoutabc[i].x+30) && (touch.py > this->Layoutabc[i].y && touch.py < this->Layoutabc[i].y+40)) {
						char c = this->Layoutabc[i].character[0];
						this->tempString += c;
						this->delay = 90;
						break;
					}
				}
			} else if (this->layout == 2) {
				// Check if a regular key was pressed
				for (uint i = 0; i < (sizeof(this->LayoutSign)/sizeof(this->LayoutSign[0])); i++) {
					if ((touch.px > this->LayoutSign[i].x && touch.px < this->LayoutSign[i].x+30) && (touch.py > this->LayoutSign[i].y && touch.py < this->LayoutSign[i].y+40)) {
						char c = this->LayoutSign[i].character[0];
						this->tempString += c;
						this->delay = 90;
						break;
					}
				}
			}
		}

		// Layout switch.
		if ((touch.px > specialStuff[3].x && touch.px < specialStuff[3].x+30) && (touch.py > specialStuff[3].y && touch.py < specialStuff[3].y+20)) {
			if (this->layout == 0)	this->layout = 1;
			else if (this->layout == 1)	this->layout = 2;
			else if (this->layout == 2)	this->layout = 0;
			this->delay = 90;
		}

		// Enter.
		if ((touch.px > this->specialStuff[2].x && touch.px < this->specialStuff[2].x+30) && (touch.py > this->specialStuff[2].y && touch.py < this->specialStuff[2].y+20)) {
			this->enter = true;
		}

		// Space.
		if ((touch.px > this->specialStuff[1].x && touch.px < this->specialStuff[1].x+180) && (touch.py > this->specialStuff[1].y && touch.py < this->specialStuff[1].y+20)) {
			if(this->tempString.length() < 81) {
				this->tempString += " ";
				this->delay = 90;
			}
		}

		// Remove.
		if ((touch.px > this->specialStuff[0].x && touch.px < this->specialStuff[0].x+30) && (touch.py > this->specialStuff[0].y && touch.py < this->specialStuff[0].y+40)) {
			if (this->tempString.length() > 0) {
				this->tempString = this->tempString.substr(0, this->tempString.length()-1);
				this->delay = 90;
			}
		}
	}

	// If we reach 40 chars, do a new line.
	if (this->tempString.size() == 40)	this->tempString += "\n"; // 40 -> New Line.

	if (hDown & KEY_B) {
		this->exit = true;
	}

	if (this->enter) {
		// We clear the chat here, cause 100+ messages could be possibly too much for Old 3DS?.
		if (cs->getChat().size() > 99) {
			this->selection = 0;
			this->screenPos = 0;
			cs->clearChat();
		}
		// Send a Message. :)
		cs->sendMessage(0, this->tempString);
		this->selection++;
		this->enter = false;
		this->tempString.clear();
	}

	if (this->exit) {
		// Leave the chat and continue on Game.
		this->isUsed = false;
	}

	if (hDown & KEY_SELECT) {
		this->DisplayMode = 1;
	}

	if (this->selection < this->screenPos) {
		this->screenPos = this->selection;
	} else if (this->selection > this->screenPos + 4 - 1) {
		this->screenPos = this->selection - 4 + 1;
	}
}

void Chat_Action::MemberListLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_DOWN) {
		if (this->memberSelection < (int)cs->getUserAmount()-1) {
			this->memberSelection++;
		}
	}

	if (hDown & KEY_UP) {
		if (this->memberSelection > 0) {
			this->memberSelection--;
		}
	}

	if (hDown & KEY_SELECT) {
		this->DisplayMode = 0;
		// Reset to not cause issues.
		this->memberSelection = 0;
		this->memberPos = 0;
	}

	if (this->memberSelection < this->memberPos) {
		this->memberPos = this->memberSelection;
	} else if (this->memberSelection > this->memberPos + 3 - 1) {
		this->memberPos = this->memberSelection - 3 + 1;
	}
}