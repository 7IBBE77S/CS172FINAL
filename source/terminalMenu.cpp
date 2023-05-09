#include "terminalMenu.h"


using namespace std;
using namespace menu;


// Basic formatting for the menu.
// menu_title 
const std::string menu::title(const std::string title)
{
	// creates a stream buffer that can be used to read and write to a string.
	std::stringstream ss;

	ss << "*** " << title << " ***"
	   << "\n"
	   << "\n";

	return ss.str();
}

const std::string menu::divider(const unsigned amount, const char symbol)
{
	std::stringstream ss;

	ss << std::string(amount, symbol)
	   << "\n"
	   << "\n";

	return ss.str();
}

const std::string menu::item(const unsigned index, const std::string text)
{
	std::stringstream ss;

	ss << "- "
	   << "(" << index << ") " << text
	   << "\n";

	return ss.str();
}