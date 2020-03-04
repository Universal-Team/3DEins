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

#include "common.hpp"
#include "config.hpp"
#include "json.hpp"

#include <3ds.h>
#include <citro2d.h>
#include <regex>
#include <string>
#include <unistd.h>

// Card & Lang.
u32 Config::Red, Config::Yellow, Config::Blue, Config::Green, Config::Selector, Config::Button, Config::Bar, Config::BG, Config::Text;
// GUI.
int Config::lang, Config::speed;
bool Config::allowBruh;

// Player names.
std::string Config::Player1, Config::Player2, Config::Player3, Config::Player4;
nlohmann::json configJson;
nlohmann::json setJson;

// Get the colors.
u32 getColor(std::string colorString) {
	if(colorString.length() < 7 || std::regex_search(colorString.substr(1), std::regex("[^0-9a-f]"))) { // invalid color
		return 0;
	}

	int r = std::stoi(colorString.substr(1, 2), nullptr, 16);
	int g = std::stoi(colorString.substr(3, 2), nullptr, 16);
	int b = std::stoi(colorString.substr(5, 2), nullptr, 16);
	return RGBA8(r, g, b, 0xFF);
}

void Config::load() {
	FILE* file = fopen("sdmc:/3ds/3DEins/Settings.json", "r");
	if(file)	configJson = nlohmann::json::parse(file, nullptr, false);
	fclose(file);

	if(!configJson.contains("LANG")) {
		Config::lang = 2;
	} else {
		Config::lang = getInt("LANG");
	}

	if(!configJson.contains("SELECTOR")) {
		Config::Selector = C2D_Color32(200, 0, 0, 255);
	} else {
		Config::Selector = getInt("SELECTOR");
	}

	// GUI.
	if(!configJson.contains("BUTTON")) {
		Config::Button = C2D_Color32(170, 60, 0, 255);
	} else {
		Config::Button = getInt("BUTTON");
	}

	if(!configJson.contains("BAR")) {
		Config::Bar = C2D_Color32(220, 60, 0, 255);
	} else {
		Config::Bar = getInt("BAR");
	}

	if(!configJson.contains("BG")) {
		Config::BG = C2D_Color32(220, 160, 0, 255);
	} else {
		Config::BG = getInt("BG");
	}

	if(!configJson.contains("TEXT")) {
		Config::Text = C2D_Color32(255, 255, 255, 255);
	} else {
		Config::Text = getInt("TEXT");
	}

	if(!configJson.contains("ALLOW_BRUH")) {
		Config::allowBruh = true;
	} else {
		Config::allowBruh = getBool("ALLOW_BRUH");
	}

	if(!configJson.contains("ANIMATION_SPEED")) {
		Config::speed = 2;
	} else {
		Config::speed = getInt("ANIMATION_SPEED");
	}

	loadSet("romfs:/Set.json");
}

// Get String of the JSON.
std::string getString(nlohmann::json json, const std::string &key, const std::string &key2) {
	if(!json.contains(key))	return "MISSING: " + key;
	if(!json.at(key).is_object())	return "NOT OBJECT: " + key;

	if(!json.at(key).contains(key2))	return "MISSING: " + key + "." + key2;
	if(!json.at(key).at(key2).is_string())	return "NOT STRING: " + key + "." + key2;

	return json.at(key).at(key2).get_ref<const std::string&>();
}

