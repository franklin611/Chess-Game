#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "Piece.h"

class Bishop : public Piece {
    public:
        // Copy Constructor 
        Bishop(const Bishop& other);

        // Default Constructor 
        Bishop(Vec coordinate, char type, bool white);

        // Return the possible moves for a Bishop 
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        
        // Creates a deep copy of a Bishop 
        shared_ptr<Piece> clone() const override;
};

#endif
