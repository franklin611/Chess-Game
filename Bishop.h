#include "Piece.h"

class Bishop : public Piece {
    public: 
        void resetMoves() override; 
        Bishop();
        vector<Vec> bishopMoves();
};

