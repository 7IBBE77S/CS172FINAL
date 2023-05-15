#include "player.h"
#include "game.h"
#include "weapon.h"
#include "gear.h"
#include <cmath>
Character::Character()
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
	this->intelligence = 0;

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

Character::Character(string name, int distanceWandered,
					 int currency, int level,
					 int experience, int strength, int vitality,
					 int dexterity, int intelligence,
					 int health, int stamina, int points)
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
	this->setSubclassType(subclass);

	this->updateStats();
}

Character::~Character()
{
}
playerType Character::getSubclassType() const
{
	return this->subclass;
}

void Character::setSubclassType(const playerType subclass)
{

	if (isSubclassType(subclass))
	{
		this->subclass = subclass;
	}
}

bool Character::isSubclassType(playerType subclass)
{
	switch (subclass)
	{
	case WIZARD:
		return true;
		break;
	case WARRIOR:
		return true;
		break;
	case ROGUE:
		return true;
		break;
	default:
		return false;
		break;
	}
}


void Character::initialize(const string name)
{
	// starting travel distance
	this->distanceWandered = 0;

	// Starting shards
	this->currency = 100;

	// character name
	this->name = name;
	// set subclass type
	// starting level
	this->level = 1;
	this->experience = 0;

	// starting stats
	this->strength = 5;
	this->vitality = 5;
	this->dexterity = 5;
	this->intelligence = 5;
	this->points = 0;

	// add starting gear
	this->weapon = Weapon(1, 5, "Rusty Sword", 1, 1, 1, 0);
	this->helmet = Gear(1, 1, "Old Helmet", 1, 1, 1, 0);
	this->chest_armor = Gear(1, 1, "Battle worn Chest Armor", 1, 1, 1, 0);
	this->gauntlet = Gear(1, 1, "Leather Gauntlet", 1, 1, 1, 0);
	this->leg_armor = Gear(1, 1, "Broken Leg Armor", 1, 1, 1, 0);

	this->setSubclassType(subclass);

	this->updateStats();
}
std::string Character::playerTypeToString(playerType type) const
{
	// make sure to get the sub class type

	switch (type)
	{
	case WIZARD:
		return "Wizard";
		break;
	case WARRIOR:
		return "Warrior";
		break;
	case ROGUE:
		return "Rogue";
		break;
	default:
		return "Unknown";
		break;
	
	}

}


	void Character::printStats() const
	{
		cout << "*** Player Info ***"
			 << "\n";
		cout << "* Name: " << this->name << "\n";

		// get the sub class type and return it as a string"
		// playerType subclassType = this->getSubclassType();

		// print the sub class type"




		cout << "* Class: " << playerTypeToString(subclass) << "\n";

		cout << "* Level: " << this->level << "\n";
		cout << "* Experience: " << this->experience << "\n";
		cout << "* Experience to next level: " << this->expGained << "\n";
		cout << "* Points: " << this->points << "\n";
		cout << "\n";
		cout << "* Strength: " << this->strength << "\n";
		cout << "* Vitality: " << this->vitality << "\n";
		cout << "* Dexterity: " << this->dexterity << "\n";
		cout << "* Intelligence: " << this->intelligence << "\n";
		cout << "\n";
		cout << "* Health Points: " << this->health << " / " << this->healthMax << "\n";
		cout << "* Stamina: " << this->stamina << " / " << this->staminaMax << "\n";
		cout << "* Damage: " << this->minAttack << "( +" << this->weapon.getMinAttack() << ")"
			 << " - " << this->maxAttack << "( +" << this->weapon.getMaxAttack() << ")"
			 << "\n";
		cout << "* Defense: " << this->defense << "( +" << std::to_string(this->getAdditionalDefense()) << ")"
			 << "\n";
		cout << "* Accuracy: " << this->accuracy << "\n";
		cout << "* Luck: " << this->luck << "\n";
		cout << "\n";
		cout << "* Distance Wandered: " << this->distanceWandered << "\n";
		cout << "* Gold: " << this->currency << "\n";
		cout << "\n";
		cout << "* Weapon: " << this->weapon.getName()
			 << " Level: " << this->weapon.getLevel()
			 << " Damage: " << this->weapon.getMinAttack() << " - " << this->weapon.getMaxAttack() << "\n";
		cout << "* Gear Head: " << this->helmet.getName()
			 << " Level: " << this->helmet.getLevel()
			 << " Defense: " << this->helmet.getDefense() << "\n";
		cout << "* Gear Chest: " << this->chest_armor.getName()
			 << " Level: " << this->chest_armor.getLevel()
			 << " Defense: " << this->chest_armor.getDefense() << "\n";
		cout << "* Gear Arms: " << this->gauntlet.getName()
			 << " Level: " << this->gauntlet.getLevel()
			 << " Defense: " << this->gauntlet.getDefense() << "\n";
		cout << "* Gear Legs: " << this->leg_armor.getName()
			 << " Level: " << this->leg_armor.getLevel()
			 << " Defense: " << this->leg_armor.getDefense() << "\n"
			 << "\n";
	}

	string Character::to_String() const
	{
		return name + " " + to_string(distanceWandered) + " " + to_string(currency) + " " + to_string(level) + " " + to_string(experience) + " " + to_string(strength) + " " + to_string(vitality) + " " + to_string(dexterity) + " " + to_string(intelligence) + " " + to_string(health) + " " + to_string(stamina) + " " + to_string(points) + " " + this->weapon.toStringSave() + this->helmet.toStringSave() + this->chest_armor.toStringSave() + this->gauntlet.toStringSave() + this->leg_armor.toStringSave();
	}

	string Character::getInventoryToString(bool shop)
	{
		string inv;

		for (size_t i = 0; i < this->inventory.size(); i++)
		{
			if (shop)
			{
				inv += to_string(i) + ": " + this->inventory[i].toString() + "\n" + " - Sell value: " + std::to_string(this->inventory[i].getSellValue()) + "\n";
			}
			else
			{
				inv += to_string(i) + ": " + this->inventory[i].toString() + "\n";
			}
		}

		return inv;
	}

	string Character::getSaveInventoryToString()
	{
		string inv;

		for (size_t i = 0; i < this->inventory.size(); i++)
		{
			if (this->inventory[i].getItemType() == itemTypes::WEAPON)
				inv += this->inventory[i].toStringSave();
		}

		inv += "\n";

		for (size_t i = 0; i < this->inventory.size(); i++)
		{
			if (this->inventory[i].getItemType() == itemTypes::ARMOR)
				inv += this->inventory[i].toStringSave();
		}

		return inv;
	}

	void Character::levelUp()
	{
		if (this->experience >= this->expGained)
		{
			this->experience -= this->expGained;
			this->level++;
			this->expGained = static_cast<int>((50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12)) + 100;

			this->points++;

			this->updateStats();

			cout << "Your level is " << this->level << "!"
				 << "\n\n";
		}
		else
		{
			cout << "Not enough experience to level up."
				 << "\n\n";
		}
	}

	void Character::updateStats()
	{
		this->expGained = static_cast<int>(
							  (50 / 3) * ((pow(level, 3) - 6 * pow(level, 2)) + 17 * level - 12)) +
						  100;

		this->healthMax = (this->vitality * 5) + (this->strength) + this->level * 5;
		this->staminaMax = this->vitality + (this->strength / 2) + (this->dexterity / 3);
		this->stamina = this->staminaMax;
		this->minAttack = this->strength;
		this->maxAttack = this->strength + 2;
		this->defense = this->dexterity + (this->intelligence / 2);
		this->accuracy = (this->dexterity / 2) + intelligence;
		this->luck = this->intelligence;

		this->health = this->healthMax;
	}

	void Character::addToStat(int stat, int value)
	{
		if (this->points < value)
			cout << "Not enough points."
				 << "\n";
		else
		{
			switch (stat)
			{
			case 0:
				this->strength += value;
				cout << "Strength Increased!"
					 << "\n";

				break;

			case 1:
				this->vitality += value;
				cout << "Vitality Increased!"
					 << "\n";
				break;

			case 2:
				this->dexterity += value;
				cout << "Dexterity Increased!"
					 << "\n";
				break;

			case 3:
				this->intelligence += value;
				cout << "Intelligence Increased!"
					 << "\n";
				break;

			default:
				cout << "Try again."
					 << "\n";
				break;
			}

			this->points -= value;

			this->updateStats();
		}
	}

	void Character::equipItem(unsigned index)
	{
		if (index < 0 || index >= this->inventory.size())
		{
			cout << "No valid item selected!"
				 << "\n\n";
		}
		else
		{
			Weapon *w = nullptr;
			w = dynamic_cast<Weapon *>(&this->inventory[index]);

			Gear *a = nullptr;
			a = dynamic_cast<Gear *>(&this->inventory[index]);

			if (w != nullptr)
			{
				if (this->weapon.getRarity() >= 0)
					this->inventory.addItem(this->weapon);
				this->weapon = *w;
				this->inventory.removeItem(index);
			}
			else if (a != nullptr)
			{
				switch (a->getType())
				{
				case gearType::HELMET:
					if (this->helmet.getRarity() >= 0)
						this->inventory.addItem(this->helmet);
					this->helmet = *a;
					this->inventory.removeItem(index);
					break;
				case gearType::CHEST:
					if (this->chest_armor.getRarity() >= 0)
						this->inventory.addItem(this->chest_armor);
					this->chest_armor = *a;
					this->inventory.removeItem(index);
					break;
				case gearType::GAUNTLET:
					if (this->gauntlet.getRarity() >= 0)
						this->inventory.addItem(this->gauntlet);
					this->gauntlet = *a;
					this->inventory.removeItem(index);
					break;
				case gearType::LEGS:
					if (this->leg_armor.getRarity() >= 0)
						this->inventory.addItem(this->leg_armor);
					this->leg_armor = *a;
					this->inventory.removeItem(index);
					break;
				default:
					cout << "Invalid Gear Type."
						 << "\n\n";
					break;
				}
			}
			else
			{
				cout << "Error equipping item.";
			}
		}
	}

	void Character::removeItem(const int index)
	{
		if (index < 0 || index >= this->inventory.size() || this->inventory[index].getRarity() < 0)
			cout << "Cannot remove item."
				 << "\n\n";
		else
		{
			this->inventory.removeItem(index);
		}
	}

	const Item &Character::getItem(const int index)
	{
		if (index < 0 || index >= this->inventory.size() || this->inventory[index].getRarity() < 0)
		{
			cout << "Cannot get item."
				 << "\n\n";
		}

		return this->inventory[index];
	}

	void Character::Damaged(const int damage)
	{
		this->health -= damage;

		if (this->health <= 0)
		{
			this->health = 0;
		}
	}