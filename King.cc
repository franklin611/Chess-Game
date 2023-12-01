#include "King.h"

King::King(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour}, moved{false} {}

King::King() : Piece{}, moved{false} {}

King::King(const King& other) : Piece{other}, moved{other.moved} {}

void King::hasMoved(){
    moved = true;
}

bool King::getMoved() {
    return moved;
}

void King::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec moveUp = Vec{coordinate.getX(), coordinate.getY() - 1};
    Vec moveLeft = Vec{coordinate.getX() - 1, coordinate.getY()};
    Vec moveRight = Vec{coordinate.getX() + 1, coordinate.getY()};
    Vec moveDown = Vec{coordinate.getX(), coordinate.getY() + 1};

    Vec castleLeft = Vec{coordinate.getX() - 2, coordinate.getY()};
    Vec castleRight = Vec{coordinate.getX() + 3, coordinate.getY()};
    // My bad left is bigger

    // Verify that left castle move is possible
    // Not moved means we are at the base position of such a king.

    // Consider two cases of "Left" for White and Black
    // Check image in Discord
    // Need to dynamically cast the piece pointers to King pointers
    shared_ptr<King> king = dynamic_pointer_cast<King>(gb[coordinate.getY()][coordinate.getX()]);
    shared_ptr<Piece> p = pieceAt(gb,Vec{coordinate.getX() - 1, coordinate.getY()});
    shared_ptr<Piece> p2 = pieceAt(gb,Vec{coordinate.getX() - 2, coordinate.getY()});
    
    if (!moved && !(king->getMoved()) && isEmptyPiece(p) && isEmptyPiece(p2)){
        possibleMoves.push_back(castleLeft);
    }
    p = pieceAt(gb, Vec{coordinate.getX() + 1, coordinate.getY()});
    p2 = pieceAt(gb, Vec{coordinate.getX() + 2, coordinate.getY()});
    if (!moved && !(king->getMoved()) && isEmptyPiece(p) && isEmptyPiece(p2)) {
        possibleMoves.push_back(castleRight);
    }
    p = pieceAt(gb, moveUp);
    if (inBounds(moveUp) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(moveUp);
    }
    p = pieceAt(gb, moveLeft);
    if (inBounds(moveLeft) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(moveLeft);
    }
    p = pieceAt(gb, moveRight);
    if (inBounds(moveRight) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(moveRight);
    }
    p = pieceAt(gb, moveDown);
    if (inBounds(moveDown) && (isEmptyPiece(p) || (p->getTeam() != getTeam()))) {
        possibleMoves.push_back(moveDown);
    }
    // Left Castle
    // THis is how a castle movehappens
    // 1. 
    // 2. 
    // 3. castleMove(start,end).THis is only called when the move (start,end) is from a King
    //      I just have to pass the start and end move. It willrecognize if it is a  + 2move by a King
    
}

// I need to check the logic for a castle

shared_ptr<Piece> King::clone() const {
    return make_shared<King>(*this);
}


