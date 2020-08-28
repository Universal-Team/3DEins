/*
*   This file is part of 3DEins
*   Copyright (C) 2019-2020 Universal-Team
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

#include "config.hpp"
#include "gameScreen.hpp"
#include "msg.hpp"
#include "overlay.hpp"
#include "saveData.hpp"

#include <ctime>

extern std::unique_ptr<SaveData> savedata;
extern std::unique_ptr<Config> config;
extern bool touching(Structs::ButtonPos button);

/* We will show 5 Cards. */
#define MAXSHOWNCARDS 5

GameScreen::GameScreen(bool useAI, int playerAmount) {
	this->playerAmount = playerAmount;
	this->useAI = useAI;
	this->InitializeNewGame();
}

bool GameScreen::isAI() const { 
	if (!this->useAI) return false;
	
	if (this->currentGame->currentPlayer() != 0) {
		return true;
	} else {
		return false;
	}
}

void GameScreen::InitializeNewGame() {
	// Set to nullptr, if not already. */
	if (this->currentGame != nullptr)	this->currentGame = nullptr;

	this->currentGame = std::make_unique<Game>(this->playerAmount);

	int randomNum[3];
	randomNum[0] = ((randomGen()) % 4) + 1;
	randomNum[1] = ((randomGen()) % 4) + 1;
	randomNum[2] = ((randomGen()) % 4) + 1;

	this->computers[0] = std::make_unique<Computer>(randomNum[0]);
	this->computers[1] = std::make_unique<Computer>(randomNum[1]);
	this->computers[2] = std::make_unique<Computer>(randomNum[2]);
}

void GameScreen::DisplayPlayerHand() const {
	if (!this->isAI()) {
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
}

void GameScreen::DisplayPlayerHandSmall() const {
	if (!this->isAI()) {
		for (int i = 0; i < (int)this->currentGame->getSize(this->currentGame->currentPlayer()); i++) {
			GFX::DrawPlayerCard(this->currentGame->getHand(this->currentGame->currentPlayer()), i, 2 + (i * 18), 150, 0.8, 0.8);
		}
	}
}	

void GameScreen::DrawPlayers() const {
	/* Player 1. */
	GFX::DrawPlayer(0, 130, 0.9, 0.9, savedata->playerAvatar());
	Gui::DrawString(90, 200, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(0)));
	/* Player 2. */
	GFX::DrawPlayer(0, 0, 0.9, 0.9, this->computers[0]->getAvatar());
	Gui::DrawString(90, 40, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(1)));

	if (this->currentGame->maxPlayer() == 3) {
		/* Player 3. */
		GFX::DrawPlayer(300, 0, 0.9, 0.9, this->computers[1]->getAvatar());
		Gui::DrawString(270, 40, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(2)));
	} else if (this->currentGame->maxPlayer() == 4) {
		/* Player 3. */
		GFX::DrawPlayer(300, 0, 0.9, 0.9, this->computers[1]->getAvatar());
		Gui::DrawString(270, 40, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(2)));
		/* Player 4. */
		GFX::DrawPlayer(300, 130, 0.9, 0.9, this->computers[2]->getAvatar());
		Gui::DrawString(270, 200, 0.6f, config->textColor(), std::to_string(this->currentGame->getSize(3)));
	}
}

std::string GameScreen::returnPlayerName(int player) const {
	switch(player) {
		case 0:
			return savedata->playerName();
		case 1:
			return this->computers[0]->getName();
		case 2:
			return this->computers[1]->getName();
		case 3:
			return this->computers[2]->getName();
	}

	return "?";
}

int GameScreen::getAvatar(int player) const {
	switch(player) {
		case 0:
			return savedata->playerAvatar();
		case 1:
			return this->computers[0]->getAvatar();
		case 2:
			return this->computers[1]->getAvatar();
		case 3:
			return this->computers[2]->getAvatar();
	}

	return 0;
}

