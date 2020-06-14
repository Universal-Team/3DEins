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

#include "graphics.hpp"
#include "selector.hpp"
#include <array>

extern std::array<int, 4> selectorspr;
bool doUpdate = false;

// Init the selector.
Selector::Selector(int w, int h) {
	this->width = w;
	this->height = h;

   for (int i = 0; i < (int)selectorspr.size(); i++) {
        setSpriteVisibility(selectorspr[i], false, false);
    }

	updateOam();
}

// Move the Selector. 16 means the spritesize there, btw.
void Selector::move(int x, int y) {
    setSpritePosition(selectorspr[0], false, x, y);
    setSpritePosition(selectorspr[1], false, x, y + (this->height - 16));
    setSpritePosition(selectorspr[2], false, x + (this->width - 16), y);
    setSpritePosition(selectorspr[3], false, x + (this->width - 16), y + (this->height - 16));
}

// Hide the Selector.
void Selector::hide() {
   for (int i = 0; i < (int)selectorspr.size(); i++) {
        setSpriteVisibility(selectorspr[i], false, false);
    }
}

// Show the Selector.
void Selector::show() {
   for (int i = 0; i < (int)selectorspr.size(); i++) {
        setSpriteVisibility(selectorspr[i], false, true);
    }
}

// Resize the selector.
void Selector::resize(int w, int h) {
	this->width = w;
	this->height = h;
}

void Selector::update() {
    // Only update OAM, if doUpdate is true.
    if (doUpdate) {
        doUpdate = false;
        updateOam();
    }
}