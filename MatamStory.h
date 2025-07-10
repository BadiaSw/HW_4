#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include "Players/Player.h"
#include "Events/Event.h"
#include "Events/Pack.h"

class MatamStory {
private:
    std::list<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<Event>> events;
    std::vector<std::unique_ptr<Event>>::iterator currentEventIter;
    unsigned int m_turnIndex;

    /**
     * Plays a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);  // Changed from const Player& to Player&

    /**
    Plays a single round of the game
    */
    void playRound();

    /**
    Read events from input stream
    */
    void readEvents(std::istream& eventsStream);

    /**
     Create a new player
    */
    std::unique_ptr<Player> MakePlayer(const std::string& Name,const std::string& Type, const std::string& Character);

    /*
      Read players from input stream
    */
    void readPlayers(std::istream& playersStream);

    /*
     Check if game is over
    */
    bool isGameOver() const;

    std::unique_ptr<Event> createPack(std::istringstream& iss, int size);

    int readPackSize(std::istringstream& iss);


public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();

    /**
     * Print end game message
     *
     * @return - void
    */
    void printEndMessage();

    /**
     * Destructor
    */
  static bool containsIllegalChars(const std::string& name) {
    for (char c : name) {
        if (!std::isalpha(c)) { // Check if the character is not alphabetic
            return true; // Return true if an illegal character is found
        }
    }
    return false; // Return false if no illegal characters are found
}
};