/*
*   This file is part of 3DEins
*   Copyright (C) 2019 VoltZ
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
	if (Gamecard < 40) {
		return true;
	} else {
		return false;
	}
}

// All Plus 2 cards are from 48 until 51.
bool CardGetter::isPlus2(int Gamecard) {
	if (Gamecard > 47 && Gamecard < 52) {
		return true;
	} else {
		return false;
	}
}

// Begins from 44 until 47.
bool CardGetter::isReturn(int Gamecard) {
	if (Gamecard > 43 && Gamecard < 48) {
		return true;
	} else {
		return false;
	}
}

// Begins from 40 until 43.
bool CardGetter::isExpose(int Gamecard) {
	if (Gamecard > 39 && Gamecard < 44) {
		return true;
	} else {
		return false;
	}
}

// 54 is the Color Wish card.
bool CardGetter::isWish(int Gamecard) {
	if (Gamecard == 53) {
		return true;
	} else {
		return false;
	}
}

// 54 is the Plus4 card.
bool CardGetter::isPlus4(int Gamecard) {
	if (Gamecard == 54) {
		return true;
	} else {
		return false;
	}
}

bool CardGetter::isBlue(int Gamecard) {
	if (Gamecard == 0 || Gamecard == 4 || Gamecard == 8 || Gamecard == 12 || Gamecard == 16 || Gamecard == 20 || Gamecard == 24
	|| Gamecard == 28 || Gamecard == 32 || Gamecard == 36 || Gamecard == 40 || Gamecard == 44 || Gamecard == 48) {
		return true;
	} else {
		return false;
	}
}

bool CardGetter::isGreen(int Gamecard) {
	if (Gamecard == 1 || Gamecard == 5 || Gamecard == 9 || Gamecard == 13 || Gamecard == 17 || Gamecard == 21 || Gamecard == 25
	|| Gamecard == 29 || Gamecard == 33 || Gamecard == 37 || Gamecard == 41 || Gamecard == 45 || Gamecard == 49) {
		return true;
	} else {
		return false;
	}
}

bool CardGetter::isRed(int Gamecard) {
	if (Gamecard == 2 || Gamecard == 6 || Gamecard == 10 || Gamecard == 14 || Gamecard == 18 || Gamecard == 22 || Gamecard == 26
	|| Gamecard == 30 || Gamecard == 34 || Gamecard == 38 || Gamecard == 42 || Gamecard == 46 || Gamecard == 50) {
		return true;
	} else {
		return false;
	}
}

bool CardGetter::isYellow(int Gamecard) {
	if (Gamecard == 3 || Gamecard == 7 || Gamecard == 11 || Gamecard == 15 || Gamecard == 19 || Gamecard == 23 || Gamecard == 27
	|| Gamecard == 31 || Gamecard == 35 || Gamecard == 39 || Gamecard == 43 || Gamecard == 47 || Gamecard == 51) {
		return true;
	} else {
		return false;
	}
}