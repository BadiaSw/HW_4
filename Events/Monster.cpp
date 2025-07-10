#include "Monster.h"

Monster::Monster(const std::string &name, int combatPower, int loot, int HPLossOnDefeat) :
        Event(name), m_combatPower(combatPower), m_loot(loot), m_HPLossOnDefeat(HPLossOnDefeat) {}

Monster::Monster() :
        Event(), m_combatPower(0), m_loot(0), m_HPLossOnDefeat(0) {}


void Monster::applyEncounter(Player &player) {

    bool playerWins = player.getCombatPower() > m_combatPower;

    if (playerWins) {
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


Monster::Monster(const string &name) :
        Event(name), m_combatPower(0), m_loot(0), m_HPLossOnDefeat(0) {}

int Monster::getCombatPower() const {
    return this->m_combatPower;
}

int Monster::getLoot() const {
    return this->m_loot;
}

int Monster::getHPLossOnDefeat() const {
    return this->m_HPLossOnDefeat;
}

