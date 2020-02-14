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
	if (currentPlayer == 1) {
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
	} else if (currentPlayer == 2) {
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
	} else if (currentPlayer == 3) {
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
	} else if (currentPlayer == 4) {
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
	}
}

void MultiPlayScreen::DisplayPlayerHandSmall() const {
	if (currentPlayer == 1) {
		for (int i = 0; i < (int)Player1Hand.size(); i++) {
			GFX::DrawCard(Player1Hand[i].CT, 2 + (i * 18), 150, Player1Hand[i].CC, 0.8, 0.8);
		}
	} else if (currentPlayer == 2) {
		for (int i = 0; i < (int)Player2Hand.size(); i++) {
			GFX::DrawCard(Player2Hand[i].CT, 2 + (i * 18), 150, Player2Hand[i].CC, 0.8, 0.8);
		}
	} else if (currentPlayer == 3) {
		for (int i = 0; i < (int)Player3Hand.size(); i++) {
			GFX::DrawCard(Player3Hand[i].CT, 2 + (i * 18), 150, Player3Hand[i].CC, 0.8, 0.8);
		}
	} else if (currentPlayer == 4) {
		for (int i = 0; i < (int)Player4Hand.size(); i++) {
			GFX::DrawCard(Player4Hand[i].CT, 2 + (i * 18), 150, Player4Hand[i].CC, 0.8, 0.8);
		}
	}
}


void MultiPlayScreen::Draw(void) const {
	GFX::DrawTop(false);
	// Draw Players & amount of cards.
	DrawPlayers();
	GFX::DrawCard(TypeToPlay, 170, 80, ColorToPlay);
	GFX::DrawBottom(false);
	char message [100];
	snprintf(message, sizeof(message), Lang::get("ITS_PLAYER_TURN").c_str(), currentPlayer);
	Gui::DrawStringCentered(0, 0, 0.7f, Config::Text, message);
	DisplayPlayerHand();
	DisplayPlayerHandSmall();
}

// TODO.
void MultiPlayScreen::DrawPlayers() const {
	// Player 1.
	GFX::DrawPlayer(-5, 130, 0.9, 0.9, PlayerChar(player1), Player1Feeling);
	Gui::DrawString(90, 200, 0.6f, Config::Text, std::to_string(Player1Hand.size()));
	// Player 2.
	GFX::DrawPlayer(-5, 0, 0.9, 0.9, PlayerChar(player2), Player2Feeling);
	Gui::DrawString(90, 40, 0.6f, Config::Text, std::to_string(Player2Hand.size()));
	if (maxPlayer == 3) {
		// Player 3.
		GFX::DrawPlayer(300, 0, 0.9, 0.9, PlayerChar(player3), Player3Feeling);
		Gui::DrawString(270, 40, 0.6f, Config::Text, std::to_string(Player3Hand.size()));
	} else if (maxPlayer == 4) {
		// Player 3.
		GFX::DrawPlayer(300, 0, 0.9, 0.9, PlayerChar(player3), Player3Feeling);
		Gui::DrawString(270, 40, 0.6f, Config::Text, std::to_string(Player3Hand.size()));
		// Player 4.
		GFX::DrawPlayer(300, 130, 0.9, 0.9, PlayerChar(player4), Player4Feeling);
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

MultiPlayScreen::MultiPlayScreen() {
	// Set Player Amount.
	maxPlayer = playerAmount;
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

void MultiPlayScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	RoundLogic(hDown, hHeld, touch);

	// Always make it possible, to quit a game.
	if (hDown & KEY_START) {
		if (Msg::promptMsg2(Lang::get("QUIT_GAME"))) {
			Gui::screenBack();
			return;
		}
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("PLAY_INSTRUCTIONS"));
	}
}


// For the Player hand.
void MultiPlayScreen::Player1Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (Player1Break == true) {
		Player1Break = false;
		if (PlayDirection == Direction::LEFT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), 1, 2);
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 2;
		} else if (PlayDirection == Direction::RIGHT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), 1, maxPlayer);
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = maxPlayer;
		}
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
		if (Player1Hand[Player1Card].CT == TypeToPlay || Player1Hand[Player1Card].CC == ColorToPlay || Player1Hand[Player1Card].CT == CardType::WISH || Player1Hand[Player1Card].CT == CardType::PLUS4) {
			TypeToPlay = Player1Hand[Player1Card].CT;
			ColorToPlay = Player1Hand[Player1Card].CC;

			// Handle.
			if (PlayDirection == Direction::LEFT) {
				CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player2Status, maxPlayer);
				CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection, Player1Break);
				CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection, Player2Break);
			} else {
				if (maxPlayer == 4) {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player4Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection, Player1Break);
					CardHelper::statusHandler(Player4Hand, Player4Status, Player4Status, PlayDirection, Player4Break);
				} else if (maxPlayer == 3) {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player3Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection, Player1Break);
					CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection, Player3Break);
				} else {
					CardHelper::specialHandle(Player1Hand[Player1Card].CT, Player1Status, Player2Status, maxPlayer);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection, Player1Break);
					CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection, Player2Break);
				}
			}

			// Special case handle for 2 Player.
			if (maxPlayer == 2) {
				if (Player1Hand[Player1Card].CT == CardType::REVERSE || Player1Hand[Player1Card].CT == CardType::SKIP) {
					canContinue = true;
				}
			}

			RemoveCard(1);

			if (Player1Hand.size() == 0) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), currentPlayer);
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
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), 1, 2);
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = 2;
				} else if (PlayDirection == Direction::RIGHT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), 1, maxPlayer);
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = maxPlayer;
				}
			}
			canContinue = false;
		}
	}

	// User cannot set, so draw a card.
	if (hDown & KEY_X) {
		AddCard(1);
	}
}

