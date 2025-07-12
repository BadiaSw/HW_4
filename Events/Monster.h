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
    // Full constructor
    explicit Monster(const std::string& name, int combatPower, int loot, int HPLossOnDefeat)
        : Event(name), m_combatPower(combatPower), m_loot(loot), m_HPLossOnDefeat(HPLossOnDefeat) {}

    // Constructor with name only
    explicit Monster(const std::string& name)
        : Event(name), m_combatPower(0), m_loot(0), m_HPLossOnDefeat(0) {}

    // Default constructor
    Monster()
        : Event(), m_combatPower(0), m_loot(0), m_HPLossOnDefeat(0) {}

    void applyEncounter(Player& player) override {
        if (player.getCombatPower() > m_combatPower) {
            player.addCoins(m_loot);
            player.levelUp();

            if (player.getRange() == "ShortRange") {
                player.damage(SHORT_RANGE_HP_LOSS);
            }

            printTurnOutcome(getEncounterWonMessage(player, m_loot));
        } else {
            player.damage(m_HPLossOnDefeat);
            printTurnOutcome(getEncounterLostMessage(player, m_HPLossOnDefeat));
        }
    }

    // Pure virtual method 
    virtual std::string getDescription() const override = 0;

    int getLoot() const {
        return m_loot;
    }

    int getCombatPower() const {
        return m_combatPower;
    }

    int getHPLossOnDefeat() const {
        return m_HPLossOnDefeat;
    }
};
