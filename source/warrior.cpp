#include "warrior.h"

Warrior::Warrior()
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

Warrior::Warrior(string name, int level, int experience, int strength, int vitality, int dexterity, int intelligence, int health, int points)
    : Character(name, 0, 0, level, experience, strength, vitality, dexterity, intelligence, health, 0, points, playerType::WARRIOR)
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

	this->subclass = subclass;



	this->setSubclassType(subclass);
    

	this->updateStats();
}


void Warrior::initializeWarrior(const std::string name, playerType subclass)
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
	this->strength = 10;
	this->vitality = 7;
	this->dexterity = 4;
	this->intelligence = 3;
	this->points = 0;


    // add starting gear
    this->weapon = Weapon(1, 5, "Great Sword", 1, 1, 1, 0);
    this->helmet = Gear(1, 1, "Horned Helmet", 1, 1, 1, 0);
    this->chest_armor = Gear(1, 1, "Battle Worn Vest", 1, 1, 1, 0);
    this->gauntlet = Gear(1, 1, "Iron Gauntlets", 1, 1, 1, 0);
    this->leg_armor = Gear(1, 1, "Iron Greaves", 1, 1, 1, 0);
    this->setSubclassType(subclass);

    this->updateStats();
}

Warrior::~Warrior()
{
}
