#include "monster.h"

// Default constructor with random values and set values
Monster::Monster(int level)
{
	this->level = level;
	this->healthMax = rand()% (level * 10) + (level * 2);
	this->health = this->healthMax;
	this->minAttack = this->level * 1;
	this->maxAttack = this->level * 2;
	this->dropChance = rand() % 100 + 1;
	this->defense = rand() % level * 5 + 1;
	this->accuracy = rand() % level * 5 + 1;
}

// This is a destructor. It is used to free up resources
// that were allocated by the constructor.
Monster::~Monster()
{

}

//This function returns a string containing the values of the monsters stats
std::string Monster::to_String()const
{
	return "Level: " + std::to_string(this->level) + "\n" +
		"HP: " + std::to_string(this->health) + " / " + std::to_string(this->healthMax) + "\n" +
		"Damage: " + std::to_string(this->minAttack) + " - " + std::to_string(this->maxAttack) + "\n" +
		"defense: " + std::to_string(this->defense) + "\n" +
		"Accuracy: " + std::to_string(this->accuracy) + "\n" +
		"Drop chance: " + std::to_string(this->dropChance) + "\n";
}

// This function is used to decrease the health of the monster.
// The health of the monster is decreased by the amount of damage passed in.
// If the health of the monster becomes less than or equal to 0, it is set to 0.
void Monster::Damaged(int damage)
{
	this->health -= damage; 

	if (this->health <= 0)
	{
		this->health = 0;
	}
}
