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

#ifndef MULTIPLAYSCREEN_HPP
#define MULTIPLAYSCREEN_HPP

#include "cardHelper.hpp"
#include "common.hpp"
#include "structs.hpp"

#include <vector>

class MultiPlayScreen : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	MultiPlayScreen();
private:
	// Sub Menu Selection | Modes.
	int selection = 0;
	int subMode = 0;

	// Player Handle.
	int maxPlayer = 2; // Up to 4.
	int tempPlayer = 2; // This is a temp for the next player handle.

	// Play Direction.
	Direction PlayDirection = Direction::LEFT;

	// in case the player needs to take a break.
	bool PlayerBreak = false;

	// Sub Menu enabler.
	bool isSubMenu = false;

	// Bruh Card Enabler.
	int setBruh = 0; // 0 -> Disabled.

	// Continue | Counter enabler.
	bool canContinue = false; // Return, if user can continue. Used in 2 Player mode.
	bool canCounter = false; // In case the opponent has a Plus 2 / 4 too. TODO.
	bool hasDrawn = false; // Only 1 Draw is allowed!

	// Card indicator for Player 1-4.
	int Player1Card = 0;
	int Player2Card = 0;
	int Player3Card = 0;
	int Player4Card = 0;

	int currentPlayer = 1; // Player 1.
	
	// Player Hands and status.

	// Player 1 Structs.
	std::vector<CardStruct> Player1Hand;
	PlayerStatus Player1Status;

	// Player 2 Structs.
	std::vector<CardStruct> Player2Hand;
	PlayerStatus Player2Status;

	// Player 3 Structs.
	std::vector<CardStruct> Player3Hand;
	PlayerStatus Player3Status;

	// Player 4 Structs.
	std::vector<CardStruct> Player4Hand;
	PlayerStatus Player4Status;

	// Display Helper.
	void DisplayPlayerHand() const;
	void DisplayPlayerHandSmall() const;
	void DrawPlayers() const;

	// Game functions.
	void restart();
	void AddCard(int player);
	void RemoveCard(int player);
	const std::vector<CardType> cardtype = {CardType::PLUS2};
	bool PlayerCanCounter(int player) const;
	bool CanPlayerPlay(int player) const;

	// Draw actual game screen.
	void DrawPlay(void) const;

	// Get the amount of remaining cards.
	int getPlayerCards(int player) const;

	// Logic's.
	void Player1Logic(u32 hDown, u32 hHeld, touchPosition touch);
	void Player2Logic(u32 hDown, u32 hHeld, touchPosition touch);
	void Player3Logic(u32 hDown, u32 hHeld, touchPosition touch);
	void Player4Logic(u32 hDown, u32 hHeld, touchPosition touch);
	void RoundLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void OpponentLogic(void);

	// Sub menu | Statistics stuff.
	void DrawSubMenu(void) const;
	void SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void DrawStats(void) const;

	// Button Struct for the Sub Menu.
	std::vector<Structs::ButtonPos> breakBtn = {
		{90, 40, 140, 40},  // Resume.
		{90, 100, 140, 40}, // Restart.
		{90, 160, 140, 40}, // Exit game.
	};

	// TODO: Add Touch to cards.
	std::vector<Structs::ButtonPos> buttonPos = {
		{1, 50, 60, 90}, // 1.
		{66, 50, 60, 90}, // 2.
		{131, 50, 60, 90}, // 3.
		{186, 50, 60, 90}, // 4.
		{261, 50, 60, 90}, // 5.
	};
};

#endif