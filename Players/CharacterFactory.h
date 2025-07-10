#pragma once
#include "Responsible.h"
#include "RiskTaking.h"
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;
using std::make_unique;

class CharacterFactory {
public:
    unique_ptr<Character> createCharacter(const string &type) {
        if (type == "Responsible") {
            return make_unique<Responsible>(type);
        } else if (type == "RiskTaking") {
            return make_unique<RiskTaking>(type);
        }
        return nullptr;
    }
};
