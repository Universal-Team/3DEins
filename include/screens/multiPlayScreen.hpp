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

class MultiPlayScreen : public Screen
{
public:
	void Draw(void) const override;
	void Logic(u32 hDown, u32 hHeld, touchPosition touch) override;
	MultiPlayScreen();
private:
	int maxPlayer = 2; // Up to 4.
	int tempPlayer = 2; // This is a temp for the next player handle.
	Direction PlayDirection = Direction::LEFT;
	// in case the player needs to break.
	bool Player1Break = false;
	bool Player2Break = false;
	bool Player3Break = false;
	bool Player4Break = false;

	bool canContinue = false; // Return, if user can continue. Used in 2 Player mode.
	bool canCounter = false; // In case the opponent has a Plus 2 / 4 too. TODO.

	// Card indicator for Player 1-4.
	int Player1Card = 0;
	int Player2Card = 0;
	int Player3Card = 0;
	int Player4Card = 0;

	int currentPlayer = 1; // Player 1.
	
	// Player Hands and status.
	std::vector<CardStruct> Player1Hand;
	PlayerStatus Player1Status;
	PlayerFeeling Player1Feeling = PlayerFeeling(0);

	std::vector<CardStruct> Player2Hand;
	PlayerStatus Player2Status;
	PlayerFeeling Player2Feeling = PlayerFeeling(0);

	std::vector<CardStruct> Player3Hand;
	PlayerStatus Player3Status;
	PlayerFeeling Player3Feeling = PlayerFeeling(0);

	std::vector<CardStruct> Player4Hand;
	PlayerStatus Player4Status;
	PlayerFeeling Player4Feeling = PlayerFeeling(0);

	void DisplayPlayerHand() const;
	void DisplayPlayerHandSmall() const;
	void DrawPlayers() const;

	void AddCard(int player);
	void RemoveCard(int player);

	void Player1Logic(u32 hDown, u32 hHeld, touchPosition touch);
	void Player2Logic(u32 hDown, u32 hHeld, touchPosition touch);
	void Player3Logic(u32 hDown, u32 hHeld, touchPosition touch);
	void Player4Logic(u32 hDown, u32 hHeld, touchPosition touch);
	void RoundLogic(u32 hDown, u32 hHeld, touchPosition touch);
	void OpponentLogic(void);
};

#endif