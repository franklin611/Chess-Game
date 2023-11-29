#include "Piece.h"
#include "Chessboard.h"


void Bishop::resetMoves() {
	legalMoves.clear();
}

// Just all possible moves
// Notes for Chiara
// I know you said just possibleMoves, but if I create a getter method that takes the type and checks if a piecee exists there
// That if that piece is of the same team, we cant go there, but if an enemy team, bishop cna go there
// And that is the last move bishop can make and break the for loop
void Bishop::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {

    // 4 for loops
    // To top right, to top left, to bottom right, to bottom left. Just keep continuously checking that we are withing bounds
    Vec move;
    // To top left Diagonal
    for (int i = 1; i < 7; ++i) {
        move = Vec{moveinate.getX() - i, coordinate.getY() - i};
        if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,coord))) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, coord)->getTeam() != getTeam()) {
            possibleMoves.push_back(move);
            // Last possible move they can make
            break;
        } else {
            break;
        }
    }

    // To top right Diagonal
    for (int i = 1; i < 7; ++i) {
        move = Vec{coordinate.getX() + i, coordinate.getY() -i};
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,coord))) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, coord)->getTeam() != getTeam()) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        }
    }

    // To bottom left Diagonal
    for (int i = 1; i < 7; ++i) {
        move = Vec{coordinate.getX() - i, coordinate.getY() + i};
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,coord))) { // If it is not an empty piece at that coordinate, then means there is a piece there. 
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, coord)->getTeam() != getTeam()) { // If the piece there is a enemy perfect! That is the last move.
            possibleMoves.push_back(move);
            break;
        } else { // Else a temamate piece, then no more moves so we break
            break;
        }
    }

    // To bottom right Diagonal
    for (int i = 1; i < 7; ++i) {
        move = Vec{coordinate.getX() + i, coordinate.getY() + i};
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,coord))) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, coord)->getTeam() != getTeam()) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        }
    }

}
