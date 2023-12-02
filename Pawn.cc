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

	Vec passantRight = Vec(coordinate.getX() + 1, coordinate.getY());
	Vec passantLeft = Vec(coordinate.getX() - 1, coordinate.getY());

	// cout << "COORD: " << coordinate << endl;

	// Checks if there is a piece there, and is an enemy
	// Or En Passant Right option. Where there is an empty piece there
	// First we have to check that it actually is a valid coordinate there. 
	shared_ptr<Piece> p = pieceAt(gb, CaptureRight);
	if ((inBounds(CaptureRight) && (!isEmptyPiece(p) && (p->getTeam() != this->getTeam())))){
		possibleMoves.push_back(CaptureRight);
	}
	p = pieceAt(gb,CaptureLeft);
	if ((inBounds(CaptureLeft) && (!isEmptyPiece(p) && (p->getTeam() != this->getTeam())))){
		possibleMoves.push_back(CaptureLeft);
	}	
	p = pieceAt(gb,moveUp);
	if (inBounds(moveUp) && isEmptyPiece(p)){
		possibleMoves.push_back(moveUp);
	}
	p = pieceAt(gb,twoStep);
	if (inBounds(twoStep) && isEmptyPiece(p) && !moved){
		possibleMoves.push_back(twoStep);
	} 



	if (inBounds(CaptureLeft)&& inBounds(passantLeft) && canPassantLeft(gb, passantLeft)){
		possibleMoves.push_back(CaptureLeft);
	}
	if (inBounds(CaptureRight) && inBounds(passantRight) && canPassantRight(gb, passantRight)){
		possibleMoves.push_back(CaptureRight);
	}
}
// MAKE SURE THE PIECE DOESNT GO OUTSIDE THE BOARD LIMIT
// make sure you check there is actually a piece to capture 

// bool Pawn::canPassantRight(vector<vector<shared_ptr<Piece>>> gb) {
// 	Vec passantRight;
	
// }

bool Pawn::canPassantRight(vector<vector<shared_ptr<Piece>>> gb, Vec passantRight) {
	if (!inBounds(passantRight)) { return false; }
	if (getTeam() && coordinate.getY() == 4 && pawnMovedTwo(gb, passantRight, !this->getTeam())){
		return true;
	} else if(!this->getTeam() && coordinate.getY() == 3 && pawnMovedTwo(gb, passantRight, this->getTeam())) {
		return true;
	} else {
		return false; 
	}
}

bool Pawn::canPassantLeft(vector<vector<shared_ptr<Piece>>> gb, Vec passantLeft) {
	if (!inBounds(passantLeft)) { return false; }
	if (getTeam() && coordinate.getY() == 4 && pawnMovedTwo(gb, passantLeft, !this->getTeam())){
		return true;
	} else if(!this->getTeam() && coordinate.getY() == 3 && pawnMovedTwo(gb, passantLeft, this->getTeam())) { // We pass true
		return true;
	} else {
		return false; 
	}
}


// Check that the piece at the coordinate is a Pawn
// Also checks that it is an enemy
// Also checks that it moved two steps in one move
// White corresponds to what team is attempting/checking if it can do an en passant
bool Pawn::pawnMovedTwo(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate, bool white) {
	shared_ptr<Piece> p = pieceAt(gb, coordinate);
	//cout << "PAWN MOVED TWO: " << coordinate << endl;
	shared_ptr<Pawn> pawn;

	if (p->getType() == 'P' || p->getType() == 'p'){ 
		pawn = dynamic_pointer_cast<Pawn>(p); 
	} else return false;
	if(((white && pawn->getType() == 'P') || (!white && pawn->getType() == 'p')) && pawn->getMovedTwo()) {
		return true;
	}
	return false;

}

shared_ptr<Piece> Pawn::clone() const {
    return make_shared<Pawn>(*this);
}

