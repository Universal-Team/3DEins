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
#include "lang.hpp"

#include <stdio.h>
#include <unistd.h>

nlohmann::json appJson;
extern std::unique_ptr<Config> config;

std::string Lang::get(const std::string &key) {
	if(!appJson.contains(key)) {
		return "MISSING: " + key;
	}
	
	return appJson.at(key).get_ref<const std::string&>();
}

std::string langs[] = {"br", "de", "en", "es", "fr", "it", "lt", "pt", "ru", "jp"};

void Lang::load() {
	FILE* values;
	if (access(("romfs:/lang/"+langs[config->language()]+"/app.json").c_str(), F_OK) == 0 ) {
		values = fopen(("romfs:/lang/"+langs[config->language()]+"/app.json").c_str(), "rt");
		if(values)	appJson = nlohmann::json::parse(values, nullptr, false);
		fclose(values);
	} else {
		// Load English otherwise.
		values = fopen(("romfs:/lang/"+langs[2]+"/app.json").c_str(), "rt");
		if(values)	appJson = nlohmann::json::parse(values, nullptr, false);
		fclose(values);
	}
}