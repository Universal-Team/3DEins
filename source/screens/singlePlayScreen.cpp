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

#include "singlePlayScreen.hpp"

#include <vector>

#define MAXSHOWNCARDS 5
extern bool touching(touchPosition touch, Structs::ButtonPos button);

// Player chars.
extern int player1;
extern int playerAmount;

// Table card.
extern CardType TypeToPlay;
extern CardColor ColorToPlay;

void SinglePlayScreen::DisplayPlayerHand() const {
	for (int i = 0; i < (int)Player1Hand.size(); i++) {
		if (Player1Card < MAXSHOWNCARDS) {
			GFX::DrawCard(Player1Hand[i].CT, 1 + (i * 65), 50, Player1Hand[i].CC);
		} else {
			GFX::DrawCard(Player1Hand[i+Player1Card-4].CT, 1 + (i * 65), 50, Player1Hand[i+Player1Card-4].CC);
		}
		if (i == Player1Card) {
			if (Player1Card < MAXSHOWNCARDS) {
				GFX::DrawCardSelector(1 + (i * 65), 50);
			} else {
				GFX::DrawCardSelector(1 + (4 * 65), 50);
			}
		}
	}
}

void SinglePlayScreen::DisplayPlayerHandSmall() const {
	for (int i = 0; i < (int)Player1Hand.size(); i++) {
		GFX::DrawCard(Player1Hand[i].CT, 2 + (i * 18), 150, Player1Hand[i].CC, 0.8, 0.8);
	}
}

// Return the name of the player.
extern std::string getPlayerName(int player);

// Return the Avatar of the Player.
int SinglePlayScreen::getPlayerAvatar(int player) const {
	switch (player) {
		case 1:
			return player1;
			break;
		case 2:
			return avatar2;
			break;
		case 3:
			return avatar3;
			break;
		case 4:
			return avatar4;
			break;
	}
	return 1; // Should never happen.
}

// Currently only for +2.
bool SinglePlayScreen::PlayerCanCounter(int player) const {
	switch (player) {
		case 1:
			if (CardHelper::checkForCounter(Player1Hand, cardtype))	return true;
			else	return false;
			break;
		case 2:
			if (CardHelper::checkForCounter(Player2Hand, cardtype))	return true;
			else	return false;
			break;
		case 3:
			if (CardHelper::checkForCounter(Player3Hand, cardtype))	return true;
			else	return false;
			break;
		case 4:
			if (CardHelper::checkForCounter(Player4Hand, cardtype))	return true;
			else	return false;
			break;
	}
	return false; // Should never happen.
}

// Check if user can play.
bool SinglePlayScreen::CanPlayerPlay(int player) const {
	switch (player) {
		case 1:
			if (CardHelper::checkForPlayableCard(Player1Hand, TypeToPlay, ColorToPlay))	return true;
			else	return false;
			break;
		case 2:
			if (CardHelper::checkForPlayableCard(Player2Hand, TypeToPlay, ColorToPlay))	return true;
			else	return false;
			break;
		case 3:
			if (CardHelper::checkForPlayableCard(Player3Hand, TypeToPlay, ColorToPlay))	return true;
			else	return false;
			break;
		case 4:
			if (CardHelper::checkForPlayableCard(Player4Hand, TypeToPlay, ColorToPlay))	return true;
			else	return false;
			break;
	}
	return false; // Should never happen.
}

// Return the remaining cards.
int SinglePlayScreen::getPlayerCards(int player) const {
	switch (player) {
		case 1:
			return (int)Player1Hand.size();
			break;
		case 2:
			return (int)Player2Hand.size();
			break;
		case 3:
			return (int)Player3Hand.size();
			break;
		case 4:
			return (int)Player4Hand.size();
			break;
	}
	return 0; // Should never happen.
}

void SinglePlayScreen::DrawPlay(void) const {
	GFX::DrawTop(false);
	// Draw Players & amount of cards.
	DrawPlayers();
	switch (currentPlayer) {
		case 1:
			GFX::DrawSelectedPlayer(130, 200);
			break;
		case 2:
			GFX::DrawSelectedPlayer(130, 70);
			break;
		case 3:
			GFX::DrawSelectedPlayer(250, 70);
			break;
		case 4:
			GFX::DrawSelectedPlayer(250, 200);
			break;
	}

	GFX::DrawCard(TypeToPlay, 170, 80, ColorToPlay);
	GFX::DrawBottom(false);
	char message [100];
	std::string pn = getPlayerName(currentPlayer);
	snprintf(message, sizeof(message), Lang::get("ITS_PLAYER_TURN").c_str(), pn.c_str());
	Gui::DrawStringCentered(0, 0, 0.7f, Config::Text, message);
	DisplayPlayerHand();
	DisplayPlayerHandSmall();
}


