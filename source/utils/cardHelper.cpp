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

#include "cardHelper.hpp"
#include "common.hpp"
#include "structs.hpp"

// Player Targets and status.
std::vector<CardStruct> Player1Hand;
PlayerStatus Player1Status = PlayerStatus::NORMAL;
std::vector<CardStruct> Player2Hand;
PlayerStatus Player2Status = PlayerStatus::NORMAL;
std::vector<CardStruct> Player3Hand;
PlayerStatus Player3Status = PlayerStatus::NORMAL;
std::vector<CardStruct> Player4Hand;
PlayerStatus Player4Status = PlayerStatus::NORMAL;
// Table card.
CardColor ColorToPlay; // The color which needs to be played.
CardType TypeToPlay; // The type which needs to be played.

void CardHelper::RemoveCard(Player player, int pos) {
	if (player == Player::PLAYER_1) {
		Player1Hand.erase(Player1Hand.begin()+pos);
	} else if (player == Player::PLAYER_2) {
		Player2Hand.erase(Player2Hand.begin()+pos);
	} else if (player == Player::PLAYER_3) {
		Player3Hand.erase(Player3Hand.begin()+pos);
	} else if (player == Player::PLAYER_4) {
		Player4Hand.erase(Player4Hand.begin()+pos);
	}
}

// Randomize Table card.
void CardHelper::RandomizeTableCard(void) {
	TypeToPlay = CardType(rand() % 12 + 0); // 12 because 13 & 14 are Wish & Plus 4 cards.
	ColorToPlay = CardColor(rand() % MAXCOLOR + 0);
}

void CardHelper::AddCard(Player player) {
	CardType Card = CardType(rand() % MAXCARDTYPE + 0);
	CardColor Color = CardColor(rand() % MAXCOLOR + 0);
	// Checks for Wish & +4.
	if (Card == CardType::WISH || Card == CardType::PLUS4) {
		Color = CardColor::SPECIAL;
	}

	if (player == Player::PLAYER_1) {
		Player1Hand.push_back({Card, Color});
	} else if (player == Player::PLAYER_2) {
		Player2Hand.push_back({Card, Color});
	} else if (player == Player::PLAYER_3) {
		Player3Hand.push_back({Card, Color});
	} else if (player == Player::PLAYER_4) {
		Player4Hand.push_back({Card, Color});
	}
}

std::vector<Structs::ButtonPos> colorPos = {
	{20, 40, 100, 60}, // Red.
	{200, 40, 100, 60}, // Blue.
	{20, 110, 100, 60}, // Yellow.
	{200, 110, 100, 60}, // Green.
};

extern touchPosition touch;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

CardColor CardHelper::wishFunction() {
	s32 selection = 0;
	while(1)
	{
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, BLACK);
		C2D_TargetClear(Bottom, BLACK);
		GFX::DrawTop();
		Gui::Draw_Rect(0, 80, 400, 80, C2D_Color32(220, 60, 0, 200));
		Gui::DrawStringCentered(0, (240-Gui::GetStringHeight(0.7f, Lang::get("SELECT_COLOR")))/2, 0.7f, WHITE, Lang::get("SELECT_COLOR"), 390, 70);
		GFX::DrawBottom();
		// Draw Color Selection.
		Gui::Draw_Rect(20, 40, 100, 60, Config::Red);
		Gui::Draw_Rect(200, 40, 100, 60, Config::Blue);
		Gui::Draw_Rect(20, 110, 100, 60, Config::Yellow);
		Gui::Draw_Rect(200, 110, 100, 60, Config::Green);
		GFX::DrawSprite(sprites_pointer_idx, colorPos[selection].x+50, colorPos[selection].y+25);
		C3D_FrameEnd(0);
		// Selection part.
		gspWaitForVBlank();
		hidScanInput();
		hidTouchRead(&touch);

		if(hidKeysDown() & KEY_UP) {
			if (selection == 2)	selection -= 2;
			else if (selection == 3)	selection -= 2;
		} else if(hidKeysDown() & KEY_DOWN) {
			if (selection == 0)	selection += 2;
			else if (selection == 1)	selection += 2;
		}
		if(hidKeysDown() & KEY_LEFT) {
			if (selection > 0)	selection--;
		} else if(hidKeysDown() & KEY_RIGHT) {
			if (selection < 3)	selection++;
		}

		if (hidKeysDown() & KEY_A) {
			if (selection == 0) {
				return CardColor::RED;
			} else if (selection == 1) {
				return CardColor::BLUE;
			} else if (selection == 2) {
				return CardColor::YELLOW;
			} else if (selection == 3) {
				return CardColor::GREEN;
			}
		}

		if (hidKeysDown() & KEY_TOUCH) {
			if (touching(touch, colorPos[0])) {
				return CardColor::RED;
			} else if (touching(touch, colorPos[1])) {
				return CardColor::BLUE;
			} else if (touching(touch, colorPos[2])) {
				return CardColor::YELLOW;
			} else if (touching(touch, colorPos[3])) {
				return CardColor::GREEN;
			}
		}
	}
}

// TODO.
void CardHelper::DrawEffect(Player player, CardType card) {
	if (player == Player::PLAYER_1) {
		switch(card) {
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
			case CardType::PLUS2:
				break;
			case CardType::PLUS4:
				break;
			case CardType::WISH:
				break;
			case CardType::PAUSE:
				break;
			case CardType::RETURN:
				break;
		}
	}
}

// TODO: Status handling like +2, +4, Wish etc.
void CardHelper::statusHandler(Player player, PlayerStatus status, CardType card) {
	specialHandle(player, card); // Set the Status with the special Handle function.

	// Do the actual status part. TODO.
}

void CardHelper::specialHandle(Player player, CardType card) {
	if (player == Player::PLAYER_1) {
		switch(card) {
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
			case CardType::PLUS2:
				AddCard(Player::PLAYER_2);
				AddCard(Player::PLAYER_2);
				break;
			case CardType::PLUS4:
				AddCard(Player::PLAYER_2);
				AddCard(Player::PLAYER_2);
				AddCard(Player::PLAYER_2);
				AddCard(Player::PLAYER_2);
				ColorToPlay = wishFunction();
				break;
			case CardType::WISH:
				ColorToPlay = wishFunction();
				break;
			case CardType::PAUSE:
				// The Pause function.
				break;
			case CardType::RETURN:
				// The Return function.
				break;
		}
	} else if (player == Player::PLAYER_2) {
		switch(card) {
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
			case CardType::PLUS2:
				AddCard(Player::PLAYER_1);
				AddCard(Player::PLAYER_1);
				break;
			case CardType::PLUS4:
				AddCard(Player::PLAYER_1);
				AddCard(Player::PLAYER_1);
				AddCard(Player::PLAYER_1);
				AddCard(Player::PLAYER_1);
				ColorToPlay = wishFunction();
				break;
			case CardType::WISH:
				ColorToPlay = wishFunction();
				break;
			case CardType::PAUSE:
				// The Pause function.
				break;
			case CardType::RETURN:
				// The Return function.
				break;
		}
	}
}