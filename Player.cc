#include "Player.h"

Player::Player(bool colour, unique_ptr<ChessBoardObserver> cb) : colour{colour}, cb{make_unique<ChessBoardObserver>()} {}

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
// vector<vector<Vec>> Player::getLegalMoves() {
//     return legalMoves;
// }
