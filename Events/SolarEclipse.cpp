
#include "SolarEclipse.h"
#include "Magician.h"

using namespace std;

SolarEclipse::SolarEclipse(const string &name) :
        SpecialEvent(name), forceLoss(SOLARECLIPS_LOSS), forceWin(SOLARECLIPS_WIN) {

}

SolarEclipse::SolarEclipse() : SpecialEvent(), forceLoss(SOLARECLIPS_LOSS), forceWin(SOLARECLIPS_WIN) {
    m_name = "SolarEclipse";
}


void SolarEclipse::applyEncounter(Player &player) {
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


