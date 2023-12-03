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
        // ISSUE: why are we feeding it a level when it has access to its own level? 
        Vec makeComputerMove(int userLevel);
        // ISSUE: does this need to be a member function? 
        // selects a random move 
        vector<Vec> selectRandomMove(vector<vector<Vec>> &vectors);
        // returns the level of the computer player 
        int getLevel();
};

#endif


// makeComputerMove needs to select a move from selectMove from its associated level and then call cb's notify (notify chessboard to make the move)
// chessboard observes the player (subject)
// to select a move, it takes the vector of legal moves that player has, and then calls select move on that (since in select move we have logic)
// of filtering what move
// then based on turn (maybe colour since player has that?) it calls chessboard's notify (check if chessbord's notify takes in a colour/turn already)
// and then in chessboard's move it calls td notify

// TODO: add game output operator rewritten and add that in chessboard's output operator to display score, confirm how main calls it