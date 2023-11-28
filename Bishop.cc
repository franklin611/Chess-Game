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

// Just all possible moves
// Notes for Chiara
// I know you said just possibleMoves, but if I create a getter method that takes the type and checks if a piecee exists there
// That if that piece is of the same team, we cant go there, but if an enemy team, bishop cna go there
// And that is the last move bishop can make and break the for loop
vector<Vec> Bishop::bishopMoves() {
    vector<Vec> moves;

    // 4 for loops
    // To top right, to top left, to bottom right, to bottom left. Just keep continuously checking that we are withing bounds
    
    // // To top left Diagonal
    // for (int i = 1; i < 7; ++i) {
    //     if((coordinate.getX() - i >= 0)  && (coordinate.getY() - i >= 0)) {
    //         moves.push_back(Vec{coordinate.getX() - i, coordinate.getY() - i});
    //     } else {
    //         break;
    //     }
    // }

    // // To top right Diagonal
    // for (int i = 1; i < 7; ++i) {
    //     if((coordinate.getX() + i <= 7)  && (coordinate.getY() - i >= 0)) {
    //         moves.push_back(Vec{coordinate.getX() + i, coordinate.getY() - i});
    //     } else {
    //         break;
    //     }
    // }

    // // To bottom left Diagonal
    // for (int i = 1; i < 7; ++i) {
    //     if((coordinate.getX() - i >= 0)  && (coordinate.getY() + i <= 7)) {
    //         moves.push_back(Vec{coordinate.getX() - i, coordinate.getY() + i});
    //     } else {
    //         break; 
    //     }
    // }

    // // To bottom right Diagonal
    // for (int i = 1; i < 7; ++i) {
    //     if((coordinate.getX() + i >= 0)  && (coordinate.getY() + i >= 0)) {
    //         moves.push_back(Vec{coordinate.getX() + i, coordinate.getY() + i});
    //     } else {
    //         break;
    //     }
    // }

    // To top right, to top left, to bottom right, to bottom left. Just keep continuously checking that we are withing bounds
    for (int i = 1; i < 7; ++i) {
        // To top left Diagonal
        if((coordinate.getX() - i >= 0)  && (coordinate.getY() - i >= 0)) {
            moves.push_back(Vec{coordinate.getX() - i, coordinate.getY() - i});
        } 
        // To top right Diagonal
        if((coordinate.getX() + i <= 7)  && (coordinate.getY() - i >= 0)) {
            moves.push_back(Vec{coordinate.getX() + i, coordinate.getY() - i});
        } 
        // To bottom left Diagonal
        if((coordinate.getX() - i >= 0)  && (coordinate.getY() + i <= 7)) {
            moves.push_back(Vec{coordinate.getX() - i, coordinate.getY() + i});
        }
        // To bottom right Diagonal
        if((coordinate.getX() + i >= 0)  && (coordinate.getY() + i >= 0)) {
            moves.push_back(Vec{coordinate.getX() + i, coordinate.getY() + i});
        }
    }

    return moves;

// bool getColour();
// void Piece::getColour() return white; // Returns the boolean value of whether it is true or not

}
