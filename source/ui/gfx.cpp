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

#include "_3DEins_Core.h"
#include "config.hpp"
#include "coreHelper.hpp"
#include "gfx.hpp"
#include "screenState.hpp"

#include <stack>

extern std::unique_ptr<Config> config;

void GFX::DrawTop(bool useBars) {
	Gui::ScreenDraw(Top);
	if (useBars) {
		Gui::Draw_Rect(0, 0, 400, 30, config->barColor());
		Gui::Draw_Rect(0, 30, 400, 180, config->bgColor());
		Gui::Draw_Rect(0, 210, 400, 30, config->barColor());
	} else {
		Gui::Draw_Rect(0, 0, 400, 240, config->bgColor());
	}
}

// False actually only draws 1 bar on the top screen. Special case for the Game screen. xD
void GFX::DrawBottom(bool useBars) {
	Gui::ScreenDraw(Bottom);
	if (useBars) {
		Gui::Draw_Rect(0, 0, 320, 30, config->barColor());
		Gui::Draw_Rect(0, 30, 320, 180, config->bgColor());
		Gui::Draw_Rect(0, 210, 320, 30, config->barColor());
	} else {
		Gui::Draw_Rect(0, 0, 320, 30, config->barColor());
		Gui::Draw_Rect(0, 30, 320, 210, config->bgColor());
	}
}

void GFX::DrawFileBrowseBG(bool isTop) {
	if (isTop == true) {
		Gui::ScreenDraw(Top);
		Gui::Draw_Rect(0, 0, 400, 27, C2D_Color32(220, 60, 0, 255));
		Gui::Draw_Rect(0, 27, 400, 31, C2D_Color32(220, 160, 0, 255));
		Gui::Draw_Rect(0, 58, 400, 31, C2D_Color32(220, 60, 0, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 89, 400, 31, C2D_Color32(220, 160, 0, 255));
		Gui::Draw_Rect(0, 120, 400, 31, C2D_Color32(220, 60, 0, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 151, 400, 31, C2D_Color32(220, 160, 0, 255));
		Gui::Draw_Rect(0, 182, 400, 31, C2D_Color32(220, 60, 0, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 213, 400, 27, C2D_Color32(220, 60, 0, 255));
	} else {
		Gui::ScreenDraw(Bottom);
		Gui::Draw_Rect(0, 0, 320, 27, C2D_Color32(220, 60, 0, 255));
		Gui::Draw_Rect(0, 27, 320, 31, C2D_Color32(220, 160, 0, 255));
		Gui::Draw_Rect(0, 58, 320, 31, C2D_Color32(220, 60, 0, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 89, 320, 31, C2D_Color32(220, 160, 0, 255));
		Gui::Draw_Rect(0, 120, 320, 31, C2D_Color32(220, 60, 0, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 151, 320, 31, C2D_Color32(220, 160, 0, 255));
		Gui::Draw_Rect(0, 182, 320, 31, C2D_Color32(220, 60, 0, 255) & C2D_Color32(255, 255, 255, 200));
		Gui::Draw_Rect(0, 213, 320, 27, C2D_Color32(220, 60, 0, 255));
	}
}

extern C2D_SpriteSheet cards;
extern C2D_SpriteSheet characters;
extern C2D_SpriteSheet sprites;

void GFX::DrawSprite(int index, int x, int y, float ScaleX, float ScaleY) {
	Gui::DrawSprite(sprites, index, x, y, ScaleX, ScaleY);
}

void GFX::DrawSelectedPlayer(int x, int y, float ScaleX, float ScaleY) {
	C2D_ImageTint tint;
	C2D_SetImageTint(&tint, C2D_TopLeft, config->selectorColor(), 0.5f);
	C2D_SetImageTint(&tint, C2D_TopRight, config->selectorColor(), 0.5f);
	C2D_SetImageTint(&tint, C2D_BotLeft, config->selectorColor(), 0.5f);
	C2D_SetImageTint(&tint, C2D_BotRight, config->selectorColor(), 0.5f);
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, sprites_selectedPlayer_idx), x, y, 0.5f, &tint, ScaleX, ScaleY);
}

void GFX::DrawCardSelector(int x, int y, float ScaleX, float ScaleY) {
	static float timer			= 0.0f;
	float highlight_multiplier	= fmax(0.0, fabs(fmod(timer, 1.0) - 0.5) / 0.5);
	u8 r						= config->selectorColor() & 0xFF;
	u8 g						= (config->selectorColor() >> 8) & 0xFF;
	u8 b						= (config->selectorColor() >> 16) & 0xFF;
	u32 color = C2D_Color32(r + (255 - r) * highlight_multiplier, g + (255 - g) * highlight_multiplier, b + (255 - b) * highlight_multiplier, 255);
	C2D_ImageTint tint;
	C2D_SetImageTint(&tint, C2D_TopLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_TopRight, color, 1);
	C2D_SetImageTint(&tint, C2D_BotLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_BotRight, color, 1);
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(sprites, sprites_outline_idx), x, y, 0.5f, &tint, ScaleX, ScaleY);
	timer += .030;
}

void GFX::DrawButtonSelector(int x, int y, float ScaleX, float ScaleY, bool useSmall) {
	static float timer			= 0.0f;
	float highlight_multiplier	= fmax(0.0, fabs(fmod(timer, 1.0) - 0.5) / 0.5);
	u8 r						= config->selectorColor() & 0xFF;
	u8 g						= (config->selectorColor() >> 8) & 0xFF;
	u8 b						= (config->selectorColor() >> 16) & 0xFF;
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

void GFX::DrawCard(CardType CT, int x, int y, CardColor CC, float ScaleX, float ScaleY) {
	// Special case "Bruh".
	#ifdef _USE_SPECIAL_CARD
		if (CT == CardType::SPECIAL) {
			Gui::DrawSprite(sprites, sprites_bruh_idx, x, y, ScaleX, ScaleY);
			return;
		}
	#endif

	// Card Color.
	if (CC == CardColor::COLOR_BLUE) {
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
			case CardType::DRAW2:
				Gui::DrawSprite(cards, 48, x, y, ScaleX, ScaleY);
				break;
			case CardType::WILD:
				Gui::DrawSprite(cards, 53, x, y, ScaleX, ScaleY);
				break;
			case CardType::DRAW4:
				Gui::DrawSprite(cards, 58, x, y, ScaleX, ScaleY);
				break;
			#ifdef _USE_SPECIAL_CARD
			case CardType::SPECIAL:
				break;
			#endif
		}
	} else if (CC == CardColor::COLOR_GREEN) {
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
			case CardType::DRAW2:
				Gui::DrawSprite(cards, 49, x, y, ScaleX, ScaleY);
				break;
			case CardType::WILD:
				Gui::DrawSprite(cards, 54, x, y, ScaleX, ScaleY);
				break;
			case CardType::DRAW4:
				Gui::DrawSprite(cards, 59, x, y, ScaleX, ScaleY);
				break;
			#ifdef _USE_SPECIAL_CARD
			case CardType::SPECIAL:
				break;
			#endif
		}
	} else if (CC == CardColor::COLOR_RED) {
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
			case CardType::DRAW2:
				Gui::DrawSprite(cards, 50, x, y, ScaleX, ScaleY);
				break;
			case CardType::WILD:
				Gui::DrawSprite(cards, 55, x, y, ScaleX, ScaleY);
				break;
			case CardType::DRAW4:
				Gui::DrawSprite(cards, 60, x, y, ScaleX, ScaleY);
				break;
			#ifdef _USE_SPECIAL_CARD
			case CardType::SPECIAL:
				break;
			#endif
		}
	} else if (CC == CardColor::COLOR_YELLOW) {
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
			case CardType::DRAW2:
				Gui::DrawSprite(cards, 51, x, y, ScaleX, ScaleY);
				break;
			case CardType::WILD:
				Gui::DrawSprite(cards, 56, x, y, ScaleX, ScaleY);
				break;
			case CardType::DRAW4:
				Gui::DrawSprite(cards, 61, x, y, ScaleX, ScaleY);
				break;
			#ifdef _USE_SPECIAL_CARD
			case CardType::SPECIAL:
				break;
			#endif
		}
	} else if (CC == CardColor::COLOR_BLACK) {
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
			case CardType::DRAW2:
				break;
			case CardType::WILD:
				Gui::DrawSprite(cards, 52, x, y, ScaleX, ScaleY);
				break;
			case CardType::DRAW4:
				Gui::DrawSprite(cards, 57, x, y, ScaleX, ScaleY);
				break;
			#ifdef _USE_SPECIAL_CARD
			case CardType::SPECIAL:
				break;
			#endif
		}
	}
}

