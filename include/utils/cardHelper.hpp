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

#ifndef CARDHELPER_HPP
#define CARDHELPER_HPP

#include <string>
#include <vector>

#define MAXCOLOR	4 // Only 4 Colors, the 5th color is for special cards.
#define MAXCARDTYPE	16 // 16 with BRUH.

enum class CardColor {
	GREEN,
	BLUE,
	YELLOW,
	RED,
	SPECIAL
};

enum class CardType {
	NUMBER_0,
	NUMBER_1,
	NUMBER_2,
	NUMBER_3,
	NUMBER_4,
	NUMBER_5,
	NUMBER_6,
	NUMBER_7,
	NUMBER_8,
	NUMBER_9,
	SKIP,
	REVERSE,
	PLUS2,
	WISH,
	PLUS4,
	BRUH
};

enum class Direction {
	RIGHT,
	LEFT
};

// TODO: Add Status handler.
enum class PlayerStatus {
	DRAW_2,
	DRAW_4,
	WISH_COLOR,
	TAKE_BREAK,
	CAN_RETURN,
	DIRECTION_CHANGE,
	HAS_NO_CARDS,
	NORMAL
};

// CardStruct.
struct CardStruct {
	CardType CT;
	CardColor CC;
};

namespace CardHelper {
	void RandomizeTableCard(void);
	void statusHandler(std::vector<CardStruct> &hand, PlayerStatus status, PlayerStatus &p, Direction &direction); // Handle Status like +2, +4, Wish etc.
	void specialHandle(CardType card, PlayerStatus &p, PlayerStatus &nP, int maxPlayer);
	void AddCard(std::vector<CardStruct> &hand);
	void RemoveCard(std::vector<CardStruct> &hand, int pos);
	void ChangeDirection(Direction &direction);
	CardColor wishFunction();
}

#endif