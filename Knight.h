#include "Piece.h"

class Knight : public Piece {
    public: 
        void resetMoves() override; 
        Knight();
        vector<Vec> knightMoves();
};