/* Return the remaining cards. */
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
		/* Draw Players & amount of cards. */
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

		/* Draw Table Card. */
		GFX::DrawCard(this->currentGame->tableCard().CT, 170, 75, this->currentGame->tableCard().CC);
		if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));

		/* Bottom Screen. */
		GFX::DrawBottom(false);
		char message [100];
		snprintf(message, sizeof(message), Lang::get("ITS_PLAYER_TURN").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str());
		Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), message);
		DisplayPlayerHand();
		DisplayPlayerHandSmall();
		if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	}
}

/* Animation! Draw a card! TODO: Show blank card for other players. */
void GameScreen::drawAnim(const int player, const CardStruct &card) {
	int wantedXPos = 0;
	int wantedYPos = 0;
	int curPosX = 170;
	int curPosY = 75;
	int speed = 4;
	bool swap = true;

	/* Set curPosX & Y. */
	switch(player) {
		case 0:
			wantedXPos = 0;
			wantedYPos = 150;
			break;
		case 1:
			wantedXPos = 0;
			wantedYPos = 0;
			break;
		case 2:
			wantedXPos = 340;
			wantedYPos = 0;
			break;
		case 3:
			wantedXPos = 340;
			wantedYPos = 150;
			break;
	}

	while(swap) {
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		GFX::DrawTop(false);
		
		if (curPosX != wantedXPos) {
			GFX::DrawCard(card.CT, curPosX, curPosY, card.CC);
		}

		/* Draw Players & amount of cards. */
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

		/* Draw Table Card. */
		GFX::DrawCard(this->currentGame->tableCard().CT, 170, 75, this->currentGame->tableCard().CC);

		/* Bottom Screen. */
		GFX::DrawBottom(false);
		char message [100];
		snprintf(message, sizeof(message), Lang::get("ITS_PLAYER_TURN").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str());
		DisplayPlayerHand();
		DisplayPlayerHandSmall();
		C3D_FrameEnd(0);

		if (player == 0 || player == 1) {
			if (curPosX > wantedXPos) {
				curPosX = curPosX - speed;
			} else if (curPosX < wantedXPos) {
				curPosX = wantedXPos;
			}

		} else if (player == 2 || player == 3) {
			if (curPosX < wantedXPos) {
				curPosX = curPosX + speed;
			} else if (curPosX > wantedXPos) {
				curPosX = wantedXPos;
			}
		}

		if (player == 0 || player == 3) {
			if (curPosY < wantedYPos) {
				curPosY = curPosY + 2.3;
			} else if (curPosY > wantedYPos) {
				curPosY = wantedYPos;
			}

		} else if (player == 1 || player == 2) {
			if (curPosY > wantedYPos) {
				curPosY = curPosY - 2.3;
			} else if (curPosY < wantedYPos) {
				curPosY = wantedYPos;
			}
		}

		if (curPosY == wantedYPos && curPosX == wantedXPos) {
			swap = false;
		}
	}
}

/* Animation! swap's the card from the player. */
void GameScreen::animationCard(const int player, const CardStruct &card) {
	int wantedXPos = 170;
	int wantedYPos = 75;
	int curPosX = 0;
	int curPosY = 0;
	int speed = 4;
	bool swap = true;

	/* Set curPosX & Y. */
	switch(player) {
		case 0:
			curPosX = 0;
			curPosY = 150;
			break;
		case 1:
			curPosX = 0;
			curPosY = 0;
			break;
		case 2:
			curPosX = 340;
			curPosY = 0;
			break;
		case 3:
			curPosX = 340;
			curPosY = 150;
			break;
	}

	while(swap) {
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		GFX::DrawTop(false);
		
		/* If X-Pos isn't the wanted one, draw it before the Players. */
		if (curPosX != wantedXPos) {
			GFX::DrawCard(card.CT, curPosX, curPosY, card.CC);
		}

		/* Draw Players & amount of cards. */
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

		/* Draw Table Card. */
		GFX::DrawCard(this->currentGame->tableCard().CT, 170, 75, this->currentGame->tableCard().CC);

		if (curPosX == wantedXPos) {
			GFX::DrawCard(card.CT, curPosX, curPosY, card.CC);
		}

		/* Bottom Screen. */
		GFX::DrawBottom(false);
		char message [100];
		snprintf(message, sizeof(message), Lang::get("ITS_PLAYER_TURN").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str());
		DisplayPlayerHand();
		DisplayPlayerHandSmall();
		C3D_FrameEnd(0);

		if (player == 0 || player == 1) {
			if (curPosX < wantedXPos) {
				curPosX = curPosX + speed;
			} else if (curPosX > wantedXPos) {
				curPosX = wantedXPos;
			}

		} else if (player == 2 || player == 3) {
			if (curPosX > wantedXPos) {
				curPosX = curPosX - speed;
			} else if (curPosX < wantedXPos) {
				curPosX = wantedXPos;
			}
		}

		if (player == 0 || player == 3) {
			if (curPosY > wantedYPos) {
				curPosY = curPosY - 2.3;
			} else if (curPosY < wantedYPos) {
				curPosY = wantedYPos;
			}

		} else if (player == 1 || player == 2) {
			if (curPosY < wantedYPos) {
				curPosY = curPosY + 2.3;
			} else if (curPosY > wantedYPos) {
				curPosY = wantedYPos;
			}
		}

		if (curPosY == wantedYPos && curPosX == wantedXPos) {
			swap = false;
		}
	}
}

