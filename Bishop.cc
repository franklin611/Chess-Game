#include "Piece.h"
#include "Chessboard.h"


void Bishop::resetMoves() {
	legalMoves.clear();
	// determine all legal moves 
	for (vector<Piece> vec : game->getGameBoard()){
		for (Piece p : vec){
			vector<Vec> moves = bishopMoves(); 
			for (Vec end: moves){
				if (!willCheck(coordinate, end)){
					legalMoves.push_back(end);
				};
			} 
		}
	}
}



#include "Piece.h"
#include "Chessboard.h"


void Bishop::resetMoves() {
	legalMoves.clear();
	// determine all legal moves 
	// for (vector<Piece> vec : game->getGameBoard()){
	// 	for (Piece p : vec){
	// 		vector<Vec> moves = bishopMoves(); 
	// 		for (Vec end: moves){
	// 			if (!willCheck(coordinate, end)){
	// 				legalMoves.push_back(end);
	// 			};
	// 		} 
	// 	}
	// }
}

// Just all possible moves
// Notes for Chiara
// I know you said just possibleMoves, but if I create a getter method that takes the type and checks if a piecee exists there
// That if that piece is of the same team, we cant go there, but if an enemy team, bishop cna go there
// And that is the last move bishop can make and break the for loop
void Bishop::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {

    // 4 for loops
    // To top right, to top left, to bottom right, to bottom left. Just keep continuously checking that we are withing bounds
    
    // To top left Diagonal
    for (int i = 1; i < 7; ++i) {
        Vec coord = Vec{coordinate.getX() - i, coordinate.getY() - i};

        if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,coord))) {
            possibleMoves.push_back(coord);
        } else if (inBounds(coord) && piecAt(gb, coord)->getTeam() != getTeam()) {
            possibleMoves.push_back(coord);
            // Last possible move they can make
            break;
        }
    }

    // To top right Diagonal
    for (int i = 1; i < 7; ++i) {
        Vec coord = Vec{coordinate.getX() + i, coordinate.getY() -i};
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,coord))) {
            possibleMoves.push_back(coord);
        } else if (inBounds(coord) && piecAt(gb, coord)->getTeam() != getTeam()) {
            possibleMoves.push_back(coord);
            break;
        }
    }

    // To bottom left Diagonal
    for (int i = 1; i < 7; ++i) {
        Vec coord = Vec{coordinate.getX() - i, coordinate.getY() + i};
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,coord))) {
            possibleMoves.push_back(coord);
        } else if (inBounds(coord) && piecAt(gb, coord)->getTeam() != getTeam()) {
            possibleMoves.push_back(coord);
            break;
        }
    }

    // To bottom right Diagonal
    for (int i = 1; i < 7; ++i) {
        Vec coord = Vec{coordinate.getX() + i, coordinate.getY() + i};
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,coord))) {
            possibleMoves.push_back(coord);
        } else if (inBounds(coord) && piecAt(gb, coord)->getTeam() != getTeam()) {
            possibleMoves.push_back(coord);
            break;
        }
    }

}
