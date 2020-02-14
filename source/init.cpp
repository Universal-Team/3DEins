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

#include "common.hpp"
#include "config.hpp"
#include "init.hpp"
#include "mainMenu.hpp"

#include <3ds.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

bool exiting = false;
touchPosition touch;
bool isDay = false;

// Include all spritesheet's.
C2D_SpriteSheet cards;
C2D_SpriteSheet sprites;


// If button Position pressed -> Do something.
bool touching(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))
		return true;
	else
		return false;
}


Result Init::Initialize() {
	gfxInitDefault();
	romfsInit();
	Gui::init();
	sdmcInit();
	mkdir("sdmc:/3ds", 0777);	// For DSP dump
	mkdir("sdmc:/3ds/3DEins", 0777); // main Path.
	mkdir("sdmc:/3ds/3DEins/cards", 0777); // Card Sheet path.
	if(access("sdmc:/3ds/3DEins/Settings.json", F_OK) == -1 ) {
		Config::initializeNewConfig();
	}
	Config::load();

	const time_t current = time(NULL);
	if(gmtime(&current)->tm_mon == 3 && gmtime(&current)->tm_mday == 1) {
		isDay = true;
	}

	// Only on *THE DAY*. ;P
	if (isDay != true) {
		Lang::load(Config::getLang("LANG"));
	} else {
		Lang::load(0);
	}

	Msg::DisplayMsg(Lang::get("LOADING_SHEET"));
	Gui::loadSheet("romfs:/gfx/cards.t3x", cards);
	Gui::loadSheet("romfs:/gfx/sprites.t3x", sprites);
	osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users.
	srand(time(NULL));
	Gui::setScreen(std::make_unique<MainMenu>());
	return 0;
}

Result Init::MainLoop() {
	// Initialize everything.
	Initialize();
	// Loop as long as the status is not exiting.
	while (aptMainLoop() && !exiting)
	{
		// Scan all the Inputs.
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hHeld = hidKeysHeld();
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, BLACK);
		C2D_TargetClear(Bottom, BLACK);
		Gui::clearTextBufs();
		Gui::mainLoop(hDown, hHeld, touch);
		C3D_FrameEnd(0);
	}
	// Exit all services and exit the app.
	Exit();
	return 0;
}

Result Init::Exit() {
	Gui::exit();
	Gui::unloadSheet(cards);
	Gui::unloadSheet(sprites);
	Config::save();
	gfxExit();
	romfsExit();
	sdmcExit();
	return 0;
}