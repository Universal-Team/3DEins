/*
*   This file is part of 3DEins
*   Copyright (C) 2019-2020 Universal-Team
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

#ifndef _3DEINS_CHAT_SYSTEM_HPP
#define _3DEINS_CHAT_SYSTEM_HPP

#include <3ds.h>
#include <string>
#include <vector>

/*	
*						3DEins ChatSystem Struct.
*		PlayerStruct PS: Contains Player Name, ID, avatar Image & Phrase.
*		std::string message: Contains the message "body".
*		int messageCount: Contains the count of the message.
*/


struct PlayerStruct {
	std::string name;
	u16 id;
	int avatar;
	std::string phrase;
};

struct ChatStruct {
	PlayerStruct PS;
	std::string message;
	int messageCount;
};

class ChatSystem {
public:
	// Constructor & Destructor.
	ChatSystem(const std::string roomName, const std::vector<PlayerStruct> &data);
	~ChatSystem() { }

	// Refresh if needed.
	void Refresh(const std::vector<PlayerStruct> &data);

	// User Information Getter's.
	const std::string getName(int index) { return this->names[index]; }
	const u16 getID(int index) { return this->playerIDs[index]; }
	const int getAvatar(int index) { return this->avatarIndex[index]; }
	const std::string getPhrase(int index) { return this->phrase[index]; }
	const std::string getChatName() { return this->chatName; }

	// ChatRoom specific Getter's.
	const int getUserAmount() { return this->userAmount; }
	const std::vector<ChatStruct> getChat() { return this->chatStruct; }
	const bool getValid() { return this->isValid; } // Check if Valid.

	// Chat Helper.
	void sendMessage(int player, const std::string message) { this->chatStruct.push_back({this->names[player], this->playerIDs[player], this->avatarIndex[player], this->phrase[player], message, (int)this->chatStruct.size()+1}); }
	void deleteMessage(int pos) { if (pos < (int) this->chatStruct.size())	this->chatStruct.erase(this->chatStruct.begin()+pos); }
	void clearChat() { this->chatStruct.clear(); }

private:
	std::vector<ChatStruct> chatStruct; // All our chat-data is there.
	std::vector<std::string> names; // Usernames.
	std::vector<u16> playerIDs; // User ID's.
	std::vector<int> avatarIndex; // User Avatar Indexes.
	std::vector<std::string> phrase; // User Phrases.
	std::string chatName; // ChatRoom name.
	bool isValid = false; // Not valid right now.
	int userAmount = 0; // Amount of users.
};

#endif