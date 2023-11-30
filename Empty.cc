#include "Piece.h"
#include "Empty.h"

Empty::Empty(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour} {}
Empty::Empty(const Empty& other) : Piece{other} {}
void Piece::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    // Do nothing
    // It is virtual so it has to be overriden
}

shared_ptr<Piece> Empty::clone() const {
    return make_shared<Empty>(*this);
}
