#ifndef _EMPTY_H_
#define _EMPTY_H_

#include "Piece.h"

class Empty : public Piece {
    public:
        // default constructor 
        Empty();

        // Copy constructor
        Empty(const Empty& other);

        ~Empty() override;

        // Empty Constructor
        Empty(Vec coordinate, char type, bool white);

        // Overrides superclass function. Determines the possible moves
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;

        // Function for a deep copy of Empty Piece
        shared_ptr<Piece> clone() const override;
};

#endif
