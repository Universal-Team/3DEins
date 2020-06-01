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

#include "colors.hpp"
#include "graphics.hpp"
#include "tonccpy.h"

#include <nds.h>

const u16 defaultPalette[] = {
	0x0000, 0xFBDE, 0xE739, 0xCA52, 0xBDEF, 0x98C6, 0x94A5, 0x8842, 0x8000, // Grays
	0x801E, 0x800F, 0xF800, 0xBC00, 0x8260, 0x8320, 0x83E0, // Colors
	0x0000, 0xFBDE, 0xBDEF, 0x0000, // WHITE_TEXT
	0x0000, 0x8C63, 0xCA52, 0x0000, // GRAY_TEXT
	0x0000, 0x801E, 0x800F, 0x0000, // RED_TEXT
	0x0000, 0xF800, 0xBC00, 0x0000, // BLUE_TEXT
};


const std::string keys[] = {
	"CLEAR", "WHITE", "LIGHT_GRAY", "GRAY", "DARKISH_GRAY", "DARK_GRAY", "DARKER_GRAY", "DARKERER_GRAY", "BLACK",
	"RED", "DARK_RED", "BLUE", "DARK_BLUE",
	"WHITE_TEXT_1", "WHITE_TEXT_2", "WHITE_TEXT_3", "WHITE_TEXT_4"
	"GRAY_TEXT_1",  "GRAY_TEXT_2",  "GRAY_TEXT_3",  "GRAY_TEXT_4"
	"RED_TEXT_1",   "RED_TEXT_2",   "RED_TEXT_3",   "RED_TEXT_4"
	"BLUE_TEXT_1",  "BLUE_TEXT_2",  "BLUE_TEXT_3",  "BLUE_TEXT_4"
};

void Colors::load(void) {
	u16 palette[sizeof(defaultPalette)];
	tonccpy(palette, defaultPalette, sizeof(palette));

	tonccpy(BG_PALETTE, palette, sizeof(palette));
	tonccpy(BG_PALETTE_SUB, palette, sizeof(palette));
}