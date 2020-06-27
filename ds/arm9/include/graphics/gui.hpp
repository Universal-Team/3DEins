/*
*   This file is part of DSEins
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

#ifndef _DSEINS_GUI_HPP
#define _DSEINS_GUI_HPP

#include "coreHelper.hpp"
#include "graphics.hpp"
#include "screen.hpp"

#include <nds.h>

struct ButtonStruct {
	int x;
	int y;
	float xSize;
	float ySize;
	std::string Text;
	u8 colorIndex;
	bool layer;
};

namespace Gui {
	// Screen stuff.
	void DrawScreen(); // Redraw the screen. Needs to be called when screen changes are made.
	void mainLoop(u16 hDown, touchPosition touch); // Logic MainLoop.
	void setScreen(std::unique_ptr<Screen> screen); // Set a specific screen.
	void screenBack(void); // Go a screen back. Needs "return;" at the end.

	// GUI Stuff.
	void DrawTop(bool useBars);
	void DrawBottom(bool useBars);

	/*	Clear a Screen & Layer.
		bool top is whether to draw on the top or bottom screen.
		bool layer is whether to draw on layer 3 (false) or layer 2 (true).
	*/
	void clearScreen(bool top, bool layer);

	// Card Loading & Drawing stuff.
	void loadGraphics();
	void DrawCard(CardType CT, CardColor CC, int x, int y, float ScaleX, float ScaleY, bool top, bool layer);
	void DrawPlayerCard(const std::vector<CardStruct> &hand, const int &card, int x, int y, float ScaleX, float ScaleY, bool top, bool layer);

	void DrawButton(ButtonStruct btn, TextColor color = TextColor::gray);
};

#endif