/*
*   This file is part of 3DEins
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

#include "_3DEins_Helper.hpp"
#include "computer.hpp"
#include "config.hpp"
#include "gameScreen.hpp"
#include "msg.hpp"
#include "saveData.hpp"

#include <ctime>

std::unique_ptr<Computer> computers[3];
extern std::unique_ptr<SaveData> savedata;
extern std::unique_ptr<Config> config;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

// We will show 5 Cards.
#define MAXSHOWNCARDS 5

GameScreen::GameScreen() {
	// Init a new game.
	this->InitializeNewGame();
}

void GameScreen::InitializeNewGame() {
	// Set to nullptr, if not already.
	if (this->currentGame != nullptr)	this->currentGame = nullptr;

	this->currentGame = std::make_unique<Game>(this->playerAmount);

	int randomNum[3];
	srand(std::time(nullptr));
	randomNum[0] = {rand() % 3 + 0};
	randomNum[1] = {rand() % 3 + 0};
	randomNum[2] = {rand() % 3 + 0};

	computers[0] = std::make_unique<Computer>(randomNum[0]);
	computers[1] = std::make_unique<Computer>(randomNum[1]);
	computers[2] = std::make_unique<Computer>(randomNum[2]);
}


void GameScreen::DisplayPlayerHand() const {
	for (int i = 0; i < (int)this->currentGame->getSize(this->currentGame->currentPlayer()); i++) {
		if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) < MAXSHOWNCARDS) {
			GFX::DrawPlayerCard(this->currentGame->getHand(this->currentGame->currentPlayer()), i, 1 + (i * 65), 50);
		} else {
			GFX::DrawPlayerCard(this->currentGame->getHand(this->currentGame->currentPlayer()), i+this->currentGame->cardIndex(this->currentGame->currentPlayer())-4, 1 + (i * 65), 50);
		}
		if (i == this->currentGame->cardIndex(this->currentGame->currentPlayer())) {
			if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) < MAXSHOWNCARDS) {
				GFX::DrawCardSelector(1 + (i * 65), 50);
			} else {
				GFX::DrawCardSelector(1 + (4 * 65), 50);
			}
		}
	}
}

void GameScreen::DisplayPlayerHandSmall() const {
	for (int i = 0; i < (int)this->currentGame->getSize(this->currentGame->currentPlayer()); i++) {
		GFX::DrawPlayerCard(this->currentGame->getHand(this->currentGame->currentPlayer()), i, 2 + (i * 18), 150, 0.8, 0.8);
	}
}

void GameScreen::DrawPlayers() const {
	// Player 1.
	GFX::DrawPlayer(0, 130, 0.9, 0.9, 0);
	Gui::DrawString(90, 200, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(0)));
	// Player 2.
	GFX::DrawPlayer(0, 0, 0.9, 0.9, computers[0]->getAvatar());
	Gui::DrawString(90, 40, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(1)));
	if (this->currentGame->maxPlayer() == 3) {
		// Player 3.
		GFX::DrawPlayer(300, 0, 0.9, 0.9, computers[1]->getAvatar());
		Gui::DrawString(270, 40, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(2)));
	} else if (this->currentGame->maxPlayer() == 4) {
		// Player 3.
		GFX::DrawPlayer(300, 0, 0.9, 0.9, computers[1]->getAvatar());
		Gui::DrawString(270, 40, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(2)));
		// Player 4.
		GFX::DrawPlayer(300, 130, 0.9, 0.9, computers[2]->getAvatar());
		Gui::DrawString(270, 200, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(3)));
	}
}

std::string GameScreen::returnPlayerName(int player) const {
	switch(player) {
		case 0:
			return savedata->playerName();
		case 1:
			return computers[0]->getName();
		case 2:
			return computers[1]->getName();
		case 3:
			return computers[2]->getName();
	}
	return "?";
}

// Return the remaining cards.
int GameScreen::getPlayerCards(int player) const {
	return this->currentGame->getSize(player);
}

void GameScreen::Draw(void) const {
	GFX::DrawTop(false);
	// Draw Players & amount of cards.
	this->DrawPlayers();
	if (this->currentGame->currentPlayer() == 0) {
		GFX::DrawSelectedPlayer(130, 200);
	} else if (this->currentGame->currentPlayer() == 1) {
		GFX::DrawSelectedPlayer(130, 70);
	} else if (this->currentGame->currentPlayer() == 2) {
		GFX::DrawSelectedPlayer(250, 70);
	} else if (this->currentGame->currentPlayer() == 3) {
		GFX::DrawSelectedPlayer(250, 200);
	}
	// Draw Table Card.
	GFX::DrawCard(this->currentGame->tableCard().CT, 170, 80, this->currentGame->tableCard().CC);
	// Bottom Screen.
	GFX::DrawBottom(false);
	Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), "It's " + this->returnPlayerName(this->currentGame->currentPlayer()) + "'s turn!");
	DisplayPlayerHand();
	DisplayPlayerHandSmall();
}


void GameScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (this->currentGame->currentPlayer() == 0) {
		this->Player1Logic(hDown, hHeld, touch);
	} else if (this->currentGame->currentPlayer() == 1) {
		this->Player2Logic(hDown, hHeld, touch);
	}
}

void GameScreen::setState(int Player) {
	switch(this->currentGame->state(Player)) {
		case PlayerState::NOTHING:
			break;
		case PlayerState::WISH:
			this->currentGame->tbCardColor(_3DEins_Helper::selectColor(this->currentGame, Player));
			break;
		case PlayerState::DRAWING2:
			this->currentGame->addCard(Player);
			this->currentGame->addCard(Player);
			break;
		case PlayerState::DRAWING4:
			this->currentGame->addCard(Player);
			this->currentGame->addCard(Player);
			this->currentGame->addCard(Player);
			this->currentGame->addCard(Player);
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

bool GameScreen::checkForPlayableCard(const std::shared_ptr<Player> &player) {
	for (int i = 0; i < (int)player->getSize(); i++) {
		if (player->CT(i) == this->currentGame->tableCard().CT || player->CC(i) == this->currentGame->tableCard().CC || player->CT(i) == CardType::DRAW4 || player->CT(i) == CardType::WILD) {
			return true;
		}
	}
	return false;
}

bool GameScreen::CanPlayerPlay(const std::shared_ptr<Player> &player) {
	return this->checkForPlayableCard(player);
}

// For the Player hand.
void GameScreen::Player1Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->currentGame->state(0) == PlayerState::BREAK) {
		this->currentGame->state(PlayerState::NOTHING, 0); // Reset.
		if (this->currentGame->direction() == DIRECTION::COUNTERCLOCKWISE) {
			char message [100];
			snprintf(message, sizeof(message), "%s needs to take a break.\n%s Continue!", this->returnPlayerName(0).c_str(), this->returnPlayerName(1).c_str());
			Msg::DisplayPlayerSwitch(message);
			this->currentGame->currentPlayer(1);
		} else if (this->currentGame->direction() == DIRECTION::CLOCKWISE) {
			char message [100];
			snprintf(message, sizeof(message), "%s needs to take a break.\n%s Continue!", this->returnPlayerName(0).c_str(), this->returnPlayerName(1).c_str());
			Msg::DisplayPlayerSwitch(message);
			this->currentGame->currentPlayer(1);
		}
	}

	if (hDown & KEY_RIGHT) {
		if (this->currentGame->cardIndex(0) < this->currentGame->getSize(0) -1)	this->currentGame->cardIndex(this->currentGame->cardIndex(0) + 1, 0);
	}

	if (hDown & KEY_R) {
		this->currentGame->cardIndex(this->currentGame->getSize(0) -1, 0);
	}

	if (hDown & KEY_LEFT ) {
		if (this->currentGame->cardIndex(0) > 0)	this->currentGame->cardIndex(this->currentGame->cardIndex(0) - 1, 0);
	}

	if (hDown & KEY_L) {
		this->currentGame->cardIndex(0, 0);
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical and play.
		if (this->currentGame->Playable(this->currentGame->cardIndex(0), 0)) {
			this->currentGame->play(this->currentGame->cardIndex(0), 0);

			// Handle.
			if (this->currentGame->direction() == DIRECTION::COUNTERCLOCKWISE) {
				GameHelper::checkAndSet(this->currentGame, 0, 1, playerAmount);
			} else {
				GameHelper::checkAndSet(this->currentGame, 0, 1, playerAmount);
			}

			// Special case handle for 2 Player.
			if (this->playerAmount == 2) {
				if (this->currentGame->state(0) == PlayerState::CONTINUE) {
					this->currentGame->canContinue(true);
				}
			}

			this->setState(0);
			this->setState(1);

			this->currentGame->drawn(false);

			// Check if player won.
			this->currentGame->checkCards(0);
			if (this->currentGame->winner() == 0) {
				char message [100];
				snprintf(message, sizeof(message), "%s won the game!", returnPlayerName(0).c_str());
				Msg::DisplayPlayerSwitch(message);
				Gui::screenBack();
				return;
			}

			// If CardIndex is higher than the amount of cards, go one card back.
			if (this->currentGame->cardIndex(0) > (int)this->currentGame->getSize(0) -1) {
				this->currentGame->cardIndex(this->currentGame->getSize(0) -1, 0);
			}


			if (!this->currentGame->canContinue()) {
				if (this->currentGame->direction() == DIRECTION::COUNTERCLOCKWISE) {
					char message [100];
					snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(0).c_str(), returnPlayerName(1).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(1);
				} else if (this->currentGame->direction() == DIRECTION::CLOCKWISE) {
					char message [100];
					snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(0).c_str(), returnPlayerName(1).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(1);
				}
			}
			this->currentGame->canContinue(false);
		}
	}

	// Player cannot set, so draw a card. If user cannot play after it, skip to next player.
	if (hDown & KEY_X) {
		if (!this->currentGame->drawn()) {
			this->currentGame->addCard(0);
			// Do not allow multiple draws.
			this->currentGame->drawn(true);
			if (!CanPlayerPlay(this->currentGame->getPlayer(0))) {
				// Reset hasDrawn.
				this->currentGame->drawn(false); // Reset.
				if (this->currentGame->direction() == DIRECTION::COUNTERCLOCKWISE) {
					char message [100];
					snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(0).c_str(), returnPlayerName(1).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(1);
				} else if (this->currentGame->direction() == DIRECTION::CLOCKWISE) {
					char message [100];
					snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(0).c_str(), returnPlayerName(1).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(1);
				}
			}
		} else {
			Msg::DisplayPlayerSwitch("You can only draw 1 card each round!");
		}
	}
}

// For the Player hand.
void GameScreen::Player2Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->currentGame->state(1) == PlayerState::BREAK) {
		this->currentGame->state(PlayerState::NOTHING, 1); // Reset.
		if (this->currentGame->direction() == DIRECTION::COUNTERCLOCKWISE) {
			char message [100];
			snprintf(message, sizeof(message), "%s needs to take a break.\n%s Continue!", this->returnPlayerName(1).c_str(), this->returnPlayerName(0).c_str());
			Msg::DisplayPlayerSwitch(message);
			this->currentGame->currentPlayer(0);
		} else if (this->currentGame->direction() == DIRECTION::CLOCKWISE) {
			char message [100];
			snprintf(message, sizeof(message), "%s needs to take a break.\n%s Continue!", this->returnPlayerName(1).c_str(), this->returnPlayerName(0).c_str());
			Msg::DisplayPlayerSwitch(message);
			this->currentGame->currentPlayer(0);
		}
	}

	if (hDown & KEY_RIGHT) {
		if (this->currentGame->cardIndex(1) < this->currentGame->getSize(1) -1)	this->currentGame->cardIndex(this->currentGame->cardIndex(1) + 1, 1);
	}

	if (hDown & KEY_R) {
		this->currentGame->cardIndex(this->currentGame->getSize(1) -1, 1);
	}

	if (hDown & KEY_LEFT ) {
		if (this->currentGame->cardIndex(1) > 0)	this->currentGame->cardIndex(this->currentGame->cardIndex(1) - 1, 1);
	}

	if (hDown & KEY_L) {
		this->currentGame->cardIndex(0, 1);
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical and play.
		if (this->currentGame->Playable(this->currentGame->cardIndex(1), 1)) {
			this->currentGame->play(this->currentGame->cardIndex(1), 1);

			// Handle.
			if (this->currentGame->direction() == DIRECTION::COUNTERCLOCKWISE) {
				GameHelper::checkAndSet(this->currentGame, 1, 0, playerAmount);
			} else {
				GameHelper::checkAndSet(this->currentGame, 1, 0, playerAmount);
			}

			// Special case handle for 2 Player.
			if (this->playerAmount == 2) {
				if (this->currentGame->state(1) == PlayerState::CONTINUE) {
					this->currentGame->canContinue(true);
				}
			}

			this->setState(1);
			this->setState(0);

			this->currentGame->drawn(false);

			// Check if player won.
			this->currentGame->checkCards(1);
			if (this->currentGame->winner() == 1) {
				char message [100];
				snprintf(message, sizeof(message), "%s won the game!", returnPlayerName(1).c_str());
				Msg::DisplayPlayerSwitch(message);
				Gui::screenBack();
				return;
			}

			// If CardIndex is higher than the amount of cards, go one card back.
			if (this->currentGame->cardIndex(1) > (int)this->currentGame->getSize(1) -1) {
				this->currentGame->cardIndex(this->currentGame->getSize(1) -1, 1);
			}


			if (!this->currentGame->canContinue()) {
				if (this->currentGame->direction() == DIRECTION::COUNTERCLOCKWISE) {
					char message [100];
					snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(1).c_str(), returnPlayerName(0).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(0);
				} else if (this->currentGame->direction() == DIRECTION::CLOCKWISE) {
					char message [100];
					snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(1).c_str(), returnPlayerName(0).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(0);
				}
			}
			this->currentGame->canContinue(false);
		}
	}

	// Player cannot set, so draw a card. If user cannot play after it, skip to next player.
	if (hDown & KEY_X) {
		if (!this->currentGame->drawn()) {
			this->currentGame->addCard(1);
			// Do not allow multiple draws.
			this->currentGame->drawn(true);
			if (!CanPlayerPlay(this->currentGame->getPlayer(1))) {
				// Reset hasDrawn.
				this->currentGame->drawn(false);
				if (this->currentGame->direction() == DIRECTION::COUNTERCLOCKWISE) {
					char message [100];
					snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(1).c_str(), returnPlayerName(0).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(0);
				} else if (this->currentGame->direction() == DIRECTION::CLOCKWISE) {
					char message [100];
					snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(1).c_str(), returnPlayerName(0).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(0);
				}
			}
		} else {
			Msg::DisplayPlayerSwitch("You can only draw 1 card each round!");
		}
	}
}