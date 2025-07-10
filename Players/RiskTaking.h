#pragma once
#include "../Utilities.h"
#include "Character.h"

const int POTION_COST_RISK = 5;
const int RISK_TAKING_MIN_HP = 50;

class RiskTaking : public Character {
public:
    explicit RiskTaking(const std::string &name) : Character(name) {}

    RiskTaking() : Character() {
        char_name = "RiskTaking";
    }

    std::string applyMerchant(Player& player) override {
        int amount = 0;
        if (player.getHealthPoints() < RISK_TAKING_MIN_HP && player.getCoins() >= POTION_COST_RISK) {
            player.buy_and_apply();
            amount++;
        }
        return getPotionsPurchaseMessage(player, amount);
    }
};
