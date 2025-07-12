#pragma once

#include "Monster.h"
#include <string>

const int SNAIL_COMBATPOWER = 5;
const int SNAIL_LOOT = 2;
const int BALROG_POWERSNAIL_HP_LOSS_IF_DEFEATED = 10;

class Snail : public Monster {
public:
    // Constructor with custom name
    explicit Snail(const std::string& name)
        : Monster(name, SNAIL_COMBATPOWER, SNAIL_LOOT, BALROG_POWERSNAIL_HP_LOSS_IF_DEFEATED) {}

    // Default constructor with "Snail" name
    Snail()
        : Monster("Snail", SNAIL_COMBATPOWER, SNAIL_LOOT, BALROG_POWERSNAIL_HP_LOSS_IF_DEFEATED) {}

    // Description override
    std::string getDescription() const override {
        return "Snail (power " + std::to_string(m_combatPower) +
               ", loot " + std::to_string(m_loot) +
               ", damage " + std::to_string(m_HPLossOnDefeat) + ")";
    }
};
