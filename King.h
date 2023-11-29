#include "Piece.h"

class King : public Piece {
        bool moved;
    public: 
        King();
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        bool getMoved();
        void hasMoved();
};

