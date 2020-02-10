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
#include "test.hpp"

#include <vector>

#define MAXCOLOR	4
#define MAXCARDTYPE	15
#define MAXSHOWNCARDS 6

// CardStruct.
struct CardStruct {
	int cardType;
	int CardColor;
};

std::vector<CardStruct> PlayerHand;
std::vector<CardStruct> OpponentHand;
std::vector<CardStruct> tableCard;

void AddCard(int Player) {
	int card = rand() % MAXCARDTYPE + 0;
	int color = rand() % MAXCOLOR + 1;

	// Checks for Wish & +4.
	if (card == 13 || card == 14) {
		color = 5;
	}

	if (Player == 0) {
		PlayerHand.push_back({card, color});
	} else if (Player == 1) {
		OpponentHand.push_back({card, color});
	} else {
		tableCard.push_back({card, color});
	}
}

void RemoveCard(int Player, int pos) {
	if (Player == 0) {
		PlayerHand.erase(PlayerHand.begin()+pos);
	} else if (Player == 1) {
		OpponentHand.erase(OpponentHand.begin()+pos);
	}
}

void Test::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 2, 0.9f, WHITE, "3DEins");
	GFX::DrawCard(tableCard[0].cardType, 170, 80, tableCard[0].CardColor);

	if (currentPlayer == 0) {
		Gui::DrawStringCentered(0, 216, 0.7f, WHITE, "It's your turn!");
	} else {
		Gui::DrawStringCentered(0, 216, 0.7f, WHITE, "It's the opponent turn!");
	}

	GFX::DrawCard(15, 10, 85, 0.8, 0.8);
	Gui::DrawString(25, 15, 0.7f, WHITE, std::to_string((int)PlayerHand.size())); // For now player's hand.

	GFX::DrawBottom();
	// TODO: Only display 6-7 Cards & Scroll cards.
	for (int i = 0; i < (int)PlayerHand.size(); i++) {
		if (i == currentCard) {
			if (currentCard < 6) {
				GFX::DrawSelectedCard(PlayerHand[i].cardType, 2 + (i * 53), 85, PlayerHand[i].CardColor);
			} else {
				GFX::DrawSelectedCard(PlayerHand[i+currentCard-5].cardType, 2 + (i * 53), 85, PlayerHand[i+currentCard-5].CardColor);
			}
		} else {
			if (currentCard < 6) {
				GFX::DrawCard(PlayerHand[i].cardType, 2 + (i * 53), 85, PlayerHand[i].CardColor);
			} else {
				GFX::DrawCard(PlayerHand[i+currentCard-5].cardType, 2 + (i * 53), 85, PlayerHand[i+currentCard-5].CardColor);
			}	
		}
	}
}

Test::Test() {
	// Clear hands for new game.
	PlayerHand.clear();
	OpponentHand.clear();
	tableCard.clear();
	// Fill Player 1.
	AddCard(0);
	AddCard(0);
	AddCard(0);
	AddCard(0);
	AddCard(0);
	AddCard(0);
	// Fill opponent.
	AddCard(1);
	AddCard(1);
	AddCard(1);
	AddCard(1);
	AddCard(1);
	AddCard(1);
	// set Table card.
	AddCard(2);
}

void Test::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	RoundLogic(hDown, hHeld, touch);
}

// TODO.
void Test::specialHandle(int Player, int card) {
	if (Player == 0) {
		// Plus 2.
		if (card == 12) {
			AddCard(1);
			AddCard(1);
			// Plus 4.
		} else if (card == 14) {
			AddCard(1);
			AddCard(1);
			AddCard(1);
			AddCard(1);
			// Wish a color, not implemented.
		} else if (card == 13) {
			// Wish a color, not implemented.
		} else if (card == 10) {
			isPause = true;
		} else if (card == 11) {
			canReturn = true;
		}
	}
}


// For the Player hand.
void Test::PlayerLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_RIGHT) {
		if (currentCard < (int)PlayerHand.size()-1) {
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
		if (PlayerHand[currentCard].cardType == tableCard[0].cardType || PlayerHand[currentCard].CardColor == tableCard[0].CardColor) {
			tableCard.clear();
			int card = PlayerHand[currentCard].cardType;
			int color = PlayerHand[currentCard].CardColor;
			tableCard.push_back({card, color});
			RemoveCard(0, currentCard);
			if (currentCard > (int)PlayerHand.size() -1) {
				currentCard = (int)PlayerHand.size() - 1;
			}
			//currentPlayer = 1;
		}
		// Set Logic -> TODO.
	}

	// User cannot set, so draw a card.
	if (hDown & KEY_X) {
		AddCard(0);
		//currentPlayer = 1;
	}
}

// TODO!!!
void Test::OpponentLogic(void) {
	for (int i = 0; i < (int)OpponentHand.size(); i++) {
		if (OpponentHand[i].cardType == tableCard[0].cardType || OpponentHand[i].CardColor == tableCard[0].CardColor) {
			tableCard.clear();
			int card = OpponentHand[i].cardType;
			int color = OpponentHand[i].CardColor;
			tableCard.push_back({card, color});
			RemoveCard(1, i);
		} else {
			AddCard(1);
		}
		currentPlayer = 0;
	}
}

void Test::RoundLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (currentPlayer == 0) {
		PlayerLogic(hDown, hHeld, touch);
	} else if (currentPlayer == 1) {
		OpponentLogic();
	}
}