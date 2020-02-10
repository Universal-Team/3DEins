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

void GFX::DrawTop(void) {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 30, C2D_Color32(220, 60, 0, 200));
	Gui::Draw_Rect(0, 30, 400, 180, C2D_Color32(220, 160, 0, 200));
	Gui::Draw_Rect(0, 210, 400, 30, C2D_Color32(220, 60, 0, 200));
}

void GFX::DrawBottom(void) {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 30, C2D_Color32(220, 60, 0, 200));
	Gui::Draw_Rect(0, 30, 320, 180, C2D_Color32(220, 160, 0, 200));
	Gui::Draw_Rect(0, 210, 320, 30, C2D_Color32(220, 60, 0, 200));
}

extern C2D_SpriteSheet cards;

void GFX::DrawCard(CardType CT, int x, int y, CardColor CC, float ScaleX, float ScaleY)
{
	if (CC == CardColor::GREEN) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(0, 200, 0, 255));
	} else if (CC == CardColor::BLUE) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(0, 200, 200, 255));
	} else if (CC == CardColor::YELLOW) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(200, 200, 0, 255));
	} else if (CC == CardColor::RED) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(200, 0, 0, 255));
	} else if (CC == CardColor::SPECIAL) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(0, 0, 0, 255));
	}

	// Card Type.
	if (CT == CardType::NUMBER_0) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 0), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_1) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 1), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_2) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 2), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_3) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 3), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_4) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 4), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_5) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 5), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_6) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 6), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_7) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 7), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_8) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 8), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_9) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 9), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::PAUSE) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 10), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::RETURN) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 11), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::PLUS2) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 12), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::WISH) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 13), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::PLUS4) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 14), x, y, 0.5f, NULL, ScaleX, ScaleY);
	}
}

// Animated Card Selector.
void GFX::DrawSelectedCard(CardType CT, int x, int y, CardColor CC, float ScaleX, float ScaleY)
{
	static float timer         = 0.0f;
	float highlight_multiplier = fmax(0.0, fabs(fmod(timer, 1.0) - 0.5) / 0.5);
	u8 r                       = C2D_Color32(200, 0, 0, 255) & 0xFF;
	u8 g                       = (C2D_Color32(200, 0, 0, 255) >> 8) & 0xFF;
	u8 b                       = (C2D_Color32(200, 0, 0, 255) >> 16) & 0xFF;
	u32 color = C2D_Color32(r + (255 - r) * highlight_multiplier, g + (255 - g) * highlight_multiplier, b + (255 - b) * highlight_multiplier, 255);
	C2D_ImageTint tint;
	C2D_SetImageTint(&tint, C2D_TopLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_TopRight, color, 1);
	C2D_SetImageTint(&tint, C2D_BotLeft, color, 1);
	C2D_SetImageTint(&tint, C2D_BotRight, color, 1);

	// Draw Rectangle for the card.
	if (CC == CardColor::GREEN) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(0, 200, 0, 255));
	} else if (CC == CardColor::BLUE) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(0, 200, 200, 255));
	} else if (CC == CardColor::YELLOW) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(200, 200, 0, 255));
	} else if (CC == CardColor::RED) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(200, 0, 0, 255));
	} else if (CC == CardColor::SPECIAL) {
		C2D_DrawRectSolid(x+2, y+3, 0.5f, 54*ScaleX-5, 80*ScaleY-5, C2D_Color32(0, 0, 0, 255));
	}

	// Draw Card & Outline.
	// Card Type.
	if (CT == CardType::NUMBER_0) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 0), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_1) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 1), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_2) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 2), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_3) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 3), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_4) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 4), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_5) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 5), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_6) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 6), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_7) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 7), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_8) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 8), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::NUMBER_9) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 9), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::PAUSE) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 10), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::RETURN) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 11), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::PLUS2) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 12), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::WISH) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 13), x, y, 0.5f, NULL, ScaleX, ScaleY);
	} else if (CT == CardType::PLUS4) {
		C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 14), x, y, 0.5f, NULL, ScaleX, ScaleY);
	}

	C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 16), x, y, 0.5f, &tint, ScaleX, ScaleY);
	timer += .030;
}