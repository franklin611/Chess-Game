#include "Player.h"
#include "Vec.h"
#include <iostream>

// Player constructor 
Player::Player(bool colour, shared_ptr<ChessBoardObserver> cb) : colour{colour}, cb{cb} {}

// Adds a new vector<Vec>, a move, to the set of moves
void Player::notifyLM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    legalMoves.emplace_back(newMove);
}

void Player::notifyCapM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    captureMoves.emplace_back(newMove);
}

void Player::notifyCheckM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    checkMoves.emplace_back(newMove);
}
void Player::notifyCMM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    checkMateMoves.emplace_back(newMove);
}

void Player::notifyACM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    avoidCaptureMoves.emplace_back(newMove);
}
