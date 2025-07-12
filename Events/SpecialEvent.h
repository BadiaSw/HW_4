#pragma once

#include "Event.h"
#include <string>

class SpecialEvent : public Event {
public:
    // Constructor with name
    explicit SpecialEvent(const std::string& name)
        : Event(name) {}

    // Default constructor
    SpecialEvent() = default;

    // Override: return name as description
    std::string getDescription() const override {
        return m_name;
    }

    // Pure virtual function - must be implemented by derived classes
    virtual void applyEncounter(Player& player) override = 0;
};
