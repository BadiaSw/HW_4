#pragma once
#include "Event.h"
#include "../Utilities.h"
#include "../Players/Range.h"

const int SHORT_RANGE_HP_LOSS = 10;
const int BALROG_COMBATPOWER_ADDITION = 2;

class Monster : public Event {
protected:

    int m_combatPower;
    int m_loot;
    int m_HPLossOnDefeat;

public:
    explicit Monster(const std::string &name, int combatPower, int loot, int HPLossOnDefeat);

    Monster(const std::string &name);

    Monster();

    void applyEncounter(Player &player) override;
 

    string getDescription() const override = 0;

    int getLoot() const;

    int getCombatPower() const;

    int getHPLossOnDefeat() const;

    
};