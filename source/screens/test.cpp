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

#include "test.hpp"

#include <vector>

#define MAXSHOWNCARDS 6
// Player Hands and table card.
extern std::vector<CardStruct> Player1Hand;
extern std::vector<CardStruct> Player2Hand;
extern std::vector<CardStruct> tableCard;

void Test::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.9f, WHITE, "3DEins");
	GFX::DrawCard(tableCard[0].CT, 170, 80, tableCard[0].CC);

	if (currentPlayer == Player::PLAYER_1) {
		Gui::DrawStringCentered(0, 216, 0.7f, WHITE, "It's your turn!");
	} else {
		Gui::DrawStringCentered(0, 216, 0.7f, WHITE, "It's the opponent turn!");
	}

	GFX::DrawBottom();

	for (int i = 0; i < (int)Player1Hand.size(); i++) {
		if (i == currentCard) {
			if (currentCard < MAXSHOWNCARDS) {
				GFX::DrawSelectedCard(Player1Hand[i].CT, 2 + (i * 53), 85, Player1Hand[i].CC);
			} else {
				GFX::DrawSelectedCard(Player1Hand[i+currentCard-5].CT, 2 + (i * 53), 85, Player1Hand[i+currentCard-5].CC);
			}
		} else {
			if (currentCard < 6) {
				GFX::DrawCard(Player1Hand[i].CT, 2 + (i * 53), 85, Player1Hand[i].CC);
			} else {
				GFX::DrawCard(Player1Hand[i+currentCard-5].CT, 2 + (i * 53), 85, Player1Hand[i+currentCard-5].CC);
			}
		}
	}
}

Test::Test() {
	// Clear Hands and the table.
	tableCard.clear();
	Player1Hand.clear();
	Player2Hand.clear();

	// Add Table card.
	CardHelper::AddCard(Player::TABLE);

	// Fill Player 1.
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);

	// Fill Player 2.
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
}

void Test::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	RoundLogic(hDown, hHeld, touch);
}


// For the Player hand.
void Test::PlayerLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_RIGHT) {
		if (currentCard < (int)Player1Hand.size()-1) {
			currentCard++;
		}
	}

	if (hDown & KEY_LEFT ) {
		if (currentCard > 0) {
			currentCard--;
		}
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical.
		if (Player1Hand[currentCard].CT == tableCard[0].CT || Player1Hand[currentCard].CC == tableCard[0].CC) {
			tableCard.clear();
			CardType card = Player1Hand[currentCard].CT;
			CardColor color = Player1Hand[currentCard].CC;
			tableCard.push_back({card, color});
			CardHelper::RemoveCard(Player::PLAYER_1, currentCard);
			if (currentCard > (int)Player1Hand.size() -1) {
				currentCard = (int)Player1Hand.size() - 1;
			}
			//currentPlayer = Player::PLAYER_2;
		}
		// Set Logic -> TODO.
	}

	// User cannot set, so draw a card.
	if (hDown & KEY_X) {
		CardHelper::AddCard(Player::PLAYER_1);
		//currentPlayer = Player::PLAYER_2;
	}
}

// TODO!!!
void Test::OpponentLogic(void) {
	for (int i = 0; i < (int)Player2Hand.size(); i++) {
		if (Player2Hand[i].CT == tableCard[0].CT || Player2Hand[i].CC == tableCard[0].CC) {
			tableCard.clear();
			CardType card = Player2Hand[i].CT;
			CardColor color = Player2Hand[i].CC;
			tableCard.push_back({card, color});
			CardHelper::RemoveCard(Player::PLAYER_2, i);
		} else {
			CardHelper::AddCard(Player::PLAYER_2);
		}
		currentPlayer = Player::PLAYER_1;
	}
}

void Test::RoundLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (currentPlayer == Player::PLAYER_1) {
		PlayerLogic(hDown, hHeld, touch);
	} else if (currentPlayer == Player::PLAYER_1) {
		OpponentLogic();
	}
}