#include "wizard.h"

Wizard::Wizard()
	: Character()
{
	this->distanceWandered = 0;

	this->currency = 0;

	this->name = "";
	this->level = 0;
	this->experience = 0;
	this->expGained = 0;

	this->strength = 0;
	this->vitality = 0;
	this->dexterity = 0;
	this->intelligence = 10;

	this->health = 0;
	this->healthMax = 0;
	this->stamina = 0;
	this->staminaMax = 0;
	this->minAttack = 0;
	this->maxAttack = 0;
	this->defense = 0;
	this->accuracy = 0;
	this->luck = 0;

	this->points = 0;


}

Wizard::Wizard(string name, int level, int experience, int strength, int vitality, int dexterity, int intelligence, int health, int points)
	: Character(name, 0, 0, level, experience, strength, vitality, dexterity, intelligence, health, 0, points)
{

	this->name = name;

	this->distanceWandered = distanceWandered;

	this->currency = currency;

	this->level = level;
	this->experience = experience;
	this->expGained = 0;

	this->strength = strength;
	this->vitality = vitality;
	this->dexterity = dexterity;
	this->intelligence = intelligence;

	this->health = health;
	this->healthMax = 0;
	this->stamina = stamina;
	this->staminaMax = 0;
	this->minAttack = 0;
	this->maxAttack = 0;
	this->defense = 0;
	this->accuracy = 0;
	this->luck = 0;

	this->points = points;

	// this->subclass = subclass;

	this->setSubclassType(subclass);

	this->updateStats();
}

void Wizard::initializeWizard(const std::string name, playerType subclass)
{
	// starting travel distance
	this->distanceWandered = 0;

	// Starting shards
	this->currency = 100;

	// character name
	this->name = name;

	// starting level
	this->level = 1;
	this->experience = 0;

	// starting stats
	this->strength = 3;
	this->vitality = 4;
	this->dexterity = 7;
	this->intelligence = 10;
	this->points = 0;

	// add starting gear
	// this->weapon = Weapon(1, 5, "Staff", 1, 1, 1, 0);
	// this->helmet = Gear(1, 1, "Hood", 1, 1, 1, 0);
	// this->chest_armor = Gear(1, 1, "Robe", 1, 1, 1, 0);
	// this->gauntlet = Gear(1, 1, "Gloves", 1, 1, 1, 0);
	// this->leg_armor = Gear(1, 1, "Trousers", 1, 1, 1, 0);

	this->inventory.addItem(Weapon(1, 5, "Staff", 1, 1, 1, 0));

	this->inventory.addItem(Gear(1, 1, "Hood", 1, 1, 1, 0));
	this->inventory.addItem(Gear(1, 1, "Robe", 1, 1, 1, 0));
	this->inventory.addItem(Gear(1, 1, "Gloves", 1, 1, 1, 0));
	this->inventory.addItem(Gear(1, 1, "Trousers", 1, 1, 1, 0));

	// equipping starting gear use the equip function
	 this->weapon = Weapon(1, 5, "Staff", 1, 1, 1, 0);
	 this->helmet = Gear(1, 1, "Hood", 1, 1, 1, 0);
	 this->chest_armor = Gear(1, 1, "Robe", 1, 1, 1, 0);
	 this->gauntlet = Gear(1, 1, "Gloves", 1, 1, 1, 0);
	 this->leg_armor = Gear(1, 1, "Trousers", 1, 1, 1, 0);


	// set the subclass
	this->setSubclassType(subclass);

	this->updateStats();
}

Wizard::~Wizard()
{
}
