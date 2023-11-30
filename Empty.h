#ifndef _EMPTY_H_
#define _EMPTY_H_

#include "Piece.h"

class Empty : public Piece {
    public:
        Empty();
        Empty(Empty&&) = default;
        Empty(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
};

#endif
