/*
*   This file is part of 3DEins/DSEins-Core
*   Copyright (C) 2020-2021 Universal-Team
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
#include "logging.hpp"

/* Add a card. */
void Cards::add(std::unique_ptr<Deck> &deck) {
	if (deck) {
		if (deck->deckSize() < 1) deck->fill(); // Cause our CardDeck is empty, we fill and shuffle it.

		this->Hand.push_back(deck->getCard());
	}
}

/* Remove a card. */
void Cards::Remove(const int position) {
	/* Only Remove card, if Hand isn't empty to avoid crashes on Vector. */
	if ((int)this->Hand.size() > 0) {
		/* Out of range checks. */
		if (position < (int)this->Hand.size()) this->Hand.erase(this->Hand.begin() + position);
	}
}

/* Check if playable. */
bool Cards::Playable(const CardStruct Table, const int position) const {
	if (position > (int)this->Hand.size())	return false; // Out of range!

	/* Do exception here for Wild. */
	if (this->Hand[position].CT == CardType::WILD) {
		if (Table.CT == CardType::WILD || Table.CT == CardType::DRAW4)	return false;
		return true;
	}

	if (this->Hand[position].CT == CardType::DRAW4)	return true; // Should be valid?
	if (this->Hand[position].CC == Table.CC) return true; // CardColor Matches!
	if (this->Hand[position].CT == Table.CT) return true; // CardType Matches!

	/* If nothing matches, return false. */
	return false;
}

/* Get the amount of points from the Card. */
int Cards::getPoints(const int position) const {
	if (position > (int)this->Hand.size()) return 0; // Out of range!

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
		case CardType::SKIP:
		case CardType::DRAW2:
			return 20;

		case CardType::WILD:
		case CardType::DRAW4:
			return 50;
	}

	return 0; // Should Never happen.
}

/* Get the amount of Cards in a Hand. */
int Cards::getSize() const { return (int)this->Hand.size(); };