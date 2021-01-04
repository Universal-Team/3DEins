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

#ifndef _3DEINS_CORE_PLAYER_HPP
#define _3DEINS_CORE_PLAYER_HPP

#include "cards.hpp"
#include "coreHelper.hpp"
#include "deck.hpp"

class Cards;
class Deck;
class Player {
protected:
	std::unique_ptr<Cards> cards;
public:
	Player(std::unique_ptr<Deck> &deck);

	/* Add & Remove. */
	void addCard(std::unique_ptr<Deck> &deck);
	void removeCard(int position);

	/* Check for playable & play. */
	bool Playable(const CardStruct &Table, const int &card) const;
	void play(int position, CardStruct &table);

	/* Get the size & hand. */
	int getSize() const;
	std::vector<CardStruct> getHand() const;

	/* Return the Card Points and overwrite it to a Player's points. */
	void returnCardPoints(std::unique_ptr<Player> &player);

	/* Get Points & State. */
	int getPoints() const { return this->playerPoints; };
	PlayerState getState() const { return this->state; };
	void setState(PlayerState st) { this->state = st; };

	CardColor CC(int card) const;
	CardType CT(int card) const;
	CardStruct CS(int card) const;
private:
	int playerPoints = 0; // The Player's points. Init as 0.
	PlayerState state = PlayerState::NOTHING; // The Player's state. Init as Nothing.
};

#endif