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

extern bool isDay;

void GFX::DrawTop(bool useBars) {
	Gui::ScreenDraw(Top);
	if (useBars) {
		Gui::Draw_Rect(0, 0, 400, 30, Config::Bar);
		Gui::Draw_Rect(0, 30, 400, 180, Config::BG);
		Gui::Draw_Rect(0, 210, 400, 30, Config::Bar);
	} else {
		Gui::Draw_Rect(0, 0, 400, 240, Config::BG);
	}
}

// False actually only draws 1 bar on the top screen. Special case for the Game screen. xD
void GFX::DrawBottom(bool useBars) {
	Gui::ScreenDraw(Bottom);
	if (useBars) {
		Gui::Draw_Rect(0, 0, 320, 30, Config::Bar);
		Gui::Draw_Rect(0, 30, 320, 180, Config::BG);
		Gui::Draw_Rect(0, 210, 320, 30, Config::Bar);
	} else {
		Gui::Draw_Rect(0, 0, 320, 30, Config::Bar);
		Gui::Draw_Rect(0, 30, 320, 210, Config::BG);
	}
}

void GFX::DrawFileBrowseBG(bool isTop) {
	if (isTop == true) {
		Gui::ScreenDraw(Top);
		Gui::Draw_Rect(0, 0, 400, 27, Config::Bar);
		Gui::Draw_Rect(0, 27, 400, 31, Config::BG);
		Gui::Draw_Rect(0, 58, 400, 31, Config::Bar);
		Gui::Draw_Rect(0, 89, 400, 31, Config::BG);
		Gui::Draw_Rect(0, 120, 400, 31, Config::Bar);
		Gui::Draw_Rect(0, 151, 400, 31, Config::BG);
		Gui::Draw_Rect(0, 182, 400, 31, Config::Bar);
		Gui::Draw_Rect(0, 213, 400, 27, Config::BG);
	} else {
		Gui::ScreenDraw(Bottom);
		Gui::Draw_Rect(0, 0, 320, 27, Config::Bar);
		Gui::Draw_Rect(0, 27, 320, 31, Config::BG);
		Gui::Draw_Rect(0, 58, 320, 31, Config::Bar);
		Gui::Draw_Rect(0, 89, 320, 31, Config::BG);
		Gui::Draw_Rect(0, 120, 320, 31, Config::Bar);
		Gui::Draw_Rect(0, 151, 320, 31, Config::BG);
		Gui::Draw_Rect(0, 182, 320, 31, Config::Bar);
		Gui::Draw_Rect(0, 213, 320, 27, Config::BG);
	}
}

extern C2D_SpriteSheet cards;
extern C2D_SpriteSheet sprites;

void GFX::DrawSprite(int index, int x, int y, float ScaleX, float ScaleY) {
	Gui::DrawSprite(sprites, index, x, y, ScaleX, ScaleY);
}

void GFX::DrawCardSelector(int x, int y, float ScaleX, float ScaleY)
{
	static float timer         = 0.0f;
	float highlight_multiplier = fmax(0.0, fabs(fmod(timer, 1.0) - 0.5) / 0.5);
	u8 r                       = Config::Selector & 0xFF;
	u8 g                       = (Config::Selector >> 8) & 0xFF;
	u8 b                       = (Config::Selector >> 16) & 0xFF;
	u32 color = C2D_Color32(r + (255 - r) * highlight_multiplier, g + (255 - g) * highlight_multiplier, b + (255 - b) * highlight_multiplier, 255);
	C2D_ImageTint tint;
	C2D_SetImageTint(&tint, C2D_TopLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_TopRight, color, 1);
	C2D_SetImageTint(&tint, C2D_BotLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_BotRight, color, 1);
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, sprites_outline_idx), x, y, 0.5f, &tint, ScaleX, ScaleY);
	timer += .030;
}

void GFX::DrawButtonSelector(int x, int y, float ScaleX, float ScaleY, bool useSmall)
{
	static float timer         = 0.0f;
	float highlight_multiplier = fmax(0.0, fabs(fmod(timer, 1.0) - 0.5) / 0.5);
	u8 r                       = Config::Selector & 0xFF;
	u8 g                       = (Config::Selector >> 8) & 0xFF;
	u8 b                       = (Config::Selector >> 16) & 0xFF;
	u32 color = C2D_Color32(r + (255 - r) * highlight_multiplier, g + (255 - g) * highlight_multiplier, b + (255 - b) * highlight_multiplier, 255);
	C2D_ImageTint tint;
	C2D_SetImageTint(&tint, C2D_TopLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_TopRight, color, 1);
	C2D_SetImageTint(&tint, C2D_BotLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_BotRight, color, 1);
	if (useSmall) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, sprites_btnSelector2_idx), x, y, 0.5f, &tint, ScaleX, ScaleY);
	} else {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, sprites_btnSelector_idx), x, y, 0.5f, &tint, ScaleX, ScaleY);
	}
	timer += .030;
}

