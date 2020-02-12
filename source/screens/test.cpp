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

#include "test.hpp"

#include <vector>

#define MAXSHOWNCARDS 5

// Player Hands and status.
extern std::vector<CardStruct> Player1Hand;
extern PlayerStatus Player1Status;
extern PlayerFeeling Player1Feeling;

extern std::vector<CardStruct> Player2Hand;
extern PlayerStatus Player2Status;
extern PlayerFeeling Player2Feeling;
/*
extern std::vector<CardStruct> Player3Hand;
extern PlayerStatus Player3Status;
extern PlayerFeeling Player3Feeling;

extern std::vector<CardStruct> Player4Hand;
extern PlayerStatus Player4Status;
extern PlayerFeeling Player4Feeling;
*/
// Table card.
extern CardType TypeToPlay;
extern CardColor ColorToPlay;

void Test::DisplayPlayerHand() const {
	if (currentPlayer == Player::PLAYER_1) {
		for (int i = 0; i < (int)Player1Hand.size(); i++) {
			if (Player1Card < MAXSHOWNCARDS) {
				GFX::DrawCard(Player1Hand[i].CT, 3 + (i * 65), 50, Player1Hand[i].CC);
			} else {
				GFX::DrawCard(Player1Hand[i+Player1Card-4].CT, 3 + (i * 65), 50, Player1Hand[i+Player1Card-4].CC);
			}
			if (i == Player1Card) {
				if (Player1Card < MAXSHOWNCARDS) {
					GFX::DrawSprite(sprites_pointer_idx, 19 + (i * 65), 78);
				} else {
					GFX::DrawSprite(sprites_pointer_idx, 19 + (4 * 65), 78);
				}
			}
		}
	} else if (currentPlayer == Player::PLAYER_2) {
		for (int i = 0; i < (int)Player2Hand.size(); i++) {
			if (Player2Card < MAXSHOWNCARDS) {
				GFX::DrawCard(Player2Hand[i].CT, 3 + (i * 65), 50, Player2Hand[i].CC);
			} else {
				GFX::DrawCard(Player2Hand[i+Player2Card-4].CT, 3 + (i * 65), 50, Player2Hand[i+Player2Card-4].CC);
			}
			if (i == Player2Card) {
				if (Player2Card < MAXSHOWNCARDS) {
					GFX::DrawSprite(sprites_pointer_idx, 19 + (i * 65), 78);
				} else {
					GFX::DrawSprite(sprites_pointer_idx, 19 + (4 * 65), 78);
				}
			}
		}
//	} else if (currentPlayer == Player::PLAYER_3) {
//		for (int i = 0; i < (int)Player3Hand.size(); i++) {
//			if (Player3Card < MAXSHOWNCARDS) {
//				GFX::DrawCard(Player3Hand[i].CT, 3 + (i * 65), 50, Player3Hand[i].CC);
//			} else {
//				GFX::DrawCard(Player3Hand[i+Player3Card-4].CT, 3 + (i * 65), 50, Player3Hand[i+Player3Card-4].CC);
//			}
//			if (i == Player3Card) {
//				if (Player3Card < MAXSHOWNCARDS) {
//					GFX::DrawSprite(sprites_pointer_idx, 19 + (i * 65), 78);
//				} else {
//					GFX::DrawSprite(sprites_pointer_idx, 19 + (4 * 65), 78);
//				}
//			}
//		}
//	} else if (currentPlayer == Player::PLAYER_4) {
//		for (int i = 0; i < (int)Player4Hand.size(); i++) {
//			if (Player4Card < MAXSHOWNCARDS) {
//				GFX::DrawCard(Player4Hand[i].CT, 3 + (i * 65), 50, Player4Hand[i].CC);
//			} else {
//				GFX::DrawCard(Player4Hand[i+Player4Card-4].CT, 3 + (i * 65), 50, Player4Hand[i+Player4Card-4].CC);
//			}
//			if (i == Player4Card) {
//				if (Player4Card < MAXSHOWNCARDS) {
//					GFX::DrawSprite(sprites_pointer_idx, 19 + (i * 65), 78);
//				} else {
//					GFX::DrawSprite(sprites_pointer_idx, 19 + (4 * 65), 78);
//				}
//			}
//		}
	}
}

