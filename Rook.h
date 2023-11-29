#include "Piece.h"

class Rook : public Piece {
    bool moved;
    public: 
        Rook();
        Rook(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        bool getMoved();
};


