#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "Piece.h"
#include <iostream>

class Queen : public Piece {
    public:

        // Copy Constructor 
        Queen(const Queen& other);

        // Default Constructor 
        Queen(Vec coordinate, char type, bool white);

        // Queen's overriden getPossibleMoves that populates its own possible moves
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;

        // Creates a deep copy of a Queen 
        shared_ptr<Piece> clone() const override; 
};

#endif

