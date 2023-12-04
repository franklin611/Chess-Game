#ifndef _ROOK_H_
#define _ROOK_H_
#include <iostream>
#include "Piece.h"

class Rook : public Piece {
    bool moved; // Boolean value if the Rook has moved (For castling)
    public:
        Rook();
        Rook(const Rook & other);
        Rook(Vec coordinate, char type, bool white); // Rook constructor with speciic values
        ~Rook() override;
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        bool getMoved();
        void hasMoved();
        shared_ptr<Piece> clone() const override;
};

#endif
