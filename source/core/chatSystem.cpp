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

#include "chatSystem.hpp"

// Init Chat-System.
ChatSystem::ChatSystem(const std::string roomName, const std::vector<PlayerStruct> &data) {
	// Clear everything first.
	this->chatStruct.clear();
	this->names.clear();
	this->playerIDs.clear();
	this->avatarIndex.clear();
	this->phrase.clear();
	this->userAmount = 0;
	this->chatName = roomName;

	// ChatSystem is invalid if empty.
	if ((int)data.size() != 0) {
		// Get User data.
		for (int i = 0; i < (int)data.size(); i++) {
			this->names.push_back(data[i].name); // Get User Names.
			this->playerIDs.push_back(data[i].id); // Get User ID's.
			this->avatarIndex.push_back(data[i].avatar); // Get User Avatar.
			this->phrase.push_back(data[i].phrase); // Get User Phrase.
		}

		this->userAmount = data.size();
		this->isValid = true;
	} else {
		// No User's found. Do not allow access!
		this->isValid = false;
	}
}

// Refresh the list.
void ChatSystem::Refresh(const std::vector<PlayerStruct> &data) {
	// Clear first.
	this->names.clear();
	this->playerIDs.clear();
	this->avatarIndex.clear();
	this->phrase.clear();
	this->userAmount = 0;

	// ChatSystem is invalid if empty.
	if ((int)data.size() != 0) {
		// Get User data.
		for (int i = 0; i < (int)data.size(); i++) {
			this->names.push_back(data[i].name); // Get User Names.
			this->playerIDs.push_back(data[i].id); // Get User ID's.
			this->avatarIndex.push_back(data[i].avatar); // Get User Avatar.
			this->phrase.push_back(data[i].phrase); // Get User Phrase.
		}

		this->userAmount = data.size();
		this->isValid = true;
	} else {
		// No User's found. Do not allow access!
		this->isValid = false;
	}
}