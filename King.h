#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King : public Piece {
        bool moved;
    public:
        King();
        King(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        bool getMoved();
        void hasMoved();
};

#endif