void Test::DisplayPlayerHandSmall() const {
	if (currentPlayer == Player::PLAYER_1) {
		for (int i = 0; i < (int)Player1Hand.size(); i++) {
			GFX::DrawCard(Player1Hand[i].CT, 2 + (i * 18), 140, Player1Hand[i].CC, 0.8, 0.8);
		}
	} else if (currentPlayer == Player::PLAYER_2) {
		for (int i = 0; i < (int)Player2Hand.size(); i++) {
			GFX::DrawCard(Player2Hand[i].CT, 2 + (i * 18), 140, Player2Hand[i].CC, 0.8, 0.8);
		}
//	} else if (currentPlayer == Player::PLAYER_3) {
//		for (int i = 0; i < (int)Player3Hand.size(); i++) {
//			GFX::DrawCard(Player3Hand[i].CT, 2 + (i * 18), 140, Player3Hand[i].CC, 0.8, 0.8);
//		}
//	} else if (currentPlayer == Player::PLAYER_4) {
//		for (int i = 0; i < (int)Player4Hand.size(); i++) {
//			GFX::DrawCard(Player4Hand[i].CT, 2 + (i * 18), 140, Player4Hand[i].CC, 0.8, 0.8);
//		}
	}
}


void Test::Draw(void) const {
	GFX::DrawTop(false);
	// Draw Players & amount of cards.
	DrawPlayers();
	GFX::DrawCard(TypeToPlay, 170, 80, ColorToPlay);
	GFX::DrawBottom();
	if (currentPlayer == Player::PLAYER_1) {
		Gui::DrawStringCentered(0, 0, 0.7f, WHITE, Lang::get("ITS_PLAYER_1_TURN"));
	} else if (currentPlayer == Player::PLAYER_2) {
		Gui::DrawStringCentered(0, 0, 0.7f, WHITE, Lang::get("ITS_PLAYER_2_TURN"));
	} else if (currentPlayer == Player::PLAYER_3) {
		Gui::DrawStringCentered(0, 0, 0.7f, WHITE, Lang::get("ITS_PLAYER_3_TURN"));
	} else if (currentPlayer == Player::PLAYER_4) {
		Gui::DrawStringCentered(0, 0, 0.7f, WHITE, Lang::get("ITS_PLAYER_4_TURN"));
	}
	DisplayPlayerHand();
	DisplayPlayerHandSmall();
}

// TODO.
void Test::DrawPlayers() const {
	// Player 1.
	GFX::DrawPlayer(-5, 130, 0.9, 0.9, PlayerChar(Config::character), Player1Feeling);
	Gui::DrawString(90, 200, 0.6f, WHITE, std::to_string(Player1Hand.size()));
	// Player 2.
	GFX::DrawPlayer(-5, 0, 0.9, 0.9, PlayerChar(3), Player2Feeling);
	Gui::DrawString(90, 40, 0.6f, WHITE, std::to_string(Player2Hand.size()));
}
	
Test::Test() {
	// Clear Player Hands.
	Player1Hand.clear();
	Player2Hand.clear();

	// Randomize Table card.
	CardHelper::RandomizeTableCard();

	// Fill Player 1.
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);
	CardHelper::AddCard(Player::PLAYER_1);

	// Fill Player 2.
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
	CardHelper::AddCard(Player::PLAYER_2);
}

void Test::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	RoundLogic(hDown, hHeld, touch);

	// Always make it possible, to quit a game.
	if (hDown & KEY_START) {
		if (Msg::promptMsg2(Lang::get("QUIT_GAME"))) {
			Gui::screenBack();
			return;
		}
	}
}


