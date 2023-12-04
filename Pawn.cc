#include "Pawn.h"

// update that a pawn has moved 
void Pawn::hasMoved(){
	moved = true;
}

// updated that a pawn has moved two spaces at start
void Pawn::hasMovedTwo(){
	movedTwo = true;
}

// default constructor 
Pawn::Pawn(Vec coordinate, char type, bool white) : Piece{coordinate, type, white}, movedTwo{false}, moved{false} {}

// copy constructor 
Pawn::Pawn(const Pawn& other) : Piece{other}, movedTwo{other.movedTwo}, moved{other.moved} {}

// return the moved boolean
bool Pawn::getMoved(){
	return moved; 
}

// return the movedTwo boolean 
bool Pawn::getMovedTwo(){
	return movedTwo;
}

// Gets the possible moves of the pawn based on the current passed gameboard
// It populates through push_back the possibleMoves field
void Pawn::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
	Vec CaptureRight;
	Vec CaptureLeft;
	Vec moveUp;
	Vec twoStep;

	// The movement of the pawn differs whether it is black or white
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

	shared_ptr<Piece> p = pieceAt(gb, CaptureRight);
	// Determines if capturing to the right is valid by checking that there is a piece there that is on the opposite team
	if ((inBounds(CaptureRight) && (!isEmptyPiece(p) && (p->getTeam() != this->getTeam())))){
		possibleMoves.push_back(CaptureRight);
	}
	p = pieceAt(gb,CaptureLeft); // Same logic for left diagonal
	if ((inBounds(CaptureLeft) && (!isEmptyPiece(p) && (p->getTeam() != this->getTeam())))){
		possibleMoves.push_back(CaptureLeft);
	}	
	p = pieceAt(gb,moveUp);
	if (inBounds(moveUp) && isEmptyPiece(p)){
		possibleMoves.push_back(moveUp);
	}
	// Determines if the piece can take move two steps
	p = pieceAt(gb,twoStep);
	shared_ptr<Piece> pCheck = pieceAt(gb,moveUp);
	// Need to make sure that it is also an empty piece between them
	if (inBounds(twoStep) && inBounds(moveUp) && isEmptyPiece(pCheck) && isEmptyPiece(p) && !moved){
		possibleMoves.push_back(twoStep);
	} 
	// Logic for determining if the Pawn can passantLeft or right
	if (inBounds(CaptureLeft)&& inBounds(passantLeft) && canPassantLeft(gb, passantLeft)){
		possibleMoves.push_back(CaptureLeft);
	}
	if (inBounds(CaptureRight) && inBounds(passantRight) && canPassantRight(gb, passantRight)){
		possibleMoves.push_back(CaptureRight);
	}
}

// Logic for determining if the Pawn can Passant Right
// Checks the condition that we are on row 4 or 3 depending on the colour of the Pawn
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

// checks if a pawn is able to en passant to the left of the board 
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

// Checks that the pawn it is attempting to capture is on the opposite team,and has moved twice in one move, and is a pawn
bool Pawn::pawnMovedTwo(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate, bool white) {
	shared_ptr<Piece> p = pieceAt(gb, coordinate);
	shared_ptr<Pawn> pawn;
	if (p->getType() == 'P' || p->getType() == 'p'){ 
		pawn = dynamic_pointer_cast<Pawn>(p); 
	} else return false;
	if(((white && pawn->getType() == 'P') || (!white && pawn->getType() == 'p')) && pawn->getMovedTwo()) {
		return true;
	}
	return false;

}

// deep copy clone function
shared_ptr<Piece> Pawn::clone() const {
    return make_shared<Pawn>(*this);
}

