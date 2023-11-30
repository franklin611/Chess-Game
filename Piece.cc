#include "Piece.h"
#include "ChessBoard.h"
#include "Observer.h"
#include "Empty.h"

void Piece::resetMoves(){ possibleMoves.clear(); }

// void Piece::addLegalMove(Vec end, bool white){ 
// 	if (white){ playerWhite->notify(coordinate, end); }
// 	else { playerBlack->notify(coordinate, end); }
// }

// Piece::Piece(const Piece* emptyBase) {
//         // Initialize Piece using information from the Empty object
//         coordinate = emptyBase->getCoordinate();
//         type = emptyBase->getType();
//         white = emptyBase->getTeam();
//         // You may want to initialize other members based on the Empty object
//     }

Piece::Piece(Piece&& other)
        : coordinate(move(other.coordinate)),
          type(move(other.type)),
          possibleMoves(move(other.possibleMoves)),
          white(move(other.white)) {}

Piece::Piece(const Piece& p): coordinate(p.coordinate), type(p.type), possibleMoves(p.possibleMoves), white(p.white) {}

// Piece::Piece(Empty& empty): Piece{empty.coordinate, empty.type, empty.white} {}

void Piece::addTestMove(Vec end){ possibleMoves.push_back(end); }

char Piece::getType() const { return type; }

bool Piece::getTeam() const { return white; }

Piece::Piece(struct Vec coordinate, char type, bool colour): coordinate{coordinate}, type{type}, white{colour} {}

// Piece::Piece(Piece& other) {
//         // Copy member variables
//         // if (other.playerWhite) {
//         //     playerWhite = make_unique<Observer>(*other.playerWhite);
//         // } else {
//         //     playerWhite = nullptr;
//         // }

//         // if (other.playerBlack) {
//         //     playerBlack = make_unique<Observer>(*other.playerBlack);
//         // } else {
//         //     playerBlack = nullptr;
//         // }

//         coordinate = other.get;
//         type = other.type;
//         possibleMoves = other.possibleMoves;
//         white = other.white;
// }

Vec Piece::getCoordinate() const { return coordinate; }

void Piece::setCoordinate(Vec coord){ coordinate = coord; }

shared_ptr<Piece> Piece::pieceAt(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate) {
    if ((!(coordinate.getX() <= 7 && coordinate.getX() >= 0)) && (!(coordinate.getY() <= 7 && coordinate.getY() >= 0))) return nullptr;

    int row = coordinate.getY();
    int col = coordinate.getX();

    return gb[row][col];
}

bool Piece::isEmptyPiece(shared_ptr<Piece> p) {
    if (p->getType() != ' ' && p->getType() != '_') {
        return true;
    } else {
        return false;
    }
}


bool Piece::inBounds(Vec coordinate) {
    int row = coordinate.getY();
    int col = coordinate.getX();
    return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
}


vector<Vec> Piece::returnPossibleMoves() {
    return possibleMoves;
}


// shared_ptr<Piece> Piece::clone() const {
//     return make_shared<Piece>(*this);
// }