void SinglePlayScreen::DrawPlayerStats(void) const {
	Animation::DrawSubBG();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	Gui::DrawStringCentered(0, 0, 0.8f, Config::Text, "3DEins - " + Lang::get("STATS"), 400);
	GFX::DrawPlayer(30, 50, 1, 1, getPlayerAvatar(subMode));
	Gui::DrawString(190, 55, 0.7f, Config::Text, Lang::get("POSITION") + std::to_string(subMode) + " | " + std::to_string(maxPlayer), 200);
	Gui::DrawString(190, 85, 0.7f, Config::Text, Lang::get("PLAYERNAME") + getPlayerName(subMode), 200);
	Gui::DrawString(190, 115, 0.7f, Config::Text, Lang::get("CARDS_LEFT") + std::to_string(getPlayerCards(subMode)), 200);
	Gui::DrawString(190, 145, 0.7f, Config::Text, Lang::get("POINTS") + "0", 200);
	Gui::DrawStringCentered(0, 216, 0.75f, Config::Text, Lang::get("STATS_INFO"), 400);
	Animation::DrawSubBG(false);
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
}

void SinglePlayScreen::DrawSubMenu(void) const {
	Animation::DrawSubBG();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	Gui::DrawStringCentered(0, 0, 0.8f, Config::Text, "3DEins - " + Lang::get("GAME_PAUSED"), 400);
	Gui::DrawStringCentered(0, 55, 0.7f, Config::Text, Lang::get("PLAYERS") + std::to_string(maxPlayer), 400);
	Gui::DrawStringCentered(0, 85, 0.7f, Config::Text, Lang::get("POINTS_TO_WIN") + ": " + std::to_string(Config::POINTS), 400);
	Gui::DrawStringCentered(0, 216, 0.75f, Config::Text, Lang::get("STATS_INFO"), 400);
	
	Animation::DrawSubBG(false);
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	for (int i = 0; i < 3; i++) {
		Gui::Draw_Rect(breakBtn[i].x, breakBtn[i].y, breakBtn[i].w, breakBtn[i].h, Config::Button);
		if (selection == i) {
			GFX::DrawButtonSelector(breakBtn[i].x, breakBtn[i].y);
		}
	}
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("RESUME")))/2-80+17.5, 0.6, Config::Text, Lang::get("RESUME"), 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("RESTART")))/2-20+17.5, 0.6, Config::Text, Lang::get("RESTART"), 130, 25);
	Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.6, Lang::get("EXIT_GAME")))/2+75-17.5, 0.6, Config::Text, Lang::get("EXIT_GAME"), 130, 25);
}


void SinglePlayScreen::Draw(void) const {
	if (isSubMenu) {
		if (subMode == 0) {
			DrawSubMenu();
		} else {
			DrawPlayerStats();
		}
	} else {
		DrawPlay();
	}
}

// TODO.
void SinglePlayScreen::DrawPlayers() const {
	// Player 1.
	GFX::DrawPlayer(0, 130, 0.9, 0.9, player1);
	Gui::DrawString(90, 200, 0.6f, Config::Text, std::to_string(Player1Hand.size()));
	// Player 2.
	GFX::DrawPlayer(0, 0, 0.9, 0.9, avatar2);
	Gui::DrawString(90, 40, 0.6f, Config::Text, std::to_string(Player2Hand.size()));
	if (maxPlayer == 3) {
		// Player 3.
		GFX::DrawPlayer(300, 0, 0.9, 0.9, avatar3);
		Gui::DrawString(270, 40, 0.6f, Config::Text, std::to_string(Player3Hand.size()));
	} else if (maxPlayer == 4) {
		// Player 3.
		GFX::DrawPlayer(300, 0, 0.9, 0.9, avatar3);
		Gui::DrawString(270, 40, 0.6f, Config::Text, std::to_string(Player3Hand.size()));
		// Player 4.
		GFX::DrawPlayer(300, 130, 0.9, 0.9, avatar4);
		Gui::DrawString(270, 200, 0.6f, Config::Text, std::to_string(Player4Hand.size()));
	}
}

void SinglePlayScreen::AddCard(int player) {
	switch (player) {
		case 1:
			CardHelper::AddCard(Player1Hand);
			break;
		case 2:
			CardHelper::AddCard(Player2Hand);
			break;
		case 3:
			CardHelper::AddCard(Player3Hand);
			break;
		case 4:
			CardHelper::AddCard(Player4Hand);
			break;
	}
}

