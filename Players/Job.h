#pragma once
#include <string>
#include <memory>

using std::string;

class Player;

class Job {
protected:
    string m_jobName;

public:
    explicit Job(const string &name) : m_jobName(name) {}

    virtual int getMaxHP() const {
        return 100;
    }

    virtual int getCoins() const {
        return 10;
    }

    virtual int getCombatPower(int force, int level) const {
        return force + level;
    }

    virtual string getJob() const {
        return m_jobName;
    }

    virtual bool isMagician() const {
        return false;
    }

    virtual ~Job() = default;
};
