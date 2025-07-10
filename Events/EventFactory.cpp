#include "EventFactory.h"
#include "Balrog.h"
#include "PotionsMerchant.h"
#include "Slime.h"
#include "Snail.h"
#include "SolarEclipse.h"
#include "Pack.h"


#include <string>
#include <memory>
#include <stdexcept>

std::unique_ptr<Event> EventFactory::createEvent(const std::string& type, std::istream& eventsStream) {
    if (type != "Pack") {
        if (type == "Balrog") return std::make_unique<Balrog>();
        if (type == "PotionsMerchant") return std::make_unique<PotionsMerchant>();
        if (type == "Slime") return std::make_unique<Slime>();
        if (type == "Snail") return std::make_unique<Snail>();
        if (type == "SolarEclipse") return std::make_unique<SolarEclipse>();

        throw std::runtime_error("Invalid Events File");
    }

    // We'll simulate a manual parsing stack
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

    stack.push_back({std::make_unique<Pack>(), numMonsters, 0});
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

            stack.push_back({std::make_unique<Pack>(), nestedNum, 0});
        } else {
            std::unique_ptr<Event> event;
            if (monsterType == "Balrog") event = std::make_unique<Balrog>();
            else if (monsterType == "PotionsMerchant") event = std::make_unique<PotionsMerchant>();
            else if (monsterType == "Slime") event = std::make_unique<Slime>();
            else if (monsterType == "Snail") event = std::make_unique<Snail>();
            else if (monsterType == "SolarEclipse") event = std::make_unique<SolarEclipse>();
            else throw std::runtime_error("Invalid Events File");

            Monster* rawPtr = dynamic_cast<Monster*>(event.get());
            if (!rawPtr) {
                throw std::runtime_error("Invalid Events File");
            }

            std::unique_ptr<Monster> monsterPtr(static_cast<Monster*>(event.release()));
            stack.back().pack->addMonster(std::move(monsterPtr));
            stack.back().added++;
        }

        // Check if the top pack is now complete
        while (!stack.empty() && stack.back().added == stack.back().expected) {
            auto completedPack = std::move(stack.back().pack);
            stack.pop_back();

            if (stack.empty()) {
                return completedPack;
            }

            stack.back().pack->addMonster(std::move(completedPack));
            stack.back().added++;
        }
    }

    throw std::runtime_error("Invalid Events File");
}
