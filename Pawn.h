#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.h"

class Pawn : public Piece {
	bool movedTwo;
	bool moved;
	public:
		Pawn();
		Pawn(Vec coordinate, char type, bool white);
		void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
		bool canPassantRight(vector<vector<shared_ptr<Piece>>> gb);
		bool canPassantLeft(vector<vector<shared_ptr<Piece>>> gb);
		bool getMovedTwo();
		bool getMoved();
		void hasMovedTwo();
		void hasMoved();
		bool pawnMovedTwo(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate, bool white);
};

#endif
