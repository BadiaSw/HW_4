#pragma once
#include "Event.h"

class SpecialEvent : public Event {

public :
    explicit SpecialEvent(const string &name);

    SpecialEvent() = default;

    string getDescription() const override;

    void applyEncounter(Player &player)  override = 0;

};

