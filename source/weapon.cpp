#include "weapon.h"

// The names of all the weapons in the game.
Dynamic<std::string> Weapon::names;

void Weapon::initializeNames()
{
	Weapon::names.push("Multi-Tool");
	Weapon::names.push("10k-Screams");
	Weapon::names.push("Dreamer-Culler");
	Weapon::names.push("Sol-Renderer");
	Weapon::names.push("Negative-Blade");
	Weapon::names.push("Daemon-Swarm");
}

Weapon::Weapon()
	: Item()
{
	this->maxAttack = 0;
	this->minAttack = 0;
}

Weapon::Weapon(int level, int rarity)
	: Item(itemTypes::WEAPON, level, rarity)
{
	// generates a random number between 0 and level * (rarity + 1) and sets it as the maxAttack value
	this->maxAttack = rand() % level * (rarity + 1);
	// adds 5 * (rarity + 1) to maxAttack
	this->maxAttack += (rarity + 1) * 5;
	// sets the name of the weapon to a random name from the names vector
	this->setName(Weapon::names[rand() % Weapon::names.size()]);

	// If the rarity is epic, increase maxAttack by 5 * level
	if (rarity == 3)
		this->maxAttack += level * 5;
	// If the rarity is legendary, increase maxAttack by 10 * level
	else if (rarity == 4)
		this->maxAttack += level * 10;

	// Set minAttack to half of maxAttack
	this->minAttack = this->maxAttack / 2;
}

Weapon::Weapon(int minAttack, int maxAttack, std::string name, int level, int buyValue, int sellValue, int rarity)
	: Item(itemTypes::WEAPON, name, level, buyValue, sellValue, rarity)
{
	this->minAttack = minAttack;
	this->maxAttack = maxAttack;
}

Weapon::~Weapon()
{
}

Weapon *Weapon::clone() const
{
	return new Weapon(*this);
}

std::string Weapon::toString() const
{
	// 	std::string name = this->getName();
	// int level = this->getLevel();
	// int rarity = this->getRarity();
	// int minDamage = this->minAttack;
	// int maxDamage = this->maxAttack;
	// std::string str = name + " | Level: " + std::to_string(level) + " | Rarity: " + std::to_string(rarity) + " | Damage: " + std::to_string(minDamage) + " - " + std::to_string(maxDamage);

	// 	return str;
	std::string str =
		this->getName() + " | Level: " + std::to_string(this->getLevel()) + " | Rarity: " + std::to_string(this->getRarity()) + " | Damage: " + std::to_string(this->minAttack) + " - " + std::to_string(this->maxAttack);

	return str;
}

std::string Weapon::toStringSave() const
{
	std::string str =
		std::to_string(this->getItemType()) + " " + this->getName() + " " + std::to_string(this->getLevel()) + " " + std::to_string(this->getRarity()) + " " + std::to_string(this->getBuyValue()) + " " + std::to_string(this->getSellValue()) + " " + std::to_string(this->minAttack) + " " + std::to_string(this->maxAttack) + " ";

	return str;
}