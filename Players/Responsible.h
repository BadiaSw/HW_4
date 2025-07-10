#pragma once
#include "Character.h"
#include "../Utilities.h"

const int POTION_COST_RESP = 5;

class Responsible : public Character {
public:
    explicit Responsible(const std::string &name) : Character(name) {}
    
    Responsible() : Character() {
        char_name = "Responsible";
    }
    
    string applyMerchant(Player &player) override {
        int amount = 0;
        while(player.getCoins() >= POTION_COST_RESP && player.getHealthPoints() < player.getMaxHP()) {
            player.buy_and_apply();
            amount++;
        }
        return getPotionsPurchaseMessage(player, amount);
    }
};