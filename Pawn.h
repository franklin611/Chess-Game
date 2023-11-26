#include "Piece.h"

class Pawn : public Piece { 
	bool movedTwo; 
	bool moved; 
	public: 
		void resetMoves() override; 
		Pawn(); 
		vector<Vec> pawnMoves();
		bool canPassant();
		bool getMovedTwo();
		bool getMoved();
		void hasMovedTwo(); 
		void hasMoved();
}; 

