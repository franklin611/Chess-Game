#include "Empty.h"

// default constructor 
Empty::Empty(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour} {}

// copy constructor 
Empty::Empty(const Empty& other) : Piece{other} {}

// Should do nothing as an Empty piece has no possible moves
void Empty::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
}

// Creates a deep copy of the clone piece
shared_ptr<Piece> Empty::clone() const {
    return make_shared<Empty>(*this);
}

// destructor 
Empty::~Empty(){}
