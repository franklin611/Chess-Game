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
		void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override; // Overrides superclass function.
		// Determines the possible moves of a pawn
		bool canPassantRight(vector<vector<shared_ptr<Piece>>> gb, Vec passantRight); // Determines if the pawn can do an en Passant to the right
		bool canPassantLeft(vector<vector<shared_ptr<Piece>>> gb, Vec passantLeft); // To the left
		bool getMovedTwo(); // Getter methods
		bool getMoved();
		void hasMovedTwo();
		void hasMoved();
		bool pawnMovedTwo(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate, bool white); // Returns whether a pawn has moved twice or not
		shared_ptr<Piece> clone() const override;
};

#endif
