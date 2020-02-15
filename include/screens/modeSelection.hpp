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

#ifndef MODESELECTION_HPP
#define MODESELECTION_HPP

#include "cardHelper.hpp"
#include "common.hpp"
#include "structs.hpp"

#include <vector>

class ModeSelection : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	int Selection = 0;
	int amountSelection = 2;
	int Mode = 1;

	void DrawPlayerAmount(void) const;
	void DrawMode(void) const;
	void PlayerSelection(u32 hDown, u32 hHeld, touchPosition touch);
	void MSelection(u32 hDown, u32 hHeld, touchPosition touch);

	std::vector<Structs::ButtonPos> mainButtons = {
		{90, 40, 140, 40},  // Single Player.
		{90, 100, 140, 40}, // Multi Player.
		{90, 160, 140, 40}, // Back.
	};

	std::vector<Structs::ButtonPos> cardButtons = {
		{20, 60, 84, 126},  // 2 Player.
		{120, 60, 84, 126}, // 3 Player.
		{220, 60, 84, 126}, // 4 Player.
	};
};

#endif