#ifndef ARMOR_H
#define ARMOR_H

#include "includes.h"
#include "item.h"

enum gearType
{
	HELMET = 0,
	CHEST,
	GAUNTLET,
	LEGS
};

class Gear : public Item
{
private:
	int type;
	std::string gearTypeToString;
	int defense;

public:
	Gear();
	Gear(
		int level,
		int rarity);
	Gear(
		int type,
		int defense,

		std::string name,
		int level,
		int buyValue,
		int sellValue,
		int rarity);
	~Gear();

	Gear *clone() const;

	std::string toString() const;
	std::string toStringSave() const;

	inline int getDefense() const { return this->defense; }
	inline int getType() const { return this->type; }
	static Dynamic<std::string> names;
	static void initializeNames();
};

#endif