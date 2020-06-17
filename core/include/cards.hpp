/*
*   This file is part of 3DEins/DSEins-Core
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

#ifndef _3DEINS_CORE_CARDS_HPP
#define _3DEINS_CORE_CARDS_HPP

#include "deck.hpp"
#include "coreHelper.hpp"
#include <vector>

class Deck;
class Cards {
protected:
	// Should it be protected?
	std::vector<CardStruct> Hand;
public:
	Cards(): Hand({}) { }

	/*	Give a card to the Hand from the cardDeck.
	*	std::unique_ptr<Deck> &deck -> A reference to the CardDeck.
	*/
	void add(std::unique_ptr<Deck> &deck);

	/*	Remove a card from the Hand.
	*	const int position -> The position from the Hand.
	*	This will not remove anything, if position is out of scope.
	*/
	void Remove(const int position);

	/*	Return, if the Card is playable.
	*	const CardStruct Table -> The CardStruct of the Tablecard.
	*	const int position -> The position of the card from the Hand which should be checked.
	*	Returns true, if card is playable, false if not.
	*/
	bool Playable(const CardStruct Table, const int position);

	/*	Return the CardColor of the card.
	*	const int position -> The position of the card from the Hand.
	*	Returns the CardColor.
	*/
	CardColor CC(const int position) { return Hand[position].CC; }

	/*	Return the CardType of the card.
	*	const int position -> The position of the card from the Hand.
	*	Returns the CardType.
	*/
	CardType CT(const int position) { return Hand[position].CT; }

	/*	Return the CardStruct of the card.
	*	const int position -> The position of the card from the Hand.
	*	Returns the CardStruct.
	*/
	CardStruct CS(const int position) { return Hand[position]; }

	/*	Return the size of the Hand.
	*	Returns the size of the Hand.
	*/
	int getSize();

	/*	Return the points of a card.
	*	const int position -> The position of the card from the Hand.
	*	Returns the points of the card.
	*/
	int getPoints(const int position);

	/*	Return the Hand.
	*	Returns a std::vector<CardStruct> of the hand.
	*/
	const std::vector<CardStruct> getCards() { return Hand; }
};

#endif