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

#ifndef _3DEINS_GFX_HPP
#define _3DEINS_GFX_HPP

#include "cards.h"
#include "chars.h"
#include "common.hpp"
#include "coreHelper.hpp"
#include "sprites.h"

#include <string>

struct ButtonStruct {
	int X;
	int Y;
	float xSize;
	float ySize;
	std::string Text;
};

namespace GFX {
	// Basic GUI.
	void DrawTop(bool useBars = true);
	void DrawBottom(bool useBars = true);
	void DrawFileBrowseBG(bool isTop = true);
	void DrawSprite(int index, int x, int y, float ScaleX = 1, float ScaleY = 1);
	// Selectors.
	void DrawCardSelector(int x, int y, float ScaleX = 1, float ScaleY = 1);
	void DrawButtonSelector(int x, int y, float ScaleX = 1, float ScaleY = 1, bool useSmall = false);
	void DrawSelectedPlayer(int x, int y, float ScaleX = 1, float ScaleY = 1);
	
	void DrawCard(CardType CT, int x, int y, CardColor CC, float ScaleX = 1, float ScaleY = 1);
	// Draws a card from the Player's Hand.
	void DrawPlayerCard(const std::vector<CardStruct> &hand, const int &card, int x, int y, float ScaleX = 1, float ScaleY = 1);
	void DrawChar(int image, int x, int y, float ScaleX = 1, float ScaleY = 1);
	void DrawPlayer(int x, int y, float ScaleX, float ScaleY, int player);

	// Main Logic.
	void Main(u32 hDown, u32 hHeld, touchPosition touch);

	// Buttons.
	void Button(const ButtonStruct btn);
}

#endif