void GameScreen::DrawPlayerStats(void) const {
	Animation::DrawSubBG();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), "3DEins - " + Lang::get("STATS"), 390);
	GFX::DrawPlayer(30, 50, 1, 1, this->getAvatar(subMode - 1));
	Gui::DrawString(190, 55, 0.7f, config->textColor(), Lang::get("POSITION") + std::to_string(subMode) + " | " + std::to_string(this->currentGame->maxPlayer()), 200);
	Gui::DrawString(190, 85, 0.7f, config->textColor(), Lang::get("PLAYER_NAME") + returnPlayerName(subMode - 1), 200);
	Gui::DrawString(190, 115, 0.7f, config->textColor(), Lang::get("CARDS_LEFT") + std::to_string(getPlayerCards(subMode - 1)), 200);
	Gui::DrawString(190, 145, 0.7f, config->textColor(), Lang::get("POINTS") + std::to_string(this->currentGame->getPoints(subMode - 1)), 200);
	Gui::DrawStringCentered(0, 216, 0.75f, config->textColor(), Lang::get("STATS_INFO"), 400);
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));

	Animation::DrawSubBG(false);
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}

void GameScreen::DrawSubMenu(void) const {
	Animation::DrawSubBG();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	Gui::DrawStringCentered(0, 0, 0.8f, config->textColor(), "3DEins - " + Lang::get("GAME_PAUSED"), 390);
	Gui::DrawStringCentered(0, 55, 0.7f, config->textColor(), Lang::get("PLAYERS") + std::to_string(this->currentGame->maxPlayer()), 390);
	Gui::DrawStringCentered(0, 216, 0.75f, config->textColor(), Lang::get("STATS_INFO"), 390);
	
	Animation::DrawSubBG(false);
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	for(int i = 0; i < 3; i++) {
		Gui::Draw_Rect(this->breakBtn[i].x, this->breakBtn[i].y, this->breakBtn[i].w, this->breakBtn[i].h, config->buttonColor());
	}

	GFX::DrawButtonSelector(this->breakBtn[this->selection].x, this->breakBtn[this->selection].y);

	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("RESUME")))/2-80+17.5, 0.6, config->textColor(), Lang::get("RESUME"), 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("RESTART")))/2-20+17.5, 0.6, config->textColor(), Lang::get("RESTART"), 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("EXIT_GAME")))/2+75-17.5, 0.6, config->textColor(), Lang::get("EXIT_GAME"), 130, 25);
}


