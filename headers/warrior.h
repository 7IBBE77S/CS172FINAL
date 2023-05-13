

#ifndef WARRIOR_H
#define WARRIOR_H

#include "player.h"


class Warrior : public Character
{
private:
    int type;

public:
    Warrior();

    Warrior(string name,
           int level,
           int experience, int strength, int vitality,
           int dexterity, int intelligence,
           int health, int points);


    inline int getStrength() const { return this->strength; }

    inline int getType() const { return this->type; }

    void initializeWarrior(const std::string name, playerType subclass);

    ~Warrior();

    inline void addStrength() { this->strength += 5; }

    
};

#endif

