#include "Pack.h"
#include "../Utilities.h"

// Calculates the total combat power of the pack, including nested packs.
int Pack::getTotalPower() const {
    int totalPower = 0;
    for (auto* monster : getPackMonsters()) {
        if (auto* pack = dynamic_cast<Pack*>(monster)) {
            totalPower += pack->getTotalPower();
        } else {
            totalPower += monster->getCombatPower();
        }
    }
    return totalPower;
}

// Computes the total loot available in the pack by summing the loot of all monsters.
int Pack::getTotalLoot() const {
    int totalLoot = 0;
    for (const auto& monster : monsters) {
        totalLoot += monster->getLoot();
    }
    return totalLoot;
}
void Pack::setNumMonsters(int num) {
    numMons = num;
}

// Calculates the total damage inflicted by all monsters in the pack when defeated.
int Pack::getTotalDamage() const {
    int totalDamage = 0;
    for (const auto& monster : monsters) {
        totalDamage += monster->getHPLossOnDefeat();
    }
    return totalDamage;
}

// Adds a monster to the pack.
void Pack::addMonster(std::unique_ptr<Monster> monster) {
    monsters.push_back(std::move(monster));
}

// Default constructor for the pack.
Pack::Pack() : Monster() {}

// Returns a set of raw pointers to the monsters in the pack for easy iteration.
std::set<Monster*> Pack::getPackMonsters() const {
    std::set<Monster*> rawPointers;
    for (const auto& mon : monsters) {
        rawPointers.insert(mon.get());
    }
    return rawPointers;
}

// Recursively checks the pack and nested packs for Balrog monsters and increases their combat power.
void Pack::check_Balrog_Pack(const std::set<Monster*>& packMonsters) {
    for (auto* monster : packMonsters) {
        if (auto* balrog = dynamic_cast<Balrog*>(monster)) {
            balrog->increaseCombatPower();
        } else if (auto* pack = dynamic_cast<Pack*>(monster)) {
            check_Balrog_Pack(pack->getPackMonsters());
        }
    }
}

// Handles an encounter between the player and the pack.
void Pack::applyEncounter(Player& player) {
    int totalPower = getTotalPower();
    int totalLoot = getTotalLoot();
    int totalDamage = getTotalDamage();

    bool playerWins = player.getCombatPower() > totalPower;

    if (playerWins) {
        player.addCoins(totalLoot);
        player.levelUp();

        if (player.getRange() == "ShortRange") {
            player.damage(SHORT_RANGE_HP_LOSS);
        }

        check_Balrog_Pack(getPackMonsters());
        printTurnOutcome(getEncounterWonMessage(player, totalLoot));
    } else {
        player.damage(totalDamage);
        check_Balrog_Pack(getPackMonsters());
        printTurnOutcome(getEncounterLostMessage(player, totalDamage));
    }
}

// Returns a descriptive string summarizing the pack's attributes.
std::string Pack::getDescription() const {
    return "Pack of " + std::to_string(monsters.size()) + " members (power " +
           std::to_string(getTotalPower()) + ", loot " +
           std::to_string(getTotalLoot()) + ", damage " +
           std::to_string(getTotalDamage()) + ")";
}
