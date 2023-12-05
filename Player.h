#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Observer.h"
#include "ChessBoardObserver.h"
#include <memory> 
#include "Vec.h"
#include <vector> 
using namespace std;


// player is an observer to pieces, and a subject for chessboard to observe
class Player : public Observer {
    protected:
    bool colour;
    // Moves are categorized into 5 different types
    vector<vector<Vec>> legalMoves;
    vector<vector<Vec>> captureMoves;
    vector<vector<Vec>> checkMoves;
    vector<vector<Vec>> checkMateMoves;
    vector<vector<Vec>> avoidCaptureMoves;
    shared_ptr<ChessBoardObserver> cb; // player has a singular observer (chessboard)
    public:
        Player();
        Player(const Player& other);
        Player(bool colour, shared_ptr<ChessBoardObserver> cb); // since it's not a vector of observers then don't need attach and detach, just in ctor
        // Each of the below notifys will add a start and end move to their respective set of moves
        void notifyLM(Vec start, Vec end) override; 
        virtual void notifyCapM(Vec start, Vec end) override;
        virtual void notifyCheckM(Vec start, Vec end) override;
        virtual void notifyCMM(Vec start, Vec end) override;
        virtual void notifyACM(Vec start, Vec end) override;
        Player& operator=(const Player& other);
        virtual shared_ptr<Player> clone() const = 0; 
        // destructor 
        ~Player() = default;
};

#endif
