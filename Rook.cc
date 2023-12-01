#include "Rook.h"


Rook::~Rook(){}

Rook::Rook(): Piece{}, moved{false} {}

Rook::Rook(const Rook& other): Piece{other}, moved{other.moved} {}

Rook::Rook(Vec coordinate, char type, bool white) : Piece{coordinate, type, white}, moved{false} {}
// To make Chiara's life easier, I can also just check if there is a piece there.
// If our team, we can't make that move and break the for loop (Assuming we have 4 for loops for each
// direction) if it is an enemy team, capturing is the last move we can make then break. 
void Rook::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec move;
    shared_ptr<Piece> p;

    for(int i = 1; i < 8; ++i) {
        // Going Down
        move = Vec{coordinate.getX(), coordinate.getY() + i};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !(p->getTeam() == getTeam())) {
            //Either out of bounds or not an empty piece
            // Still in bounds and is an enemy piece
            possibleMoves.push_back(move);
            break;
            // Last Capture Move
        } else {
            break;
        }   // Elseit is a teammate piece there so we can no longer go further
    }
    for(int i = 1; i < 8; ++i) {
        // Going Up
        move = Vec{coordinate.getX(), coordinate.getY() - i};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !(p->getTeam() == getTeam())) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        } 
    }
    for(int i = 1; i < 8; ++i) {
        // Going right
        move = Vec{coordinate.getX() + i, coordinate.getY()};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !(p->getTeam() == getTeam())) {
            possibleMoves.push_back(move);
            break;
        } else {
            break;
        } 
    }
    for(int i = 1; i < 8; ++i) {
      // Going Left
        move = Vec{coordinate.getX() - i, coordinate.getY()};
        p = pieceAt(gb, move);
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !(p->getTeam() == getTeam())) {
            possibleMoves.push_back(move);
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

shared_ptr<Piece> Rook::clone() const {
    return make_shared<Rook>(*this);
}



