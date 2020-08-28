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

#ifndef _3DEINS_CORE_HELPER_HPP
#define _3DEINS_CORE_HELPER_HPP

#include "_3DEins_Core.h"
#include <memory>
#include <random>
#include <string>
#include <vector>

#define MAXCARDCOLOR 4 // Only 4 Colors, the 5th color is for special cards.

#ifdef _USE_SPECIAL_CARD
	#define MAXCARDTYPE	16
#else
	#define MAXCARDTYPE	15
#endif

inline std::mt19937 randomGen; // Our Random generator / used for shuffle the cards.

/* The CardTypes. */
enum class CardType {
	NUMBER_0,
	NUMBER_1,
	NUMBER_2,
	NUMBER_3,
	NUMBER_4,
	NUMBER_5,
	NUMBER_6,
	NUMBER_7,
	NUMBER_8,
	NUMBER_9,
	REVERSE,
	SKIP,
	DRAW2,
	WILD,
	DRAW4
	#ifdef _USE_SPECIAL_CARD
	,SPECIAL
	#endif
};

/* The CardColors. */
enum class CardColor {
	COLOR_RED,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLACK
};

/* The PlayerState. */
enum class PlayerState {
	NOTHING,
	DRAWING,
	BREAK,
	CONTINUE,
	#ifdef _USE_SPECIAL_CARD
	SPECIAL,
	#endif
	WISH
};

/* The Play Direction. */
enum class DIRECTION {
	CLOCKWISE,
	COUNTERCLOCKWISE
};

/*
	Card Struct. A CardStruct contains:
	1.) Card Color (Like Green, Blue, Yellow, Red, Black.)
	2.) Card Type (Like 0, 4, 7, Plus 2, Wild, etc.)
	Size: u16 || 2x u8.
*/
struct CardStruct {
	CardColor CC;
	CardType CT;
};


namespace CoreHelper {
	/*
		Generate a seed for the shuffling cards. Only call this on application start.
		Generates the seed for std::mt19937 randomGen.
	*/
	void generateSeed();
}

#include "game.hpp"
class Game;

namespace GameHelper {
	/*
		Handle Status for the Players & the game.
		std::unique_ptr<Game> &game -> A reference to the current game.
		const int firstPlayer -> The current Player.
		const int secondPlayer -> The next Player.
		const int maxPlayer -> The Player amount.
	*/
	void checkAndSet(std::unique_ptr<Game> &game, const int firstPlayer, const int secondPlayer, const int maxPlayer);

	/*
		Return the amount of points of a card.
		const CardType card -> The CardType.
		Returns the amount of points of the specific CardType.
	*/
	int getPoints(const CardType card);

	/*
		Return the name of the CardType.
		const CardType Card -> The CardType.
		Returns the name of the CardType with 'Lang::get(...);'.
	*/
	std::string getTypeName(const CardType Card);

	/*
		Return the name of the CardColor.
		const CardColor Card -> The CardColor.
		Returns the name of the CardColor with 'Lang::get(...);'.
	*/
	std::string getColorName(const CardColor Card);

	/*
		Return the amount of points of a CardType for the AI.
		const CardType Card -> The CardType.
		Returns the amount of points from the specific CardType.
	*/
	int AIPointTable(const CardType card);

	/*
		Return the highest card index points for the AI.
		std::unique_ptr<Game> &currentGame -> The current Game.
		const int player -> The current player.
		Return the index of the best card.
	*/
	int getHighestCard(std::unique_ptr<Game> &currentGame, const int player);
}

#endif