void GFX::DrawCard(CardType CT, int x, int y, CardColor CC, float ScaleX, float ScaleY)
{
	if (isDay == true) {
		Gui::DrawSprite(sprites, sprites_bruh_idx, x, y, ScaleX, ScaleY);
	} else if (isDay == false) {
		// Card Color.
		if (CC == CardColor::BLUE) {
			switch (CT) {
				case CardType::NUMBER_0:
					Gui::DrawSprite(cards, 0, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_1:
					Gui::DrawSprite(cards, 4, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_2:
					Gui::DrawSprite(cards, 8, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_3:
					Gui::DrawSprite(cards, 12, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_4:
					Gui::DrawSprite(cards, 16, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_5:
					Gui::DrawSprite(cards, 20, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_6:
					Gui::DrawSprite(cards, 24, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_7:
					Gui::DrawSprite(cards, 28, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_8:
					Gui::DrawSprite(cards, 32, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_9:
					Gui::DrawSprite(cards, 36, x, y, ScaleX, ScaleY);
					break;
				case CardType::SKIP:
					Gui::DrawSprite(cards, 40, x, y, ScaleX, ScaleY);
					break;
				case CardType::REVERSE:
					Gui::DrawSprite(cards, 44, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS2:
					Gui::DrawSprite(cards, 48, x, y, ScaleX, ScaleY);
					break;
				case CardType::WISH:
					Gui::DrawSprite(cards, 53, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS4:
					Gui::DrawSprite(cards, 58, x, y, ScaleX, ScaleY);
					break;
			}
		} else if (CC == CardColor::GREEN) {
			switch (CT) {
				case CardType::NUMBER_0:
					Gui::DrawSprite(cards, 1, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_1:
					Gui::DrawSprite(cards, 5, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_2:
					Gui::DrawSprite(cards, 9, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_3:
					Gui::DrawSprite(cards, 13, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_4:
					Gui::DrawSprite(cards, 17, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_5:
					Gui::DrawSprite(cards, 21, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_6:
					Gui::DrawSprite(cards, 25, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_7:
					Gui::DrawSprite(cards, 29, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_8:
					Gui::DrawSprite(cards, 33, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_9:
					Gui::DrawSprite(cards, 37, x, y, ScaleX, ScaleY);
					break;
				case CardType::SKIP:
					Gui::DrawSprite(cards, 41, x, y, ScaleX, ScaleY);
					break;
				case CardType::REVERSE:
					Gui::DrawSprite(cards, 45, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS2:
					Gui::DrawSprite(cards, 49, x, y, ScaleX, ScaleY);
					break;
				case CardType::WISH:
					Gui::DrawSprite(cards, 54, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS4:
					Gui::DrawSprite(cards, 59, x, y, ScaleX, ScaleY);
					break;
			}
		} else if (CC == CardColor::RED) {
			switch (CT) {
				case CardType::NUMBER_0:
					Gui::DrawSprite(cards, 2, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_1:
					Gui::DrawSprite(cards, 6, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_2:
					Gui::DrawSprite(cards, 10, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_3:
					Gui::DrawSprite(cards, 14, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_4:
					Gui::DrawSprite(cards, 18, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_5:
					Gui::DrawSprite(cards, 22, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_6:
					Gui::DrawSprite(cards, 26, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_7:
					Gui::DrawSprite(cards, 30, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_8:
					Gui::DrawSprite(cards, 34, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_9:
					Gui::DrawSprite(cards, 38, x, y, ScaleX, ScaleY);
					break;
				case CardType::SKIP:
					Gui::DrawSprite(cards, 42, x, y, ScaleX, ScaleY);
					break;
				case CardType::REVERSE:
					Gui::DrawSprite(cards, 46, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS2:
					Gui::DrawSprite(cards, 50, x, y, ScaleX, ScaleY);
					break;
				case CardType::WISH:
					Gui::DrawSprite(cards, 55, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS4:
					Gui::DrawSprite(cards, 60, x, y, ScaleX, ScaleY);
					break;
			}
		} else if (CC == CardColor::YELLOW) {
			switch (CT) {
				case CardType::NUMBER_0:
					Gui::DrawSprite(cards, 3, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_1:
					Gui::DrawSprite(cards, 7, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_2:
					Gui::DrawSprite(cards, 11, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_3:
					Gui::DrawSprite(cards, 15, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_4:
					Gui::DrawSprite(cards, 19, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_5:
					Gui::DrawSprite(cards, 23, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_6:
					Gui::DrawSprite(cards, 27, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_7:
					Gui::DrawSprite(cards, 31, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_8:
					Gui::DrawSprite(cards, 35, x, y, ScaleX, ScaleY);
					break;
				case CardType::NUMBER_9:
					Gui::DrawSprite(cards, 39, x, y, ScaleX, ScaleY);
					break;
				case CardType::SKIP:
					Gui::DrawSprite(cards, 43, x, y, ScaleX, ScaleY);
					break;
				case CardType::REVERSE:
					Gui::DrawSprite(cards, 47, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS2:
					Gui::DrawSprite(cards, 51, x, y, ScaleX, ScaleY);
					break;
				case CardType::WISH:
					Gui::DrawSprite(cards, 56, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS4:
					Gui::DrawSprite(cards, 61, x, y, ScaleX, ScaleY);
					break;
			}
		} else if (CC == CardColor::SPECIAL) {
			switch (CT) {
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
				case CardType::SKIP:
				case CardType::REVERSE:
				case CardType::PLUS2:
					break;
				case CardType::WISH:
					Gui::DrawSprite(cards, 52, x, y, ScaleX, ScaleY);
					break;
				case CardType::PLUS4:
					Gui::DrawSprite(cards, 57, x, y, ScaleX, ScaleY);
					break;
			}
		}
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