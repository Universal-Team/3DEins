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

#include "multiPlayScreen.hpp"

#include <vector>

#define MAXSHOWNCARDS 5
extern bool touching(touchPosition touch, Structs::ButtonPos button);

// Player chars.
extern int player1;
extern int player2;
extern int player3;
extern int player4;
extern int playerAmount;

// Table card.
extern CardType TypeToPlay;
extern CardColor ColorToPlay;

void MultiPlayScreen::DisplayPlayerHand() const {
	switch (currentPlayer) {
		case 1:
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
			break;
		case 2:
			for (int i = 0; i < (int)Player2Hand.size(); i++) {
				if (Player2Card < MAXSHOWNCARDS) {
					GFX::DrawCard(Player2Hand[i].CT, 1 + (i * 65), 50, Player2Hand[i].CC);
				} else {
					GFX::DrawCard(Player2Hand[i+Player2Card-4].CT, 1 + (i * 65), 50, Player2Hand[i+Player2Card-4].CC);
				}
				if (i == Player2Card) {
					if (Player2Card < MAXSHOWNCARDS) {
						GFX::DrawCardSelector(1 + (i * 65), 50);
					} else {
						GFX::DrawCardSelector(1 + (4 * 65), 50);
					}
				}
			}
			break;
		case 3:
			for (int i = 0; i < (int)Player3Hand.size(); i++) {
				if (Player3Card < MAXSHOWNCARDS) {
					GFX::DrawCard(Player3Hand[i].CT, 1 + (i * 65), 50, Player3Hand[i].CC);
				} else {
					GFX::DrawCard(Player3Hand[i+Player3Card-4].CT, 1 + (i * 65), 50, Player3Hand[i+Player3Card-4].CC);
				}
				if (i == Player3Card) {
					if (Player3Card < MAXSHOWNCARDS) {
						GFX::DrawCardSelector(1 + (i * 65), 50);
					} else {
						GFX::DrawCardSelector(1 + (4 * 65), 50);
					}
				}
			}
			break;
		case 4:
			for (int i = 0; i < (int)Player4Hand.size(); i++) {
				if (Player4Card < MAXSHOWNCARDS) {
					GFX::DrawCard(Player4Hand[i].CT, 1 + (i * 65), 50, Player4Hand[i].CC);
				} else {
					GFX::DrawCard(Player4Hand[i+Player4Card-4].CT, 1 + (i * 65), 50, Player4Hand[i+Player4Card-4].CC);
				}
				if (i == Player4Card) {
					if (Player4Card < MAXSHOWNCARDS) {
						GFX::DrawCardSelector(1 + (i * 65), 50);
					} else {
						GFX::DrawCardSelector(1 + (4 * 65), 50);
					}
				}
			}
			break;
	}
}

void MultiPlayScreen::DisplayPlayerHandSmall() const {
	switch (currentPlayer) {
		case 1:
			for (int i = 0; i < (int)Player1Hand.size(); i++) {
				GFX::DrawCard(Player1Hand[i].CT, 2 + (i * 18), 150, Player1Hand[i].CC, 0.8, 0.8);
			}
			break;
		case 2:
			for (int i = 0; i < (int)Player2Hand.size(); i++) {
				GFX::DrawCard(Player2Hand[i].CT, 2 + (i * 18), 150, Player2Hand[i].CC, 0.8, 0.8);
			}
			break;
		case 3:
			for (int i = 0; i < (int)Player3Hand.size(); i++) {
				GFX::DrawCard(Player3Hand[i].CT, 2 + (i * 18), 150, Player3Hand[i].CC, 0.8, 0.8);
			}
			break;
		case 4:
			for (int i = 0; i < (int)Player4Hand.size(); i++) {
				GFX::DrawCard(Player4Hand[i].CT, 2 + (i * 18), 150, Player4Hand[i].CC, 0.8, 0.8);
			}
			break;
	}
}

// Return the name of the player.
std::string getPlayerName(int player) {
	switch (player) {
		case 1:
			return Config::Player1;
			break;
		case 2:
			return Config::Player2;
			break;
		case 3:
			return Config::Player3;
			break;
		case 4:
			return Config::Player4;
			break;
	}
	return ""; // Should never happen.
}

// Return the Avatar of the Player.
int getPlayerAvatar(int player) {
	switch (player) {
		case 1:
			return player1;
			break;
		case 2:
			return player2;
			break;
		case 3:
			return player3;
			break;
		case 4:
			return player4;
			break;
	}
	return 1; // Should never happen.
}

