#pragma once

#include "Monster.h"
#include <string>

const int SLIME_COMBATPOWER = 12;
const int SLIME_LOOT = 5;
const int SLIME_HP_LOSS_ON_DEFEAT = 25;

class Slime : public Monster {
public:
    // Constructor with custom name
    explicit Slime(const std::string& name)
        : Monster(name, SLIME_COMBATPOWER, SLIME_LOOT, SLIME_HP_LOSS_ON_DEFEAT) {}

    // Default constructor with "Slime" as name
    Slime()
        : Monster("Slime", SLIME_COMBATPOWER, SLIME_LOOT, SLIME_HP_LOSS_ON_DEFEAT) {}

    // Description override
    std::string getDescription() const override {
        return "Slime (power " + std::to_string(m_combatPower) +
               ", loot " + std::to_string(m_loot) +
               ", damage " + std::to_string(m_HPLossOnDefeat) + ")";
    }
};
