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

#include "charSelection.hpp"
#include "multiPlayScreen.hpp"

// Player char's.
int player1 = 0;
int player2 = 1;
int player3 = 2;
int player4 = 3;

extern int playerAmount;
extern int selectedMode;

extern bool touching(touchPosition touch, Structs::ButtonPos button);

CharSelection::CharSelection() {
	// Get Max amount of Players.
	maxPlayers = playerAmount;
}

// 4 Chars: StackZ, Carl, Isabel, Lea.
void CharSelection::Draw(void) const {
	GFX::DrawTop();
	Gui::DrawStringCentered(0, 0, 0.9f, Config::Text, "3DEins - " + Lang::get("CHAR_SELECTION"), 320);
	GFX::DrawPlayer(-5, 35, 1, 1, PlayerChar::STACKZ, PlayerFeeling(state));
	GFX::DrawPlayer(95, 35, 1, 1, PlayerChar::CARL, PlayerFeeling(state));
	GFX::DrawPlayer(195, 35, 1, 1, PlayerChar::ISABEL, PlayerFeeling(state));
	GFX::DrawPlayer(295, 35, 1, 1, PlayerChar::LEA, PlayerFeeling(state));

	if (currentPlayer != maxPlayers+1) {
		char message [100];
		snprintf(message, sizeof(message), Lang::get("PLAYER_SELECT").c_str(), currentPlayer);
		Gui::DrawStringCentered(0, 216, 0.7f, Config::Text, message);
	} else {
		Gui::DrawStringCentered(0, 216, 0.7f, Config::Text, Lang::get("ALL_PLAYER_READY"));
	}

	Gui::Draw_Rect(10, 160, 80, 30, Config::Button);
	Gui::Draw_Rect(110, 160, 80, 30, Config::Button);
	Gui::Draw_Rect(210, 160, 80, 30, Config::Button);
	Gui::Draw_Rect(310, 160, 80, 30, Config::Button);
	GFX::DrawButtonSelector(10 + (Selection * 100), 160, 1, 1, true);

	Gui::DrawString(25, 165, 0.7f, Config::Text, "StackZ");
	Gui::DrawString(133, 165, 0.7f, Config::Text, "Carl");
	Gui::DrawString(227, 165, 0.7f, Config::Text, "Isabel");
	Gui::DrawString(332, 165, 0.7f, Config::Text, "Lea");

	GFX::DrawBottom();
}

void CharSelection::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack();
		return;
	}

	if (hDown & KEY_A) {
		if (allSelected == true) {
			if (selectedMode == 1) {
				Gui::setScreen(std::make_unique<MultiPlayScreen>());
			}
		}

		if (currentPlayer != maxPlayers+1) {
			if (currentPlayer == 1) {
				player1 = Selection;
			} else if (currentPlayer == 2) {
				player2 = Selection;
			} else if (currentPlayer == 3) {
				player3 = Selection;
			} else if (currentPlayer == 4) {
				player4 = Selection;
			}
			currentPlayer++;
		}

		if (currentPlayer == maxPlayers+1) {
			allSelected = true;
		}

	}

	if (hDown & KEY_R) {
		if (state < 4)	state++;
	}

	if (hDown & KEY_L) {
		if (state > 0)	state--;
	}

	if (hDown & KEY_RIGHT) {
		if (Selection < 3)	Selection++;
	}

	if (hDown & KEY_LEFT) {
		if (Selection > 0)	Selection--;
	}

	if (hHeld & KEY_SELECT) {
		Msg::HelperBox(Lang::get("CHAR_SELECTION_INSTR"));
	}
}