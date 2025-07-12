#pragma once

#include "SpecialEvent.h"
#include "../Utilities.h" 
#include <string>

class PotionsMerchant : public SpecialEvent {
public:
    // Constructor with custom name
    explicit PotionsMerchant(const std::string& name)
        : SpecialEvent(name) {}

    // Default constructor with fixed name
    PotionsMerchant()
        : SpecialEvent() {
        m_name = "PotionsMerchant";
    }

    // Encounter logic
    void applyEncounter(Player& player) override {
        printTurnOutcome(player.getCharacter()->applyMerchant(player));
    }
};
