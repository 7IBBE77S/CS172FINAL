#ifndef TERMINALMENU_H
#define TERMINALMENU_H

#include <sstream>
#include <string>

namespace menu
{
	// Returns a title string
	const std::string title(const std::string title);
	
	// Returns a divider string
	const std::string divider(const unsigned amount = 30, const char symbol = '-');
	
	// Returns a menu item string
	const std::string item(const unsigned index, const std::string text);
}

#endif