// For the Player hand.
void Test::Player1Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_RIGHT) {
		if (Player1Card < (int)Player1Hand.size()-1) {
			Player1Card++;
		}
	}

	if (hDown & KEY_LEFT ) {
		if (Player1Card > 0) {
			Player1Card--;
		}
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical.
		if (Player1Hand[Player1Card].CT == TypeToPlay || Player1Hand[Player1Card].CC == ColorToPlay || Player1Hand[Player1Card].CT == CardType::WISH || Player1Hand[Player1Card].CT == CardType::PLUS4) {
			TypeToPlay = Player1Hand[Player1Card].CT;
			ColorToPlay = Player1Hand[Player1Card].CC;
			CardHelper::statusHandler(Player::PLAYER_1, Player1Status, Player1Hand[Player1Card].CT);
			// Special case for Pause / Return card.
			if (Player1Hand[Player1Card].CT == CardType::RETURN || Player1Hand[Player1Card].CT == CardType::PAUSE) {
				canContinue = true;
			}

			CardHelper::RemoveCard(Player::PLAYER_1, Player1Card);
			if (Player1Hand.size() == 0) {
				Msg::DisplayPlayerSwitch("Player 1 won!");
				Gui::screenBack();
				return;
			}
			if (Player1Card > (int)Player1Hand.size() -1) {
				Player1Card = (int)Player1Hand.size() - 1;
			}
			if (!canContinue) {
				Msg::DisplayPlayerSwitch("Player 1 has finished his round.\nPlayer 2: Continue!");
				currentPlayer = Player::PLAYER_2;
			}
			canContinue = false;
		}
	}

	// User cannot set, so draw a card.
	if (hDown & KEY_X) {
		CardHelper::AddCard(Player::PLAYER_1);
	}
}

void Test::Player2Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_RIGHT) {
		if (Player2Card < (int)Player2Hand.size()-1) {
			Player2Card++;
		}
	}

	if (hDown & KEY_LEFT ) {
		if (Player2Card > 0) {
			Player2Card--;
		}
	}

	if (hDown & KEY_A) {
		// Check if cardType or CardColor are identical.
		if (Player2Hand[Player2Card].CT == TypeToPlay || Player2Hand[Player2Card].CC == ColorToPlay || Player2Hand[Player2Card].CT == CardType::WISH || Player2Hand[Player2Card].CT == CardType::PLUS4) {
			TypeToPlay = Player2Hand[Player2Card].CT;
			ColorToPlay = Player2Hand[Player2Card].CC;
			CardHelper::statusHandler(Player::PLAYER_2, Player2Status, Player2Hand[Player2Card].CT);

			// Special case for Pause / Return card.
			if (Player2Hand[Player2Card].CT == CardType::RETURN || Player2Hand[Player2Card].CT == CardType::PAUSE) {
				canContinue = true;
			}

			CardHelper::RemoveCard(Player::PLAYER_2, Player2Card);
			if (Player2Hand.size() == 0) {
				Msg::DisplayPlayerSwitch("Player 2 won!");
				Gui::screenBack();
				return;
			}
			if (Player2Card > (int)Player2Hand.size() -1) {
				Player2Card = (int)Player2Hand.size() - 1;
			}
			if (!canContinue) {
				Msg::DisplayPlayerSwitch("Player 2 has finished his round.\nPlayer 1: Continue!");
				currentPlayer = Player::PLAYER_1;
			}
			canContinue = false;
		}
	}

	// User cannot set, so draw a card.
	if (hDown & KEY_X) {
		CardHelper::AddCard(Player::PLAYER_2);
	}
}

void Test::RoundLogic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (currentPlayer == Player::PLAYER_1) {
		Player1Logic(hDown, hHeld, touch);
	} else if (currentPlayer == Player::PLAYER_2) {
		Player2Logic(hDown, hHeld, touch);
	}
}