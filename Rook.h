#include "Piece.h"

class Rook : public Piece {
    bool moved;
    public: 
        void resetMoves() override; 
        Rook();
        vector<Vec> rookMoves();
        bool getMoved();
};


