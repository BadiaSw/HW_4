#include "Snail.h"

using namespace std;

Snail::Snail(const string &name) :

Monster(name,SNAIL_COMBATPOWER,SNAIL_LOOT,BALROG_POWERSNAIL_HP_LOSS_IF_DEFEATED){}

string Snail::getDescription() const {
    return "Snail (power " + to_string(m_combatPower)+", loot " +
        to_string(m_loot) + ", damage " + to_string(m_HPLossOnDefeat) + ")";
}


Snail::Snail() :
        Monster("Snail", SNAIL_COMBATPOWER, SNAIL_LOOT, BALROG_POWERSNAIL_HP_LOSS_IF_DEFEATED) {}
