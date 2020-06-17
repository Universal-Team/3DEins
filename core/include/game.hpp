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

#ifndef _3DEINS_CORE_GAME_HPP
#define _3DEINS_CORE_GAME_HPP

#include "cards.hpp"
#include "coreHelper.hpp"
#include "deck.hpp"
#include "player.hpp"

class Deck;
class Player;
class Game {
protected:
	std::vector<std::unique_ptr<Player>> Players; // Our player Variables.
	CardStruct TableCard; // The card from the table.
	std::unique_ptr<Deck> cardDeck; // The CardDeck variable.
	int playerAmount; // The amount of players.
public:
	// Constructor initialized with amount of players.
	Game(const int players);

	// Player stuff.

	/*	Add a Card to the specific player's hand.
	*	const int player -> The player.
	*	Adds a card to the specific Player's hand.
	*/
	void addCard(const int player);

	/*	Remove a Card from the specific player's hand.
	*	const int position -> The Position of the card.
	*	const int player -> The player.
	*	If position is out of scope -> Don't do anything.
	*/
	void removeCard(const int position, const int player); // If no player passed, use currentPlayer.

	/*	Return if the card is playable.
	*	const int position -> The Position of the card.
	*	const int player -> The player.
	*	Returns true, if card is playable, false if not.
	*/
	bool Playable(const int position, const int player); // Check if card is playable.

	/*	Play a card.
	*	const int position -> The Position of the card.
	*	const int player -> The player.
	*	If TableCard & Current Card does not match -> Do nothing.
	*/
	void play(const int position, const int player); // Play's a card.

	// Get and Set the current Player.
	int currentPlayer() const { return this->v_currentPlayer; }
	void currentPlayer(const int player) { if (player <= this->playerAmount - 1)	this->v_currentPlayer = player; }

	// Return the player amount.
	int maxPlayer() const { return this->playerAmount; }

	// Get and Set direction.
	DIRECTION direction() const { return this->v_playDirection; }
	void direction(const DIRECTION d) { this->v_playDirection = d; }

	// Get and Set, if able to continue the round.
	bool canContinue() const { return this->v_canContinue; }
	void canContinue(const bool v) { this->v_canContinue = v; }

	// Get and Set the Card Indexes of the players.
	int cardIndex(const int player) const { return this->v_cardIndex[player]; }
	void cardIndex(const int index, const int player) { this->v_cardIndex[player] = index; }

	// Get the current winner.
	int winner() const { return this->v_winner; }
	// Check if player has won and set it to v_winner.
	void checkCards(const int player);


	// Get the Player's Hand.
	const std::vector<CardStruct> getHand(int player);
	// Get the size of the player's hand.
	int getSize(int player) const;

	// Get and Set Player Status.
	const PlayerState state(const int player);
	void state(const PlayerState s, const int player);

	// Get the TableCard's CardStruct.
	CardStruct tableCard() { return this->TableCard; }
	// Set the TableCard's color.
	void tbCardColor(const CardColor color) { this->TableCard.CC = color; }
	// Set the TableCard's type.
	void tbCardType(const CardType cardtype) { this->TableCard.CT = cardtype; }
	CardStruct getTableTop();

	// Get the CardColor from a card of the Player's hand.
	CardColor getColor(const int index, const int player) const;
	// Get the CardType from a card of the Player's hand.
	CardType getType(const int index, const int player) const;
	// Get the CardStruct from a card of the Player's hand.
	CardStruct getPlayerCard(const int index, const int player);
	// Return the points from a player.
	int getPoints(const int player) const;
	
	// Card Drawing stuff.
	// Return, if card was already drawn.
	bool drawn() const { return this->v_hasDrawn; }
	// Set CardDraw status. Only 1 draw each turn allowed.
	void drawn(const bool v) { this->v_hasDrawn = v; }
	// Get the Plus 2 / 4 Drawing Counter.
	int drawingCounter() { return this->v_drawingCounter; }
	// Add the Plus 2 / 4 Drawing Counter.
	void drawingCounter(const int v) { this->v_drawingCounter += v; }
	// Reset the Plus 2 / 4 Drawing Counter.
	void resetCounter() { this->v_drawingCounter = 0; }

private:
	DIRECTION v_playDirection = DIRECTION::CLOCKWISE; // Clockwise play direction.
	std::vector<int> v_cardIndex; // Index of the currentCard for all players.
	bool v_canContinue = false; // Special stuff.
	bool v_hasDrawn = false; // Return whetever a card was drawn to avoid multiple draws.
	int v_currentPlayer = 0; // 0 by default.
	int v_winner = -1; // -1 -> No winner.
	int v_drawingCounter = 0; // For counter like +2, +4.
};

#endif