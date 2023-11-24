#include "Pawn.h"
#include "ChessBoard.h"

vector<Vec> Pawn::pawnCaptureMoves() {
	vector<Vec> CaptureMoves; 
	if (white){
		CaptureMoves.emplace_back(coordinate.getX() + 1, coordinate.getY() + 1);
		CaptureMoves.emplace_back(coordinate.getX() - 1, coordinate.getY() + 1);
	} else { 
		CaptureMoves.emplace_back(coordinate.getX() + 1, coordinate.getY() - 1);
		CaptureMoves.emplace_back(coordinate.getX() - 1, coordinate.getY() - 1);
	}
	return CaptureMoves; 
}


vector<Vec> Pawn::pawnMove(){
	Vec moveUp;
	if (white){ moveUp = Vec(coordinate.getX(), coordinate.getY() + 1); }
	else { moveUp = Vec(coordinate.getX(), coordinate.getY() - 1); }
	vector<Vec> moves;
	// if there is no piece at moveUp add it to the vector 
	vector<vector<Piece>> gameBoard = game->getGameBoard(); 
	for(vector<Piece> vec : gameBoard){
		for(Piece p : vec){
			if (p.getCoordinate() == moveUp){ moves.push_back(moveUp); }
		}
	}
	return moves;
}

// if the pawn has not moved yet and there isnt another piece at the point then it is a valid move 
// FINISH
vector<Vec> Pawn::pawnTwoStep(){
	Vec twoStep;
	if (white) {
		twoStep = Vec(coordinate.getX(), coordinate.getY() + 2);
	} else {
		twoStep = Vec(coordinate.getX(), coordinate.getY() - 2);
	}

	// if there is no piece at twoStep and the pawn hasn't moved yet add it to the vector 

	// else return empty vector

}

// passant 
// white is at 4 -> white pawn can move diagonal to 5 and capture a black pawn in 4
// black is at 3 -> black pawn can move diagonal to 2 and capture a white pawn in 3 
// we therefore need to know the two cases 
// case 1: i am a white pawn and i want to capture a black pawn 
// 	it is a valid move if there is a black pawn to my right or left that has it's movedTwo boolean true
// case 2: i am a black pawn and i want to capture a white pawn
//  it is a valid move if there is a white pawn to my right or left that has it's movedTwo boolean true
// if it is valid we add it to the valid moves list -> how do we know to capture the pawn? we would need to have a different notification case for that 


vector<Vec> Pawn::passant(){
	Vec passant; 

	// if another pawn moved forward 2 

	
}

void Pawn::resetMoves(){
	legalMoves.clear();
	// determine all legal moves 
	for (vector<Piece> vec : game->getGameBoard()){
		for (Piece p : vec){
			// if this pawn and opposing piece are diagonal 
			vector<Vec> captureMoves = pawnCaptureMoves(); 

			// if there exists no piece in front of the pawn 
			vector<Vec> move = pawnMove();

			// if it hasn't moved yet can it move two spaces forward 
			vector<Vec> twoStep = pawnTwoStep();
		
			// determine if any of the moves put the king in check
			for (Vec end: captureMoves){
				if (!willCheck(coordinate, end)){
					legalMoves.push_back(end);
				}
			} 

			for (Vec end: move){
				if (!willCheck(coordinate, end)){
					legalMoves.push_back(end);
				};
			} 

			for (Vec end: twoStep){
				if (!willCheck(coordinate, end)){
					legalMoves.push_back(end);
				};
			} 


		}
	}

	// remove any moves that do not take king out of check 
	if (white && WCheck) { ... }
	if (!white && BCheck) { ... }
}
