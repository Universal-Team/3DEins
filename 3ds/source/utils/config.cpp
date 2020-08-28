/*
*   This file is part of 3DEins
*   Copyright (C) 2019-2020 Universal-Team
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
#include "colorHelper.hpp"
#include <citro2d.h>
#include <regex>
#include <unistd.h>

/* Get String of the JSON. */
std::string getColorString(nlohmann::json json, const std::string &key, const std::string &key2) {
	if (!json.contains(key)) return "";
	if (!json.at(key).is_object()) return "";

	if (!json.at(key).contains(key2)) return "";
	if (!json.at(key).at(key2).is_string()) return "";

	return json.at(key).at(key2).get_ref<const std::string&>();
}

/* Get the colors. */
u32 getColor(std::string colorString) {
	if (colorString.length() < 7 || std::regex_search(colorString.substr(1), std::regex("[^0-9a-f]"))) { // invalid color.
		return 0;
	}

	int r = std::stoi(colorString.substr(1, 2), nullptr, 16);
	int g = std::stoi(colorString.substr(3, 2), nullptr, 16);
	int b = std::stoi(colorString.substr(5, 2), nullptr, 16);
	return RGBA8(r, g, b, 0xFF);
}

/* In case it doesn't exist. */
void Config::initialize() {
	/* Create through fopen "Write". */
	FILE *file = fopen("sdmc:/3ds/3DEins/Settings.json", "w");

	/* Set default values. */
	this->setBool("Allow_Animation", true);
	this->setInt("Bar_Color", C2D_Color32(220, 60, 0, 255));
	this->setInt("Text_Color", C2D_Color32(255, 255, 255, 255));
	this->setInt("BG_Color", C2D_Color32(220, 160, 0, 255));
	this->setInt("Button_Color", C2D_Color32(200, 0, 0, 255));
	this->setInt("Language", 2);

	/* Write to file. */
	fwrite(this->json.dump(1, '\t').c_str(), 1, this->json.dump(1, '\t').size(), file);
	fclose(file); // Now we have the file and can properly access it.
}

Config::Config() {
	if (access("sdmc:/3ds/3DEins/Settings.json", F_OK) != 0 ) {
		this->initialize();
	}

	FILE* file = fopen("sdmc:/3ds/3DEins/Settings.json", "r");
	this->json = nlohmann::json::parse(file, nullptr, false);
	fclose(file);

	/* Here we get the initial settings. */

	if (!this->json.contains("Allow_Animation")) {
		this->allowAnimation(true);
	} else {
		this->allowAnimation(this->getBool("Allow_Animation"));
	}

	if (!this->json.contains("Bar_Color")) {
		this->barColor(C2D_Color32(220, 60, 0, 255));
	} else {
		this->barColor(this->getInt("Bar_Color"));
	}

	if (!this->json.contains("BG_Color")) {
		this->bgColor(C2D_Color32(220, 160, 0, 255));
	} else {
		this->bgColor(this->getInt("BG_Color"));
	}

	if (!this->json.contains("Text_Color")) {
		this->textColor(C2D_Color32(255, 255, 255, 255));
	} else {
		this->textColor(this->getInt("Text_Color"));
	}

	if (!this->json.contains("Button_Color")) {
		this->buttonColor(C2D_Color32(170, 60, 0, 255));
	} else {
		this->buttonColor(this->getInt("Button_Color"));
	}

	if (!this->json.contains("Selector_Color")) {
		this->selectorColor(C2D_Color32(200, 0, 0, 255));
	} else {
		this->selectorColor(this->getInt("Selector_Color"));
	}

	if (!this->json.contains("Language")) {
		this->language(2);
	} else {
		this->language(this->getInt("Language"));
	}

	this->changesMade = false; // No changes made yet.
}

/* Write to config if changesMade. */
void Config::save() {
	if (this->changesMade) {
		FILE *file = fopen("sdmc:/3ds/3DEins/Settings.json", "w");
		/* Set values. */
		this->setBool("Allow_Animation", this->allowAnimation());
		this->setInt("Bar_Color", this->barColor());
		this->setInt("Text_Color", this->textColor());
		this->setInt("BG_Color", this->bgColor());
		this->setInt("Button_Color", this->buttonColor());
		this->setInt("Selector_Color", this->selectorColor());
		this->setInt("Language", this->language());
		/* Write changes to file. */
		fwrite(this->json.dump(1, '\t').c_str(), 1, this->json.dump(1, '\t').size(), file);
		fclose(file);
	}
}

/* Load card set colors. */
void Config::loadCardSets(std::string file) {
	FILE *file2= fopen(file.c_str(), "r");
	nlohmann::json cardset = nlohmann::json::parse(file2, nullptr, false);
	fclose(file2);

	this->cardBlue(getColor(getColorString(cardset, "info", "Blue")));
	this->cardGreen(getColor(getColorString(cardset, "info", "Green")));
	this->cardRed(getColor(getColorString(cardset, "info", "Red")));
	this->cardYellow(getColor(getColorString(cardset, "info", "Yellow")));
}

/* Helper functions. */
bool Config::getBool(const std::string &key) {
	if (!this->json.contains(key)) {
		return false;
	}

	return this->json.at(key).get_ref<const bool&>();
}
void Config::setBool(const std::string &key, bool v) {
	this->json[key] = v;
}

int Config::getInt(const std::string &key) {
	if (!this->json.contains(key)) {
		return 0;
	}

	return this->json.at(key).get_ref<const int64_t&>();
}
void Config::setInt(const std::string &key, int v) {
	this->json[key] = v;
}

std::string Config::getString(const std::string &key) {
	if (!this->json.contains(key)) {
		return "";
	}
	
	return this->json.at(key).get_ref<const std::string&>();
}
void Config::setString(const std::string &key, const std::string &v) {
	this->json[key] = v;
}