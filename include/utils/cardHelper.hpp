/*
*   This file is part of 3DEins
*   Copyright (C) 2019 VoltZ
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

#ifndef CARDHELPER_HPP
#define CARDHELPER_HPP

// Card Type getter.
namespace CardGetter {
    bool isNumberCard(int Gamecard);
    bool isPlus2(int Gamecard);
    bool isReturn(int Gamecard);
    bool isExpose(int Gamecard);
    bool isWish(int Gamecard);
    bool isPlus4(int Gamecard);

    // Color getter!
    bool isBlue(int Gamecard);
    bool isGreen(int Gamecard);
    bool isRed(int Gamecard);
    bool isYellow(int Gamecard);
}

namespace CardSetter {

}


#endif