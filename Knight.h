#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "Piece.h"

class Knight : public Piece {
    public:
        // Copy Constructor 
        Knight(const Knight& other);

        // Default Constructor 
        Knight(Vec coordinate, char type, bool white);

        // Overrides superclass function. Determines the possible moves of a pawn
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override; 

        // Creates a deep copy of a Bishop 
        shared_ptr<Piece> clone() const override;
};

#endif
