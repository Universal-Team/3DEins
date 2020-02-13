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
#include "json.hpp"

#include <3ds.h>
#include <citro2d.h>
#include <string>
#include <unistd.h>

// Card & Lang.
int Config::lang, Config::Red, Config::Yellow, Config::Blue, Config::Green, Config::Selector;
// GUI.
int Config::Button, Config::Bar, Config::BG, Config::Text;

nlohmann::json configJson;

void Config::load() {
	FILE* file = fopen("sdmc:/3ds/3DEins/Settings.json", "r");
	if(file)	configJson = nlohmann::json::parse(file, nullptr, false);
	fclose(file);
	if(!configJson.contains("RED")) {
		Config::Red = C2D_Color32(255, 0, 0, 255);
	} else {
		Config::Red = getInt("RED");
	}

	if(!configJson.contains("YELLOW")) {
		Config::Yellow = C2D_Color32(200, 200, 0, 255);
	} else {
		Config::Yellow = getInt("YELLOW");
	}

	if(!configJson.contains("BLUE")) {
		Config::Blue = C2D_Color32(0, 0, 255, 255);
	} else {
		Config::Blue = getInt("BLUE");
	}

	if(!configJson.contains("GREEN")) {
		Config::Green = C2D_Color32(0, 255, 0, 255);
	} else {
		Config::Green = getInt("GREEN");
	}

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
		Config::Button = C2D_Color32(170, 60, 0, 200);
	} else {
		Config::Button = getInt("BUTTON");
	}

	if(!configJson.contains("BAR")) {
		Config::Bar = C2D_Color32(220, 60, 0, 200);
	} else {
		Config::Bar = getInt("BAR");
	}

	if(!configJson.contains("BG")) {
		Config::BG = C2D_Color32(220, 160, 0, 200);
	} else {
		Config::BG = getInt("BG");
	}

	if(!configJson.contains("TEXT")) {
		Config::Text = C2D_Color32(255, 255, 255, 255);
	} else {
		Config::Text = getInt("TEXT");
	}
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
	Config::setInt("BUTTON", C2D_Color32(170, 60, 0, 200));
	Config::setInt("BAR", C2D_Color32(220, 60, 0, 200));
	Config::setInt("BG", C2D_Color32(220, 160, 0, 200));
	Config::setInt("TEXT", C2D_Color32(255, 255, 255, 255));

	if(file)	fwrite(configJson.dump(1, '\t').c_str(), 1, configJson.dump(1, '\t').size(), file);
	fclose(file);
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