#include "item.h"

Item::Item()
{
	this->itemType = -1;
	this->name = "Empty";
	this->level = 0;
	this->buyValue = 0;
	this->sellValue = 0;
	this->rarity = -1;
}

Item::Item(int itemType, int level, int rarity)
{
	this->name = "Random";
	this->level = rand() % (level + 2) + 1;
	this->rarity = rarity;
	// This function sets the buy value of an item based on its level and rarity.
	// The formula is (level + rarity) + level*rarity*10.
	// Example:
	// Level 1, Rarity 1: 2 + 1*1*10 = 12

	this->buyValue = (this->level + this->rarity) + this->level * this->rarity * 10;
	this->sellValue = this->buyValue / 2;
	this->itemType = itemType;
}

Item::Item(int itemType, std::string name, int level, int buyValue, int sellValue, int rarity)
{
	this->itemType = itemType;
	this->name = name;
	this->level = level;
	this->buyValue = buyValue;
	this->sellValue = sellValue;
	this->rarity = rarity;
}

// This function is called when the item is destroyed. It is used to
// free any resources the item may have allocated.
Item::~Item()
{
}
