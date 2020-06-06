/*
*   This file is part of DSEins
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

#include "colors.hpp"
#include "gui.hpp"

#include <stack>
#include <vector>

std::stack<std::unique_ptr<Screen>> screens;
FILE* cardGFX; // The file for the cards combi.

void Gui::DrawScreen() {
	clearScreen(false, true);
	clearScreen(true, true);
	screens.top()->Draw();
}

void Gui::mainLoop(u16 hDown, touchPosition touch) {
	screens.top()->Logic(hDown, touch);
}

void Gui::setScreen(std::unique_ptr<Screen> screen) {
	screens.push(std::move(screen));
}

void Gui::screenBack() {
	screens.pop();
}

// Basic GUI Stuff.

void Gui::DrawTop(bool useBars) {
	if (useBars) {
		drawRectangle(0, 20, 256, 152, GREEN, true, false);
		drawRectangle(0, 0, 256, 20, DARK_GREEN, true, false);
		drawRectangle(0, 172, 256, 20, DARK_GREEN, true, false);
	} else {
		drawRectangle(0, 0, 256, 192, GREEN, true, false);
	}
}

void Gui::DrawBottom(bool useBars) {
	if (useBars) {
		drawRectangle(0, 20, 256, 152, GREEN, false, false);
		drawRectangle(0, 0, 256, 20, DARK_GREEN, false, false);
		drawRectangle(0, 172, 256, 20, DARK_GREEN, false, false);
	} else {
		drawRectangle(0, 0, 256, 192, GREEN, false, false);
	}
}

void Gui::clearScreen(bool top, bool layer) {
	drawRectangle(0, 0, 256, 192, CLEAR, top, layer);
}

// Load the card Graphics.
void Gui::loadGraphics() {
	// Open Cards combo's gfx file.
	if (cardGFX)	fclose(cardGFX);
	cardGFX = fopen("nitro:/graphics/cards.combo.gfx", "rb");
}


// Load the Card Sprite / Graphic from the combi gfx file.
Image Gui::loadCardSprite(CardType CT, CardColor CC) {
	int cardOffset = 0;

	switch(CT) {
		case CardType::NUMBER_0:
			cardOffset = 0;
			break;
		case CardType::NUMBER_1:
			cardOffset = 0x153C;
			break;
		case CardType::NUMBER_2:
			cardOffset = 0x2A78 ;
			break;
		case CardType::NUMBER_3:
			cardOffset = 0x3FB4;
			break;
		case CardType::NUMBER_4:
			cardOffset = 0x54F0;
			break;
		case CardType::NUMBER_5:
			cardOffset = 0x6A2C;
			break;
		case CardType::NUMBER_6:
			cardOffset = 0x7F68;
			break;
		case CardType::NUMBER_7:
			cardOffset = 0x94A4;
			break;
		case CardType::NUMBER_8:
			cardOffset = 0xA9E0;
			break;
		case CardType::NUMBER_9:
			cardOffset = 0xBF1C;
			break;
			// 0xD458 for "blank".
		case CardType::DRAW2:
			cardOffset = 0xE994;
			break;
			// 0xFED0 for "outline".
		case CardType::REVERSE:
			cardOffset = 0x1140C;
			break;
		case CardType::SKIP:
			cardOffset = 0x12948;
			break;
		case CardType::WILD:
			// Special cases for it, cause Color Black.
			if (CC == CardColor::COLOR_BLACK)	cardOffset = 0x153C0;
			else						cardOffset = 0x13E84;
			break;
		case CardType::DRAW4:
			// Special cases for it, cause Color Black.
			if (CC == CardColor::COLOR_BLACK)	cardOffset = 0x17E38;
			else						cardOffset = 0x168FC;
			break;
	}

	Image image = {0, 0};
	u16 palCount, palOfs;
	if (cardGFX) {
		fseek(cardGFX, cardOffset + 4, SEEK_SET);
		fread(&image.width, 1, 2, cardGFX);
		fread(&image.height, 1, 2, cardGFX);
		image.bitmap = std::vector<u8>(image.width*image.height);
		fread(image.bitmap.data(), 1, image.width*image.height, cardGFX);
		fread(&palCount, 1, 2, cardGFX);
		fread(&palOfs, 1, 2, cardGFX);
		image.palette = std::vector<u16>(palCount);
		fread(image.palette.data(), 2, palCount, cardGFX);
	}

	return image;
}

// Draw a card.
void Gui::DrawCard(CardType CT, CardColor CC, int x, int y, float ScaleX, float ScaleY, bool top, bool Layer) {
	Image cardImage = Gui::loadCardSprite(CT, CC); // Get Card Image.
	drawImageScaled(x, y, ScaleX, ScaleY, cardImage, top, Layer); // Draw Image.
}

// Draw a card from the Player's Hand.
void Gui::DrawPlayerCard(const std::vector<CardStruct> &hand, const int &card, int x, int y, float ScaleX, float ScaleY, bool top, bool layer) {
	Gui::DrawCard(hand[card].CT, hand[card].CC, x, y, ScaleX, ScaleY, top, layer);
}

// Draws the Card Selector.
void Gui::DrawCardSelector(int x, int y, float ScaleX, float ScaleY, bool top, bool Layer) {
	Image image = {0, 0};
	u16 palCount, palOfs;
	if (cardGFX) {
		fseek(cardGFX, 0xFED0 + 4, SEEK_SET);
		fread(&image.width, 1, 2, cardGFX);
		fread(&image.height, 1, 2, cardGFX);
		image.bitmap = std::vector<u8>(image.width*image.height);
		fread(image.bitmap.data(), 1, image.width*image.height, cardGFX);
		fread(&palCount, 1, 2, cardGFX);
		fread(&palOfs, 1, 2, cardGFX);
		image.palette = std::vector<u16>(palCount);
		fread(image.palette.data(), 2, palCount, cardGFX);
	}

	drawImageScaled(x, y, ScaleX, ScaleY, image, top, Layer); // Draw Image.
}