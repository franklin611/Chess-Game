#include "Rook.h"

// updates if a rook has moved 
void Rook::hasMoved(){
    moved = true;
}

// destructor 
Rook::~Rook(){}

// default constructor 
Rook::Rook(): Piece{}, moved{false} {} // Moved is default assumed to be false

// copy constructor 
Rook::Rook(const Rook& other): Piece{other}, moved{other.moved} {}

// default constructor 
Rook::Rook(Vec coordinate, char type, bool white) : Piece{coordinate, type, white}, moved{false} {}

// Get the specific Rook's possible moves based on the state of the gameboard
// Possible Moves are just moves the piece can take when taking into account the pieces on the board and the nove pattern of a Rook, not taking into consideration whether the move is valid or not
void Rook::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    Vec move;
    shared_ptr<Piece> p;

    for(int i = 1; i < 8; ++i) {
        // Going Down
        move = Vec{coordinate.getX(), coordinate.getY() + i};
        p = pieceAt(gb, move); // Checks the piece at the potential move of the Rook
        if(inBounds(move) && isEmptyPiece(p)) {
            possibleMoves.push_back(move);
        } else if (inBounds(move) && !(p->getTeam() == getTeam())) {
            //Either out of bounds or not an empty piece
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
}

// returns the moved boolean 
bool Rook::getMoved() {
    return moved;
}

// deep copy clone function 
shared_ptr<Piece> Rook::clone() const {
    return make_shared<Rook>(*this);
}
