
#pragma once

#include <string>
#include "Character.h"
#include "Job.h"
#include "Range.h"
#include <memory>
using std::string;



const int MAX_LEVEL = 10;
const int INITIAL_LEVEL = 1;
const int MIN_HP = 0;
const int MIN_FORCE = 0;
const int INITIAL_FORCE = 5;

class Player {
protected:
    int m_force;
    int m_coins;
    int m_level;
    int m_HP;
    int m_maxHP;
    std::string m_name;
    std::unique_ptr<Job> m_job;
    std::unique_ptr<Character> m_character;
   std::unique_ptr<Range> m_range;

public:
     Player(const std::string &name,std::unique_ptr<Job> &&job,
                       std::unique_ptr<Character> &&character,
                       std::unique_ptr<Range> &&range);
    void levelUp();

    bool isAlive() const;
    void changeForce(int force);

    void damage(int HP);

    bool isKnockedOut() const;

    void addCoins(int coins);

    void buy_and_apply();


    int getCombatPower() const;

    void setCharacter(std::unique_ptr<Character> character);

    Character* getCharacter();


    string getRange();

    int getMaxHP() const;

    Job* getJob() const;

    void setJob(std::unique_ptr<Job> job);

    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;
};
