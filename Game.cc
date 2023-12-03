#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() : blackScore{0}, whiteScore{0} {}

void Game::updateWhite(bool half) {
    if (half) {
        whiteScore += 0.5;
        blackScore += 0.5;  
    } else {
        ++whiteScore;
    }
}

void Game::updateBlack(bool half) {
    if (half) {
        blackScore += 0.5;
        whiteScore += 0.5;
    } else {
        ++blackScore;
    }
}

ostream &operator<<(ostream &out, const Game &g) {
    // out << "Final Score:" << endl << "White: " << g.whiteScore << endl << "Black: " << g.blackScore;
    out << "White: " << g.whiteScore << endl << "Black: " << g.blackScore;
    return out;
}
