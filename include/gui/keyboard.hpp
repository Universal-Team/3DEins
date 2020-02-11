#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <3ds.h>
#include <string>

namespace Input {
	void DrawHex();
	void DrawNumpad();
	std::string Numpad(std::string Text);
	std::string Numpad(uint maxLength, std::string Text);
	// -1 if invaild text entered
	int getUint(int max, std::string Text);
	std::string getHex(int max, std::string Text);
}

#endif