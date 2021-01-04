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

#include "player.hpp"

/*
	Init Player with 6 Cards at begin.
*/
Player::Player(std::unique_ptr<Deck> &deck): cards(std::make_unique<Cards>()) {
	for (int i = 0; i < 6; i++) {
		this->cards->add(deck);
	}
}

/* Add a card to the hand. */
void Player::addCard(std::unique_ptr<Deck> &deck) { this->cards->add(deck); };

/* Remove a card of the hand. */
void Player::removeCard(int position) {
	if ((int)this->cards->getSize() > 0) {
		/* Out of range checks. */
		if (position < (int)this->cards->getSize()) this->cards->Remove(position);
	}
}

/* Play a card. */
void Player::play(int position, CardStruct &table) {
	table = this->cards->CS(position); // Set the current card as the table card.

	this->removeCard(position); // Remove the card from the hand.
}

/* Get the amount of cards. */
int Player::getSize() const { return (int)this->cards->getSize(); };

/* Return the Vector of the CardStruct. Basically the Player-Hand. */
std::vector<CardStruct> Player::getHand() const { return this->cards->getCards(); };

/* Return if playable. */
bool Player::Playable(const CardStruct &Table, const int &card) const { return this->cards->Playable(Table, card); };

/*
	Return the amount of points from the Player's hand.
	points -> Reference to the Player where the Points should be added.
*/
void Player::returnCardPoints(std::unique_ptr<Player> &player) {
	if (this->getSize() > 0) {
		for (int i = 0; i < this->getSize(); i++) {
			player->playerPoints += this->cards->getPoints(i);
		}
	}
}

/* Return the CardColor. */
CardColor Player::CC(int card) const { return this->cards->CC(card); };

/* Return the CardType. */
CardType Player::CT(int card) const { return this->cards->CT(card); };

/* Return the CardStruct. */
CardStruct Player::CS(int card) const { return this->cards->CS(card); };