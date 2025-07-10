#pragma once
#include "Range.h"
#include <memory>
#include <string>

class RangeFactory {
public:
    static std::unique_ptr<Range> createRange(const std::string& type) {
        if (type == "Archer" || type == "Magician") {
            return std::make_unique<LongRange>();
        } else if (type == "Warrior") {
            return std::make_unique<ShortRange>();
        }
        return nullptr;
    }

    ~RangeFactory() = default;
};
