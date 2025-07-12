#pragma once

#include "Monster.h"
#include <string>

const int BALROG_POWER = 15;
const int BALROG_LOOT = 100;
const int BALROG_HP_LOSS = 9001;

class Balrog : public Monster {
public:
    // Constructor with custom name
    explicit Balrog(const std::string& name)
        : Monster(name, BALROG_POWER, BALROG_LOOT, BALROG_HP_LOSS) {}

    // Default constructor with "Balrog" as name
    Balrog()
        : Monster("Balrog", BALROG_POWER, BALROG_LOOT, BALROG_HP_LOSS) {}

    // Copy constructor
    Balrog(const Balrog& br) = default;

    // Increase Balrog power on every encounter
    void increaseCombatPower() {
        m_combatPower += BALROG_COMBATPOWER_ADDITION;
    }

    void applyEncounter(Player& player) override {
        if (player.getCombatPower() > m_combatPower) {
            player.levelUp();
            player.addCoins(m_loot);
            if (player.getRange() == "ShortRange") {
                player.damage(SHORT_RANGE_HP_LOSS);
            }
            increaseCombatPower();
            printTurnOutcome(getEncounterWonMessage(player, m_loot));
            return;
        }

        increaseCombatPower();
        player.damage(m_HPLossOnDefeat);
        printTurnOutcome(getEncounterLostMessage(player, m_HPLossOnDefeat));
    }

    std::string getDescription() const override {
        return "Balrog (power " + std::to_string(m_combatPower) +
               ", loot " + std::to_string(m_loot) +
               ", damage " + std::to_string(m_HPLossOnDefeat) + ")";
    }
};
