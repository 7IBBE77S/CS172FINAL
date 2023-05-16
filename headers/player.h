#ifndef CHARACTER_H
#define CHARACTER_H

#include "includes.h"
#include "inventory.h"
#include "weapon.h"
#include "gear.h"
#include "monster.h"

using namespace std;

enum playerType
{
	WIZARD,
	WARRIOR,
	ROGUE,
};

class Character
{
	// separate private and protected for derived access
protected:
	int distanceWandered;

	Inventory inventory;
	Weapon weapon;
	Gear helmet;
	Gear chest_armor;
	Gear gauntlet;
	Gear leg_armor;
	int currency;

	std::string name;

	int level;
	int experience;
	int expGained;

	int strength;
	int vitality;
	int dexterity;
	int intelligence;

	int health;
	int healthMax;
	int stamina;
	int staminaMax;
	int minAttack;
	int maxAttack;
	int defense;
	int accuracy;
	int luck;

	int points;

	playerType subclass; 

public:
	Character();
	Character(string name, int distanceWandered,
			  int currency, int level,
			  int experience, int strength, int vitality,
			  int dexterity, int intelligence,
			  int health, int stamina, int points);
	virtual ~Character();

	void initialize(const std::string name);
	// void initializeWizard(const std::string name);

	// base starting gear and weapon function
	void setOs(std::string os);
	std::string getOs();
	void printStats() const;
	string to_String() const;
	string getInventoryToString(bool shop = false);
	string getSaveInventoryToString();
	void levelUp();
	void updateStats();
	void addToStat(int stat, int value);
	void equipItem(unsigned index);
	inline void resetHealthPoints() { this->health = this->healthMax; }
	void addItem(const Item &item) { this->inventory.addItem(item); }
	void removeItem(const int index);
	const Item &getItem(const int index);

	// default points for each class
	// warrior
	inline void addStrength() { this->strength += 5; }
	// warrior
	inline void addVitality() { this->vitality += 5; }
	// rogue
	inline void addDexterity() { this->dexterity += 5; }
	// wizard
	inline void addIntelligence() { this->intelligence += 5; }

	// wizard ability
	inline void restoreHealth() {
		this->health += (this->intelligence * 0.5);
		if (this->health > this->healthMax)
			this->health = this->healthMax;
	};

	// warrior ability
	inline void heavyAttack(Monster *enemy)
	{
		// damage = player.getDamage();
		// 			enemies[choice].Damaged(damage);
		// enemy->Damaged(this->strength += (0.5 * this->strength));
		enemy->Damaged(getMaxAttack() * 1.5);
	}
	// rogue ability
	inline void weakenDebuff(Monster *enemy)
	{
		enemy->setDefense(enemy->getDefense() * 0.5);
	}

	void setSubclassType(const playerType subclass);
	playerType getSubclassType() const;

	bool isSubclassType(playerType subclass);

	std::string playerTypeToString(playerType subclass) const;

	inline const int &getDistTravel() const { return this->distanceWandered; }
	inline const std::string &getName() const { return this->name; }

	inline const int &getLevel() const { return this->level; }
	inline const int &getExperience() const { return this->experience; }
	inline const int &getExperienceNext() const { return this->expGained; }
	inline const int &getStatPoints() const { return this->points; }
	inline const int &getHealthPoints() const { return this->health; }
	inline const int &getHealthPointsMax() const { return this->healthMax; }
	inline const bool isAlive() { return this->health > 0; }
	inline const int &getStamina() const { return this->stamina; }
	inline const int &getDamageMin() const { return this->minAttack; }
	inline const int &getMaxAttack() const { return this->maxAttack; }
	inline const int getDamage() const { return rand() % (this->maxAttack + this->weapon.getMaxAttack()) + (this->minAttack + this->weapon.getMinAttack()); }
	inline const int getMaxDamage() const { return this->maxAttack + this->weapon.getMaxAttack(); }

	inline const int &getDefense() const { return this->defense; }
	inline const int getAdditionalDefense() const { return this->gauntlet.getDefense() + this->chest_armor.getDefense() + this->leg_armor.getDefense() + this->helmet.getDefense(); }
	inline const int &getAccuracy() const { return this->accuracy; }
	inline const int getShards() const { return this->currency; }
	inline const int getInventorySize() const { return this->inventory.size(); }

	inline void setWanderDistance(const int &distance) { this->distanceWandered = distance; }
	inline void travel() { this->distanceWandered++; }
	inline void gainExperience(const int experience) { this->experience += experience; }
	inline void gainShards(const int currency) { this->currency += currency; }
	inline void payShards(const int currency) { this->currency -= currency; }
	void Damaged(const int damage);
	inline void setWeapon(Weapon weapon) { this->weapon = weapon; }
	inline void setGearHead(Gear helmet) { this->helmet = helmet; }
	inline void setGearChest(Gear chest_armor) { this->chest_armor = chest_armor; }
	inline void setGearArms(Gear gauntlet) { this->gauntlet = gauntlet; }
	inline void setGearLegs(Gear leg_armor) { this->leg_armor = leg_armor; }
	inline void setStats(const int &strength, const int &vitality, const int &dexterity, const int &intelligence)
	{
		this->strength = strength;
		this->vitality = vitality;
		this->dexterity = dexterity;
		this->intelligence = intelligence;
	}
};

#endif
