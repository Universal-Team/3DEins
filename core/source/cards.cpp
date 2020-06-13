/*
*   This file is part of 3DEins-Core
*   Copyright (C) 2020 Universal-Team
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

#include "cards.hpp"
#include "coreHelper.hpp"
#include "msg.hpp"

// Deck &deck is the reference to our CardDeck.
void Cards::add(std::unique_ptr<Deck> &deck) {
	if (deck != nullptr) {
		if (deck->deckSize() == 0) {
			deck->fill(); // Cause our CardDeck is empty, we fill and shuffle it.
		}
	
		this->Hand.push_back(deck->getCard());
	} else {
		Msg::DisplayWaitMsg("Carddeck is not initialized.");
	}
}

void Cards::Remove(const int position) {
	// Only Remove card, if Hand isn't empty to avoid crashes on Vector.
	if ((int)this->Hand.size() > 0) {
		if (position < (int)this->Hand.size()) { // Out of range checks.
			this->Hand.erase(this->Hand.begin()+position);
		} else {
			Msg::DisplayWaitMsg("Position out of scope.\nDo not remove card.");
		}
	} else {
		Msg::DisplayWaitMsg("Hand size is 0 or lower.\nDo not remove card.");
	}
}

bool Cards::Playable(const CardStruct Table, const int position) {
	if (position > (int)this->Hand.size())	return false; // Out of range!

	// Special case for the special card.
	#ifdef _USE_SPECIAL_CARD
		if (this->Hand[position].CT == CardType::SPECIAL) return true;
	#endif

	// First, we will check for Playable Colors.
	if (this->Hand[position].CC == Table.CC) return true; // CardColor Matches!
	if (this->Hand[position].CC == CardColor::COLOR_BLACK) return true; // The CardColor is black, which should be valid.

	// Now the a bit more complex thing -> CardType.
	if (this->Hand[position].CT == Table.CT) return true; // CardType Matches!
	if (this->Hand[position].CT == CardType::WILD || this->Hand[position].CT == CardType::DRAW4) return true; // Wild & Wild Draw 4 are valid anyways.

	// If nothing matches, return false.
	return false;
}

// Get the amount of points from the Card.
int Cards::getPoints(const int position) {
	if (position > (int)this->Hand.size())	return 0; // Out of range!

	switch(this->Hand[position].CT) {
		case CardType::NUMBER_0:
			return 0;
		case CardType::NUMBER_1:
			return 1;
		case CardType::NUMBER_2:
			return 2;
		case CardType::NUMBER_3:
			return 3;
		case CardType::NUMBER_4:
			return 4;
		case CardType::NUMBER_5:
			return 5;
		case CardType::NUMBER_6:
			return 6;
		case CardType::NUMBER_7:
			return 7;
		case CardType::NUMBER_8:
			return 8;
		case CardType::NUMBER_9:
			return 9;
		case CardType::REVERSE:
			return 20;
		case CardType::SKIP:
			return 20;
		case CardType::DRAW2:
			return 20;
		case CardType::WILD:
			return 50;
		case CardType::DRAW4:
			return 50;
		#ifdef _USE_SPECIAL_CARD
		case CardType::SPECIAL:
			return SPECIAL_CARD_POINTS;
		#endif
	}
	return 0; // Should Never happen.
}

// Get the amount of Cards in a Hand.
int Cards::getSize() {
	return (int)this->Hand.size();
}