#include "Piece.h"

class Queen : public Piece {
    public: 
        void resetMoves() override; 
        Queen();
        vector<Vec> queenMoves();
};
