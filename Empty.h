#include "Piece.h"

class Empty : public Piece {
    public: 
        Empty();
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
};

