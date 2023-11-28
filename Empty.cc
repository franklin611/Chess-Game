#include "Piece.h"
#include "Empty.h"


void Empty::resetMoves() {
    // Do nothing cuz emptyMoves literally doesn't have any moves?
    // We don't even need to have override but chatGpt said it was good practice. 
}

vector<Vec> Empty::emptyMove() {
    // Can I return just an empty?
    return vector<Vec>(); 
    // Default
}