// Currently only for +2.
bool MultiPlayScreen::PlayerCanCounter(int player) const {
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
bool MultiPlayScreen::CanPlayerPlay(int player) const {
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
int MultiPlayScreen::getPlayerCards(int player) const {
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

void MultiPlayScreen::DrawPlay(void) const {
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

void MultiPlayScreen::DrawStats(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, Config::Text, "3DEins - " + Lang::get("STATS"), 320);
	GFX::DrawPlayer(30, 35, 1, 1, getPlayerAvatar(subMode));
	Gui::DrawString(210, 70, 0.7f, Config::Text, Lang::get("PLAYERNAME") + getPlayerName(subMode), 160);
	Gui::DrawString(210, 120, 0.7f, Config::Text, Lang::get("CARDS_LEFT") + std::to_string(getPlayerCards(subMode)), 160);
	GFX::DrawBottom();
}

void MultiPlayScreen::DrawSubMenu(void) const {
	Animation::DrawSubBG();
	Gui::DrawString(100, 0, 0.9f, Config::Text, "3DEins - " + Lang::get("GAME_PAUSED"));
	GFX::DrawBottom();
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


void MultiPlayScreen::Draw(void) const {
	if (isSubMenu) {
		if (subMode == 0) {
			DrawSubMenu();
		} else {
			DrawStats();
		}
	} else {
		DrawPlay();
	}
}

// TODO.
void MultiPlayScreen::DrawPlayers() const {
	// Player 1.
	GFX::DrawPlayer(0, 130, 0.9, 0.9, player1);
	Gui::DrawString(90, 200, 0.6f, Config::Text, std::to_string(Player1Hand.size()));
	// Player 2.
	GFX::DrawPlayer(0, 0, 0.9, 0.9, player2);
	Gui::DrawString(90, 40, 0.6f, Config::Text, std::to_string(Player2Hand.size()));
	if (maxPlayer == 3) {
		// Player 3.
		GFX::DrawPlayer(300, 0, 0.9, 0.9, player3);
		Gui::DrawString(270, 40, 0.6f, Config::Text, std::to_string(Player3Hand.size()));
	} else if (maxPlayer == 4) {
		// Player 3.
		GFX::DrawPlayer(300, 0, 0.9, 0.9, player3);
		Gui::DrawString(270, 40, 0.6f, Config::Text, std::to_string(Player3Hand.size()));
		// Player 4.
		GFX::DrawPlayer(300, 130, 0.9, 0.9, player4);
		Gui::DrawString(270, 200, 0.6f, Config::Text, std::to_string(Player4Hand.size()));
	}
}

void MultiPlayScreen::AddCard(int player) {
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

void MultiPlayScreen::RemoveCard(int player) {
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

void MultiPlayScreen::restart() {
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


MultiPlayScreen::MultiPlayScreen() {
	// Set Player Amount.
	maxPlayer = playerAmount;
	// restart | start a new game.
	restart();
}

void MultiPlayScreen::SubMenuLogic(u32 hDown, u32 hHeld, touchPosition touch) {
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

void MultiPlayScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
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
void MultiPlayScreen::Player1Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (PlayerBreak == true) {
		PlayerBreak = false;
		if (PlayDirection == Direction::LEFT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), getPlayerName(1).c_str(), getPlayerName(2).c_str());
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 2;
		} else if (PlayDirection == Direction::RIGHT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), getPlayerName(1).c_str(), getPlayerName(maxPlayer).c_str());
			Msg::DisplayPlayerSwitch(message);
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
				CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection);
				CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection);
			} else {
				if (maxPlayer == 4) {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player4Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection);
					CardHelper::statusHandler(Player4Hand, Player4Status, Player4Status, PlayDirection);
				} else if (maxPlayer == 3) {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player3Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection);
					CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection);
				} else {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player2Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection);
					CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection);
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
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(1).c_str(), getPlayerName(2).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = 2;
				} else if (PlayDirection == Direction::RIGHT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(1).c_str(), getPlayerName(maxPlayer).c_str());
					Msg::DisplayPlayerSwitch(message);
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
					char message [100];
						snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(1).c_str(), getPlayerName(2).c_str());
				Msg::DisplayPlayerSwitch(message);
					currentPlayer = 2;
				} else if (PlayDirection == Direction::RIGHT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(1).c_str(), getPlayerName(maxPlayer).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = maxPlayer;
				}
			}
		} else {
			Msg::DisplayPlayerSwitch(Lang::get("DRAW_1_MSG"));
		}
	}
}

