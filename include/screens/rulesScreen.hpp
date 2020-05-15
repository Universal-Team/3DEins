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

#ifndef RULESSCREEN_HPP
#define RULESSCREEN_HPP

#include "_3DEins_Core.h"
#include "common.hpp"
#include "structs.hpp"

#include <vector>

class RulesScreen : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
private:
	void DrawDescription(void) const;
	void DisplayCards(void) const;
	int rulePage = 0;

	std::vector<Structs::ButtonPos> cards = {
		{0, 0, 48, 72},
		{52, 0, 48, 72},
		{104, 0, 48, 72},
		{156, 0, 48, 72},
		{208, 0, 48, 72},
		{260, 0, 48, 72},

		{0, 80, 48, 72},
		{52, 80, 48, 72},
		{104, 80, 48, 72},
		{156, 80, 48, 72},

		{208, 80, 48, 72},
		{260, 80, 48, 72},
		{0, 160, 48, 72},
		{52, 160, 48, 72},
		{104, 160, 48, 72}
		#ifdef _USE_SPECIAL_CARD
		,{156, 160, 48, 72}
		#endif
	};
};

#endif