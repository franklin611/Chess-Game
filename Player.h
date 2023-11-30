#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Observer.h"
#include "ChessBoardObserver.h"
#include <memory> // Not sure if we need
#include "Vec.h"
#include <vector> // if I have the include in .h then don't need in .cc
using namespace std;


// player is an observer to pieces, and a subject for chessboard to observe
class Player : public Observer {
    protected:
    bool colour;
    vector<vector<Vec>> legalMoves;
    vector<vector<Vec>> captureMoves;
    vector<vector<Vec>> checkMoves;
    vector<vector<Vec>> checkMateMoves;
    vector<vector<Vec>> avoidCaptureMoves;
    unique_ptr<ChessBoardObserver> cb; // player has a singular observer (chessboard)
    // vector of vectors that contain vec (start and end)
    // friend class Computer;
    public:
        Player(bool colour, shared_ptr<ChessBoardObserver> cb); // since it's not a vector of observers then don't need attach and detach, just in ctor

        // TODO: this should be that it gets notified by chessboard
        // this is so it can get notified by Pieces
        void notifyLM(Vec start, Vec end) override; // this will add a legal move to the legal moves field
        virtual void notifyCapM(Vec start, Vec end) override;
        virtual void notifyCheckM(Vec start, Vec end) override;
        virtual void notifyCMM(Vec start, Vec end) override;

        // don't need a notifyChessboard or anything because we are calling chessboard's notify inside chooseHumanMove/chooseComputerMove
        ~Player() = default;
        // vector<vector<Vec>> getLegalMoves(); // TODO: think dont need this
        // virtual shared_ptr<Player> clone() const = 0;
};

#endif
