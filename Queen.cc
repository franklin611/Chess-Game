#include "Queen.h"

Queen::Queen(Vec coordinate, char type, bool white) : Piece{coordinate, type, white} {}

Queen::Queen(const Queen& other): Piece{other} {}

void Queen::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec move;
    shared_ptr<Piece> p;
    // To top left diagonal
    for (int i = 1; i < 8; ++i) {
        move = Vec{coordinate.getX() - i, coordinate.getY() - i};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) { // We dont care that 
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) {
            possibleMoves.push_back(move);
            // Last possible move they can make
            break;
        } else {
            break;
        }
    }

    // To top right Diagonal
    for (int i = 1; i < 8; ++i) {
        move = Vec{coordinate.getX() + i, coordinate.getY() -i};
        p = pieceAt(gb, move);
         if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        }
    }

    // To bottom left Diagonal
    for (int i = 1; i < 8; ++i) {
        move = Vec{coordinate.getX() - i, coordinate.getY() + i};
        p = pieceAt(gb, move);
         if(inBounds(move) && isEmptyPiece(p)) { // If it is not an empty piece at that coordinate, then means there is a piece there. 
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) { // If the piece there is a enemy perfect! That is the last move.
            possibleMoves.push_back(move);
            break;
        } else { // Else a temamate piece, then no more moves so we break
            break;
        }
    }

    // To bottom right Diagonal
    for (int i = 1; i < 8; ++i) {
        move = Vec{coordinate.getX() + i, coordinate.getY() + i};
        p = pieceAt(gb, move);
         if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        }
    }

    for (int i = 1; i < 8; ++i) {
        // Going Down
        move = Vec{coordinate.getX(), coordinate.getY() + i};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) {
            //Either out of bounds or not an empty piece
            // Still in bounds and is an enemy piece
            possibleMoves.push_back(move);
            break;
            // Last Capture Move
        } else {
            break;
        }   // Elseit is a teammate piece there so we can no longer go further
    }

    for (int i = 1; i < 8; ++i) {
        // Going Up
        move = Vec{coordinate.getX(), coordinate.getY() - i};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        } 
    }

    for (int i = 1; i < 8; ++i) {
        // Going right
        move = Vec{coordinate.getX() + i, coordinate.getY()};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        } 
    }
    
    for (int i = 1; i < 8; ++i) {
      // Going Left
        move = Vec{coordinate.getX() - i, coordinate.getY()};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        } 
    }
}

shared_ptr<Piece> Queen::clone() const {
    return make_shared<Queen>(*this);
}


