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
        // Queen's overriden getPossibleMoves that populates its own possible moves
        shared_ptr<Piece> clone() const override; // For piece subclass copying/cloning
};

#endif