void MultiPlayScreen::Player2Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (PlayerBreak == true) {
		PlayerBreak = false;
		if (PlayDirection == Direction::LEFT) {
			if (maxPlayer > 2)	tempPlayer = 3;
			else				tempPlayer = 1;
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), getPlayerName(2).c_str(), getPlayerName(tempPlayer).c_str());
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = tempPlayer;
		} else if (PlayDirection == Direction::RIGHT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), getPlayerName(2).c_str(), getPlayerName(1).c_str());
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 1;
		}
	}

	if (setBruh == 2) {
		Msg::Bruh(getPlayerName(2));
		CardHelper::RandomizeTableCard();
		setBruh = 0;
	}

	if (hDown & KEY_RIGHT) {
		if (Player2Card < (int)Player2Hand.size()-1) {
			Player2Card++;
		}
	}

	if (hDown & KEY_R) {
		Player2Card = (int)Player2Hand.size()-1;
	}

	if (hDown & KEY_LEFT ) {
		if (Player2Card > 0) {
			Player2Card--;
		}
	}

	if (hDown & KEY_L) {
		Player2Card = 0;
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical.
		if (Player2Hand[Player2Card].CT == TypeToPlay || Player2Hand[Player2Card].CC == ColorToPlay || Player2Hand[Player2Card].CT == CardType::WISH || Player2Hand[Player2Card].CT == CardType::PLUS4 || Player2Hand[Player2Card].CT == CardType::BRUH) {
			TypeToPlay = Player2Hand[Player2Card].CT;
			ColorToPlay = Player2Hand[Player2Card].CC;

			// Handle.
			if (PlayDirection == Direction::LEFT) {
				if (maxPlayer == 3) {
					CardHelper::specialHandle(Player2Hand[Player2Card].CT, Player2Status, Player3Status, maxPlayer);
					CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection);
					CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection);
				} else {
					CardHelper::specialHandle(Player2Hand[Player2Card].CT, Player2Status, Player1Status, maxPlayer);
					CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection);
				}
			} else {
				CardHelper::specialHandle(Player2Hand[Player2Card].CT, Player2Status, Player1Status, maxPlayer);
				CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection);
				CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection);
			}

			// Special case handle for 2 Player.
			if (maxPlayer == 2) {
				if (Player2Hand[Player2Card].CT == CardType::REVERSE || Player2Hand[Player2Card].CT == CardType::SKIP) {
					canContinue = true;
				}
			}

			// Skip special handle.
			if (maxPlayer > 2) {
				if (Player2Hand[Player2Card].CT == CardType::SKIP) {
					PlayerBreak = true;
				}
			}

			// Give a Bruh to the next player! xD
			if (Player2Hand[Player2Card].CT == CardType::BRUH) {
				if (PlayDirection == Direction::LEFT) {
					if (maxPlayer > 2)	setBruh = 3;
					else				setBruh = 1;
				} else if (PlayDirection == Direction::RIGHT) {
					setBruh = 1;
				}
			}

			RemoveCard(2);
			hasDrawn = false;

			if (Player2Hand.size() == 0) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), getPlayerName(currentPlayer).c_str());
				Msg::DisplayPlayerSwitch(message);
				Gui::screenBack();
				return;
			}
			if (Player2Card > (int)Player2Hand.size() -1) {
				Player2Card = (int)Player2Hand.size() - 1;
			}
			if (!canContinue) {
				if (PlayDirection == Direction::LEFT) {
					if (maxPlayer > 2)	tempPlayer = 3;
					else				tempPlayer = 1;
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(2).c_str(), getPlayerName(tempPlayer).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = tempPlayer;
				} else if (PlayDirection == Direction::RIGHT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(),getPlayerName(2).c_str(), getPlayerName(1).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = 1;
				}
			}
			canContinue = false;
		}
	}

	// Player cannot set, so draw a card. If user cannot play after it, skip to next player.
	if (hDown & KEY_X) {
		if (!hasDrawn) {
			AddCard(2);
			// Do not allow multiple draws.
			hasDrawn = true;
			if (!CanPlayerPlay(currentPlayer)) {
				// Reset hasDrawn state.
				hasDrawn = false;
				if (PlayDirection == Direction::LEFT) {
					if (maxPlayer > 2)	tempPlayer = 3;
					else				tempPlayer = 1;
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(2).c_str(), getPlayerName(tempPlayer).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = tempPlayer;
				} else if (PlayDirection == Direction::RIGHT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(2).c_str(), getPlayerName(1).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = 1;
				}
			}
		} else {
			Msg::DisplayPlayerSwitch(Lang::get("DRAW_1_MSG"));
		}
	}
}


