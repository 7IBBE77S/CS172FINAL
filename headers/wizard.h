
#ifndef WIZARD_H
#define WIZARD_H

#include "player.h"


class Wizard : public Character
{
private:
    int type;
    // int intelligence;

public:
    Wizard();

    Wizard(string name,
           int level,
           int experience, int strength, int vitality,
           int dexterity, int intelligence,
           int health, int points);


    inline int getIntelligence() const { return this->intelligence; }

    inline int getType() const { return this->type; }

    void initializeWizard(const std::string name, playerType subclass);

    ~Wizard();

    inline void addIntelligence() { this->intelligence += 5; }

	inline const int &getHealthPointsMax() const { return this->healthMax; }
    
};

#endif
