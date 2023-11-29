#include "Piece.h"
#include "ChessBoard.h"
#include "Bishop.h"
#include "Vec.h"

Bishop::Bishop(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour} {}

// Generates all possible Moves, taking into account the pieces on the GameBoard
void Bishop::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec move;
    // To top left Diagonal
    shared_ptr<Piece> p;
    for (int i = 1; i < 7; ++i) {
        move = Vec{coordinate.getX() - i, coordinate.getY() - i};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(pieceAt(gb,move))) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, move)->getTeam() != getTeam()) {
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
        p = pieceAt(gb, move);
         if(inBounds(move) && isEmptyPiece(pieceAt(gb,move))) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, move)->getTeam() != getTeam()) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        }
    }
    // To bottom left Diagonal
    for (int i = 1; i < 7; ++i) {
        move = Vec{coordinate.getX() - i, coordinate.getY() + i};
        p = pieceAt(gb, move);
         if(inBounds(move) && isEmptyPiece(pieceAt(gb,move))) { // If it is not an empty piece at that coordinate, then means there is a piece there. 
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, move)->getTeam() != getTeam()) { // If the piece there is a enemy perfect! That is the last move.
            possibleMoves.push_back(move);
            break;
        } else { // Else a temamate piece, then no more moves so we break
            break;
        }
    }
    // To bottom right Diagonal
    for (int i = 1; i < 7; ++i) {
        move = Vec{coordinate.getX() + i, coordinate.getY() + i};
        p = pieceAt(gb, move);
         if(inBounds(move) && isEmptyPiece(pieceAt(gb,move))) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, move)->getTeam() != getTeam()) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        }
    }
}
