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

#include "game.hpp"

// Init the game.
Game::Game(const int players): playerAmount(players) {
	this->v_cardIndex.clear(); // Clear index.
	this->cardDeck = std::make_unique<Deck>(); // First init CardDeck.
	
	for (int i = 0; i < this->playerAmount; i++) {
		this->v_cardIndex.push_back({0}); // Push back the CardIndex.
		this->Players.push_back({std::make_unique<Player>(this->cardDeck)}); // Init players.
	}

	// Redraw a Card for the TableCard.
	this->TableCard = this->cardDeck->getCard();

	// if TableCard is Draw 4 or Wild or Special card -> Redraw.
	#ifdef _USE_SPECIAL_CARD
		if (this->TableCard.CT == CardType::WILD || this->TableCard.CT == CardType::DRAW4 || this->TableCard.CT == CardType::SPECIAL) {
			this->TableCard = this->cardDeck->getCard();
		}

	#else
		if (this->TableCard.CT == CardType::WILD || this->TableCard.CT == CardType::DRAW4) {
			this->TableCard = this->cardDeck->getCard();
		}

	#endif
}

void Game::addCard(const int player) {
	this->Players[player]->addCard(this->cardDeck);
}

void Game::removeCard(const int position, int player) {
	this->Players[player]->removeCard(position);
}

bool Game::Playable(const int position, const int player) {
	return this->Players[player]->Playable(this->TableCard, position);
}

void Game::play(const int position, const int player) {
	if (this->Playable(position, player)) {
		// Only play if playable.
		this->Players[player]->play(position, this->TableCard);
	}
}

// 0 Cards -> Won!
void Game::checkCards(const int player) {
	if (this->Players[player]->getSize() == 0)	this->v_winner = player;
}

const std::vector<CardStruct> Game::getHand(const int player) {
	return this->Players[player]->getHand();
}

int Game::getSize(const int player) const {
	return this->Players[player]->getSize();
}

const PlayerState Game::state(const int player) {
	return this->Players[player]->getState();
}

void Game::state(const PlayerState s, const int player) {
	this->Players[player]->setState(s);
}

CardColor Game::getColor(const int index, const int player) const {
	return this->Players[player]->CC(index);
}

CardType Game::getType(const int index, const int player) const {
	return this->Players[player]->CT(index);
}

int Game::getPoints(const int player) const {
	return this->Players[player]->getPoints();
}

CardStruct Game::getPlayerCard(const int index, const int player) {
	return this->Players[player]->CS(index);
}

CardStruct Game::getTableTop() {
	return this->cardDeck->topCard();
}