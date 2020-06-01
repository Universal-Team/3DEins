/*
*   This file is part of DSEins
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

#ifndef _DSEINS_COLORS_HPP
#define _DSEINS_COLORS_HPP

#include <nds/ndstypes.h>

#define CLEAR			0x0
#define WHITE			0x1
#define LIGHT_GRAY		0x2
#define GRAY			0x3
#define DARKISH_GRAY	0x4
#define DARK_GRAY		0x5
#define DARKER_GRAY		0x6
#define DARKERER_GRAY	0x7
#define BLACK			0x8
#define RED				0x9
#define DARK_RED		0xA
#define BLUE			0xB
#define DARK_BLUE		0xC
#define DARK_GREEN		0xD
#define GREEN			0xE
#define LIGHT_GREEN		0xF

// Text
enum TextColor {
	white = 4,
	gray  = 5,
	red   = 6,
	blue  = 7,
	green = 8,
};

namespace Colors {
	void load(void);
}

#endif