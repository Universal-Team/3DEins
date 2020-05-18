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


#ifndef _3DEINS_CHAT_ACTION_HPP
#define _3DEINS_CHAT_ACTION_HPP

#include "chatSystem.hpp"
#include "common.hpp"
#include "screenState.hpp"
#include "structs.hpp"

class ChatSystem;
class Chat_Action : public ScreenState
{
protected:
	ChatSystem *cs;
public:
	void DrawStateTop(void) const override;
	void DrawStateBottom(void) const override;
	void StateLogic(u32 hDown, u32 hHeld, touchPosition touch) override;
	Chat_Action(std::unique_ptr<ChatSystem> &chat): cs(chat.get()) {
		this->isUsed = true;
		this->selection = (int)cs->getChat().size();
	}

private:
	std::string tempString = ""; // Our Temp String where we write to.
	mutable int keyDownDelay = 10, cursorBlink = 20, layout = 0, selection = 0, screenPos = 0, delay = 0, memberPos = 0, DisplayMode = 0, memberSelection = 0, keySelection = 0; // Other Variables.
	bool enter = false, exit = false, touched = false; // Our "enter" & "exit" & touched boolean.

	void DrawMemberListTop(void) const;
	void DrawMemberListBottom(void) const;
	void MemberListLogic(u32 hDown, u32 hHeld, touchPosition touch);

	void DrawChatTop(void) const;
	void DrawChatBottom(void) const;
	void ChatLogic(u32 hDown, u32 hHeld, touchPosition touch);

	// ABC Struct.
	Structs::Key LayoutABC[26] = {
		{"A", 6, 42}, {"B", 41, 42}, {"C", 76, 42}, {"D", 111, 42}, {"E", 146, 42}, {"F", 181, 42}, {"G", 216, 42}, {"H", 251, 42},
		{"I", 6, 90}, {"J", 41, 90}, {"K", 76, 90}, {"L", 111, 90}, {"M", 146, 90}, {"N", 181, 90}, {"O", 216, 90}, {"P", 251, 90}, {"Q", 286, 90},
		{"R", 6, 138}, {"S", 41, 138}, {"T", 76, 138}, {"U", 111, 138}, {"V", 146, 138}, {"W", 181, 138}, {"X", 216, 138}, {"Y", 251, 138}, {"Z", 286, 138}
	};

	// abc Struct.
	Structs::Key Layoutabc[26] = {
		{"a", 6, 42}, {"b", 41, 42}, {"c", 76, 42}, {"d", 111, 42}, {"e", 146, 42}, {"f", 181, 42}, {"g", 216, 42}, {"h", 251, 42},
		{"i", 6, 90}, {"j", 41, 90}, {"k", 76, 90}, {"l", 111, 90}, {"m", 146, 90}, {"n", 181, 90}, {"o", 216, 90}, {"p", 251, 90}, {"q", 286, 90},
		{"r", 6, 138}, {"s", 41, 138}, {"t", 76, 138}, {"u", 111, 138}, {"v", 146, 138}, {"w", 181, 138}, {"x", 216, 138}, {"y", 251, 138}, {"z", 286, 138}
	};

	// Special Sign Struct.
	Structs::Key LayoutSign[26] = {
		{"0", 6, 42}, {"1", 41, 42}, {"2", 76, 42}, {"3", 111, 42}, {"4", 146, 42}, {"5", 181, 42}, {"6", 216, 42}, {"7", 251, 42},
		{"8", 6, 90}, {"9", 41, 90}, {"/", 76, 90}, {"\\", 111, 90}, {".", 146, 90}, {",", 181, 90}, {":", 216, 90}, {";", 251, 90}, {")", 286, 90},
		{"(", 6, 138}, {"+", 41, 138}, {"-", 76, 138}, {"!", 111, 138}, {">", 146, 138}, {"<", 181, 138}, {"?", 216, 138}, {"[", 251, 138}, {"]", 286, 138}
	};

	// Special struct. Like Delete, space etc.
	Structs::Key specialStuff[4] = {
		{"\uE071", 286, 42}, // Delete.
		{" ", 70, 185}, // Space.
		{"\uE056", 270, 185}, // Enter.
		{"", 30, 185}, // Mode switch.
	};

};

#endif