void MultiPlayScreen::Player3Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (PlayerBreak == true) {
		PlayerBreak = false;
		if (PlayDirection == Direction::LEFT) {
			if (maxPlayer > 3)	tempPlayer = 4;
			else	tempPlayer = 2;
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), getPlayerName(3).c_str(), getPlayerName(tempPlayer).c_str());
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = tempPlayer;
		} else if (PlayDirection == Direction::RIGHT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), getPlayerName(3).c_str(), getPlayerName(2).c_str());
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 2;
		}
	}

	if (setBruh == 3) {
		Msg::Bruh(getPlayerName(3));
		CardHelper::RandomizeTableCard();
		setBruh = 0;
	}

	if (hDown & KEY_RIGHT) {
		if (Player3Card < (int)Player3Hand.size()-1) {
			Player3Card++;
		}
	}

	if (hDown & KEY_R) {
		Player3Card = (int)Player3Hand.size()-1;
	}

	if (hDown & KEY_LEFT ) {
		if (Player3Card > 0) {
			Player3Card--;
		}
	}

	if (hDown & KEY_L) {
		Player3Card = 0;
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical.
		if (Player3Hand[Player3Card].CT == TypeToPlay || Player3Hand[Player3Card].CC == ColorToPlay || Player3Hand[Player3Card].CT == CardType::WISH || Player3Hand[Player3Card].CT == CardType::PLUS4 || Player3Hand[Player3Card].CT == CardType::BRUH) {
			TypeToPlay = Player3Hand[Player3Card].CT;
			ColorToPlay = Player3Hand[Player3Card].CC;

			// Handle.
			if (PlayDirection == Direction::LEFT) {
				if (maxPlayer == 4) {
					CardHelper::specialHandle(Player3Hand[Player3Card].CT, Player3Status, Player4Status, maxPlayer);
					CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection);
					CardHelper::statusHandler(Player4Hand, Player4Status, Player4Status, PlayDirection);
				} else {
					CardHelper::specialHandle(Player3Hand[Player3Card].CT, Player3Status, Player1Status, maxPlayer);
					CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection);
				}
			} else {
				CardHelper::specialHandle(Player3Hand[Player3Card].CT, Player3Status, Player2Status, maxPlayer);
				CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection);
				CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection);
			}

			// Skip special handle.
			if (Player3Hand[Player3Card].CT == CardType::SKIP) {
				PlayerBreak = true;
			}

			// Give a Bruh to the next player! xD
			if (Player3Hand[Player3Card].CT == CardType::BRUH) {
				if (PlayDirection == Direction::LEFT) {
					if (maxPlayer > 3)	setBruh = 4;
					else				setBruh = 1;
				} else if (PlayDirection == Direction::RIGHT) {
					setBruh = 2;
				}
			}

			RemoveCard(3);
			hasDrawn = false;

			if (Player3Hand.size() == 0) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), getPlayerName(currentPlayer).c_str());
				Msg::DisplayPlayerSwitch(message);
				Gui::screenBack();
				return;
			}
			if (Player3Card > (int)Player3Hand.size() -1) {
				Player3Card = (int)Player3Hand.size() - 1;
			}

			if (PlayDirection == Direction::LEFT) {
				if (maxPlayer > 3)	tempPlayer = 4;
				else				tempPlayer = 1;
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(3).c_str(), getPlayerName(tempPlayer).c_str());
				Msg::DisplayPlayerSwitch(message);
				currentPlayer = tempPlayer;
			} else if (PlayDirection == Direction::RIGHT) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(3).c_str(), getPlayerName(2).c_str());
				Msg::DisplayPlayerSwitch(message);
				currentPlayer = 2;
			}
		}
	}

	// Player cannot set, so draw a card. If user cannot play after it, skip to next player.
	if (hDown & KEY_X) {
		if (!hasDrawn) {
			AddCard(3);
			// Do not allow multiple draws.
			hasDrawn = true;
			if (!CanPlayerPlay(currentPlayer)) {
				// Reset hasDrawn state.
				hasDrawn = false;
				if (PlayDirection == Direction::LEFT) {
					if (maxPlayer > 3)	tempPlayer = 4;
					else				tempPlayer = 1;
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(3).c_str(), getPlayerName(tempPlayer).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = tempPlayer;
				} else if (PlayDirection == Direction::RIGHT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(3).c_str(), getPlayerName(2).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = 2;
				}
			}
		} else {
			Msg::DisplayPlayerSwitch(Lang::get("DRAW_1_MSG"));
		}
	}
}

