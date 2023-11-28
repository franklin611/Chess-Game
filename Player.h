#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Observer.h"
#include "Vec.h"
#include <vector>
class Player : public Observer {
    bool colour;
    unique_ptr<Observer> cb; // use this to call chessboard's notify()
    vector<vector<Vec>> legalMoves;
    public:
        Player(bool colour) : colour{colour} {}
        void notify(Vec start, Vec end) override; // this will add a legal move to the legal moves field 
};

#endif
