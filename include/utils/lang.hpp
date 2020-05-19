#ifndef _3DEINS_LANG_HPP
#define _3DEINS_LANG_HPP

#include "json.hpp"

#include <string>

namespace Lang {
	std::string get(const std::string &key);
	void load();
}

#endif