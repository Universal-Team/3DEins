/*
*   This file is part of 3DEins
*   Copyright (C) 2019-2021 Universal-Team
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

#ifndef _3DEINS_CONFIG_HPP
#define _3DEINS_CONFIG_HPP

#include "json.hpp"

#include <3ds.h>
#include <string>

class Config {
public:
	Config();
	void save();
	void initialize();

	// Allow Animation.
	bool allowAnimation() { return this->v_allowAnimation; }
	void allowAnimation(bool v) { this->v_allowAnimation = v; if (!this->changesMade)	this->changesMade = true; }
	// Bar Color.
	u32 barColor() { return this->v_barColor; }
	void barColor(u32 v) { this->v_barColor = v; if (!this->changesMade)	this->changesMade = true; }
	// BG Color.
	u32 bgColor() { return this->v_bgColor; }
	void bgColor(u32 v) { this->v_bgColor = v; if (!this->changesMade)	this->changesMade = true; }
	// Text Color.
	u32 textColor() { return this->v_textColor; }
	void textColor(u32 v) { this->v_textColor = v; if (!this->changesMade)	this->changesMade = true; }
	// Button Color.
	u32 buttonColor() { return this->v_buttonColor; }
	void buttonColor(u32 v) { this->v_buttonColor = v; if (!this->changesMade)	this->changesMade = true; }
	// Selector Color.
	u32 selectorColor() { return this->v_selectorColor; }
	void selectorColor(u32 v) { this->v_selectorColor = v; if (!this->changesMade)	this->changesMade = true; }
	// Language.
	int language() { return this->v_language; }
	void language(int v) { this->v_language = v; if (!this->changesMade)	this->changesMade = true; }

	// Card Color stuff.
	int cardBlue() { return this->v_colorBlue; }
	void cardBlue(u32 v) { this->v_colorBlue = v; }

	int cardGreen() { return this->v_colorGreen; }
	void cardGreen(u32 v) { this->v_colorGreen = v; }

	int cardRed() { return this->v_colorRed; }
	void cardRed(u32 v) { this->v_colorRed = v; }

	int cardYellow() { return this->v_colorYellow; }
	void cardYellow(u32 v) { this->v_colorYellow = v; }

	void loadCardSets(std::string file);


	// Mainly helper.
	bool getBool(const std::string &key);
	void setBool(const std::string &key, bool v);
	int getInt(const std::string &key);
	void setInt(const std::string &key, int v);
	std::string getString(const std::string &key);
	void setString(const std::string &key, const std::string &v);
private:
	nlohmann::json json; // Our private JSON file.
	bool changesMade = false;

	// Color variables and more.
	bool v_allowAnimation;
	u32 v_barColor;
	u32 v_bgColor;
	u32 v_textColor;
	u32 v_buttonColor;
	u32 v_selectorColor;
	int v_language;

	u32 v_colorBlue, v_colorGreen, v_colorRed, v_colorYellow;
};

#endif