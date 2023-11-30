#ifndef _ROOK_H_
#define _ROOK_H_

#include "Piece.h"

class Rook : public Piece {
    bool moved;
    public:
        Rook();
        Rook(const Rook & other);
        Rook(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        bool getMoved();
        shared_ptr<Piece> clone() const override;
};

#endif
