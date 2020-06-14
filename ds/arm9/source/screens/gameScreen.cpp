/*
*   This file is part of DSEins
*   Copyright (C) 2019-2020 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, StackZ, TotallyNotGuy
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

#include "_DSEins_Helper.hpp"
#include "gameScreen.hpp"
#include "lang.hpp"
#include "msg.hpp"
#include "selector.hpp"

extern std::unique_ptr<Selector> selector;

GameScreen::GameScreen() {
	this->currentGame = std::make_unique<Game>(this->playerAmount);
}

bool GameScreen::isAI() const { 
	if (this->currentGame->currentPlayer() != 0) {
		return true;
	} else {
		return false;
	}
}

std::string GameScreen::returnPlayerName(int player) const {
	switch(player) {
		case 0:
			return "Player 1";
		case 1:
			return "Player 2";
		case 2:
			return "Player 3";
		case 3:
			return "Player 4";
	}
	return "?";
}

bool GameScreen::checkForPlayableCard(const int player) {
	for(int i = 0; i < (int)this->currentGame->getSize(player); i++) {
		if (this->currentGame->getType(i, player) == this->currentGame->tableCard().CT || this->currentGame->getColor(i, player) == this->currentGame->tableCard().CC || this->currentGame->getType(i, player) == CardType::DRAW4 || this->currentGame->getType(i, player) == CardType::WILD) {
			return true;
		}
	}
	return false;
}

bool GameScreen::CanPlayerPlay(const int player) { return this->checkForPlayableCard(player); }

void GameScreen::AILogic() {
	if (this->isAI()) {
		bool doInitial = true;
		int index = -1;
		bool needDraw = false;

		// Here we do the stuff to check for playable cards, draw and play.
		if (doInitial) {
			doInitial = false;

			// Check if player has break.
			if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::BREAK) {
				this->currentGame->state(PlayerState::NOTHING, this->currentGame->currentPlayer()); // Reset.
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), this->returnPlayerName(this->currentGame->currentPlayer()).c_str(), this->returnPlayerName(this->getNextPlayer()).c_str());
				Msg::DisplayPlayerSwitch(message);
				this->currentGame->currentPlayer(this->getNextPlayer());
				Gui::DrawScreen();
				return;
			}

			index = GameHelper::getHighestCard(this->currentGame, this->currentGame->currentPlayer());

			if (index == -1)	needDraw = true; // Cause not found -> We need to draw.

			// If our index is not -1, do play!
			if (index != -1) {
				this->currentGame->play(index, this->currentGame->currentPlayer());

				// Handle.
				GameHelper::checkAndSet(this->currentGame, this->currentGame->currentPlayer(), this->getNextPlayer(), playerAmount);

				// Set Draw Counter if needed.
				if (this->currentGame->tableCard().CT == CardType::DRAW2)	this->currentGame->drawingCounter(2);
				else if (this->currentGame->tableCard().CT == CardType::DRAW4)	this->currentGame->drawingCounter(4);

				// Special case handle for 2 Player.
				if (this->currentGame->maxPlayer() == 2) {
					if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::CONTINUE) {
						this->currentGame->canContinue(true);
					}
				}

				this->setState(this->currentGame->currentPlayer());
				this->setState(this->getNextPlayer());
				this->currentGame->drawn(false);

				// Check if player won.
				this->currentGame->checkCards(this->currentGame->currentPlayer());
				if (this->currentGame->winner() == this->currentGame->currentPlayer()) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str());
					Msg::DisplayPlayerSwitch(message);
					Gui::screenBack();
					Gui::DrawScreen();
					return;
				}

				// We are not able to continue. Go to the next player.
				if (!this->currentGame->canContinue()) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(this->getNextPlayer());
					Gui::DrawScreen();
					// We can continue!
				} else {
					this->currentGame->canContinue(false);
					index = -1;
					doInitial = true;
				}
			}

			// If need to draw, we draw here.
			if (needDraw) {
				if (!this->currentGame->drawn()) {
					this->currentGame->addCard(this->currentGame->currentPlayer());
					// Do not allow multiple draws.
					this->currentGame->drawn(true);
					needDraw = false;
					if (!CanPlayerPlay(this->currentGame->currentPlayer())) {
						// Reset hasDrawn.
						this->currentGame->drawn(false); // Reset.
						char message [100];
						snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
						Msg::DisplayPlayerSwitch(message);
						needDraw = false;
						doInitial = false;
						index = -1;
						this->currentGame->currentPlayer(this->getNextPlayer());
						Gui::DrawScreen();
					} else {
						index = -1;
						doInitial = true;
					}
				}
			}
		}
	}
}

// Return the next player.
int GameScreen::getNextPlayer() {
	if (this->currentGame->direction() == DIRECTION::CLOCKWISE) {
		if (this->currentGame->currentPlayer() < this->currentGame->maxPlayer() -1) {
			// If Player is smaller than the max Player, go to Player ++.
			return this->currentGame->currentPlayer() + 1;
		} else {
			// If Player is max Player, go to the first Player.
			return 0; // Player 0.
		}
		// Other Direction handle.
	} else {
		if (this->currentGame->currentPlayer() > 0) {
			// If Player is larger than 0, go to Player --.
			return this->currentGame->currentPlayer() - 1;
		} else {
			// If Player is 0, go to the max Player.
			return this->currentGame->maxPlayer() -1;
		}
	}
	return 0; // Should never happen.
}

// Set the specific Player-State.
void GameScreen::setState(int Player) {
	switch(this->currentGame->state(Player)) {
		case PlayerState::NOTHING:
			break;
		case PlayerState::WISH:
			if (this->isAI()) {
				for (int i = 0; i < this->currentGame->getSize(Player); i++) {
					if (this->currentGame->getColor(i, Player) != CardColor::COLOR_BLACK) {
						this->currentGame->tbCardColor(this->currentGame->getColor(i, Player));
						this->currentGame->state(PlayerState::NOTHING, Player); // Set state to Nothing after it.
						break;
					}

					this->currentGame->tbCardColor(CardColor::COLOR_BLUE);
					this->currentGame->state(PlayerState::NOTHING, Player); // Set state to Nothing after it.
				}
				break;
			} else {
				this->currentGame->tbCardColor(_DSEins_Helper::selectColor());
				this->currentGame->state(PlayerState::NOTHING, Player); // Set state to Nothing after it.
				break;
			}
		case PlayerState::DRAWING:
			if (this->currentGame->drawingCounter() > 0) {
				for (int i = 0; i < this->currentGame->drawingCounter(); i++) {
					this->currentGame->addCard(Player);
				}

				this->currentGame->resetCounter(); // Reset.
				this->currentGame->state(PlayerState::NOTHING, Player); // Set state to Nothing after it.
			}
			break;
		case PlayerState::BREAK:
			break;
		case PlayerState::CONTINUE:
			break;
		#ifdef _USE_SPECIAL_CARD
		case PlayerState::SPECIAL:
			break;
		#endif
	}
}

void GameScreen::displayPlayerCards(void) const {
	// P1.
	printText(this->returnPlayerName(0) + " " + Lang::get("CARDS_LEFT") + std::to_string(this->currentGame->getSize(0)), 10, 5, true, true);
	// P2.
	printText(this->returnPlayerName(1) + " " + Lang::get("CARDS_LEFT") + std::to_string(this->currentGame->getSize(1)), 10, 25, true, true);
}


void GameScreen::Draw(void) const {
	Gui::DrawTop(false);
	this->displayPlayerCards();
	// Draw TableCard.
	Gui::DrawCard(this->currentGame->tableCard().CT, this->currentGame->tableCard().CC, 100, 45, 1, 1, true, true);
	printText(GameHelper::getTypeName(this->currentGame->tableCard().CT) + " | " + GameHelper::getColorName(this->currentGame->tableCard().CC), 100, 140, true, true);
	Gui::DrawBottom(true);
	// Display the hand.
	this->ShowCards();
}

// Display the Player's hand.
void GameScreen::ShowCards(void) const {
	if (!this->isAI()) {
		for (unsigned i = 0; i < std::min(7u, (unsigned)this->currentGame->getSize(this->currentGame->currentPlayer())-this->screenPos); i++) {
			printText(GameHelper::getTypeName(this->currentGame->getType(this->screenPos+i, this->currentGame->currentPlayer())) + " | " + GameHelper::getColorName(this->currentGame->getColor(this->screenPos+i, this->currentGame->currentPlayer())), 8, 20 + (i * 15), false, true);
		}

		// Draw Current Card.
		Gui::DrawPlayerCard(this->currentGame->getHand(this->currentGame->currentPlayer()), this->currentGame->cardIndex(this->currentGame->currentPlayer()), 140, 45, 1, 1, false, true);
	}

	char message [100];
	snprintf(message, sizeof(message), Lang::get("ITS_PLAYER_TURN").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str());
	printTextCentered(message, 0, 2, false, true);
}


void GameScreen::Logic(u16 hDown, touchPosition touch) {
	if (this->isAI()) {
		this->AILogic();
	} else {
		if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::BREAK) {
			this->currentGame->state(PlayerState::NOTHING, this->currentGame->currentPlayer()); // Reset.
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), this->returnPlayerName(this->currentGame->currentPlayer()).c_str(), this->returnPlayerName(this->getNextPlayer()).c_str());
			Msg::DisplayPlayerSwitch(message);
			this->currentGame->currentPlayer(this->getNextPlayer());
			Gui::DrawScreen();
		}

		if (hDown & KEY_A) {
			// Check if cardType or CardColor are identical and play.
			if (this->currentGame->Playable(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer())) {
				this->currentGame->play(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer());

				// Handle.
				GameHelper::checkAndSet(this->currentGame, this->currentGame->currentPlayer(), this->getNextPlayer(), playerAmount);

				// Set Draw Counter if needed.
				if (this->currentGame->tableCard().CT == CardType::DRAW2)	this->currentGame->drawingCounter(2);
				else if (this->currentGame->tableCard().CT == CardType::DRAW4)	this->currentGame->drawingCounter(4);
				
				// Special case handle for 2 Player.
				if (this->currentGame->maxPlayer() == 2) {
					if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::CONTINUE) {
						this->currentGame->canContinue(true);
					}
				}

				this->setState(this->currentGame->currentPlayer());
				this->setState(this->getNextPlayer());
				this->currentGame->drawn(false);

				// Check if player won.
				this->currentGame->checkCards(this->currentGame->currentPlayer());
				if (this->currentGame->winner() == this->currentGame->currentPlayer()) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str());
					Msg::DisplayPlayerSwitch(message);
					Gui::screenBack();
					Gui::DrawScreen();
					return;
				}

				// If CardIndex is higher than the amount of cards, go one card back.
				if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) > (int)this->currentGame->getSize(this->currentGame->currentPlayer()) -1) {
					this->currentGame->cardIndex(this->currentGame->getSize(this->currentGame->currentPlayer()) -1, this->currentGame->currentPlayer());
				}

				if (!this->currentGame->canContinue()) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(this->getNextPlayer());
					Gui::DrawScreen();
				}
				this->currentGame->canContinue(false);
				Gui::DrawScreen();
			}
		}

		// Should this be removed?
		if (hDown & KEY_B) {
			Gui::screenBack();
			Gui::DrawScreen();
			selector->show();
			selector->update();
			return;
		}

		if (hDown & KEY_DOWN) {
			if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) < this->currentGame->getSize(this->currentGame->currentPlayer()) -1) {
				this->currentGame->cardIndex(this->currentGame->cardIndex(this->currentGame->currentPlayer()) + 1, this->currentGame->currentPlayer());
				Gui::clearScreen(false, true);
				this->ShowCards();
			}
		}

		if (hDown & KEY_UP) {
			if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) > 0) {
				this->currentGame->cardIndex(this->currentGame->cardIndex(this->currentGame->currentPlayer()) - 1, this->currentGame->currentPlayer());
				Gui::clearScreen(false, true);
				this->ShowCards();
			}
		}

		// Player cannot set, so draw a card. If user cannot play after it, skip to next player.
		if (hDown & KEY_X) {
			if (!this->currentGame->drawn()) {
				this->currentGame->addCard(this->currentGame->currentPlayer());
				// Do not allow multiple draws.
				this->currentGame->drawn(true);
				if (!CanPlayerPlay(this->currentGame->currentPlayer())) {
					// Reset hasDrawn.
					this->currentGame->drawn(false); // Reset.
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(this->getNextPlayer());
					Gui::DrawScreen();
				} else {
					// Update card display.
					Gui::clearScreen(false, true);
					this->ShowCards();
				}
			} else {
				Msg::DisplayPlayerSwitch(Lang::get("DRAW_1_MSG"));
			}
		}

		// Scroll screen if needed.
		if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) < screenPos) {
			this->screenPos = this->currentGame->cardIndex(this->currentGame->currentPlayer());
			Gui::clearScreen(false, true);
			this->ShowCards();
		} else if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) > screenPos + 7 - 1) {
			this->screenPos = this->currentGame->cardIndex(this->currentGame->currentPlayer()) - 7 + 1;
			Gui::clearScreen(false, true);
			this->ShowCards();
		}
	}
}