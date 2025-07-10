#pragma once
#include "Job.h"

const int WARRIOR_MAXHP = 150;
const int WARRIOR_MULTIPLIER = 2;

class Warrior : public Job {
public:
    explicit Warrior(const std::string &name) : Job(name) {}

    int getCombatPower(int force, int level) const override {
        return force * WARRIOR_MULTIPLIER + level;
    }

    int getMaxHP() const override {
        return WARRIOR_MAXHP;
    }
};