void MultiPlayScreen::Player2Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (Player2Break == true) {
		Player2Break = false;
		if (PlayDirection == Direction::LEFT) {
			if (maxPlayer > 2)	tempPlayer = 3;
			else				tempPlayer = 1;
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), 2, tempPlayer);
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = tempPlayer;
		} else if (PlayDirection == Direction::RIGHT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), 2, 1);
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 1;
		}
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
		if (Player2Hand[Player2Card].CT == TypeToPlay || Player2Hand[Player2Card].CC == ColorToPlay || Player2Hand[Player2Card].CT == CardType::WISH || Player2Hand[Player2Card].CT == CardType::PLUS4) {
			TypeToPlay = Player2Hand[Player2Card].CT;
			ColorToPlay = Player2Hand[Player2Card].CC;

			// Handle.
			if (PlayDirection == Direction::LEFT) {
				if (maxPlayer == 3) {
					CardHelper::specialHandle(Player2Hand[Player2Card].CT, Player2Status, Player3Status, maxPlayer);
					CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection, Player2Break);
					CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection, Player3Break);
				} else {
					CardHelper::specialHandle(Player2Hand[Player2Card].CT, Player2Status, Player1Status, maxPlayer);
					CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection, Player2Break);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection, Player1Break);
				}
			} else {
				CardHelper::specialHandle(Player2Hand[Player2Card].CT, Player2Status, Player1Status, maxPlayer);
				CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection, Player2Break);
				CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection, Player1Break);
			}

			// Special case handle for 2 Player.
			if (maxPlayer == 2) {
				if (Player2Hand[Player2Card].CT == CardType::REVERSE || Player2Hand[Player2Card].CT == CardType::SKIP) {
					canContinue = true;
				}
			}

			RemoveCard(2);

			if (Player2Hand.size() == 0) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), currentPlayer);
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
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), 2, tempPlayer);
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = tempPlayer;
				} else if (PlayDirection == Direction::RIGHT) {
					char message [100];
					snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), 2, 1);
					Msg::DisplayPlayerSwitch(message);
					currentPlayer = 1;
				}
			}
			canContinue = false;
		}
	}

	// User cannot set, so draw a card.
	if (hDown & KEY_X) {
		AddCard(2);
	}
}


