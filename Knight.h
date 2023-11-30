#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "Piece.h"

class Knight : public Piece {
    public:
        Knight();
        Knight(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
};

#endif
