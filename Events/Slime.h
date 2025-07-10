#pragma once
#include "Monster.h"

const int SLIME_COMBATPOWER = 12;
const int SLIME_LOOT = 5;
const int SLIME_HP_LOSS_ON_DEFEAT = 25;

class Slime : public Monster{

public:

    explicit Slime(const string &name);

    string getDescription() const override;

    Slime();


};