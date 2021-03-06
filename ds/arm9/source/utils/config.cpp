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

#include "config.hpp"
#include "flashcard.hpp"
#include <unistd.h>

// In case it doesn't exist.
void Config::initialize() {
	// Create through fopen "Write".
	FILE *file = fopen(sdFound() ? "sd:/_nds/DSEins/Settings.json" : "fat:/_nds/DSEins/Settings.json", "w");

	// Set default values.
	this->setInt("Language", 2);

	// Write to file.
	fwrite(this->json.dump(1, '\t').c_str(), 1, this->json.dump(1, '\t').size(), file);
	fclose(file); // Now we have the file and can properly access it.
}

Config::Config() {
	if (access(sdFound() ? "sd:/_nds/DSEins/Settings.json" : "fat:/_nds/DSEins/Settings.json", F_OK) != 0 ) {
		this->initialize();
	}

	FILE* file = fopen(sdFound() ? "sd:/_nds/DSEins/Settings.json" : "fat:/_nds/DSEins/Settings.json", "r");
	this->json = nlohmann::json::parse(file, nullptr, false);
	fclose(file);

	// Here we get the initial settings.

	if (!this->json.contains("Language")) {
		this->language(2);
	} else {
		this->language(this->getInt("Language"));
	}

	this->changesMade = false; // No changes made yet.
}

// Write to config if changesMade.
void Config::save() {
	if (this->changesMade) {
		FILE *file = fopen(sdFound() ? "sd:/_nds/DSEins/Settings.json" : "fat:/_nds/DSEins/Settings.json", "w");
		// Set values.
		this->setInt("Language", this->language());
		// Write changes to file.
		fwrite(this->json.dump(1, '\t').c_str(), 1, this->json.dump(1, '\t').size(), file);
		fclose(file);
	}
}

// Helper functions.
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