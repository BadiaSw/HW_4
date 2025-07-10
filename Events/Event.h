
#pragma once

#include "../Players/Player.h"
using std::string;

class Event {
    protected:
    string m_name;

public:

    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const=0;

    explicit Event(const string &name) : m_name(name){

}

    Event() = default;

    virtual ~Event() = default;



    virtual void applyEncounter(Player &player) = 0;

};
