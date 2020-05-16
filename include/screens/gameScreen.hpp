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

#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "common.hpp"
#include "game.hpp"
#include "structs.hpp"

#include <vector>

class GameScreen : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	GameScreen();
private:
	std::unique_ptr<Game> currentGame;
	bool checkForPlayableCard(const std::shared_ptr<Player> &player);
	void PlayerLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch);

	void InitializeNewGame();
	void setState(int Player);
	
	// Hand displays.
	void DisplayPlayerHand() const;
	void DisplayPlayerHandSmall() const;
	void DrawPlayers() const;
	void DrawPlayerStats(void) const;
	void DrawSubMenu(void) const;
	int getAvatar(int player) const;

	// Useful functions.
	std::string returnPlayerName(int player) const;
	int getPlayerCards(int player) const;
	bool CanPlayerPlay(const std::shared_ptr<Player> &player);
	int getNextPlayer();
	
	// Player Amount & Current Player.
	int playerAmount = 4;
	int subMode = 0;
	int selection = 0;
	bool isSubMenu = false;

	// Button Struct for the Sub Menu.
	std::vector<Structs::ButtonPos> breakBtn = {
		{90, 40, 140, 40},  // Resume.
		{90, 100, 140, 40}, // Restart.
		{90, 160, 140, 40}, // Exit game.
	};
};

#endif