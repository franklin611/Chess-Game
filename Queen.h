#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.h"
#include <iostream>

class Queen : public Piece {
    public:
        Queen();
        Queen(const Queen& other);
        Queen(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        shared_ptr<Piece> clone() const override;
};

#endif

