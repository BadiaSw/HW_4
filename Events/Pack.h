#pragma once
#include <vector>

#include "Balrog.h"
#include "set"
#include "memory"
#include <list>
class Pack : public Monster {
private:
    std::list<std::unique_ptr<Monster>> monsters;
    int numMons;
public:
    explicit Pack(const string &name);
    Pack(int size);
    Pack();
    void addMonster(std::unique_ptr<Monster> monster);

    void addPowerLootDamage(int power,int loot,int damage);

    std::set<Monster*> getPackMonsters() const;

    int getTotalPower() const;

    int getTotalLoot() const;

    int getTotalDamage() const;

    void setNumMonsters(int num);

    void applyEncounter(Player &player) override;

    void check_Balrog_Pack(const std::set<Monster*>& PackMonsters);

    string getDescription() const override;
};