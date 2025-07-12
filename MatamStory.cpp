#include "Pack.h"
#include "MatamStory.h"
#include "Utilities.h"
#include <stdexcept>
#include <list>
#include "Job.h"
#include "CharacterFactory.h"
#include "EventFactory.h"
#include "JobFactory.h"
#include "RangeFactory.h"
#include "Player.h"
#include <algorithm>

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream)
    : currentEventIter(events.end()), m_turnIndex(1) {
    readEvents(eventsStream);
    if (events.size() < 2) {
        throw std::runtime_error("Invalid Events File");
    }

    readPlayers(playersStream);
    if (players.size() < 2 || players.size() > 6) {
        throw std::runtime_error("Invalid Players File");
    }
}


void MatamStory::readEvents(std::istream& eventsStream) {
    EventFactory eventFactory;
    std::string input;

    while (eventsStream >> input) {
    std::unique_ptr<Event> event = eventFactory.createEvent(input, eventsStream);
        if (!event) {
            throw std::runtime_error("Invalid Events File");
        }
        events.push_back(std::move(event));
    }
}



void MatamStory::readPlayers(std::istream& playersStream) {
    std::string name, type, character;

    while (playersStream >> name >> type >> character) {
        if (name.length() < 3 || name.length() > 15 || containsIllegalChars(name)) {
            throw std::runtime_error("Invalid Players File");
        }

    std::unique_ptr<Player> player = MakePlayer(name, type, character);
        if (!player) {
            throw std::runtime_error("Invalid Players File");
        }

        players.push_back(std::move(player));
    }

    if (!playersStream.eof() || players.empty()) {
        throw std::runtime_error("Invalid Players File");
    }
}



std::unique_ptr<Player> MatamStory::MakePlayer(const std::string& name,
                                               const std::string& type,
                                               const std::string& character) {
    JobFactory jobFactory;
    CharacterFactory characterFactory;
    RangeFactory rangeFactory;

    std::unique_ptr<Job> job = jobFactory.CreateJob(type);
    std::unique_ptr<Range> range = rangeFactory.createRange(type);
    std::unique_ptr<Character> characterObj = characterFactory.createCharacter(character);

    if (!job || !range || !characterObj) {
        return nullptr;
    }

    try {
        return std::make_unique<Player>(name, std::move(job), std::move(characterObj), std::move(range));
    } catch (...) {
        return nullptr;
    }
}


void MatamStory::playRound() {
    printRoundStart();

    // Step 1: Gather active players (alive)
    std::list<std::reference_wrapper<Player>> activePlayers;
    for (std::list<std::unique_ptr<Player>>::iterator it = players.begin(); it != players.end(); ++it)
 {
        if ((*it)->isAlive()) {
            activePlayers.push_back(*(*it));
        }
    }

    // Step 2: Let each active player take a turn
    for (std::list<std::reference_wrapper<Player>>::iterator it = activePlayers.begin(); it != activePlayers.end(); ++it) {
        playTurn(it->get());
    }

    printRoundEnd();
    printLeaderBoardMessage();

    // Step 3: Sort players and print leaderboard
    std::vector<std::reference_wrapper<Player>> sortedPlayers;

    for (std::list<std::unique_ptr<Player>>::iterator it = players.begin(); it != players.end(); ++it)
 {
        sortedPlayers.push_back(*(*it)); // convert unique_ptr<Player> to Player&
    }

    struct {
        bool operator()(const Player& p1, const Player& p2) const {
            if (p1.getLevel() != p2.getLevel()) return p1.getLevel() > p2.getLevel();
            if (p1.getCoins() != p2.getCoins()) return p1.getCoins() > p2.getCoins();
            return p1.getName() < p2.getName();
        }
    } playerComparator;

    std::sort(sortedPlayers.begin(), sortedPlayers.end(), playerComparator);

    int rank = 1;
    for (std::vector<std::reference_wrapper<Player>>::const_iterator it = sortedPlayers.begin(); it != sortedPlayers.end(); ++it) {
        printLeaderBoardEntry(rank++, it->get());
    }

    printBarrier();
}







void MatamStory::playTurn(Player& player) {
    if (events.empty()) return;

    std::unique_ptr<Event> currEvent = std::move(events.front()); 
    events.erase(events.begin());

    printTurnDetails(m_turnIndex++, player, *currEvent);
    currEvent->applyEncounter(player);
    events.push_back(std::move(currEvent));
}




void MatamStory::play() {
    printStartMessage();

    int playerNum = 1;
    for (std::list<std::unique_ptr<Player>>::const_iterator it = players.begin(); it != players.end(); ++it) {
        printStartPlayerEntry(playerNum++, *(*it)); // dereference unique_ptr
    }

    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    printEndMessage();
}





bool MatamStory::isGameOver() const {
    if (std::any_of(players.begin(), players.end(),
                    [](const std::unique_ptr<Player>& p) { return p->getLevel() >= 10; })) {
        return true;
    }

    return std::none_of(players.begin(), players.end(),
                        [](const std::unique_ptr<Player>& p) { return p->isAlive(); });
}



void MatamStory::printEndMessage() {
    std::vector<std::reference_wrapper<const Player>> sortedPlayers;
    std::transform(players.begin(), players.end(), std::back_inserter(sortedPlayers),
                   [](const std::unique_ptr<Player>& p) { return std::cref(*p); });

    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
              [](const Player& p1, const Player& p2) {
                  if (p1.getLevel() != p2.getLevel()) return p1.getLevel() > p2.getLevel();
                  if (p1.getCoins() != p2.getCoins()) return p1.getCoins() > p2.getCoins();
                  return p1.getName() < p2.getName();
              });

    for (const Player& player : sortedPlayers) {
        if (player.getLevel() >= 10) {
            printWinner(player);
            return;
        }
    }

    printNoWinners();
}