void loadSetStuff(void) {
	u32 colorTemp;
	// Colors.
	colorTemp = getColor(getString(setJson, "info", "Red"));
	Config::Red = colorTemp == 0 ? CARD_RED : colorTemp;
	colorTemp = getColor(getString(setJson, "info", "Blue"));
	Config::Blue = colorTemp == 0 ? CARD_BLUE : colorTemp;
	colorTemp = getColor(getString(setJson, "info", "Yellow"));
	Config::Yellow = colorTemp == 0 ? CARD_YELLOW : colorTemp;
	colorTemp = getColor(getString(setJson, "info", "Green"));
	Config::Green = colorTemp == 0 ? CARD_GREEN : colorTemp;

	// GUI.
	colorTemp = getColor(getString(setJson, "info", "BarColor"));
	Config::Bar = colorTemp == 0 ? Config::Bar : colorTemp;
	colorTemp = getColor(getString(setJson, "info", "BGColor"));
	Config::BG = colorTemp == 0 ? Config::BG : colorTemp;
	colorTemp = getColor(getString(setJson, "info", "Selector"));
	Config::Selector = colorTemp == 0 ? Config::Selector : colorTemp;
	colorTemp = getColor(getString(setJson, "info", "TextColor"));
	Config::Text = colorTemp == 0 ? Config::Text : colorTemp;
	colorTemp = getColor(getString(setJson, "info", "ButtonColor"));
	Config::Button = colorTemp == 0 ? Config::Button : colorTemp;
}

void Config::loadSet(std::string sets) {
	FILE* file = fopen(sets.c_str(), "r");
	if(file)	setJson = nlohmann::json::parse(file, nullptr, false);
	fclose(file);
	// Load Card Colors.
	loadSetStuff();
}

void Config::save() {
	Config::setInt("RED", Config::Red);
	Config::setInt("YELLOW", Config::Yellow);
	Config::setInt("BLUE", Config::Blue);
	Config::setInt("GREEN", Config::Green);
	Config::setInt("LANG", Config::lang);
	Config::setInt("SELECTOR", Config::Selector);
	// GUI.
	Config::setInt("BUTTON", Config::Button);
	Config::setInt("BAR", Config::Bar);
	Config::setInt("BG", Config::BG);
	Config::setInt("TEXT", Config::Text);
	Config::setInt("ANIMATION_SPEED", Config::speed);
	// Game Stuff.
	Config::setBool("ALLOW_BRUH", Config::allowBruh);

	FILE* file = fopen("sdmc:/3ds/3DEins/Settings.json", "w");
	if(file)	fwrite(configJson.dump(1, '\t').c_str(), 1, configJson.dump(1, '\t').size(), file);
	fclose(file);
}

// If no Settings File is found, set a default one. ;)
void Config::initializeNewConfig() {
	FILE* file = fopen("sdmc:/3ds/3DEins/Settings.json", "r");
	if(file)	configJson = nlohmann::json::parse(file, nullptr, false);
	fclose(file);
	setInt("RED", C2D_Color32(255, 0, 0, 255));
	setInt("YELLOW", C2D_Color32(200, 200, 0, 255));
	setInt("BLUE", C2D_Color32(0, 0, 255, 255));
	setInt("GREEN", C2D_Color32(0, 255, 0, 255));
	setInt("LANG", 2);
	setInt("SELECTOR", C2D_Color32(200, 0, 0, 255));
	// GUI.
	Config::setInt("BUTTON", C2D_Color32(170, 60, 0, 255));
	Config::setInt("BAR", C2D_Color32(220, 60, 0, 255));
	Config::setInt("BG", C2D_Color32(220, 160, 0, 255));
	Config::setInt("TEXT", C2D_Color32(255, 255, 255, 255));
	Config::setInt("ANIMATION_SPEED", 2);
	// Game stuff.
	Config::setBool("ALLOW_BRUH", true);
	
	if(file)	fwrite(configJson.dump(1, '\t').c_str(), 1, configJson.dump(1, '\t').size(), file);
	fclose(file);
}

bool Config::getBool(const std::string &key) {
	if(!configJson.contains(key)) {
		return false;
	}
	return configJson.at(key).get_ref<const bool&>();
}
void Config::setBool(const std::string &key, bool v) {
	configJson[key] = v;
}

int Config::getInt(const std::string &key) {
	if(!configJson.contains(key)) {
		return 0;
	}
	return configJson.at(key).get_ref<const int64_t&>();
}
void Config::setInt(const std::string &key, int v) {
	configJson[key] = v;
}

int Config::getLang(const std::string &key) {
	if(!configJson.contains(key)) {
		return 1;
	}
	return configJson.at(key).get_ref<const int64_t&>();
}