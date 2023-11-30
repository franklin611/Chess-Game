#include "Pawn.h"

void Pawn::hasMoved(){
	moved = true;
}

void Pawn::hasMovedTwo(){
	movedTwo = true;
}

Pawn::Pawn(Vec coordinate, char type, bool white) : Piece{coordinate, type, white}, movedTwo{false}, moved{false} {}

Pawn::Pawn(const Pawn& other) : Piece{other}, movedTwo{other.movedTwo}, moved{other.moved} {}
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
	shared_ptr<Piece> p = pieceAt(gb, CaptureRight);
	if ((inBounds(CaptureRight) && (!isEmptyPiece(p) && (p->getTeam() != this->getTeam()))) || inBounds(CaptureRight) && (isEmptyPiece(p) && canPassantRight(gb))){
		possibleMoves.push_back(CaptureRight);
	}
	p = pieceAt(gb,CaptureLeft);
	if ((inBounds(CaptureLeft) && (!isEmptyPiece(p) && (p->getTeam() != this->getTeam()))) || inBounds(CaptureLeft) && (isEmptyPiece(p) && canPassantRight(gb))){
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

bool Pawn::canPassantRight(vector<vector<shared_ptr<Piece>>> gb) {
	Vec passantRight = Vec(coordinate.getX() + 1, coordinate.getY());
	if (getTeam() && coordinate.getY() == 4 && pawnMovedTwo(gb, passantRight, this->getTeam())){
		return true;
	} else if(!this->getType() && coordinate.getY() == 3 && pawnMovedTwo(gb, passantRight, !this->getTeam())) {
		return true;
	} else {
		return false; 
	}
}

bool Pawn::canPassantLeft(vector<vector<shared_ptr<Piece>>> gb) {
	Vec passantLeft = Vec(coordinate.getX() - 1, coordinate.getY());
	if (getTeam() && coordinate.getY() == 4 && pawnMovedTwo(gb, passantLeft, this->getTeam())){
		return true;
	} else if(!this->getTeam() && coordinate.getY() == 3 && pawnMovedTwo(gb, passantLeft, !this->getTeam())) {
		return true;
	} else {
		return false; 
	}
}

// Chessboard has one but this is specifically to the Pawn Piece
// Logic is pawnMovedTwo

// Check that the piece at the coordinate is a Pawn
// Also checks that it is an enemy
// Also checks that it moved two steps in one move
// White corresponds to what team is attempting/checking if it can do an en passant
bool Pawn::pawnMovedTwo(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate, bool white) {
	shared_ptr<Piece> p = pieceAt(gb, coordinate);
	char type = p->getType();
	shared_ptr<Pawn> pawn;
	if (type == 'P' || type == 'p'){ 
		pawn = dynamic_pointer_cast<Pawn>(p); 
	} else return false;
	if(((white && type == 'p') || (!white && type == 'P')) && pawn->getMovedTwo()) {
		return true;
	}
	return false;

}

shared_ptr<Piece> Pawn::clone() const {
    return make_shared<Pawn>(*this);
}

