#include "Piece.h"

class Knight : public Piece {
    public: 
        Knight();
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
};

