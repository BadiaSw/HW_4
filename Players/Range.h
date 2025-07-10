#pragma once

#include <string>
using std::string;

class Range {
protected:
    std::string range_name;

public:
    explicit Range(const std::string &name) {
        range_name = name;
    }

    Range() = default;

    virtual string getRange() {
        return range_name;
    }

    virtual ~Range() = default;
};

class LongRange : public Range {
public:
    LongRange(const LongRange &longRange) = default;

    explicit LongRange(const std::string &name) : Range(name) {}

    LongRange() {
        range_name = "LongRange";
    }
};

class ShortRange : public Range {
public:
    ShortRange(const ShortRange &shortRange) = default;

    explicit ShortRange(const std::string &name) : Range(name) {}

    ShortRange() {
        range_name = "ShortRange";
    }
};
