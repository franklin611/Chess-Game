#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "Player.h"
#include "Level.h"
#include <random>
using namespace std;

class Computer : public Player {
    protected:
    // level of the player
    int userLevel;
    // facilitates what moves a player should prioritize
    unique_ptr<Level> level = nullptr;
    public:
        // computer constructor
        Computer(bool colour, shared_ptr<ChessBoardObserver> cb, int userLevel);
        // selects a move based on the level
        Vec makeComputerMove();
        // returns the level of the computer player
        int getLevel();
        // destructor 
        virtual ~Computer() = default;
};

#endif
