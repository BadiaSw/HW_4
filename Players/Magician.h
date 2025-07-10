#pragma once
#include "Job.h"

class Magician : public Job {
public:
    explicit Magician(const std::string &name) : Job(name) {}

    bool isMagician() const override {
        return true;
    }
};
