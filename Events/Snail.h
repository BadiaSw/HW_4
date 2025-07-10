#pragma once
#include "Monster.h"

const int SNAIL_COMBATPOWER = 5;
const int SNAIL_LOOT = 2;
const int BALROG_POWERSNAIL_HP_LOSS_IF_DEFEATED = 10;

class Snail : public Monster{

public:

    explicit Snail(const string &name);

    string getDescription() const override;

    Snail();

};
