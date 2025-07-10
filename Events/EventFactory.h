#pragma once
#include "Monster.h"
#include  "Snail.h"
#include "Balrog.h"
#include "Slime.h"
#include "PotionsMerchant.h"
#include "SolarEclipse.h"
#include "Pack.h"
#include "sstream"

class EventFactory {
public:
unique_ptr<Event> createEvent(const string &type, std::istream &eventsStream);

    ~EventFactory() = default;
};


