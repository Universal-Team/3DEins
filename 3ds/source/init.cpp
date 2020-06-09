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

#include "_3DEins_Helper.hpp"
#include "common.hpp"
#include "config.hpp"
#include "coreHelper.hpp"
#include "errorScreen.hpp"
#include "init.hpp"
#include "keyboard.hpp"
#include "mainMenu.hpp"
#include "saveData.hpp"

#include <3ds.h>
#include <ctime>
#include <dirent.h>
#include <random>

bool exiting = false;
touchPosition touch;

std::unique_ptr<SaveData> savedata;
std::unique_ptr<Config> config;

// Include all spritesheet's.
C2D_SpriteSheet cards;
C2D_SpriteSheet characters;
C2D_SpriteSheet sprites;

bool isGood = true;

// If Position pressed -> Do something.
bool touching(touchPosition touch, Structs::ButtonPos button) {
	if (touch.px >= button.x && touch.px <= (button.x + button.w) && touch.py >= button.y && touch.py <= (button.y + button.h))	return true;
	else	return false;
}

// If Button Position pressed -> Do something.
bool buttonTouch(touchPosition touch, ButtonStruct button) {
	if (touch.px >= button.X && touch.px <= (button.X + button.xSize) && touch.py >= button.Y && touch.py <= (button.Y + button.ySize))	return true;
	else	return false;
}

// Generate random ID between 1 and 65535.
void Init::GenerateID() {
	srand(std::time(nullptr));
	u16 id = rand() % 65535 + 1;
	savedata->playerID(id);
}

void Init::enterName() {
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0)); // Avoid glitchy things on bottom.
	std::string str = Keyboard::getString(10, Lang::get("ENTER_PLAYER_NAME"), 0.6);
	savedata->playerName(str);
}

Result Init::Initialize() {
	gfxInitDefault();
	romfsInit();
	Gui::init();
	// Load Sheets.
	Gui::loadSheet("romfs:/gfx/cards.t3x", cards);
	Gui::loadSheet("romfs:/gfx/chars.t3x", characters);
	Gui::loadSheet("romfs:/gfx/sprites.t3x", sprites);

	mkdir("sdmc:/3ds/3DEins", 0777);
	
	config = std::make_unique<Config>();
	if (!config)	isGood = false;

	if (!isGood) {
		Gui::setScreen(std::make_unique<ErrorScreen>(), false, true);
		osSetSpeedupEnable(true);	// Enable speed-up for New 3DS users.
		return 0;
	}

	Lang::load();
	savedata = std::make_unique<SaveData>("sdmc:/3ds/3DEins/SaveData.dat");
	
	if (savedata) {
		if (savedata->playerID() == 0) {
			GenerateID(); // We don't have an ID yet, so generate it.
			enterName(); // Enter username.
			savedata->playerAvatar(_3DEins_Helper::selectAvatar(savedata->playerAvatar()));
		}
	}
	
	osSetSpeedupEnable(true); // Enable speed-up for New 3DS users.
	config->loadCardSets("romfs:/Set.json"); // Load initial colors.
	Gui::setScreen(std::make_unique<MainMenu>(), false, true);
	return 0;
}

Result Init::MainLoop() {
	// Initialize everything.
	Initialize();
	CoreHelper::generateSeed();
	// Here we set the initial fade effect for fadein.
	fadealpha = 255;
	fadein = true;
	// Loop as long as the status is not exiting.
	while (aptMainLoop()) {
		// Scan all the Inputs.
		hidScanInput();
		u32 hDown = hidKeysDown();
		u32 hHeld = hidKeysHeld();
		hidTouchRead(&touch);
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs();
		GFX::Main(hDown, hHeld, touch);
		C3D_FrameEnd(0);
		if (exiting) {
			if (!fadeout)	break;
		}

		Gui::fadeEffects(16, 16, true);
	}
	// Exit all services and exit the app.
	Exit();
	return 0;
}

Result Init::Exit() {
	Gui::exit();
	if (isGood)	config->save(); // Only save if config is good.
	savedata->write(); // Only write if changes made.
	// Free all SpriteSheets.
	Gui::unloadSheet(cards);
	Gui::unloadSheet(characters);
	Gui::unloadSheet(sprites);
	gfxExit();
	romfsExit();
	return 0;
}