void MultiPlayScreen::Player4Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (PlayerBreak == true) {
		PlayerBreak = false;
		if (PlayDirection == Direction::LEFT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), getPlayerName(4).c_str(), getPlayerName(1).c_str());
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 1;
		} else if (PlayDirection == Direction::RIGHT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), getPlayerName(4).c_str(), getPlayerName(3).c_str());
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 3;
		}
	}

	if (setBruh == 4) {
		Msg::Bruh(getPlayerName(4));
		CardHelper::RandomizeTableCard();
		setBruh = 0;
	}

	if (hDown & KEY_RIGHT) {
		if (Player4Card < (int)Player4Hand.size()-1) {
			Player4Card++;
		}
	}

	if (hDown & KEY_R) {
		Player4Card = (int)Player4Hand.size()-1;
	}

	if (hDown & KEY_LEFT ) {
		if (Player4Card > 0) {
			Player4Card--;
		}
	}

	if (hDown & KEY_L) {
		Player4Card = 0;
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical.
		if (Player4Hand[Player4Card].CT == TypeToPlay || Player4Hand[Player4Card].CC == ColorToPlay || Player4Hand[Player4Card].CT == CardType::WISH || Player4Hand[Player4Card].CT == CardType::PLUS4 || Player4Hand[Player4Card].CT == CardType::BRUH) {
			TypeToPlay = Player4Hand[Player4Card].CT;
			ColorToPlay = Player4Hand[Player4Card].CC;

			// Handle.
			if (PlayDirection == Direction::LEFT) {
				CardHelper::specialHandle(Player4Hand[Player4Card].CT, Player4Status, Player1Status, maxPlayer);
				CardHelper::statusHandler(Player4Hand, Player4Status, Player4Status, PlayDirection);
				CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection);
			} else {
				CardHelper::specialHandle(Player4Hand[Player4Card].CT, Player4Status, Player3Status, maxPlayer);
				CardHelper::statusHandler(Player4Hand, Player4Status, Player4Status, PlayDirection);
				CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection);
			}

			// Skip special handle.
			if (Player4Hand[Player4Card].CT == CardType::SKIP) {
				PlayerBreak = true;
			}

			// Give a Bruh to the next player! xD
			if (Player4Hand[Player4Card].CT == CardType::BRUH) {
				if (PlayDirection == Direction::LEFT) {
					setBruh = 1;
				} else if (PlayDirection == Direction::RIGHT) {
					setBruh = 3;
				}
			}

			RemoveCard(4);
			hasDrawn = false;

			if (Player4Hand.size() == 0) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), getPlayerName(currentPlayer).c_str());
				Msg::DisplayPlayerSwitch(message);
				Gui::screenBack();
				return;
			}
			if (Player4Card > (int)Player4Hand.size() -1) {
				Player4Card = (int)Player4Hand.size() - 1;
			}

			if (PlayDirection == Direction::LEFT) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(4).c_str(), getPlayerName(1).c_str());
				Msg::DisplayPlayerSwitch(message);
				currentPlayer = 1;
			} else if (PlayDirection == Direction::RIGHT) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(4).c_str(), getPlayerName(3).c_str());
				Msg::DisplayPlayerSwitch(message);
				currentPlayer = 3;
			}
		}
	}


	// Player cannot set, so draw a card. If user cannot play after it, skip to next player.
	if (hDown & KEY_X) {
		if (!hasDrawn) {
			AddCard(4);
			// Do not allow multiple Draws.
			hasDrawn = true;
			if (!CanPlayerPlay(currentPlayer)) {
				// Reset hasDrawn state.
				hasDrawn = false;
				if (PlayDirection == Direction::LEFT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(4).c_str(), getPlayerName(1).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = 1;
				} else if (PlayDirection == Direction::RIGHT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), getPlayerName(4).c_str(), getPlayerName(3).c_str());
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = 3;
				}
			}
		} else {
			Msg::DisplayPlayerSwitch(Lang::get("DRAW_1_MSG"));
		}
	}
}

void MultiPlayScreen::RoundLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	switch (currentPlayer) {
		case 1:
			Player1Logic(hDown, hHeld, touch);
			break;
		case 2:
			Player2Logic(hDown, hHeld, touch);
			break;
		case 3:
			Player3Logic(hDown, hHeld, touch);
			break;
		case 4:
			Player4Logic(hDown, hHeld, touch);
			break;
	}
}