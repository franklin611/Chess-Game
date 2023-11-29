#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Observer.h"
#include "Vec.h"
#include <vector> // if I have the include in .h then don't need in .cc
using namespace std;

// player is an observer to pieces, and a subject for chessboard to observe
class Player : public Observer {
    bool colour;
    // use this to call chessboard's notify()
    unique_ptr<Observer> cb; // player has a singular observer (chessboard)
    // vector of vectors that contain vec (start and end)
    vector<vector<Vec>> legalMoves;

    public:
        Player(bool colour, unique_ptr<Observer> cb); // since it's not a vector of observers then don't need attach and detach, just in ctor

        // this is so it can get notified by Pieces
        void notify(Vec start, Vec end) override; // this will add a legal move to the legal moves field

        // don't need a notifyChessboard or anything because we are calling chessboard's notify inside chooseHumanMove/chooseComputerMove
        ~Player() = default;
};

#endif