void SinglePlayScreen::RemoveCard(int player) {
	switch (player) {
		case 1:
			CardHelper::RemoveCard(Player1Hand, Player1Card);
			break;
		case 2:
			CardHelper::RemoveCard(Player2Hand, Player2Card);
			break;
		case 3:
			CardHelper::RemoveCard(Player3Hand, Player3Card);
			break;
		case 4:
			CardHelper::RemoveCard(Player4Hand, Player4Card);
			break;
	}
}

void SinglePlayScreen::restart() {
	// Randomize Computer chars.
	avatar2 = rand() % 7 + 0;
	if (maxPlayer == 3) {
		avatar3 = rand() % 7 + 0;
	} else if (maxPlayer == 4) {
		avatar3 = rand() % 7 + 0;
		avatar4 = rand() % 7 + 0;
	}

	// Reset stuff.
	currentPlayer = 1;
	PlayDirection = Direction::LEFT;
	hasDrawn = false;
	// Reset Card Indicator.
	Player1Card = 0;
	Player2Card = 0;
	Player3Card = 0;
	Player4Card = 0;
	// Clear Player Hands.
	Player1Hand.clear();
	Player2Hand.clear();
	if (maxPlayer == 3) {
		Player3Hand.clear();
	} else if (maxPlayer == 4) {
		Player3Hand.clear();
		Player4Hand.clear();
	}
	// Randomize Table card.
	CardHelper::RandomizeTableCard();
	// Fill Player 1.
	AddCard(1);
	AddCard(1);
	AddCard(1);
	AddCard(1);
	AddCard(1);
	AddCard(1);
	// Fill Player 2.
	AddCard(2);
	AddCard(2);
	AddCard(2);
	AddCard(2);
	AddCard(2);
	AddCard(2);
	// Only fill Player 3 | 4, if used.
	if (maxPlayer == 3) {
		// Fill Player 3.
		AddCard(3);
		AddCard(3);
		AddCard(3);
		AddCard(3);
		AddCard(3);
		AddCard(3);
	} else if (maxPlayer == 4) {
		// Fill Player 3.
		AddCard(3);
		AddCard(3);
		AddCard(3);
		AddCard(3);
		AddCard(3);
		AddCard(3);
		// Fill Player 4.
		AddCard(4);
		AddCard(4);
		AddCard(4);
		AddCard(4);
		AddCard(4);
		AddCard(4);
	}
}


SinglePlayScreen::SinglePlayScreen() {
	// Set Player Amount.
	maxPlayer = playerAmount;
	// restart | start a new game.
	restart();
}

void SinglePlayScreen::SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (subMode == 0) {
		if (hDown & KEY_A) {
			switch (selection) {
				case 0:
					isSubMenu = false;
					break;
				case 1:
					if (Msg::promptMsg(Lang::get("RESTART_GAME"))) {
						restart();
						isSubMenu = false;
					}
					break;
				case 2:
					if (Msg::promptMsg(Lang::get("QUIT_GAME"))) {
						Gui::screenBack();
						return;
					}
					break;
			}
		}

		if (hDown & KEY_DOWN) {
			if (selection < 2)	selection++;
		} else if (hDown & KEY_UP) {
			if (selection > 0)	selection--;
		}	

		if (hDown & KEY_TOUCH) {
			if (touching(touch, breakBtn[0])) {
				isSubMenu = false;
			} else if (touching(touch, breakBtn[1])) {
				if (Msg::promptMsg(Lang::get("RESTART_GAME"))) {
					restart();
					isSubMenu = false;
				}
			} else if (touching(touch, breakBtn[2])) {
				if (Msg::promptMsg(Lang::get("QUIT_GAME"))) {
					Gui::screenBack();
					return;
				}
			}
		}
	}
	if (hDown & KEY_L) {
		if (subMode > 0)	subMode--;
	}

	if (hDown & KEY_R) {
		if (subMode < playerAmount)	subMode++;
	}
}

void SinglePlayScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (isSubMenu) {
		SubMenuLogic(hDown, hHeld, touch);
	} else {
		RoundLogic(hDown, hHeld, touch);

		// Pressing Start goes to the Sub Menu.
		if (hDown & KEY_START) {
			isSubMenu = true;
		}

		if (hHeld & KEY_SELECT) {
			Msg::HelperBox(Lang::get("PLAY_INSTRUCTIONS"));
		}
	}
}


