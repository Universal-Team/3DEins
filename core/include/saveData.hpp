/*
*   This file is part of 3DEins/DSEins-Core
*   Copyright (C) 2020 Universal-Team
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

#ifndef _3DEINS_CORE_SAVEDATA_HPP
#define _3DEINS_CORE_SAVEDATA_HPP

#include <cstring>
#include <memory>
#include <stdlib.h>
#include <string>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/*	
	3DEins | DSEins SaveData Struct.
	0x0 - 0x9: Player Name. (size: 10, UTF-8, 10 chars)
	0xA - 0xC: Player ID. (size: 2, u16)
	0xD - 0x2B: Player Phrase. (size: 30, UTF-8, 30 chars)
	0x2C - 0x2D: Player Win amount. (size: 1, u8)
	0x2D - 0x2E: Player Lose amount. (size: 1, u8)
*/

class SaveData {
protected:
	/* Protected data. */
	std::unique_ptr<u8[]> saveData;
	u32 saveSize;
public:
	SaveData(std::string saveFile);
	~SaveData() { }

	/* Return and Set's. */
	std::string playerName();	void playerName(std::string name);
	u16 playerID();				void playerID(u16 ID);
	int playerAvatar();			void playerAvatar(int avatar);
	std::string playerPhrase();	void playerPhrase(std::string phrase);
	u8 playerWins(); void playerWins(u8 wins);
	u8 playerLose(); void playerLose(u8 lose);

	/* Operations. */
	void write();
	void create(std::string saveFile);

	/* Write. */
	template <typename T>
	void Write(u32 offset, T data) {
		*reinterpret_cast<T*>(this->saveData.get() + offset) = data;
		if (!this->changesMade)	this->changesMade = true; // Set changes made to true.
	}

	/* Read an offset from the saveData. */
	template <typename T>
	T Read(u32 offset) {
		if (saveData != nullptr) return *(T*)(this->saveData.get() + offset);
		else return *(T*)0;
	}
	
private:
	std::string savePath;
	bool changesMade = false;
};

#endif