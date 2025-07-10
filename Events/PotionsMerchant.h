#pragma once
#include "SpecialEvent.h"

const int ADDHP = 10;

class PotionsMerchant : public SpecialEvent {

public:

    explicit PotionsMerchant(const string &name);

    PotionsMerchant();

    void applyEncounter(Player &player) override;
};