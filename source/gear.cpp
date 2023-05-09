#include "gear.h"

Dynamic<std::string> Gear::names;
// Each of these represents a set. For example there is a full set of
// ophidian-facet helmet, legs, chest, and gauntlets.
void Gear::initializeNames()
{
	Gear::names.push("Ophidian-facet");
	Gear::names.push("Hyperborea-schema");
	Gear::names.push("Outerplane-Phasers");
	Gear::names.push("Eye-Ethereal");
	Gear::names.push("Ardent-Alchemy");
	Gear::names.push("Chromatic-Mantle");
}

Gear::Gear()
	: Item()
{
	this->type = -1;
	this->defense = 0;
}

Gear::Gear(int level, int rarity)
	: Item(itemTypes::ARMOR, level, rarity)
{
	// Generates a random defense value for the item.
	// The defense value is determined by the item's level and rarity.
	// The defense value is also determined by the type of item.
	// If the item is a weapon, its defense value is 0.
	// Otherwise, the defense value is randomly generated from 5 to 20.
	// (rarity + 1) * 5 is the lower bound of the defense value.
	// level * (rarity + 1) is the upper bound of the defense value.
	// This is the final defense value.
	this->defense = rand() % (level * (rarity + 1));
	this->defense += (rarity + 1) * 5;
	// The type is randomly generated from 0 to 3.
	this->type = rand() % 4;

	switch (this->type)
	{
	case gearType::HELMET:
		this->gearTypeToString = "Helmet";
		break;
	case gearType::CHEST:
		this->gearTypeToString = "Chest";
		break;
	case gearType::GAUNTLET:
		this->gearTypeToString = "Gauntlets";
		break;
	case gearType::LEGS:
		this->gearTypeToString = "Legs";
		break;
	default:
		this->gearTypeToString = "Invalid input";
		break;
	}

	this->setName(Gear::names[rand() % Gear::names.size()]);

	if (rarity == 3)
		this->defense += level * 5;
	else if (rarity == 4)
		this->defense += level * 10;
}


// type: the type of gear (e.g. headgear, body armor, etc.)
// defense: the amount of defense that the gear provides
// name: the name of the gear
// level: the level required to use the gear
// buyValue: the amount of money that the gear costs to buy
// sellValue: the amount of money that the gear is sold for
// rarity: the rarity of the gear
Gear::Gear(int type, int defense, std::string name, int level, int buyValue, int sellValue, int rarity)
	: Item(itemTypes::ARMOR, name, level, buyValue, sellValue, rarity)
{
	this->type = type;
	this->defense = defense;
}

// This function is called when the gear is destroyed.
// It deallocates any memory that was allocated in the constructor.
Gear::~Gear()
{
}

// It is used in the copy constructor and the assignment operator.
// It calls the copy constructor for the base class, and then copies
// the member variables of the derived class.
Gear *Gear::clone() const
{
	return new Gear(*this);
}

// returns a string representation of the gear
std::string Gear::toString() const
{
	// concatenates the string representation of the gear's name, type, level, rarity, and defense
	std::string str =
		this->getName() + " | Type: " + this->gearTypeToString + " | Level: " + std::to_string(this->getLevel()) + " | Rarity: " + std::to_string(this->getRarity()) + " | Def: " + std::to_string(this->defense);

	return str;
}

//This function converts the Gear object to a string for saving
std::string Gear::toStringSave() const
{
	std::string str =
		std::to_string(this->getItemType()) + " " + this->getName() + " " + std::to_string(this->getLevel()) + " " + std::to_string(this->getRarity()) + " " + std::to_string(this->getBuyValue()) + " " + std::to_string(this->getSellValue()) + " " + std::to_string(this->defense) + " " + std::to_string(this->type) + " ";

	return str;
}


