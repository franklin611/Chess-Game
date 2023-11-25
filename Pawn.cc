#include "Pawn.h"
#include "ChessBoard.h"


// MAKE SURE THE PIECE DOESNT GO OUTSIDE THE BOARD LIMIT
// make sure you check there is actually a piece to capture 
vector<Vec> Pawn::pawnMoves() {
	Vec CaptureRight;
	Vec CaptureLeft;
	Vec moveUp;
	Vec twoStep;
	vector<Vec> moves; 

	// determine possible capture moves
	if (white){
		CaptureRight = Vec(coordinate.getX() + 1, coordinate.getY() + 1);
		CaptureLeft = Vec(coordinate.getX() - 1, coordinate.getY() + 1);
		moveUp = Vec(coordinate.getX(), coordinate.getY() + 1);
		twoStep = Vec(coordinate.getX(), coordinate.getY() + 2);
	} else {
		CaptureRight = Vec(coordinate.getX() + 1, coordinate.getY() - 1);
		CaptureLeft = Vec(coordinate.getX() - 1, coordinate.getY() - 1);
		moveUp = Vec(coordinate.getX(), coordinate.getY() - 1);
		twoStep = Vec(coordinate.getX(), coordinate.getY() - 2);

	}

	if (game->isThere(CaptureRight) || canPassant()){
		moves.push_back(CaptureRight);
	} else if (game->isThere(CaptureLeft) || canPassant()){
		moves.push_back(CaptureLeft);
	} else if (!game->isThere(moveUp)){
		moves.push_back(moveUp);
	} else if (!game->isThere(twoStep) && !moved){
		moves.push_back(twoStep);
	} 


	// determine possible passant moves 

	return moves; 
}


bool Pawn::canPassant(){
	Vec passantLeft = Vec(coordinate.getX() - 1, coordinate.getY());
	Vec passantRight = Vec(coordinate.getX() + 1, coordinate.getY());

	// if white and my y coordinate is 4 
	if (white && coordinate.getY() == 4 && game->pawnMovedTwo(passantLeft, white)){
		

	}
	

	//  if my y coordinate is 3 

	
}


// this might now look the same for all pieces because you decide the individuals moves per piece, then all the validation is the same for all pieces 
void Pawn::resetMoves(){
	legalMoves.clear();
	// determine all legal moves 
	for (vector<Piece> vec : game->getGameBoard()){
		for (Piece p : vec){
			vector<Vec> moves = pawnMoves(); 
			for (Vec end: moves){
				if (!willCheck(coordinate, end)){
					legalMoves.push_back(end);
				};
			} 
		}
	}
}