// For the Player hand.
void SinglePlayScreen::Player1Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (PlayerBreak == true) {
		PlayerBreak = false;
		if (PlayDirection == Direction::LEFT) {
			currentPlayer = 2;
		} else if (PlayDirection == Direction::RIGHT) {
			currentPlayer = maxPlayer;
		}
	}

	if (setBruh == 1) {
		Msg::Bruh(getPlayerName(1));
		CardHelper::RandomizeTableCard();
		setBruh = 0;
	}

	if (hDown & KEY_RIGHT) {
		if (Player1Card < (int)Player1Hand.size()-1) {
			Player1Card++;
		}
	}

	if (hDown & KEY_R) {
		Player1Card = (int)Player1Hand.size()-1;
	}

	if (hDown & KEY_LEFT ) {
		if (Player1Card > 0) {
			Player1Card--;
		}
	}

	if (hDown & KEY_L) {
		Player1Card = 0;
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical.
		if (Player1Hand[Player1Card].CT == TypeToPlay || Player1Hand[Player1Card].CC == ColorToPlay || Player1Hand[Player1Card].CT == CardType::WISH || Player1Hand[Player1Card].CT == CardType::PLUS4 || Player1Hand[Player1Card].CT == CardType::BRUH) {
			TypeToPlay = Player1Hand[Player1Card].CT;
			ColorToPlay = Player1Hand[Player1Card].CC;

			// Handle.
			if (PlayDirection == Direction::LEFT) {
				CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player2Status, maxPlayer);
				CardHelper::statusHandler(Player1Hand, Player1Status, PlayDirection);
				CardHelper::statusHandler(Player2Hand, Player2Status, PlayDirection);
			} else {
				if (maxPlayer == 4) {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player4Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, PlayDirection);
					CardHelper::statusHandler(Player4Hand, Player4Status, PlayDirection);
				} else if (maxPlayer == 3) {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player3Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, PlayDirection);
					CardHelper::statusHandler(Player3Hand, Player3Status, PlayDirection);
				} else if (maxPlayer == 2) {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player2Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, PlayDirection);
					CardHelper::statusHandler(Player2Hand, Player2Status, PlayDirection);
				}
			}

			// Special case handle for 2 Player.
			if (maxPlayer == 2) {
				if (Player1Hand[Player1Card].CT == CardType::REVERSE || Player1Hand[Player1Card].CT == CardType::SKIP) {
					canContinue = true;
				}
			}

			// Skip special handle.
			if (maxPlayer > 2) {
				if (Player1Hand[Player1Card].CT == CardType::SKIP) {
					PlayerBreak = true;
				}
			}

			// Give a Bruh to the next player! xD
			if (Player1Hand[Player1Card].CT == CardType::BRUH) {
				if (PlayDirection == Direction::LEFT) {
					setBruh = 2;
				} else if (PlayDirection == Direction::RIGHT) {
					setBruh = maxPlayer;
				}
			}

			RemoveCard(1);
			hasDrawn = false;

			if (Player1Hand.size() == 0) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), getPlayerName(currentPlayer).c_str());
				Msg::DisplayPlayerSwitch(message);
				Gui::screenBack();
				return;
			}
			if (Player1Card > (int)Player1Hand.size() -1) {
				Player1Card = (int)Player1Hand.size() - 1;
			}


			if (!canContinue) {
				if (PlayDirection == Direction::LEFT) {
					currentPlayer = 2;
				} else if (PlayDirection == Direction::RIGHT) {
					currentPlayer = maxPlayer;
				}
			}
			canContinue = false;
		}
	}

	// Player cannot set, so draw a card. If user cannot play after it, skip to next player.
	if (hDown & KEY_X) {
		if (!hasDrawn) {
			AddCard(1);
			// Do not allow multiple draws.
			hasDrawn = true;
			if (!CanPlayerPlay(currentPlayer)) {
				// Reset hasDrawn.
				hasDrawn = false;
				if (PlayDirection == Direction::LEFT) {
					currentPlayer = 2;
				} else if (PlayDirection == Direction::RIGHT) {
					currentPlayer = maxPlayer;
				}
			}
		} else {
			Msg::DisplayPlayerSwitch(Lang::get("DRAW_1_MSG"));
		}
	}

	// This is for Colorblind users.
	if (hHeld & KEY_B) {
		Msg::HelperBox(Lang::get("TABLECARD") + CardHelper::returnCardTypeName(TypeToPlay) + " - " + CardHelper::returnCardColorName(ColorToPlay)
		+ "\n\n" + Lang::get("CURRENT_CARD") + CardHelper::returnCardTypeName(Player1Hand[Player1Card].CT) + " - " + CardHelper::returnCardColorName(Player1Hand[Player1Card].CC));
	}
}

void SinglePlayScreen::Player2Logic() { }

void SinglePlayScreen::Player3Logic() { }

void SinglePlayScreen::Player4Logic() { }

void SinglePlayScreen::RoundLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	switch (currentPlayer) {
		case 1:
			Player1Logic(hDown, hHeld, touch);
			break;
		case 2:
			Player2Logic();
			break;
		case 3:
			Player3Logic();
			break;
		case 4:
			Player4Logic();
			break;
	}
}