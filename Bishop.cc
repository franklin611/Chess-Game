#include "Bishop.h"

// Default Constructor 
Bishop::Bishop(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour} {}

// Copy Constructor 
Bishop::Bishop(const Bishop& other): Piece{other} {}

// Generates all possible Moves, taking into account the pieces on the GameBoard
void Bishop::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec move;

    // To top left Diagonal
    shared_ptr<Piece> p;
    for (int i = 1; i < 8; ++i) {
        move = Vec{coordinate.getX() - i, coordinate.getY() - i};
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
         if(inBounds(move) && isEmptyPiece(p)) {  
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) { 
            possibleMoves.push_back(move);
            break;
        } else { 
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
}

// Creates a deep copy of a Bishop 
shared_ptr<Piece> Bishop::clone() const {
    return make_shared<Bishop>(*this);
}
