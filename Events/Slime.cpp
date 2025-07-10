#include <string.h>
#include "Slime.h"

using namespace std;

Slime::Slime(const string &name) :

Monster(name,SLIME_COMBATPOWER,SLIME_LOOT,SLIME_HP_LOSS_ON_DEFEAT){}

string Slime::getDescription() const {
    return "Slime (power " + to_string(m_combatPower)+", loot " +
        to_string(m_loot) + ", damage " + to_string(m_HPLossOnDefeat) + ")";
}
Slime::Slime() :
        Monster("Slime", SLIME_COMBATPOWER, SLIME_LOOT, SLIME_HP_LOSS_ON_DEFEAT) {}