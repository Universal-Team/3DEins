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

#include "_3DEins_Helper.hpp" // Used for the special actions.
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
	GFX::DrawPlayer(0, 130, 0.9, 0.9, savedata->playerAvatar());
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

int GameScreen::getAvatar(int player) const {
	switch(player) {
		case 0:
			return savedata->playerAvatar();
		case 1:
			return computers[0]->getAvatar();
		case 2:
			return computers[1]->getAvatar();
		case 3:
			return computers[2]->getAvatar();
	}
	return 0;
}

// Return the remaining cards.
int GameScreen::getPlayerCards(int player) const {
	return this->currentGame->getSize(player);
}

void GameScreen::Draw(void) const {
	if (this->isSubMenu) {
		if (this->subMode == 0) {
			this->DrawSubMenu();
		} else {
			this->DrawPlayerStats();
		}
	} else {
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
}

void GameScreen::DrawPlayerStats(void) const {
	Animation::DrawSubBG();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), "3DEins - Stats Screen", 400);
	GFX::DrawPlayer(30, 50, 1, 1, this->getAvatar(subMode - 1));
	Gui::DrawString(190, 55, 0.7f, config->textColor(), "Position: " + std::to_string(subMode) + " | " + std::to_string(this->currentGame->maxPlayer()), 200);
	Gui::DrawString(190, 85, 0.7f, config->textColor(), "Playername: " + returnPlayerName(subMode - 1), 200);
	Gui::DrawString(190, 115, 0.7f, config->textColor(), "Cards Left: " + std::to_string(getPlayerCards(subMode - 1)), 200);
	Gui::DrawString(190, 145, 0.7f, config->textColor(), "Points: " + std::to_string(this->currentGame->getPoints(subMode - 1)), 200);
	Gui::DrawStringCentered(0, 216, 0.75f, config->textColor(), "Press L / R to switch pages.", 400);
	Animation::DrawSubBG(false);
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
}

void GameScreen::DrawSubMenu(void) const {
	Animation::DrawSubBG();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), "3DEins - Game Paused.", 400);
	Gui::DrawStringCentered(0, 55, 0.7f, config->textColor(), "Players: " + std::to_string(this->currentGame->maxPlayer()), 400);
	Gui::DrawStringCentered(0, 216, 0.75f, config->textColor(), "Press R to switch to stats.", 400);
	
	Animation::DrawSubBG(false);
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	for (int i = 0; i < 3; i++) {
		Gui::Draw_Rect(this->breakBtn[i].x, this->breakBtn[i].y, this->breakBtn[i].w, this->breakBtn[i].h, config->buttonColor());
		if (this->selection == i) {
			GFX::DrawButtonSelector(this->breakBtn[i].x, this->breakBtn[i].y);
		}
	}
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, "Resume"))/2-80+17.5, 0.6, config->textColor(), "Resume", 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, "Restart"))/2-20+17.5, 0.6, config->textColor(), "Restart", 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, "Exit Game"))/2+75-17.5, 0.6, config->textColor(), "Exit Game", 130, 25);
}

void GameScreen::SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->subMode == 0) {
		if (hDown & KEY_A) {
			switch (this->selection) {
				case 0:
					this->isSubMenu = false;
					break;
				case 1:
					if (Msg::promptMsg("Do you like to restart the game?")) {
						this->InitializeNewGame();
						this->isSubMenu = false;
					}
					break;
				case 2:
					if (Msg::promptMsg("Do you like to quit the game?")) {
						Gui::screenBack();
						return;
					}
					break;
			}
		}

		if (hDown & KEY_DOWN) {
			if (this->selection < 2)	this->selection++;
		} else if (hDown & KEY_UP) {
			if (this->selection > 0)	this->selection--;
		}	

		if (hDown & KEY_TOUCH) {
			if (touching(touch, breakBtn[0])) {
				this->isSubMenu = false;
			} else if (touching(touch, breakBtn[1])) {
				if (Msg::promptMsg("Do you like to restart the game?")) {
					this->InitializeNewGame();
					this->isSubMenu = false;
				}
			} else if (touching(touch, breakBtn[2])) {
				if (Msg::promptMsg("Do you like to quit the game?")) {
					Gui::screenBack();
					return;
				}
			}
		}
	}
	if (hDown & KEY_L) {
		if (this->subMode > 0)	this->subMode--;
	}

	if (hDown & KEY_R) {
		if (this->subMode < this->currentGame->maxPlayer())	this->subMode++;
	}
}

void GameScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->isSubMenu) {
		this->SubMenuLogic(hDown, hHeld, touch);
	} else {
		this->PlayerLogic(hDown, hHeld, touch);
	}
}

void GameScreen::setState(int Player) {
	switch(this->currentGame->state(Player)) {
		case PlayerState::NOTHING:
			break;
		case PlayerState::WISH:
			this->currentGame->tbCardColor(_3DEins_Helper::selectColor());
			this->currentGame->state(PlayerState::NOTHING, Player); // Set state to Nothing after it.
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

bool GameScreen::checkForPlayableCard(const int player) {
	for (int i = 0; i < (int)this->currentGame->getSize(player); i++) {
		if (this->currentGame->getType(i, player) == this->currentGame->tableCard().CT || this->currentGame->getColor(i, player) == this->currentGame->tableCard().CC || this->currentGame->getType(i, player) == CardType::DRAW4 || this->currentGame->getType(i, player) == CardType::WILD) {
			return true;
		}
	}
	return false;
}

bool GameScreen::CanPlayerPlay(const int player) {
	return this->checkForPlayableCard(player);
}

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


void GameScreen::PlayerLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::BREAK) {
		this->currentGame->state(PlayerState::NOTHING, this->currentGame->currentPlayer()); // Reset.
		char message [100];
		snprintf(message, sizeof(message), "%s needs to take a break.\n%s Continue!", this->returnPlayerName(this->currentGame->currentPlayer()).c_str(), this->returnPlayerName(this->getNextPlayer()).c_str());
		Msg::DisplayPlayerSwitch(message);
		this->currentGame->currentPlayer(this->getNextPlayer());
	}

	// Pressing Start goes to the Sub Menu.
	if (hDown & KEY_START) {
		this->isSubMenu = true;
	}

	if (hDown & KEY_RIGHT) {
		if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) < this->currentGame->getSize(this->currentGame->currentPlayer()) -1)	this->currentGame->cardIndex(this->currentGame->cardIndex(this->currentGame->currentPlayer()) + 1, this->currentGame->currentPlayer());
	}

	if (hDown & KEY_R) {
		this->currentGame->cardIndex(this->currentGame->getSize(this->currentGame->currentPlayer()) -1, this->currentGame->currentPlayer());
	}

	if (hDown & KEY_LEFT) {
		if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) > 0)	this->currentGame->cardIndex(this->currentGame->cardIndex(this->currentGame->currentPlayer()) - 1, this->currentGame->currentPlayer());
	}

	if (hDown & KEY_L) {
		this->currentGame->cardIndex(0, this->currentGame->currentPlayer());
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical and play.
		if (this->currentGame->Playable(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer())) {
			this->currentGame->play(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer());

			// Handle.
			GameHelper::checkAndSet(this->currentGame, this->currentGame->currentPlayer(), this->getNextPlayer(), playerAmount);

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
				snprintf(message, sizeof(message), "%s won the game!", returnPlayerName(this->currentGame->currentPlayer()).c_str());
				Msg::DisplayPlayerSwitch(message);
				Gui::screenBack();
				return;
			}

			// If CardIndex is higher than the amount of cards, go one card back.
			if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) > (int)this->currentGame->getSize(this->currentGame->currentPlayer()) -1) {
				this->currentGame->cardIndex(this->currentGame->getSize(this->currentGame->currentPlayer()) -1, this->currentGame->currentPlayer());
			}

			if (!this->currentGame->canContinue()) {
				char message [100];
				snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
				Msg::DisplayPlayerSwitch(message);
				this->currentGame->currentPlayer(this->getNextPlayer());
			}
			this->currentGame->canContinue(false);
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
				snprintf(message, sizeof(message), "%s has ended their round.\n%s Continue!", returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
				Msg::DisplayPlayerSwitch(message);
				this->currentGame->currentPlayer(this->getNextPlayer());
			}
		} else {
			Msg::DisplayPlayerSwitch("You can only draw 1 card each round!");
		}
	}
}