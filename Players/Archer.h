#pragma once
#include "Job.h"

const int ARCHER_COINS = 20;

class Archer : public Job {
public:
    explicit Archer(const std::string& name) : Job(name) {}

    int getCoins() const override {
        return ARCHER_COINS;
    }
};
