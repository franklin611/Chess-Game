#include "Player.h"
#include "Vec.h"
#include <iostream>

Player::Player() {}
// Player constructor 
Player::Player(bool colour, shared_ptr<ChessBoardObserver> cb) : colour{colour}, cb{cb} {}

// Copy constructor
Player::Player(const Player& other) 
        : Observer(other), colour(other.colour), legalMoves(other.legalMoves),
          captureMoves(other.captureMoves), checkMoves(other.checkMoves),
          checkMateMoves(other.checkMateMoves), avoidCaptureMoves(other.avoidCaptureMoves),
          cb(other.cb) {}
    
Player& Player::operator=(const Player& other) {
        if (this != &other) { // self-assignment check
            Observer::operator=(other); // call base class assignment operator
            colour = other.colour;
            legalMoves = other.legalMoves;
            captureMoves = other.captureMoves;
            checkMoves = other.checkMoves;
            checkMateMoves = other.checkMateMoves;
            avoidCaptureMoves = other.avoidCaptureMoves;
            cb = other.cb;
        }
        return *this;
}

// Adds a new vector<Vec>, a move, to the set of moves
void Player::notifyLM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    legalMoves.emplace_back(newMove);
}

// notifies the player of a capture move 
void Player::notifyCapM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    captureMoves.emplace_back(newMove);
}

// notifies the player of a check move 
void Player::notifyCheckM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    checkMoves.emplace_back(newMove);
}

// notifies the player of a checkmate move
void Player::notifyCMM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    checkMateMoves.emplace_back(newMove);
}

// notify the player of a an avoid capture move 
void Player::notifyACM(Vec start, Vec end) {
    vector<Vec> newMove = {start, end};
    avoidCaptureMoves.emplace_back(newMove);
}

// Creates a deep copy of a Player 
// shared_ptr<Player> Player::clone() const {
//     return make_shared<Player>(*this);
// }

