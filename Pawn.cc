#include "Pawn.h"
#include "ChessBoard.h"

bool Pawn::getMoved(){
	return moved; 
}

bool Pawn::getMovedTwo(){
	return movedTwo;
}

// We have to push back to vector<Vec> possibleMoves;
void Pawn::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
	Vec CaptureRight;
	Vec CaptureLeft;
	Vec moveUp;
	Vec twoStep;

	if (getTeam()){
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

	// Checks if there is a piece there, and is an enemy
	// Or En Passant Right option. Where there is an empty piece there
	// First we have to check that it actually is a valid coordinate there. 
	shared_ptr<Piece>() p = pieceAt(gb, CaptureRight);
	if (inBounds(CaptureRight) && (!isEmptyPiece(p) && (p->getTeam() != this->getTeam())) || (isEmptyPiece(p) && canPassantRight())){
		possibleMoves.push_back(CaptureRight);
	}
	p = pieceAt(gb,CaptureLeft);
	if (inBounds(CaptureLeft) && (!isEmptyPiece(p) && (p->getTeam() != this->getTeam())) || (isEmptyPiece(p) && canPassantRight())){
		possibleMoves.push_back(CaptureLeft);
	}	
	p = pieceAt(gb,moveUp);
	if (inBounds(moveUp) && isEmptyPiece(p)){
		possibleMoves.push_back(moveUp);
	}
	p = pieceAt(gb,twoStep);
	if (isEmptyPiece(p) && !moved){
		possibleMoves.push_back(twoStep);
	} 
}
// MAKE SURE THE PIECE DOESNT GO OUTSIDE THE BOARD LIMIT
// make sure you check there is actually a piece to capture 

bool Pawn::canPassantRight() {
	Vec passantRight = Vec(coordinate.getX() + 1, coordinate.getY());
	if (getTeam() && coordinate.getY() == 4 && game->pawnMovedTwo(passantRight, this->getTeam())){
		return true;
	} else if(!this->getType() && coordinate.getY() == 3 && game->pawnMovedTwo(passantRight, !this->getTeam())) {
		return true;
	} else {
		return false; 
	}
}

bool Pawn::canPassantLeft() {
	Vec passantLeft = Vec(coordinate.getX() - 1, coordinate.getY());
	if (getTeam() && coordinate.getY() == 4 && game->pawnMovedTwo(passantLeft, this->getTeam())){
		return true;
	} else if(!this->getTeam() && coordinate.getY() == 3 && game->pawnMovedTwo(passantLeft, !this->getTeam())) {
		return true;
	} else {
		return false; 
	}
}



// this might now look the same for all pieces because you decide the individuals moves per piece, then all the validation is the same for all pieces 
void Pawn::resetMoves(){
	legalMoves.clear();
	// determine all legal moves 
	// for (vector<Piece> vec : game->getGameBoard()){
	// 	for (Piece p : vec){
	// 		vector<Vec> moves = pawnMoves(); 
	// 		for (Vec end: moves){
	// 			if (!willCheck(coordinate, end)){
	// 				legalMoves.push_back(end);
	// 			};
	// 		} 
	// 	}
	// }
	// We are getting rid of this and putting in CHessboard
	// Each piece should just update is possibleM
}
