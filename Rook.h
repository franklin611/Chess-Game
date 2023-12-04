#ifndef _ROOK_H_
#define _ROOK_H_
#include <iostream>
#include "Piece.h"

class Rook : public Piece {
    bool moved; // Boolean value if the Rook has moved (For castling)
    public:
        // Copy Constructor
        Rook(const Rook & other);

        // Default Constructor 
        Rook(Vec coordinate, char type, bool white); // Rook constructor with speciic values

        ~Rook() override;

        // Overrides superclass function. Determines the possible moves of a pawn
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override; 

        // Getter method
        bool getMoved();  

         // Creates a deep copy of a Rook 
        shared_ptr<Piece> clone() const override; // Used for subclass cloning
};

#endif
