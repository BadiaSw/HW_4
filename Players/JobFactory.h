#pragma once
#include "Archer.h"
#include "Magician.h"
#include "Warrior.h"
#include <memory>
#include <string>

class JobFactory {
public:
    std::unique_ptr<Job> CreateJob(const std::string &type) {
        if (type == "Warrior") {
            return std::make_unique<Warrior>(type);
        } else if (type == "Archer") {
            return std::make_unique<Archer>(type);
        } else if (type == "Magician") {
            return std::make_unique<Magician>(type);
        }
        return nullptr;
    }
};
