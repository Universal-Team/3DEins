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

#include "computer.hpp"

#include <array>
#include <stdlib.h>

#define COM_AMOUNT	3

std::array<std::string, COM_AMOUNT+1> files {
	{
		"romfs:/computer/computer_1.bin", "romfs:/computer/computer_2.bin",
		"romfs:/computer/computer_3.bin", "romfs:/computer/computer_4.bin"
	}
};


Computer::Computer(int character) {
	// Now we open the Computer File.
	FILE* in = fopen(files[character].c_str(), "r");
	fseek(in, 0, SEEK_END);
	u32 fileSize = ftell(in);
	fseek(in, 0, SEEK_SET);
	u8 *Buffer = new u8[fileSize];
	fread(Buffer, 1, fileSize, in);
	fclose(in);

	// Getting COM Name.
	const std::string name_1(reinterpret_cast<char *>(Buffer + 0), 9 + 1);

	// Make sure to only get valid chars.
	for(char character : name_1) {
		if (character == '\0')	break;
		if (character < 256) {
			this->name += character;
		}
	}
	// Get Computer avatar.
	this->avatar = Buffer[0xA];

	// Here we delete the buffer.
	delete[] Buffer;
}