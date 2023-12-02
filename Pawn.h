#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.h"
#include "ChessBoard.h"

class Pawn : public Piece {
	bool movedTwo;
	bool moved;
	public:
		Pawn();
		Pawn(const Pawn& other);
		Pawn(Vec coordinate, char type, bool white);
		void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
		bool canPassantRight(vector<vector<shared_ptr<Piece>>> gb, Vec passantRight);
		bool canPassantLeft(vector<vector<shared_ptr<Piece>>> gb, Vec passantLeft);
		bool getMovedTwo();
		bool getMoved();
		void hasMovedTwo();
		void hasMoved();
		bool pawnMovedTwo(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate, bool white);
		shared_ptr<Piece> clone() const override;
};

#endif
