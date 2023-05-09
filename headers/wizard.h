#ifndef WIZARD_H
#define WIZARD_H

#include "player.h"

class Wizard : public Character
{
private:
    int manaCost; 
    std::string spellName;


    

public:
    Wizard();
    // virtual wizard 💻😏🧙🪄🔥🔮
    virtual ~Wizard();

    // we love casting spells
    void castSpell(const std::string spellName, int manaCost);
    void restoreHealth();
};

#endif
