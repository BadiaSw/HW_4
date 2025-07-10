
#include "Balrog.h"

using namespace std;

Balrog::Balrog(const string &name) :
        Monster(name, BALROG_POWER, BALROG_LOOT, BALROG_HP_LOSS) {}
Balrog::Balrog() :
        Monster("Balrog", BALROG_POWER, BALROG_LOOT, BALROG_HP_LOSS) {}

void Balrog::increaseCombatPower() {
    m_combatPower += BALROG_COMBATPOWER_ADDITION;
}


void Balrog::applyEncounter(Player &player) {
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

string Balrog::getDescription() const {
    return "Balrog (power " + to_string(m_combatPower) + ", loot " +
           to_string(m_loot) + ", damage " + to_string(m_HPLossOnDefeat) + ")";
}
