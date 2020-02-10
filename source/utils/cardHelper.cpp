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

#include "cardHelper.hpp"

#define MAXCOLOR	3 // Only 4 Colors, the 5th color is for special cards.
#define MAXCARDTYPE	15

// Player Targets.
std::vector<CardStruct> Player1Hand;
std::vector<CardStruct> Player2Hand;
std::vector<CardStruct> Player3Hand;
std::vector<CardStruct> Player4Hand;
std::vector<CardStruct> tableCard;

void CardHelper::RemoveCard(Player player, int pos) {
	if (player == Player::PLAYER_1) {
		Player1Hand.erase(Player1Hand.begin()+pos);
	} else if (player == Player::PLAYER_2) {
		Player2Hand.erase(Player2Hand.begin()+pos);
	} else if (player == Player::PLAYER_3) {
		Player3Hand.erase(Player3Hand.begin()+pos);
	} else if (player == Player::PLAYER_4) {
		Player4Hand.erase(Player4Hand.begin()+pos);
	}
}

void CardHelper::AddCard(Player player) {
	CardType Card = CardType(rand() % MAXCARDTYPE + 0);
	CardColor Color = CardColor(rand() % MAXCOLOR + 0);
	// Checks for Wish & +4.
	if (Card == CardType::WISH || Card == CardType::PLUS4) {
		Color = CardColor::SPECIAL;
	}

	if (player == Player::PLAYER_1) {
		Player1Hand.push_back({Card, Color});
	} else if (player == Player::PLAYER_2) {
		Player2Hand.push_back({Card, Color});
	} else if (player == Player::PLAYER_3) {
		Player3Hand.push_back({Card, Color});
	} else if (player == Player::PLAYER_4) {
		Player4Hand.push_back({Card, Color});
	} else if (player == Player::TABLE) {
		tableCard.push_back({Card, Color});
	}
}

void CardHelper::specialHandle(Player player, CardType card) {
	if (player == Player::PLAYER_1) {
		switch(card) {
			case CardType::NUMBER_0:
			case CardType::NUMBER_1:
			case CardType::NUMBER_2:
			case CardType::NUMBER_3:
			case CardType::NUMBER_4:
			case CardType::NUMBER_5:
			case CardType::NUMBER_6:
			case CardType::NUMBER_7:
			case CardType::NUMBER_8:
			case CardType::NUMBER_9:
				break;
			case CardType::PLUS2:
				AddCard(Player::PLAYER_2);
				AddCard(Player::PLAYER_2);
				break;
			case CardType::PLUS4:
				AddCard(Player::PLAYER_2);
				AddCard(Player::PLAYER_2);
				AddCard(Player::PLAYER_2);
				AddCard(Player::PLAYER_2);
				//Color wish function.
				break;
			case CardType::WISH:
				// Color wish function.
				break;
			case CardType::PAUSE:
				// The Pause function.
				break;
			case CardType::RETURN:
				// The Return function.
				break;
		}
	} else if (player == Player::PLAYER_2) {
		switch(card) {
			case CardType::NUMBER_0:
			case CardType::NUMBER_1:
			case CardType::NUMBER_2:
			case CardType::NUMBER_3:
			case CardType::NUMBER_4:
			case CardType::NUMBER_5:
			case CardType::NUMBER_6:
			case CardType::NUMBER_7:
			case CardType::NUMBER_8:
			case CardType::NUMBER_9:
				break;
			case CardType::PLUS2:
				AddCard(Player::PLAYER_1);
				AddCard(Player::PLAYER_1);
				break;
			case CardType::PLUS4:
				AddCard(Player::PLAYER_1);
				AddCard(Player::PLAYER_1);
				AddCard(Player::PLAYER_1);
				AddCard(Player::PLAYER_1);
				//Color wish function.
				break;
			case CardType::WISH:
				// Color wish function.
				break;
			case CardType::PAUSE:
				// The Pause function.
				break;
			case CardType::RETURN:
				// The Return function.
				break;
		}
	}
}