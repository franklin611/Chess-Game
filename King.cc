#include "King.h"
#include "Player.h"
#include "Piece.h"

King::King() : Piece{}, moved{false} {}

void King::hasMoved(){
    moved = true;
}

void::getMOved() {
    return moved;
}

void King::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec move;

    Vec moveUp;
    Vec moveLeft;
    Vec moveRight;
    Vec moveDown;
    
}




    public: 
        void resetMoves() override; 
        King();
        vector<Vec> kingMoves();
        bool getMoved();
        void hasMoved();
};
