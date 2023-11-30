#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "Piece.h"

class Bishop : public Piece {
    public:
        Bishop();
        Bishop(Vec coordinate, char type, bool white);
        void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
};

#endif
