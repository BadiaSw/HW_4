#pragma once
#include "SpecialEvent.h"
#include "../Utilities.h"

const int SOLARECLIPS_WIN = 1;
const int SOLARECLIPS_LOSS = -1;


class SolarEclipse : public SpecialEvent {
    int forceLoss;
    int forceWin;

public :
    explicit SolarEclipse(const string &name);

    SolarEclipse();

    void applyEncounter(Player &player)  override;

};
