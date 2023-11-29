#include "Piece.h"
#include "Empty.h"

Empty::Empty(Vec coordinate, char type, bool colour): Piece{coordinate, type, colour} {}
void Piece::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
    // Do nothing
    // It is virtual so it has to be overriden
}
