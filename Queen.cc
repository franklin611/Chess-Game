#include "Queen.h"

// default constructor 
Queen::Queen(Vec coordinate, char type, bool white) : Piece{coordinate, type, white} {} 

// copy constructor 
Queen::Queen(const Queen& other): Piece{other} {}

// updates the queen's possible moves 
void Queen::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec move;
    shared_ptr<Piece> p;
    // To top left diagonal
    for (int i = 1; i < 8; ++i) { // i = 1, minimum 1 
        move = Vec{coordinate.getX() - i, coordinate.getY() - i}; // Since in our gameboard, top left is 0,0
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) { // The move is in bounds and there is an emptypiece
            possibleMoves.push_back(move);
        } else if (inBounds(move) && (p->getTeam() != getTeam())) { // Move is in bounds and the piece at the coordinate is on the opposite team
            possibleMoves.push_back(move);
            // Last possible move they can make as the Queen cannot jump over a piece
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
            possibleMoves.push_back(move);
            break;
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

// Piece Subclass copying
shared_ptr<Piece> Queen::clone() const {
    return make_shared<Queen>(*this);
}
