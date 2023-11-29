#include "Player.h"

Player::Player(bool colour, unique_ptr<Observer> cb) : colour{colour}, cb{make_unique<Observer>()} {}

void Player::notifyLM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    legalMoves.emplace_back(newMove);
}

vector<vector<Vec>> Player::getLegalMoves() {
    return legalMoves;
}
