#pragma once

#include "Monster.h"
#include "Balrog.h"
#include <list>
#include <set>
#include <memory>
#include <string>

class Pack : public Monster {
private:
    std::list<std::unique_ptr<Monster>> monsters;
    int numMons;

public:
    Pack();
    explicit Pack(const std::string& name);
    Pack(int size);

    void addMonster(std::unique_ptr<Monster> monster);
    std::set<Monster*> getPackMonsters() const;
    int getTotalPower() const;
    int getTotalLoot() const;
    int getTotalDamage() const;
    void setNumMonsters(int num);
    void applyEncounter(Player& player) override;
    void check_Balrog_Pack(const std::set<Monster*>& packMonsters);
    std::string getDescription() const override;
    void addPowerLootDamage(int power, int loot, int damage); // dummy or unimplemented
    int getSize() const override {
        int totalSize = 0;
        for (std::list<std::unique_ptr<Monster>>::const_iterator it = monsters.begin(); it != monsters.end(); ++it) {
            totalSize += (*it)->getSize(); // Recursive call
        }
        return totalSize;
    }
};
