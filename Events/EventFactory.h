#pragma once

#include "Monster.h"
#include "Snail.h"
#include "Balrog.h"
#include "Slime.h"
#include "PotionsMerchant.h"
#include "SolarEclipse.h"
#include "Pack.h"

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <istream>

class EventFactory {
public:
    std::unique_ptr<Event> createEvent(const std::string& type, std::istream& eventsStream) {
        if (type != "Pack") {
            if (type == "Balrog") return std::unique_ptr<Event>(new Balrog());
            if (type == "PotionsMerchant") return std::unique_ptr<Event>(new PotionsMerchant());
            if (type == "Slime") return std::unique_ptr<Event>(new Slime());
            if (type == "Snail") return std::unique_ptr<Event>(new Snail());
            if (type == "SolarEclipse") return std::unique_ptr<Event>(new SolarEclipse());
            throw std::runtime_error("Invalid Events File");
        }

        struct PackContext {
            std::unique_ptr<Pack> pack;
            int expected;
            int added;
        };

        std::vector<PackContext> stack;

        int numMonsters;
        if (!(eventsStream >> numMonsters) || numMonsters < 2) {
            throw std::runtime_error("Invalid Events File");
        }

        stack.push_back(PackContext{std::unique_ptr<Pack>(new Pack()), numMonsters, 0});
        std::string monsterType;

        while (!stack.empty()) {
            if (!(eventsStream >> monsterType)) {
                throw std::runtime_error("Invalid Events File");
            }

            if (monsterType == "Pack") {
                int nestedNum;
                if (!(eventsStream >> nestedNum) || nestedNum < 2) {
                    throw std::runtime_error("Invalid Events File");
                }

                stack.push_back(PackContext{std::unique_ptr<Pack>(new Pack()), nestedNum, 0});
            } else {
                std::unique_ptr<Event> event;

                if (monsterType == "Balrog") event = std::unique_ptr<Event>(new Balrog());
                else if (monsterType == "PotionsMerchant") event = std::unique_ptr<Event>(new PotionsMerchant());
                else if (monsterType == "Slime") event = std::unique_ptr<Event>(new Slime());
                else if (monsterType == "Snail") event = std::unique_ptr<Event>(new Snail());
                else if (monsterType == "SolarEclipse") event = std::unique_ptr<Event>(new SolarEclipse());
                else throw std::runtime_error("Invalid Events File");

                Monster* rawPtr = dynamic_cast<Monster*>(event.get());
                if (rawPtr == nullptr) {
                    throw std::runtime_error("Invalid Events File");
                }

                std::unique_ptr<Monster> monsterPtr(static_cast<Monster*>(event.release()));
                stack[stack.size() - 1].pack->addMonster(std::move(monsterPtr));
                stack[stack.size() - 1].added++;
            }

            while (!stack.empty() && stack[stack.size() - 1].added == stack[stack.size() - 1].expected) {
                std::unique_ptr<Pack> completedPack = std::move(stack[stack.size() - 1].pack);
                stack.pop_back();

                if (stack.empty()) {
                    return std::move(completedPack);
                }

                stack[stack.size() - 1].pack->addMonster(std::move(completedPack));
                stack[stack.size() - 1].added++;
            }
        }

        throw std::runtime_error("Invalid Events File");
    }

    ~EventFactory() = default;
};
