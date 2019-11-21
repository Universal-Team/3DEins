/*
*   This file is part of 3DEins
*   Copyright (C) 2019 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, TotallyNotGuy, VoltZ
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

#include "utils/cardHelper.hpp"


// The Number cards start from 0 until 39.
bool CardGetter::isNumberCard(int Gamecard) {
	if (Gamecard < 10) {
		return true;
	} else {
		return false;
	}
}

// All Plus 2 cards are from 48 until 51.
bool CardGetter::isPlus2(int Gamecard) {
	if (Gamecard == 12) {
		return true;
	} else {
		return false;
	}
}

// 11 is the return card.
bool CardGetter::isReturn(int Gamecard) {
	if (Gamecard == 11) {
		return true;
	} else {
		return false;
	}
}

// 10 is the Expose / Pause card.
bool CardGetter::isExpose(int Gamecard) {
	if (Gamecard == 10) {
		return true;
	} else {
		return false;
	}
}

// 13 is the Color Wish card.
bool CardGetter::isWish(int Gamecard) {
	if (Gamecard == 13) {
		return true;
	} else {
		return false;
	}
}

// 14 is the Plus4 card.
bool CardGetter::isPlus4(int Gamecard) {
	if (Gamecard == 14) {
		return true;
	} else {
		return false;
	}
}

std::string CardGetter::getColor(int color) {
	if (color == 1) {
		return "Color1";
	} else if (color == 2) {
		return "Color2";
	} else if (color == 3) {
		return "Color3";
	} else if (color == 4) {
		return "Color4";
	} else {
		return "?";
	}
}