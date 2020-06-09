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

#include "saveData.hpp"

#include <algorithm>
#include <unistd.h>

#define SAVESIZE	0x20000
#define NAME_SIZE	10

void SaveData::create(std::string saveFile) {
	u8 *Buffer; // 128 KB.
	Buffer = new u8[SAVESIZE];

	for (int i = 0; i < SAVESIZE; i++) {
		Buffer[i] = 0;
	}

	FILE *file = fopen(saveFile.c_str(), "w");
	fwrite(Buffer, SAVESIZE, 1, file);
	fclose(file);
	delete[] Buffer;
}

SaveData::SaveData(std::string saveFile) {
	this->savePath = saveFile;
	// Try to access the saveFile.
	if (access(saveFile.c_str(), F_OK) != 0 ) {
		// SaveFile does not exist. Create it.
		this->create(this->savePath);
	}

	// Now we open the SaveFile.
	FILE* in = fopen(this->savePath.c_str(), "r");
	if (in) {
		fseek(in, 0, SEEK_END);
		this->saveSize = ftell(in);
		fseek(in, 0, SEEK_SET);
		this->saveData = std::unique_ptr<u8[]>(new u8[this->saveSize]);
		fread(this->saveData.get(), 1, this->saveSize, in);
		fclose(in);
	}
}


/*	Player Name. */
std::string SaveData::playerName() {
	std::string output;
	std::string test(reinterpret_cast<char *>(this->saveData.get() + 0), 9 + 1);

	for(char character : test) {
		if (character == '\0')	break;
		if (character < 256) {
			output += character;
		}
	}
	return output;
}

void SaveData::playerName(const std::string name) {
	// Do not allow a string longer as 10.
	if (name.length() > NAME_SIZE) {
		return;
	}

	memcpy(this->saveData.get() + 0, (u8 *)name.data(), name.length()); // 9 + 1
	if (!this->changesMade)	this->changesMade = true;
}

/*	Player ID. */
u16 SaveData::playerID() {
	return Read<u16>(0xA);
}
void SaveData::playerID(u16 ID) {
	this->Write<u16>(0xA, ID);
	if (!this->changesMade)	this->changesMade = true;
}

/*	Player Avatar. */
int SaveData::playerAvatar() {
	return this->saveData.get()[0xC];
}
void SaveData::playerAvatar(int avatar) {
	this->saveData.get()[0xC] = avatar;
	if (!this->changesMade)	this->changesMade = true;
}

/*	Phrase. */
std::string SaveData::playerPhrase() {
	std::string output;
	std::string test(reinterpret_cast<char *>(this->saveData.get() + 0xD), 29 + 1);

	for(char character : test) {
		if (character == '\0')	break;
		if (character < 256) {
			output += character;
		}
	}
	return output;
}

void SaveData::playerPhrase(const std::string phrase) {
	// Do not allow a string longer as 30.
	if (phrase.length() > 30) {
		return;
	}

	memcpy(this->saveData.get() + 0xD, (u8 *)phrase.data(), phrase.length()); // 29 + 1
	if (!this->changesMade)	this->changesMade = true;
}


// Write data to SaveFile. Call this when exiting or so.
void SaveData::write() {
	if (this->changesMade) {
		FILE *file = fopen(this->savePath.c_str(), "w");
		fwrite(this->saveData.get(), this->saveSize, 1, file);
		fclose(file);
	}
}