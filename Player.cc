#include "Player.h"
#include "Vec.h"
#include <iostream>

Player::Player(bool colour, shared_ptr<ChessBoardObserver> cb) : colour{colour}, cb{nullptr} {}

void Player::notifyLM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    legalMoves.emplace_back(newMove);
    // cout << "move: " << newMove[0] << ", " << newMove[1] << endl;
    // cout << "MOVES: " << legalMoves.size() << endl;
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
// vector<vector<Vec>> Player::getLegalMoves() {
//     return legalMoves;
// }

