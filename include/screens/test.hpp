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

#ifndef TEST_HPP
#define TEST_HPP

#include "common.hpp"

class Test : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	Test();

private:
	bool isPause = false;
	bool canReturn = false;
	bool canCounter = false; // In case the opponent has a Plus 2 / 4 too.
	int currentCard = 0; // Always set to 0.
	int currentPlayer = 0; // Player 1.
	int toPlayColor = 1; // The to play color.
	void PlayerLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void RoundLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void OpponentLogic(void);

	// Special stuff.
	void specialHandle(int Player, int card);
};

#endif