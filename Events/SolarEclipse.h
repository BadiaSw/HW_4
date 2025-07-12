#pragma once

#include "SpecialEvent.h"
#include "../Utilities.h"
#include "Magician.h"

const int SOLARECLIPS_WIN = 1;
const int SOLARECLIPS_LOSS = -1;

class SolarEclipse : public SpecialEvent {
    int forceLoss;
    int forceWin;

public:
    // Constructor with custom name
    explicit SolarEclipse(const std::string& name)
        : SpecialEvent(name), forceLoss(SOLARECLIPS_LOSS), forceWin(SOLARECLIPS_WIN) {}

    // Default constructor with fixed name
    SolarEclipse()
        : SpecialEvent(), forceLoss(SOLARECLIPS_LOSS), forceWin(SOLARECLIPS_WIN) {
        m_name = "SolarEclipse";
    }

    void applyEncounter(Player& player) override {
        if (player.getJob()->isMagician()) {
            player.changeForce(SOLARECLIPS_WIN);
            printTurnOutcome(getSolarEclipseMessage(player, SOLARECLIPS_WIN));
            return;
        }

        if (player.getForce() == MIN_FORCE) {
            printTurnOutcome(getSolarEclipseMessage(player, 0));
            return;
        }

        player.changeForce(SOLARECLIPS_LOSS);
        printTurnOutcome(getSolarEclipseMessage(player, SOLARECLIPS_LOSS));
    }
};
