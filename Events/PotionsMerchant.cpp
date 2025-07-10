
#include "PotionsMerchant.h"
#include "Utilities.h"


// Constructor with parameter
PotionsMerchant::PotionsMerchant(const string &name) : SpecialEvent(name) {}

// Default constructor
PotionsMerchant::PotionsMerchant() : SpecialEvent() {
    m_name = "PotionsMerchant"; // Set the name directly in the constructor
}

// Method to apply encounter with player
void PotionsMerchant::applyEncounter(Player &player) {
    // Call applyMerchant method on the player's character and print the outcome
    printTurnOutcome(player.getCharacter()->applyMerchant(player));
}

