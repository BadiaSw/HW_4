#include "SpecialEvent.h"

string SpecialEvent::getDescription() const {
    return m_name;
}
SpecialEvent::SpecialEvent(const string &name) : Event(name) {}

