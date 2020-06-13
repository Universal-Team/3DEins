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

#include "deck.hpp"
#include <algorithm>

// This has all the default Cards from the regular game inside the Vector.
// Used to initialize a new deck.
// If "_USE_SPECIAL_CARD" is defined, the deck is 110 Cards, else 108. (Special Card 2 times included.)
const std::vector<CardStruct> defaultDeck = {
	// RED COLOR.
	{CardColor::COLOR_RED, CardType::NUMBER_0}, // 0.
	{CardColor::COLOR_RED, CardType::NUMBER_1}, {CardColor::COLOR_RED, CardType::NUMBER_1}, // 1.
	{CardColor::COLOR_RED, CardType::NUMBER_2}, {CardColor::COLOR_RED, CardType::NUMBER_2}, // 2.
	{CardColor::COLOR_RED, CardType::NUMBER_3}, {CardColor::COLOR_RED, CardType::NUMBER_3}, // 3.
	{CardColor::COLOR_RED, CardType::NUMBER_4}, {CardColor::COLOR_RED, CardType::NUMBER_4}, // 4.
	{CardColor::COLOR_RED, CardType::NUMBER_5}, {CardColor::COLOR_RED, CardType::NUMBER_5}, // 5.
	{CardColor::COLOR_RED, CardType::NUMBER_6}, {CardColor::COLOR_RED, CardType::NUMBER_6}, // 6.
	{CardColor::COLOR_RED, CardType::NUMBER_7}, {CardColor::COLOR_RED, CardType::NUMBER_7}, // 7.
	{CardColor::COLOR_RED, CardType::NUMBER_8}, {CardColor::COLOR_RED, CardType::NUMBER_8}, // 8.
	{CardColor::COLOR_RED, CardType::NUMBER_9}, {CardColor::COLOR_RED, CardType::NUMBER_9}, // 9.
	{CardColor::COLOR_RED, CardType::REVERSE}, {CardColor::COLOR_RED, CardType::REVERSE}, // Reverse.
	{CardColor::COLOR_RED, CardType::SKIP}, {CardColor::COLOR_RED, CardType::SKIP}, // Skip.
	{CardColor::COLOR_RED, CardType::DRAW2}, {CardColor::COLOR_RED, CardType::DRAW2}, // Draw 2.

	// YELLOW COLOR.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_0}, // 0.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_1}, {CardColor::COLOR_YELLOW, CardType::NUMBER_1}, // 1.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_2}, {CardColor::COLOR_YELLOW, CardType::NUMBER_2}, // 2.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_3}, {CardColor::COLOR_YELLOW, CardType::NUMBER_3}, // 3.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_4}, {CardColor::COLOR_YELLOW, CardType::NUMBER_4}, // 4.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_5}, {CardColor::COLOR_YELLOW, CardType::NUMBER_5}, // 5.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_6}, {CardColor::COLOR_YELLOW, CardType::NUMBER_6}, // 6.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_7}, {CardColor::COLOR_YELLOW, CardType::NUMBER_7}, // 7.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_8}, {CardColor::COLOR_YELLOW, CardType::NUMBER_8}, // 8.
	{CardColor::COLOR_YELLOW, CardType::NUMBER_9}, {CardColor::COLOR_YELLOW, CardType::NUMBER_9}, // 9.
	{CardColor::COLOR_YELLOW, CardType::REVERSE}, {CardColor::COLOR_YELLOW, CardType::REVERSE}, // Reverse.
	{CardColor::COLOR_YELLOW, CardType::SKIP}, {CardColor::COLOR_YELLOW, CardType::SKIP}, // Skip.
	{CardColor::COLOR_YELLOW, CardType::DRAW2}, {CardColor::COLOR_YELLOW, CardType::DRAW2}, // Draw 2.

	// GREEN COLOR.
	{CardColor::COLOR_GREEN, CardType::NUMBER_0}, // 0.
	{CardColor::COLOR_GREEN, CardType::NUMBER_1}, {CardColor::COLOR_GREEN, CardType::NUMBER_1}, // 1.
	{CardColor::COLOR_GREEN, CardType::NUMBER_2}, {CardColor::COLOR_GREEN, CardType::NUMBER_2}, // 2.
	{CardColor::COLOR_GREEN, CardType::NUMBER_3}, {CardColor::COLOR_GREEN, CardType::NUMBER_3}, // 3.
	{CardColor::COLOR_GREEN, CardType::NUMBER_4}, {CardColor::COLOR_GREEN, CardType::NUMBER_4}, // 4.
	{CardColor::COLOR_GREEN, CardType::NUMBER_5}, {CardColor::COLOR_GREEN, CardType::NUMBER_5}, // 5.
	{CardColor::COLOR_GREEN, CardType::NUMBER_6}, {CardColor::COLOR_GREEN, CardType::NUMBER_6}, // 6.
	{CardColor::COLOR_GREEN, CardType::NUMBER_7}, {CardColor::COLOR_GREEN, CardType::NUMBER_7}, // 7.
	{CardColor::COLOR_GREEN, CardType::NUMBER_8}, {CardColor::COLOR_GREEN, CardType::NUMBER_8}, // 8.
	{CardColor::COLOR_GREEN, CardType::NUMBER_9}, {CardColor::COLOR_GREEN, CardType::NUMBER_9}, // 9.
	{CardColor::COLOR_GREEN, CardType::REVERSE}, {CardColor::COLOR_GREEN, CardType::REVERSE}, // Reverse.
	{CardColor::COLOR_GREEN, CardType::SKIP}, {CardColor::COLOR_GREEN, CardType::SKIP}, // Skip.
	{CardColor::COLOR_GREEN, CardType::DRAW2}, {CardColor::COLOR_GREEN, CardType::DRAW2}, // Draw 2.

	// BLUE COLOR.
	{CardColor::COLOR_BLUE, CardType::NUMBER_0}, // 0.
	{CardColor::COLOR_BLUE, CardType::NUMBER_1}, {CardColor::COLOR_BLUE, CardType::NUMBER_1}, // 1.
	{CardColor::COLOR_BLUE, CardType::NUMBER_2}, {CardColor::COLOR_BLUE, CardType::NUMBER_2}, // 2.
	{CardColor::COLOR_BLUE, CardType::NUMBER_3}, {CardColor::COLOR_BLUE, CardType::NUMBER_3}, // 3.
	{CardColor::COLOR_BLUE, CardType::NUMBER_4}, {CardColor::COLOR_BLUE, CardType::NUMBER_4}, // 4.
	{CardColor::COLOR_BLUE, CardType::NUMBER_5}, {CardColor::COLOR_BLUE, CardType::NUMBER_5}, // 5.
	{CardColor::COLOR_BLUE, CardType::NUMBER_6}, {CardColor::COLOR_BLUE, CardType::NUMBER_6}, // 6.
	{CardColor::COLOR_BLUE, CardType::NUMBER_7}, {CardColor::COLOR_BLUE, CardType::NUMBER_7}, // 7.
	{CardColor::COLOR_BLUE, CardType::NUMBER_8}, {CardColor::COLOR_BLUE, CardType::NUMBER_8}, // 8.
	{CardColor::COLOR_BLUE, CardType::NUMBER_9}, {CardColor::COLOR_BLUE, CardType::NUMBER_9}, // 9.
	{CardColor::COLOR_BLUE, CardType::REVERSE}, {CardColor::COLOR_BLUE, CardType::REVERSE}, // Reverse.
	{CardColor::COLOR_BLUE, CardType::SKIP}, {CardColor::COLOR_BLUE, CardType::SKIP}, // Skip.
	{CardColor::COLOR_BLUE, CardType::DRAW2}, {CardColor::COLOR_BLUE, CardType::DRAW2}, // Draw 2.

	// Special Cards.
	{CardColor::COLOR_BLACK, CardType::WILD}, {CardColor::COLOR_BLACK, CardType::WILD}, {CardColor::COLOR_BLACK, CardType::WILD}, {CardColor::COLOR_BLACK, CardType::WILD}, // Wild.
	#ifdef _USE_SPECIAL_CARD // Special card.
		{CardColor::COLOR_BLACK, CardType::SPECIAL}, {CardColor::COLOR_BLACK, CardType::SPECIAL},
	#endif
	{CardColor::COLOR_BLACK, CardType::DRAW4}, {CardColor::COLOR_BLACK, CardType::DRAW4}, {CardColor::COLOR_BLACK, CardType::DRAW4}, {CardColor::COLOR_BLACK, CardType::DRAW4} // Wild Draw 4.
};

// Here we put the default CardDeck here to initialize it.
void Deck::Initialize() {
	this->CardDeck.clear();
	this->CardDeck = defaultDeck;
}

// We will fill our Deck with Default and shuffle it here.
void Deck::fill() {
	this->Initialize();
	this->shuffleDeck();
}

// We will shuffle our deck here.
void Deck::shuffleDeck() {
	std::shuffle(this->CardDeck.begin(), this->CardDeck.end(), std::default_random_engine(randomGen()));
}

// Return the Card from the Deck and remove from Deck.
CardStruct Deck::getCard() {
	CardStruct temp = {this->CC(), this->CT()};
	this->CardDeck.erase(this->CardDeck.begin()+this->deckSize()-1); // Remove Card from deck.
	return temp;
}

CardStruct Deck::topCard() {
	if (this->deckSize() == 0) {
		this->fill();
	}
	
	return CardStruct({this->CC(), this->CT()});
}