void GameScreen::AILogic() {
	if (this->isAI()) {
		bool doInitial = true;
		int index = -1;
		bool needDraw = false;

		/* Here we do the stuff to check for playable cards, draw and play. */
		if (doInitial) {
			doInitial = false;

			/* Check if player has break. */
			if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::BREAK) {
				this->currentGame->state(PlayerState::NOTHING, this->currentGame->currentPlayer()); // Reset.
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), this->returnPlayerName(this->currentGame->currentPlayer()).c_str(), this->returnPlayerName(this->getNextPlayer()).c_str());
				Msg::DisplayPlayerSwitch(message);
				this->currentGame->currentPlayer(this->getNextPlayer());
				return;
			}

			index = GameHelper::getHighestCard(this->currentGame, this->currentGame->currentPlayer());

			if (index == -1) needDraw = true; // Cause not found -> We need to draw.

			/* If our index is not -1, do play! */
			if (index != -1) {
				if (config->allowAnimation()) this->animationCard(this->currentGame->currentPlayer(), this->currentGame->getPlayerCard(index, this->currentGame->currentPlayer()));
				this->currentGame->play(index, this->currentGame->currentPlayer());

				/* Handle. */
				GameHelper::checkAndSet(this->currentGame, this->currentGame->currentPlayer(), this->getNextPlayer(), playerAmount);

				/* Set Draw Counter if needed. */
				if (this->currentGame->tableCard().CT == CardType::DRAW2)	this->currentGame->drawingCounter(2);
				else if (this->currentGame->tableCard().CT == CardType::DRAW4)	this->currentGame->drawingCounter(4);

				/* Special case handle for 2 Player. */
				if (this->currentGame->maxPlayer() == 2) {
					if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::CONTINUE) {
						this->currentGame->canContinue(true);
					}
				}

				this->setState(this->currentGame->currentPlayer());
				this->setState(this->getNextPlayer());
				this->currentGame->drawn(false);

				/* Check if player won. */
				this->currentGame->checkCards(this->currentGame->currentPlayer());
				if (this->currentGame->winner() == this->currentGame->currentPlayer()) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str());
					Msg::DisplayPlayerSwitch(message);
					if (savedata->playerLose() < 255)	savedata->playerLose(savedata->playerLose() + 1);
					Gui::screenBack(true);
					return;
				}

				/* We are not able to continue. Go to the next player. */
				if (!this->currentGame->canContinue()) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
					Msg::DisplayPlayerSwitch(message);
					this->currentGame->currentPlayer(this->getNextPlayer());
					/* We can continue! */
				} else {
					this->currentGame->canContinue(false);
					index = -1;
					doInitial = true;
				}
			}

			/* If need to draw, we draw here. */
			if (needDraw) {
				if (!this->currentGame->drawn()) {
					if (config->allowAnimation())	this->drawAnim(this->currentGame->currentPlayer(), this->currentGame->getTableTop());
					this->currentGame->addCard(this->currentGame->currentPlayer());
					/* Do not allow multiple draws. */
					this->currentGame->drawn(true);
					needDraw = false;
					if (!CanPlayerPlay(this->currentGame->currentPlayer())) {
						/* Reset hasDrawn. */
						this->currentGame->drawn(false); // Reset.
						char message [100];
						snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
						Msg::DisplayPlayerSwitch(message);
						needDraw = false;
						doInitial = false;
						index = -1;
						this->currentGame->currentPlayer(this->getNextPlayer());
					} else {
						index = -1;
						doInitial = true;
					}
				}
			}
		}
	}
}


void GameScreen::SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->subMode == 0) {
		if (hDown & KEY_A) {
			switch (this->selection) {
				case 0:
					this->isSubMenu = false;
					break;
				case 1:
					if (Msg::promptMsg(Lang::get("RESTART_GAME"))) {
						this->InitializeNewGame();
						this->isSubMenu = false;
					}
					break;
				case 2:
					if (Msg::promptMsg(Lang::get("QUIT_GAME"))) {
						Gui::screenBack(true);
						return;
					}
					break;
			}
		}

		if (hDown & KEY_DOWN) {
			if (this->selection < 2) this->selection++;
		} else if (hDown & KEY_UP) {
			if (this->selection > 0) this->selection--;
		}	

		if (hDown & KEY_TOUCH) {
			if (touching(breakBtn[0])) {
				this->isSubMenu = false;
			} else if (touching(breakBtn[1])) {
				if (Msg::promptMsg(Lang::get("RESTART_GAME"))) {
					this->InitializeNewGame();
					this->isSubMenu = false;
				}

			} else if (touching(breakBtn[2])) {
				if (Msg::promptMsg(Lang::get("QUIT_GAME"))) {
					Gui::screenBack(true);
					return;
				}
			}
		}
	}

	if (hDown & KEY_L) {
		if (this->subMode > 0) this->subMode--;
	}

	if (hDown & KEY_R) {
		if (this->subMode < this->currentGame->maxPlayer()) this->subMode++;
	}
}

void GameScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->isSubMenu) {
		this->SubMenuLogic(hDown, hHeld, touch);
	} else {
		if (this->isAI()) {
			this->AILogic();
		} else {
			this->PlayerLogic(hDown, hHeld, touch);
		}
	}
}

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
				this->currentGame->tbCardColor(Overlays::SelectCardColor());
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

bool GameScreen::checkForPlayableCard(const int player) {
	for(int i = 0; i < (int)this->currentGame->getSize(player); i++) {
		if (this->currentGame->getType(i, player) == this->currentGame->tableCard().CT || this->currentGame->getColor(i, player) == this->currentGame->tableCard().CC || this->currentGame->getType(i, player) == CardType::DRAW4 || this->currentGame->getType(i, player) == CardType::WILD) {
			return true;
		}
	}

	return false;
}

bool GameScreen::CanPlayerPlay(const int player) { return this->checkForPlayableCard(player); }

int GameScreen::getNextPlayer() {
	if (this->currentGame->direction() == DIRECTION::CLOCKWISE) {
		if (this->currentGame->currentPlayer() < this->currentGame->maxPlayer() -1) {
			/* If Player is smaller than the max Player, go to Player++. */
			return this->currentGame->currentPlayer() + 1;
		} else {
			/* If Player is max Player, go to the first Player. */
			return 0; // Player 0.
		}

		// Other Direction handle.
	} else {
		if (this->currentGame->currentPlayer() > 0) {
			/* If Player is larger than 0, go to Player--. */
			return this->currentGame->currentPlayer() - 1;
		} else {
			/* If Player is 0, go to the max Player. */
			return this->currentGame->maxPlayer() -1;
		}
	}

	return 0; // Should never happen.
}

void GameScreen::PlayLogic(int cardPos) {
	if (cardPos > this->currentGame->getSize(this->currentGame->currentPlayer())) return;
	this->currentGame->cardIndex(cardPos, this->currentGame->currentPlayer());

	/* Check if cardType or CardColor are identical and play. */
	if (this->currentGame->Playable(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer())) {
		if (config->allowAnimation())	this->animationCard(this->currentGame->currentPlayer(), this->currentGame->getPlayerCard(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer()));
		this->currentGame->play(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer());

		/* Handle. */
		GameHelper::checkAndSet(this->currentGame, this->currentGame->currentPlayer(), this->getNextPlayer(), playerAmount);

		/* Set Draw Counter if needed. */
		if (this->currentGame->tableCard().CT == CardType::DRAW2)	this->currentGame->drawingCounter(2);
		else if (this->currentGame->tableCard().CT == CardType::DRAW4)	this->currentGame->drawingCounter(4);

		/* Special case handle for 2 Player. */
		if (this->currentGame->maxPlayer() == 2) {
			if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::CONTINUE) {
				this->currentGame->canContinue(true);
			}
		}

		this->setState(this->currentGame->currentPlayer());
		this->setState(this->getNextPlayer());
		this->currentGame->drawn(false);

		/* Check if player won. */
		this->currentGame->checkCards(this->currentGame->currentPlayer());

		if (this->currentGame->winner() == this->currentGame->currentPlayer()) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str());
			Msg::DisplayPlayerSwitch(message);

			if (this->useAI) {
				if (savedata->playerWins() < 255) savedata->playerWins(savedata->playerWins() + 1);
			}

			Gui::screenBack(true);
			return;
		}

		/* If CardIndex is higher than the amount of cards, go one card back. */
		if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) > (int)this->currentGame->getSize(this->currentGame->currentPlayer()) -1) {
			this->currentGame->cardIndex(this->currentGame->getSize(this->currentGame->currentPlayer()) -1, this->currentGame->currentPlayer());
		}

		if (!this->currentGame->canContinue()) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
			Msg::DisplayPlayerSwitch(message);
			this->currentGame->currentPlayer(this->getNextPlayer());
		}

		this->currentGame->canContinue(false);
	}
}


