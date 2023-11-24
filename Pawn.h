#include "Piece.h"

class Pawn : public Piece { 
	bool movedTwo; 
	bool moved; 
	public: 
		void resetMoves() override; 
		Pawn(); 
		vector<Vec> passant(); 
		vector<Vec> pawnCaptureMoves(); 
		vector<Vec> pawnMove();
		vector<Vec> pawnTwoStep(); 
}; 
