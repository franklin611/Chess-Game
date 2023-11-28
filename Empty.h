#include "Piece.h"

class Empty : public Piece {
    public: 
        void resetMoves() override; 
        Empty();
        vector<Vec> emptyMove();
};

