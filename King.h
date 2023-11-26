#include "Piece.h"

class King : public Piece {
        bool moved;
    public: 
        void resetMoves() override; 
        King();
        vector<Vec> kingMoves();
        bool getMoved();
        void hasMoved();
};

