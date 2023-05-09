#ifndef ROGUE_H
#define ROGUE_H

#include "player.h"

class Rogue : public Character
{
private:
    int stealthLevel; 

public:
    Rogue();
    virtual ~Rogue();


    void performSneakAttack(); // does a cirtical hit, some sort of multiplier
    // void increaseStealthLevel(int amount);
    void useEvasionAbility(); // dodge an attack
};

#endif
