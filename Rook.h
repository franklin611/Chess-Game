#include "Piece.h"

class Rook : public Piece {
    bool moved;
    public: 
        Rook();
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        bool getMoved();
};


