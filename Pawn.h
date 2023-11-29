#include "Piece.h"

class Pawn : public Piece { 
	bool movedTwo; 
	bool moved; 
	public: 
		Pawn(); 
		void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) override;
		bool canPassantRight();
		bool canPassantLeft();
		bool getMovedTwo();
		bool getMoved();
		void hasMovedTwo(); 
		void hasMoved();
		bool pawnMovedTwo();
}; 

