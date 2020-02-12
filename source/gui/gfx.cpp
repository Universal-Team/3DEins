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
#include "config.hpp"

void GFX::DrawTop(bool useBars) {
	Gui::ScreenDraw(Top);
	if (useBars) {
		Gui::Draw_Rect(0, 0, 400, 30, C2D_Color32(220, 60, 0, 200));
		Gui::Draw_Rect(0, 30, 400, 180, C2D_Color32(220, 160, 0, 200));
		Gui::Draw_Rect(0, 210, 400, 30, C2D_Color32(220, 60, 0, 200));
	} else {
		Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(220, 160, 0, 200));
	}
}

void GFX::DrawBottom(void) {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 30, C2D_Color32(220, 60, 0, 200));
	Gui::Draw_Rect(0, 30, 320, 180, C2D_Color32(220, 160, 0, 200));
	Gui::Draw_Rect(0, 210, 320, 30, C2D_Color32(220, 60, 0, 200));
}

extern C2D_SpriteSheet cards;
extern C2D_SpriteSheet sprites;

void GFX::DrawSprite(int index, int x, int y, float ScaleX, float ScaleY) {
	Gui::DrawSprite(sprites, index, x, y, ScaleX, ScaleY);
}

void GFX::DrawCard(CardType CT, int x, int y, CardColor CC, float ScaleX, float ScaleY)
{
	// Card Color.
	switch (CC) {
		case CardColor::GREEN:
			C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, Config::Green);
			break;
		case CardColor::BLUE:
			C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, Config::Blue);
			break;
		case CardColor::YELLOW:
			C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, Config::Yellow);
			break;
		case CardColor::RED:
			C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, Config::Red);
			break;
		case CardColor::SPECIAL:
			C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(0, 0, 0, 255));
			break;
	}

	// Card Type.
	switch (CT) {
		case CardType::NUMBER_0:
			Gui::DrawSprite(cards, 0, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_1:
			Gui::DrawSprite(cards, 1, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_2:
			Gui::DrawSprite(cards, 2, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_3:
			Gui::DrawSprite(cards, 3, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_4:
			Gui::DrawSprite(cards, 4, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_5:
			Gui::DrawSprite(cards, 5, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_6:
			Gui::DrawSprite(cards, 6, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_7:
			Gui::DrawSprite(cards, 7, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_8:
			Gui::DrawSprite(cards, 8, x, y, ScaleX, ScaleY);
			break;
		case CardType::NUMBER_9:
			Gui::DrawSprite(cards, 9, x, y, ScaleX, ScaleY);
			break;
		case CardType::PAUSE:
			Gui::DrawSprite(cards, 10, x, y, ScaleX, ScaleY);
			break;
		case CardType::RETURN:
			Gui::DrawSprite(cards, 11, x, y, ScaleX, ScaleY);
			break;
		case CardType::PLUS2:
			Gui::DrawSprite(cards, 12, x, y, ScaleX, ScaleY);
			break;
		case CardType::WISH:
			Gui::DrawSprite(cards, 13, x, y, ScaleX, ScaleY);
			break;
		case CardType::PLUS4:
			Gui::DrawSprite(cards, 14, x, y, ScaleX, ScaleY);
			break;
	}
}

void GFX::DrawPlayer(int x, int y, float ScaleX, float ScaleY, PlayerChar player, PlayerFeeling state) {
	if (player == PlayerChar::STACKZ) {
		switch (state) {
			case PlayerFeeling::NORMAL:
				DrawSprite(sprites_char1_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::PROUD:
				DrawSprite(sprites_proud1_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::ANGRY:
				DrawSprite(sprites_angry1_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::SMILE:
				DrawSprite(sprites_smile1_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::SIGH:
				DrawSprite(sprites_sigh1_idx, x, y, ScaleX, ScaleY);
				break;
		}
	} else if (player == PlayerChar::CARL) {
		switch (state) {
			case PlayerFeeling::NORMAL:
				DrawSprite(sprites_char2_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::PROUD:
				DrawSprite(sprites_proud2_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::ANGRY:
				DrawSprite(sprites_angry2_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::SMILE:
				DrawSprite(sprites_smile2_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::SIGH:
				DrawSprite(sprites_sigh2_idx, x, y, ScaleX, ScaleY);
				break;
		}
	} else if (player == PlayerChar::ISABEL) {
		switch (state) {
			case PlayerFeeling::NORMAL:
				DrawSprite(sprites_char3_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::PROUD:
				DrawSprite(sprites_proud3_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::ANGRY:
				DrawSprite(sprites_angry3_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::SMILE:
				DrawSprite(sprites_smile3_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::SIGH:
				DrawSprite(sprites_sigh3_idx, x, y, ScaleX, ScaleY);
				break;
		}
	} else if (player == PlayerChar::LEA) {
		switch (state) {
			case PlayerFeeling::NORMAL:
				DrawSprite(sprites_char4_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::PROUD:
				DrawSprite(sprites_proud4_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::ANGRY:
				DrawSprite(sprites_angry4_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::SMILE:
				DrawSprite(sprites_smile4_idx, x, y, ScaleX, ScaleY);
				break;
			case PlayerFeeling::SIGH:
				DrawSprite(sprites_sigh4_idx, x, y, ScaleX, ScaleY);
				break;
		}
	}
}