void GFX::DrawPlayerCard(const std::vector<CardStruct> &hand, const int &card, int x, int y, float ScaleX, float ScaleY) {
	DrawCard(hand[card].CT, x, y, hand[card].CC, ScaleX, ScaleY);
}

void GFX::DrawChar(int image, int x, int y, float ScaleX, float ScaleY) {
	Gui::DrawSprite(characters, image, x, y, ScaleX, ScaleY);
}

void GFX::DrawPlayer(int x, int y, float ScaleX, float ScaleY, int player) {
	switch (player) {
		case 0:
			DrawChar(chars_char1_idx, x, y, ScaleX, ScaleY);
			break;
		case 1:
			DrawChar(chars_char2_idx, x, y, ScaleX, ScaleY);
			break;
		case 2:
			DrawChar(chars_char3_idx, x, y, ScaleX, ScaleY);
			break;
		case 3:
			DrawChar(chars_char4_idx, x, y, ScaleX, ScaleY);
			break;
		case 4:
			DrawChar(chars_char5_idx, x, y, ScaleX, ScaleY);
			break;
		case 5:
			DrawChar(chars_char6_idx, x, y, ScaleX, ScaleY);
			break;
		case 6:
			DrawChar(chars_char7_idx, x, y, ScaleX, ScaleY);
			break;
		case 7:
			DrawChar(chars_char8_idx, x, y, ScaleX, ScaleY);
			break;
	}
}

std::unique_ptr<ScreenState> screenS;
extern std::stack<std::unique_ptr<Screen>> screens;

// Main Logic.
void GFX::Main(u32 hDown, u32 hHeld, touchPosition touch) {
	if (screenS != nullptr) {
		if (screenS->isUsed) {
			DrawTop();
			Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 190));
			screenS->DrawStateTop();
			DrawBottom();
			Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 190));
			screenS->DrawStateBottom();
			screenS->StateLogic(hDown, hHeld, touch);
		} else {
			screens.top()->Draw();
			screens.top()->Logic(hDown, hHeld, touch);
		}
	} else {
		screens.top()->Draw();
		screens.top()->Logic(hDown, hHeld, touch);
	}
}

// TODO: Change to "Lang::get(...)"?
void GFX::Button(const ButtonStruct btn) {
	Gui::Draw_Rect(btn.X, btn.Y, btn.xSize, btn.ySize, config->buttonColor());
	Gui::DrawStringCentered(btn.X - 160 + (btn.xSize/2), btn.Y + (btn.ySize/2) - 10, 0.6f, config->textColor(), Lang::get(btn.Text), btn.X-10, btn.Y-5);
}