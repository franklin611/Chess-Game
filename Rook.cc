#include "Piece.h"
#include "Rook.h"

Rook:Rook() : Piece{}, moved{false} {}

void Rook::resetMoves() {
	legalMoves.clear();
	// determine all legal moves 
	for (vector<Piece> vec : game->getGameBoard()){
		for (Piece p : vec){
			vector<Vec> moves = rookMovse(); 
			for (Vec end: moves){
				if (!willCheck(coordinate, end)){
					legalMoves.push_back(end);
				};
			} 
		}
	}
}

// To make Chiara's life easier, I can also just check if there is a piece there.
// If our team, we can't make that move and break the for loop (Assuming we have 4 for loops for each
// direction) if it is an enemy team, capturing is the last move we can make then break. 
vector<Vec> rookMoves() {
    vector<Ve> moves;

    for(int i = 1; i < 7; ++i) {
        // Going Down
        if(coordinate.getY() + i <= 7) {
            moves.push_back(Vec{coordinate.getX(), coordinate.getY() + i})
        }
        // Going Up
        if(coordinate.getY() - i >= 0) {
            moves.push_back(Vec{coordinate.getX(), coordinate.getY() - i})
        }
        // Going right
        if(coordinate.getX() + i <= 7) {
            moves.push_back(Vec{coordinate.getX() + i, coordinate.getY()})
        }
        // Going Left
        if(coordinate.getY() - i >= 0) {
            moves.push_back(Vec{coordinate.getX() - i, coordinate.getY()})
        }
    }

    return moves; 

}

bool Rook::getMoved() {
    return moved;
}
