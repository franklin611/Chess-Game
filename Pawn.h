#ifndef _PAWN_H_
#define _PAWN_H_

#include "Piece.h"
#include "ChessBoard.h"

class Pawn : public Piece {

	// updates if a pawn moves two spaces as a starting move 
	bool movedTwo;

	// updates if a pawn moves from its starting position 
	bool moved;
	public:

		// default constructor 
		Pawn();

		// copy constructor 
		Pawn(const Pawn& other);

		// default constructor 
		Pawn(Vec coordinate, char type, bool white);


		void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override; // Overrides superclass function.

		bool canPassantRight(vector<vector<shared_ptr<Piece>>> gb, Vec passantRight); // Determines if the pawn can do an en Passant to the right
		bool canPassantLeft(vector<vector<shared_ptr<Piece>>> gb, Vec passantLeft); // Determines if the pawn can do an en passant to the left 

		bool getMovedTwo(); // Gets the movedTwo boolean 
		bool getMoved(); // gets the moved boolean 

		// updates that a pawn has moved two forward 
		void hasMovedTwo();

		// updates that a pawn moved forward 
		void hasMoved();

		bool pawnMovedTwo(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate, bool white); // Returns whether a pawn has moved twice or not

		// deep copy clone function 
		shared_ptr<Piece> clone() const override;
};

#endif
