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
    Vec move;

    for(int i = 1; i < 7; ++i) {
        // Going Down
        move = Vec{coordinate.getX(), coordinate.getY() + i};
        shared_ptr<Piece> p = pieceAt(gb, move);
        
        if(isBound(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (isBound(move) && !p->getTeam()) {
            //Either out of bounds or not an empty piece
            // Still in bounds and is an enemy piece
            possibleMoves.pushBack(move);
            break;
            // Last Capture Move
        } else {
            break;
        }   // Elseit is a teammate piece there so we can no longer go further
    }
    for(int i = 1; i < 7; ++i) {
        // Going Up
        move = Vec{coordinate.getX(), coordinate.getY() - i};
        shared_ptr<Piece> p = pieceAt(gb, move);
        if(isBound(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (isBound(move) && !p->getTeam()) {
            possibleMoves.pushBack(move);
            break;
        } else {
            break;
        } 
    }
    for(int i = 1; i < 7; ++i) {
        // Going right
        move = Vec{coordinate.getX() + i, coordinate.getY()};
        shared_ptr<Piece> p = pieceAt(gb, move);
        if(isBound(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (isBound(move) && !p->getTeam()) {
            possibleMoves.pushBack(move);
            break;
        } else {
            break;
        } 
    }
    for(int i = 1; i < 7; ++i) {
      // Going Left
        move = Vec{coordinate.getX() - i, coordinate.getY()};
        shared_ptr<Piece> p = pieceAt(gb, move);
        if(isBound(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (isBound(move) && !p->getTeam()) {
            possibleMoves.pushBack(move);
            break;
        } else {
            break;
        } 
    }
    // Above were just the regular moves. Now to consider the Castle
    // Will be done in King
    // I do not need to worry about it in Rooks
}

bool Rook::getMoved() {
    return moved;
}
