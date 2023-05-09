#ifndef WEAPON_H
#define WEAPON_H

#include "includes.h"
#include "item.h"


class Weapon : public Item
{
private:
	int minAttack;
	int maxAttack;

public:
	Weapon();
	Weapon(
		int level,
		int rarity);
	Weapon(
		int minAttack,
		int maxAttack,
		std::string name,
		int level,
		int buyValue,
		int sellValue,
		int rarity);
	virtual ~Weapon();

	virtual Weapon *clone() const;

	std::string toString() const;
	std::string toStringSave() const;

	inline int getMinAttack() const { return this->minAttack; }
	inline int getMaxAttack() const { return this->maxAttack; }





	 



	 
	






	static Dynamic<std::string> names;
	static void initializeNames();
};
#endif