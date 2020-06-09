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

extern std::unique_ptr<Config> config;

int animated_cardYPos[2] = {0};
bool animated_cardMoveDelay = false;

void Animation::DrawSubBG(bool isTop) {
	if (!animated_cardMoveDelay) {
		animated_cardYPos[0] -= 2;
		animated_cardYPos[1] += 2;
		if (animated_cardYPos[0] <= -240) animated_cardYPos[0] = 0;
		if (animated_cardYPos[1] >= +240) animated_cardYPos[1] = 0;
	}
	
	animated_cardMoveDelay = !animated_cardMoveDelay;

	if (isTop) {
		// BG.
		Gui::ScreenDraw(Top);
		Gui::Draw_Rect(0, 30, 400, 180, config->bgColor());
		// First Cards.
		GFX::DrawCard(CardType(0), 20, animated_cardYPos[0], CardColor(0));
		GFX::DrawCard(CardType(0), 20, animated_cardYPos[0]+240, CardColor(0));
		// Second Cards.
		GFX::DrawCard(CardType(1), 120, animated_cardYPos[1], CardColor(1));
		GFX::DrawCard(CardType(1), 120, animated_cardYPos[1]-240, CardColor(1));
		// Third Cards.
		GFX::DrawCard(CardType(2), 220, animated_cardYPos[0], CardColor(2));
		GFX::DrawCard(CardType(2), 220, animated_cardYPos[0]+240, CardColor(2));
		// Fourth Cards.
		GFX::DrawCard(CardType(3), 320, animated_cardYPos[1], CardColor(3));
		GFX::DrawCard(CardType(3), 320, animated_cardYPos[1]-240, CardColor(3));
		// Draw Bars with 225 Alpha, so it looks pretty nice.
		Gui::Draw_Rect(0, 0, 400, 30, config->barColor() - C2D_Color32(0, 0, 0, 30));
		Gui::Draw_Rect(0, 210, 400, 30, config->barColor() - C2D_Color32(0, 0, 0, 30));
	} else {
		// BG.
		Gui::ScreenDraw(Bottom);
		Gui::Draw_Rect(0, 30, 320, 180, config->bgColor());
		// First Cards.
		GFX::DrawCard(CardType(0), 0, animated_cardYPos[0], CardColor(0));
		GFX::DrawCard(CardType(0), 0, animated_cardYPos[0]+240, CardColor(0));
		// Second Cards.
		GFX::DrawCard(CardType(1), 100, animated_cardYPos[1], CardColor(1));
		GFX::DrawCard(CardType(1), 100, animated_cardYPos[1]-240, CardColor(1));
		// Third Cards.
		GFX::DrawCard(CardType(2), 200, animated_cardYPos[0], CardColor(2));
		GFX::DrawCard(CardType(2), 200, animated_cardYPos[0]+240, CardColor(2));
		// Fourth Cards.
		GFX::DrawCard(CardType(3), 300, animated_cardYPos[1], CardColor(3));
		GFX::DrawCard(CardType(3), 300, animated_cardYPos[1]-240, CardColor(3));
		// Draw Bars with 225 Alpha, so it looks pretty nice.
		Gui::Draw_Rect(0, 0, 320, 30, config->barColor() - C2D_Color32(0, 0, 0, 30));
		Gui::Draw_Rect(0, 210, 320, 30, config->barColor() - C2D_Color32(0, 0, 0, 30));
	}
}