void MultiPlayScreen::Player3Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (Player3Break == true) {
		Player3Break = false;
		if (PlayDirection == Direction::LEFT) {
			if (maxPlayer > 3)	tempPlayer = 4;
			else	tempPlayer = 2;
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), 3, tempPlayer);
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = tempPlayer;
		} else if (PlayDirection == Direction::RIGHT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), 3, 2);
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 2;
		}
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
		if (Player3Hand[Player3Card].CT == TypeToPlay || Player3Hand[Player3Card].CC == ColorToPlay || Player3Hand[Player3Card].CT == CardType::WISH || Player3Hand[Player3Card].CT == CardType::PLUS4) {
			TypeToPlay = Player3Hand[Player3Card].CT;
			ColorToPlay = Player3Hand[Player3Card].CC;

			// Handle.
			if (PlayDirection == Direction::LEFT) {
				if (maxPlayer == 4) {
					CardHelper::specialHandle(Player3Hand[Player3Card].CT, Player3Status, Player4Status, maxPlayer);
					CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection, Player3Break);
					CardHelper::statusHandler(Player4Hand, Player4Status, Player4Status, PlayDirection, Player4Break);
				} else {
					CardHelper::specialHandle(Player3Hand[Player3Card].CT, Player3Status, Player1Status, maxPlayer);
					CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection, Player3Break);
					CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection, Player1Break);
				}
			} else {
				CardHelper::specialHandle(Player3Hand[Player3Card].CT, Player3Status, Player2Status, maxPlayer);
				CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection, Player3Break);
				CardHelper::statusHandler(Player2Hand, Player2Status, Player2Status, PlayDirection, Player2Break);
			}

			RemoveCard(3);

			if (Player3Hand.size() == 0) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), currentPlayer);
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
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), 3, tempPlayer);
				Msg::DisplayPlayerSwitch(message);
				currentPlayer = tempPlayer;
			} else if (PlayDirection == Direction::RIGHT) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), 3, 2);
				Msg::DisplayPlayerSwitch(message);
				currentPlayer = 2;
			}
		}
	}

	// User cannot set, so draw a card.
	if (hDown & KEY_X) {
		AddCard(3);
	}
}

void MultiPlayScreen::Player4Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (Player4Break == true) {
		Player4Break = false;
		if (PlayDirection == Direction::LEFT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), 4, 1);
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 1;
		} else if (PlayDirection == Direction::RIGHT) {
			char message [100];
			snprintf(message, sizeof(message), Lang::get("PLAYER_BREAK").c_str(), 4, 3);
			Msg::DisplayPlayerSwitch(message);
			currentPlayer = 3;
		}
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
		if (Player4Hand[Player4Card].CT == TypeToPlay || Player4Hand[Player4Card].CC == ColorToPlay || Player4Hand[Player4Card].CT == CardType::WISH || Player4Hand[Player4Card].CT == CardType::PLUS4) {
			TypeToPlay = Player4Hand[Player4Card].CT;
			ColorToPlay = Player4Hand[Player4Card].CC;

			// Handle.
			if (PlayDirection == Direction::LEFT) {
				CardHelper::specialHandle(Player4Hand[Player4Card].CT, Player4Status, Player1Status, maxPlayer);
				CardHelper::statusHandler(Player4Hand, Player4Status, Player4Status, PlayDirection, Player4Break);
				CardHelper::statusHandler(Player1Hand, Player1Status, Player1Status, PlayDirection, Player1Break);
			} else {
				CardHelper::specialHandle(Player4Hand[Player4Card].CT, Player4Status, Player3Status, maxPlayer);
				CardHelper::statusHandler(Player4Hand, Player4Status, Player4Status, PlayDirection, Player4Break);
				CardHelper::statusHandler(Player3Hand, Player3Status, Player3Status, PlayDirection, Player3Break);
			}

			RemoveCard(4);

			if (Player4Hand.size() == 0) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_WON").c_str(), currentPlayer);
				Msg::DisplayPlayerSwitch(message);
				Gui::screenBack();
				return;
			}
			if (Player4Card > (int)Player4Hand.size() -1) {
				Player4Card = (int)Player4Hand.size() - 1;
			}

			if (PlayDirection == Direction::LEFT) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), 4, 1);
				Msg::DisplayPlayerSwitch(message);
				currentPlayer = 1;
			} else if (PlayDirection == Direction::RIGHT) {
				char message [100];
				snprintf(message, sizeof(message), Lang::get("PLAYER_NEXT").c_str(), 4, 3);
				Msg::DisplayPlayerSwitch(message);
				currentPlayer = 3;
			}
		}
	}

	// User cannot set, so draw a card.
	if (hDown & KEY_X) {
		AddCard(4);
	}
}



void MultiPlayScreen::RoundLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (currentPlayer == 1) {
		Player1Logic(hDown, hHeld, touch);
	} else if (currentPlayer == 2) {
		Player2Logic(hDown, hHeld, touch);
	} else if (currentPlayer == 3) {
		Player3Logic(hDown, hHeld, touch);
	} else if (currentPlayer == 4) {
		Player4Logic(hDown, hHeld, touch);
	}
}