#ifndef WARRIOR_H
#define WARRIOR_H

#include "player.h"

class Warrior : public Character
{
private:
    int rage; //maybe a bar will fill up and then you can use a special ability

public:
    Warrior();
    virtual ~Warrior();

    void performHeavyAttack();
    void increaseRage(int amount);
};

#endif