void GameScreen::PlayerLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (this->currentGame->state(this->currentGame->currentPlayer()) == PlayerState::BREAK) {
		this->currentGame->state(PlayerState::NOTHING, this->currentGame->currentPlayer()); // Reset.
		char message [100];
		snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), this->returnPlayerName(this->currentGame->currentPlayer()).c_str(), this->returnPlayerName(this->getNextPlayer()).c_str());
		Msg::DisplayPlayerSwitch(message);
		this->currentGame->currentPlayer(this->getNextPlayer());
	}

	u32 hRepeat = hidKeysDownRepeat();

	/* Pressing Start goes to the Sub Menu. */
	if (hDown & KEY_START) {
		this->isSubMenu = true;
	}

	if (hRepeat & KEY_RIGHT) {
		if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) < this->currentGame->getSize(this->currentGame->currentPlayer()) -1)	this->currentGame->cardIndex(this->currentGame->cardIndex(this->currentGame->currentPlayer()) + 1, this->currentGame->currentPlayer());
	}

	if (hDown & KEY_R) {
		this->currentGame->cardIndex(this->currentGame->getSize(this->currentGame->currentPlayer()) -1, this->currentGame->currentPlayer());
	}

	if (hRepeat & KEY_LEFT) {
		if (this->currentGame->cardIndex(this->currentGame->currentPlayer()) > 0)	this->currentGame->cardIndex(this->currentGame->cardIndex(this->currentGame->currentPlayer()) - 1, this->currentGame->currentPlayer());
	}

	if (hDown & KEY_L) {
		this->currentGame->cardIndex(0, this->currentGame->currentPlayer());
	}

	if (hDown & KEY_A) {
		this->PlayLogic(this->currentGame->cardIndex(this->currentGame->currentPlayer()));
	}

	/* Player cannot set, so draw a card. If user cannot play after it, skip to next player. */
	if (hDown & KEY_X) {
		if (!this->currentGame->drawn()) {
			if (config->allowAnimation())	this->drawAnim(this->currentGame->currentPlayer(), this->currentGame->getTableTop());
			this->currentGame->addCard(this->currentGame->currentPlayer());
			/* Do not allow multiple draws. */
			this->currentGame->drawn(true);
			if (!CanPlayerPlay(this->currentGame->currentPlayer())) {
				/* Reset hasDrawn. */
				this->currentGame->drawn(false); // Reset.
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), returnPlayerName(this->currentGame->currentPlayer()).c_str(), returnPlayerName(this->getNextPlayer()).c_str());
				Msg::DisplayPlayerSwitch(message);
				this->currentGame->currentPlayer(this->getNextPlayer());
			}

		} else {
			Msg::DisplayPlayerSwitch(Lang::get("DRAW_1_MSG"));
		}
	}

	/* This is for Colorblind users. */
	if (hHeld & KEY_B) {
		Msg::HelperBox(Lang::get("TABLECARD") + GameHelper::getTypeName(this->currentGame->tableCard().CT) + " - " + GameHelper::getColorName(this->currentGame->tableCard().CC)
		+ "\n\n" + Lang::get("CURRENT_CARD") + GameHelper::getTypeName(this->currentGame->getType(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer())) + " - " + GameHelper::getColorName(this->currentGame->getColor(this->currentGame->cardIndex(this->currentGame->currentPlayer()), this->currentGame->currentPlayer())));
	}

	if (hDown & KEY_TOUCH) {
		for (int i = 0; i < 5; i++) {
			if (touching(this->cardPos[i])) {
				int temp = this->currentGame->cardIndex(this->currentGame->currentPlayer());
				if (temp > 4) {
					this->PlayLogic(i + (temp - 4));
				} else {
					this->PlayLogic(i);
				}
			}
		}
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("PLAY_INSTRUCTIONS"));
	}
}