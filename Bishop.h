#include "Piece.h"

class Bishop : public Piece {
    public: 
        Bishop();
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb);
};

