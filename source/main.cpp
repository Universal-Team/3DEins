/*
*   This file is part of 3DEins
*   Copyright (C) 2019 DeadPhoenix8091, Epicpkmn11, Flame, RocketRobz, TotallyNotGuy, VoltZ
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

#include "gui/gui.hpp"

#include "screens/mainMenu.hpp"
#include "screens/screenCommon.hpp"

bool exiting = false;
touchPosition touch;

int main()
{
	gfxInitDefault();
	romfsInit();
	Gui::init();
	sdmcInit();
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users.

	Gui::setScreen(std::make_unique<MainMenu>());
	
	// Loop as long as the status is not exit.
	while (aptMainLoop() && !exiting)
	{
		// Scan all the Inputs.
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hHeld = hidKeysHeld();
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, BLACK);
		C2D_TargetClear(bottom, BLACK);
		Gui::clearTextBufs();
		Gui::mainLoop(hDown, hHeld, touch);
		C3D_FrameEnd(0);
	}
	Gui::exit();
	gfxExit();
	romfsExit();
	sdmcExit();
	return 0;
}