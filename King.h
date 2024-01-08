#ifndef _KING_H_
#define _KING_H_

#include "Piece.h"

class King : public Piece {
        bool moved;
    public:

        // default constructor 
        King();

        // Copy constructor
        King(const King& other);

        // Default cosntructor
        King(Vec coordinate, char type, bool white);

        // Overrides superclass function. Determines the possible moves
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;

        // Getters
        bool getMoved();

        // updates if the king has moved 
        void hasMoved();

        // Deep copy of King pieces
        shared_ptr<Piece> clone() const override;

};

#endif
