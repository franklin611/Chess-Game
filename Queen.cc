#include "Piece.h"
#include "Queen.h"

Queen::Queen(Vec coordinate, char type, bool white) : Piece{coordinate, type, white} {}

void Queen::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec move;

    // To top left diagonal
    for (int i = 1; i < 7; ++i) {
        move = Vec{coordinate.getX() - i, coordinate.getY() - i};
        if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,move))) {
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
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,move))) {
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
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,move))) { // If it is not an empty piece at that coordinate, then means there is a piece there. 
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
         if(inBounds(Vec) && isEmptyPiece(pieceAt(gb,move))) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && pieceAt(gb, move)->getTeam() != getTeam()) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        }
    }

    for(int i = 1; i < 7; ++i) {
        // Going Down
        move = Vec{coordinate.getX(), coordinate.getY() + i};
        shared_ptr<Piece> p = pieceAt(gb, move);
        
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !p->getTeam()) {
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
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !p->getTeam()) {
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
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !p->getTeam()) {
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
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !p->getTeam()) {
            possibleMoves.pushBack(move);
            break;
        } else {
            break;
        } 
    }
}
