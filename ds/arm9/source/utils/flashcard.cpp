/*
*   This file is part of DSEins
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

#include <fat.h>
#include <nds.h>
#include <stdio.h>
#include <sys/stat.h>

static bool sdAccessed = false;
static bool sdRead = false;

static bool flashcardAccessed = false;
static bool flashcardRead = false;

bool sdFound(void) {
	if (!sdAccessed) {
		if (access("sd:/", F_OK) == 0) {
			sdRead = true;
		} else {
			sdRead = false;
		}

		sdAccessed = true;
	}

	return sdRead;
}

bool flashcardFound(void) {
	if (!flashcardAccessed) {
		if (access("fat:/", F_OK) == 0) {
			flashcardRead = true;
		} else {
			flashcardRead = false;
		}

		flashcardAccessed = true;
	}

	return flashcardRead;
}

bool bothSDandFlashcard(void) {
	if (sdFound() && flashcardFound()) {
		return true;
	} else {
		return false;
	}
}
