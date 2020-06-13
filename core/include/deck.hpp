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

#ifndef _3DEINS_CORE_DECK_HPP
#define _3DEINS_CORE_DECK_HPP

#include "coreHelper.hpp"

class Deck {
protected:
	// Should it be protected?
	std::vector<CardStruct> CardDeck; // 108 Cards are there, 110 with special card.
public:
	Deck(): CardDeck({}) { this->fill(); } // Our Constructor will create a new CardDeck for us.

	// Initialize a new Deck. Also called by fill.
	void Initialize();

	// Shuffle the Deck. Useful for special cases in game.
	void shuffleDeck();

	// Initialize, fill and shuffle the Deck.
	void fill();

	/*	Return the Decksize.
	*	Returns the amount of cards in the current deck.
	*/
	int deckSize() { return CardDeck.size(); }


	/*	Return the CardType of the last card.
	*	Returns the CardType of the last card from the deck.
	*/
	CardType CT() { return CardDeck[CardDeck.size() - 1].CT; }

	/*	Return the CardColor of the last card.
	*	Returns the CardColor of the last card from the deck.
	*/
	CardColor CC() { return CardDeck[CardDeck.size() - 1].CC; }

	/*	Return the CardStruct from the last card and remove it from the Deck as well.
	*	Returns the CardStruct of the last card from the deck and remove it from the deck as well.
	*/
	CardStruct getCard();

	/*	Return the CardStruct from the last card.
	*	Returns the CardStruct of the last card from the deck.
	*/
	CardStruct topCard();
};

#endif