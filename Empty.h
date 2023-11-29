#include "Piece.h"

class Empty : public Piece {
    public: 
        Empty();
        Empty(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
};

