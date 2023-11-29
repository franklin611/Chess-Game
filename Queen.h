#include "Piece.h"

class Queen : public Piece {
    public: 
        Queen();
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
};

