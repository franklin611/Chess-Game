#include "Piece.h"

class Queen : public Piece {
    public: 
        Queen();
        Queen(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
};

