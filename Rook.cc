#include "Piece.h"
#include "Rook.h"

Rook:Rook() : Piece{}, moved{false} {}

void Rook::resetMoves() {
	legalMoves.clear();
	// determine all legal moves 
	// for (vector<Piece> vec : game->getGameBoard()){
	// 	for (Piece p : vec){
	// 		vector<Vec> moves = rookMovse(); 
	// 		for (Vec end: moves){
	// 			if (!willCheck(coordinate, end)){
	// 				legalMoves.push_back(end);
	// 			};
	// 		} 
	// 	}
	// }
}

// To make Chiara's life easier, I can also just check if there is a piece there.
// If our team, we can't make that move and break the for loop (Assuming we have 4 for loops for each
// direction) if it is an enemy team, capturing is the last move we can make then break. 
void Piece::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {

    for(int i = 1; i < 7; ++i) {
        // Going Down
        shared_ptr<Piece> p = pieceAt(gb,Vec{coordinate.getX(), coordinate.getY() + i});
        if(coordinate.getY() + i <= 7 && isEmptyPiece(p)) {
            possibleMoves.push_back(Vec{coordinate.getX(), coordinate.getY() + i})
        } else if (coordinate.getY() + i <= 7 && !p->getTeam()) {
            //Either out of bounds or not an empty piece
            // Still in bounds and is an enemy piece
            possibleMoves.pushBack(Vec{coordinate.getX(), coordinate.getY() + i});
            break;
            // Last Capture Move
        } // Elseit is a teammate piece or not possible
    }
    for(int i = 1; i < 7; ++i) {
        // Going Up
        shared_ptr<Piece> p = pieceAt(gb,Vec{coordinate.getX(), coordinate.getY() - i});
        if(coordinate.getY() - i >= 0 && isEmptyPiece(p)) {
            possibleMoves.push_back(Vec{coordinate.getX(), coordinate.getY() - i})
        } else if (coordinate.getY() - i >= 0 && !p->getTeam()) {
            possibleMoves.pushBack(Vec{coordinate.getX(), coordinate.getY() - i});
            break;
        }
    }
    for(int i = 1; i < 7; ++i) {
        // Going right
        shared_ptr<Piece> p = pieceAt(gb,Vec{coordinate.getX() + i, coordinate.getY()});
        if(coordinate.getX() + i <= 7 && isEmptyPiece(p)) {
            possibleMoves.push_back(Vec{coordinate.getX() + i, coordinate.getY()})
        } else if (coordinate.getX() + i <= 7 && !p->getTeam()) {
            possibleMoves.pushBack(Vec{coordinate.getX() + i, coordinate.getY()});
            break;
        }
    }
    for(int i = 1; i < 7; ++i) {
      // Going Left
        shared_ptr<Piece> p = pieceAt(gb,Vec{coordinate.getX() - i, coordinate.getY()});
        if(coordinate.getY() - i >= 0 && isEmptyPiece(p)) {
            possibleMoves.push_back(Vec{coordinate.getX(), coordinate.getY()})
        } else if (coordinate.getX() - i >= 0 && !p->getTeam()) {
            possibleMoves.pushBack(Vec{coordinate.getX(), coordinate.getY()});
            break;
        }
    }
    // Above were just the regular moves. Now to consider the Castle
}

bool Rook::getMoved() {
    return moved;
}
