#pragma once
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Player;

class Character {
protected:
    string char_name;

public:
    explicit Character(const std::string &name) {
        char_name = name;
    }

    Character() = default;

    virtual ~Character() = default;

    virtual string applyMerchant(Player &player) = 0;

    virtual string getCharacter() {
        return char_name;
    }
};
