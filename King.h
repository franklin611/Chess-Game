#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King : public Piece {
        bool moved;
    public:
        King();
        King(const King& other);
        King(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        bool getMoved();
        void hasMoved();
        shared_ptr<Piece> clone() const override;
};

#endif
