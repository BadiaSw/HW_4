#pragma once
#include "string"
#include "Monster.h"


const int BALROG_POWER = 15;

const int BALROG_LOOT = 100;

const int BALROG_HP_LOSS = 9001;


class Balrog : public Monster {
public:

    explicit Balrog(const string &name);

    Balrog(const Balrog& br) = default;

    Balrog();

    void increaseCombatPower() ;

    string getDescription() const override;

    void applyEncounter(Player &player) override;
};
