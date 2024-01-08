#include "Game.h"
#include <iostream>
using namespace std;

// Default constructor
Game::Game() : blackScore{0}, whiteScore{0} {}

// Determines whether to update the score by +1 or +0.5 depending on a checkmate or stalemate 
void Game::updateWhite(bool half) {
    if (half) {
        whiteScore += 0.5;
        blackScore += 0.5;  
    } else {
        ++whiteScore;
    }
}

// updates the black score if it's checkmate or stalemate 
void Game::updateBlack(bool half) {
    if (half) {
        blackScore += 0.5;
        whiteScore += 0.5;
    } else {
        ++blackScore;
    }
}

// outputs the score 
ostream &operator<<(ostream &out, const Game &g) {
    out << "White: " << g.whiteScore << endl << "Black: " << g.blackScore;
    return out;
}
