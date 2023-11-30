#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "Piece.h"
#include <iostream>

class Bishop : public Piece {
    public:
        Bishop();
        Bishop(const Bishop& other);
        Bishop(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
        shared_ptr<Piece> clone() const override;
};

#endif
