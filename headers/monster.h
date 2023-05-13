#ifndef MONSTER_H
#define MONSTER_H

#include "includes.h"

class Monster
{
private:
	int defense;
	int accuracy;
	int healthMax;
	int health;
	int maxAttack;
	int minAttack;
	int level;
	float dropChance;

public:
	Monster(int level = 0);


	~Monster();

	bool isAlive()
	{
		return this->health > 0;
		// if (health > 0)
		// {
		// 	return true;
		// }
		// else
		// {
		// 	return false;
		// }
	}

	std::string to_String() const;
	void Damaged(int damage);

	int getLevel() const { return this->level; }

	int getMinAttack() const { return this->minAttack; }
	int getMaxAttack() const { return this->maxAttack; }
	int getDamage() const { return rand() % this->maxAttack + this->minAttack; }
	int getExperience() const { return this->level * 100; }
	int getHealthPoint() const { return this->health; }
	int getHealthPointMax() const { return this->healthMax; }
	int getDefense() const { return this->defense; }
	int setDefense(int defense) { return this->defense = defense; }
	int getAccuracy() const { return this->accuracy; }
};

#endif