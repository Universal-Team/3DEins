/*
*   This file is part of Universal-Updater
*   Copyright (C) 2019 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, TotallyNotGuy, VoltZ
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

#include "gui/gui.hpp"

#include "screens/screenCommon.hpp"

#include <3ds.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stack>

C3D_RenderTarget* top;
C3D_RenderTarget* bottom;

C2D_TextBuf sizeBuf;
std::stack<std::unique_ptr<Screen>> screens;
C2D_SpriteSheet cards;
bool currentScreen = false;

// Clear Text.
void Gui::clearTextBufs(void)
{
	C2D_TextBufClear(sizeBuf);
}

// Initialize GUI.
Result Gui::init(void)
{
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	cards = C2D_SpriteSheetLoad("romfs:/gfx/cards.t3x");
	sizeBuf = C2D_TextBufNew(4096);
	return 0;
}

// Exit the whole GUI.
void Gui::exit(void)
{
	C2D_TextBufDelete(sizeBuf);
	C2D_SpriteSheetFree(cards);
	C2D_Fini();
	C3D_Fini();
}

void Gui::DrawCard(int key, int x, int y, float ScaleX, float ScaleY)
{
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, key), x, y, 0.5f, NULL, ScaleX, ScaleY);
}

// Animated Card Selector.
void Gui::DrawSelectedCard(int key, int x, int y, float ScaleX, float ScaleY)
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
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, 55), x, y, 0.5f, &tint, ScaleX, ScaleY);
	C2D_DrawImageAt(C2D_SpriteSheetGetImage(cards, key), x, y, 0.5f, NULL, ScaleX, ScaleY);
	timer += .030;
}


void Gui::DrawStringCentered(float x, float y, float size, u32 color, std::string Text, int maxWidth) {
	Gui::DrawString((currentScreen ? 200 : 160)+x-(std::min(maxWidth, (int)Gui::GetStringWidth(size, Text))/2), y, size, color, Text, maxWidth);
}

// Draw String or Text.
void Gui::DrawString(float x, float y, float size, u32 color, std::string Text, int maxWidth) {
	C2D_Text c2d_text;
	C2D_TextParse(&c2d_text, sizeBuf, Text.c_str());
	C2D_TextOptimize(&c2d_text);
	if(maxWidth == 0) {
		C2D_DrawText(&c2d_text, C2D_WithColor, x, y, 0.5f, size, size, color);
	} else {
		C2D_DrawText(&c2d_text, C2D_WithColor, x, y, 0.5f, std::min(size, size*(maxWidth/Gui::GetStringWidth(size, Text))), size, color);
	}
}


// Get String or Text Width.
float Gui::GetStringWidth(float size, std::string Text) {
	float width = 0;
	GetStringSize(size, &width, NULL, Text);
	return width;
}

// Get String or Text Size.
void Gui::GetStringSize(float size, float *width, float *height, std::string Text) {
	C2D_Text c2d_text;
	C2D_TextParse(&c2d_text, sizeBuf, Text.c_str());
	C2D_TextGetDimensions(&c2d_text, size, size, width, height);
}


// Get String or Text Height.
float Gui::GetStringHeight(float size, std::string Text) {
	float height = 0;
	GetStringSize(size, NULL, &height, Text.c_str());
	return height;
}

// Draw a Rectangle.
bool Gui::Draw_Rect(float x, float y, float w, float h, u32 color) {
	return C2D_DrawRectSolid(x, y, 0.5f, w, h, color);
}

// Mainloop the GUI.
void Gui::mainLoop(u32 hDown, u32 hHeld, touchPosition touch) {
	screens.top()->Draw();
	screens.top()->Logic(hDown, hHeld, touch);
}

// Set the current Screen.
void Gui::setScreen(std::unique_ptr<Screen> screen)
{
	screens.push(std::move(screen));
}

// Go a Screen back.
void Gui::screenBack()
{
	screens.pop();
}

// Select, on which Screen should be drawn.
void Gui::ScreenDraw(C3D_RenderTarget * screen)
{
	C2D_SceneBegin(screen);
	currentScreen = screen == top ? 1 : 0;
}

void Gui::DrawTop(void) {
	Gui::ScreenDraw(top);
	Gui::Draw_Rect(0, 0, 400, 30, C2D_Color32(220, 60, 0, 200));
	Gui::Draw_Rect(0, 30, 400, 180, C2D_Color32(220, 160, 0, 200));
	Gui::Draw_Rect(0, 210, 400, 30, C2D_Color32(220, 60, 0, 200));
}

void Gui::DrawBottom(void) {
	Gui::ScreenDraw(bottom);
	Gui::Draw_Rect(0, 0, 320, 30, C2D_Color32(220, 60, 0, 200));
	Gui::Draw_Rect(0, 30, 320, 180, C2D_Color32(220, 160, 0, 200));
	Gui::Draw_Rect(0, 210, 320, 30, C2D_Color32(220, 60, 0, 200));
}