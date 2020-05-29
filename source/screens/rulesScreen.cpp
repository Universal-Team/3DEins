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

#include "config.hpp"
#include "coreHelper.hpp"
#include "rulesScreen.hpp"

extern std::unique_ptr<Config> config;
extern bool touching(touchPosition touch, Structs::ButtonPos button);

#ifdef _USE_SPECIAL_CARD
#define MAXRULES	15
#else
#define MAXRULES	14
#endif

void RulesScreen::DrawDescription(void) const {
	switch (rulePage) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			Gui::DrawStringCentered(0, 170, 0.7f, config->textColor(), Lang::get("NUMBER_CARD"), 400);
			break;
		case 10:
			Gui::DrawStringCentered(0, 170, 0.7f, config->textColor(), Lang::get("REVERSE_CARD"), 400);
			break;
		case 11:
			Gui::DrawStringCentered(0, 170, 0.7f, config->textColor(), Lang::get("SKIP_CARD"), 400);
			break;
		case 12:
			Gui::DrawStringCentered(0, 170, 0.7f, config->textColor(), Lang::get("PLUS2_CARD"), 400);
			break;
		case 13:
			Gui::DrawStringCentered(0, 170, 0.7f, config->textColor(), Lang::get("WILD_CARD"), 400);
			break;
		case 14:
			Gui::DrawStringCentered(0, 170, 0.7f, config->textColor(), Lang::get("WILD_DRAW4_CARD"), 400);
			break;
		#ifdef _USE_SPECIAL_CARD
		case 15:
			Gui::DrawStringCentered(0, 170, 0.7f, config->textColor(), "Plays a 'Bruh' soundeffect.\nThe Tablecard get's randomized.", 400);
			break;
		#endif
	}
}

void RulesScreen::DisplayCards(void) const {
	switch (rulePage) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
			GFX::DrawCard(CardType(rulePage), 200, 95, CardColor(0), 0.7, 0.7);
			GFX::DrawCard(CardType(rulePage), 250, 95, CardColor(1), 0.7, 0.7);
			GFX::DrawCard(CardType(rulePage), 300, 95, CardColor(2), 0.7, 0.7);
			GFX::DrawCard(CardType(rulePage), 350, 95, CardColor(3), 0.7, 0.7);
			break;
		case 13:
		case 14:
			GFX::DrawCard(CardType(rulePage), 200, 95, CardColor(4), 0.7, 0.7);
			break;
		#ifdef _USE_SPECIAL_CARD
		case 15:
			GFX::DrawCard(CardType(rulePage), 200, 95, CardColor(4), 0.7, 0.7);
			break;
		#endif
	}
}

void RulesScreen::Draw(void) const {
	Animation::DrawSubBG();
	Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	Gui::DrawStringCentered(0, 0, 0.7f, config->textColor(), "3DEins - " + Lang::get("RULES"), 400);
	// Draw Card.
	GFX::DrawCard(CardType(rulePage), 30, 50, CardColor(1));
	Gui::DrawString(210, 40, 0.7f, config->textColor(), Lang::get("POINTS") + std::to_string(GameHelper::getPoints(CardType(rulePage))), 160);
	Gui::DrawString(210, 70, 0.7f, config->textColor(), Lang::get("CARDTYPE") + Lang::get(GameHelper::getTypeName(CardType(rulePage))), 160);
	Gui::DrawString(30, 140, 0.7f, config->textColor(), Lang::get("AVAILABLE_COLORS"), 160);
	DrawDescription();
	DisplayCards();
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
	Animation::DrawSubBG(false);
	Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, 210)); // Darken the screen.
	for(int i = 0; i < (int)cards.size(); i++) {
		GFX::DrawCard(CardType(i), cards[i].x, cards[i].y, CardColor(1), 0.8, 0.8);
	}
	if (fadealpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(fadecolor, fadecolor, fadecolor, fadealpha));
}

void RulesScreen::Logic(u32 hDown, u32 hHeld, touchPosition touch) {
	if (hDown & KEY_B) {
		Gui::screenBack(true);
		return;
	}

	if (hDown & KEY_R) {
		if (rulePage < MAXRULES)	rulePage++;
	} else if (hDown & KEY_L) {
		if (rulePage > 0)	rulePage--;
	}

	if (hDown & KEY_TOUCH) {
		for(int i = 0; i < (int)cards.size(); i++) {
			if (touching(touch, cards[i])) {
				rulePage = i;
			}
		}
	}
}