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

#include "coreHelper.hpp"
#include "lang.hpp"
#include <algorithm>
#include <time.h>

// We need to do this hacky style. There is NO workaround.
#ifdef _USE_SPECIAL_CARD
extern void _3DEins_SpecialHandle(std::unique_ptr<Game> &game, const int firstPlayer, const int secondPlayer, const int maxPlayer);
#endif

void GameHelper::checkAndSet(std::unique_ptr<Game> &game, const int firstPlayer, const int secondPlayer, const int maxPlayer) {
	game->state(PlayerState::NOTHING, firstPlayer);
	game->state(PlayerState::NOTHING, secondPlayer);
	switch(game->tableCard().CT) {
		case CardType::NUMBER_0:
		case CardType::NUMBER_1:
		case CardType::NUMBER_2:
		case CardType::NUMBER_3:
		case CardType::NUMBER_4:
		case CardType::NUMBER_5:
		case CardType::NUMBER_6:
		case CardType::NUMBER_7:
		case CardType::NUMBER_8:
		case CardType::NUMBER_9:
			break;
		case CardType::REVERSE:
			if (maxPlayer > 2) {
				if (game->direction() == DIRECTION::CLOCKWISE) {
					game->direction(DIRECTION::COUNTERCLOCKWISE);
				} else {
					game->direction(DIRECTION::CLOCKWISE);
				}
			} else {
				game->state(PlayerState::CONTINUE, firstPlayer);
			}
			break;
		case CardType::SKIP:
			if (maxPlayer > 2) {
				game->state(PlayerState::BREAK, secondPlayer);
			} else {
				game->state(PlayerState::CONTINUE, firstPlayer);
			}
			break;
		case CardType::DRAW2:
			game->state(PlayerState::DRAWING, secondPlayer);
			break;
		case CardType::WILD:
			game->state(PlayerState::WISH, firstPlayer);
			break;
		case CardType::DRAW4:
			game->state(PlayerState::WISH, firstPlayer);
			game->state(PlayerState::DRAWING, secondPlayer);
			break;
		#ifdef _USE_SPECIAL_CARD
		case CardType::SPECIAL:
			_3DEins_SpecialHandle(Table, playerNow, playerNext, direction, maxPlayer); // Needs to include all params to make sure.
			break;
		#endif
	}
}

// Get the amount of points from the Card.
int GameHelper::getPoints(const CardType card) {
	switch(card) {
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

// Return the CardType Name. It should be better handled through a Language getter or so.
std::string GameHelper::getTypeName(const CardType Card) {
	switch(Card) {
		case CardType::NUMBER_0:
			return Lang::get("CARD_0");
		case CardType::NUMBER_1:
			return Lang::get("CARD_1");
		case CardType::NUMBER_2:
			return Lang::get("CARD_2");
		case CardType::NUMBER_3:
			return Lang::get("CARD_3");
		case CardType::NUMBER_4:
			return Lang::get("CARD_4");
		case CardType::NUMBER_5:
			return Lang::get("CARD_5");
		case CardType::NUMBER_6:
			return Lang::get("CARD_6");
		case CardType::NUMBER_7:
			return Lang::get("CARD_7");
		case CardType::NUMBER_8:
			return Lang::get("CARD_8");
		case CardType::NUMBER_9:
			return Lang::get("CARD_9");
		case CardType::REVERSE:
			return Lang::get("CARD_REVERSE");
		case CardType::SKIP:
			return Lang::get("CARD_SKIP");
		case CardType::DRAW2:
			return Lang::get("CARD_PLUS2");
		case CardType::WILD:
			return Lang::get("CARD_WILD");
		case CardType::DRAW4:
			return Lang::get("CARD_WILD4");
		#ifdef _USE_SPECIAL_CARD
		case CardType::SPECIAL:
			return Lang::get("CARD_SPECIAL");
		#endif
	}
	return "?"; // Should Never Happen.
}

// Return the CardColor Name. It should be better handled through a Language getter or so.
std::string GameHelper::getColorName(const CardColor Card) {
	switch(Card) {
		case CardColor::COLOR_GREEN:
			return Lang::get("COLOR_GREEN");
		case CardColor::COLOR_BLUE:
			return Lang::get("COLOR_BLUE");
		case CardColor::COLOR_RED:
			return Lang::get("COLOR_RED");
		case CardColor::COLOR_YELLOW:
			return Lang::get("COLOR_YELLOW");
		case CardColor::COLOR_BLACK:
			return Lang::get("COLOR_BLACK");
	}
	return "?"; // Should Never Happen.
}

// Return the amount of points for a CardType for the AI. TODO: Change some points or so?
int GameHelper::AIPointTable(const CardType card) {
	switch(card) {
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
			return 50;
		case CardType::WILD:
			return 40;
		case CardType::DRAW4:
			return 50;
		#ifdef _USE_SPECIAL_CARD
		case CardType::SPECIAL:
			return SPECIAL_CARD_AI_POINTS;
		#endif
	}

	return -1; // Should not happen.
}

// Return the highest card index. Is that even properly made?
int GameHelper::getHighestCard(std::unique_ptr<Game> &currentGame, const int player) {
	std::vector<int> index;
	std::vector<int>::iterator result;

	// Check, if we can play a card and set index.
	for (int i = 0; i < currentGame->getSize(player); i++) {
		if (currentGame->Playable(i, player)) {
			index.push_back({GameHelper::AIPointTable(currentGame->getType(i, player))});
		} else {
			index.push_back({-1});
		}
	}

	for (int i = 0; i < (int)index.size(); i++) {
		if (index[i] != -1) {
			result = std::max_element(index.begin(), index.end());
			return std::distance(index.begin(), result);
		}
	}

	return -1;
}

// Generate a seed for the shuffle cards function.
void CoreHelper::generateSeed() {
	randomGen.seed(time(NULL));
}