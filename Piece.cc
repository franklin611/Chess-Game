#include "Piece.h"
#include "ChessBoard.h"
#include "Observer.h"
#include "Empty.h"

void Piece::resetMoves(){ possibleMoves.clear(); }

Piece::Piece(Piece&& other)
        : coordinate(move(other.coordinate)),
          type(move(other.type)),
          possibleMoves(move(other.possibleMoves)),
          white(move(other.white)) {}

Piece::Piece(const Piece& p): coordinate(p.coordinate), type(p.type), possibleMoves(p.possibleMoves), white(p.white) {}

// Adds a move to possibleMoves of that piece
void Piece::addTestMove(Vec end){ possibleMoves.push_back(end); }

char Piece::getType() const { return type; }

bool Piece::getTeam() const { return white; }

// It wsa struct coordinate before TODO
Piece::Piece(Vec coordinate, char type, bool colour): coordinate{coordinate}, type{type}, white{colour} {}

Vec Piece::getCoordinate() const { return coordinate; }

void Piece::setCoordinate(Vec coord){ coordinate = coord; }

shared_ptr<Piece> Piece::pieceAt(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate) {
    // First checks that the passed coordinate is in bounds (A safety handle)
    if ((!(coordinate.getX() <= 7 && coordinate.getX() >= 0)) || (!(coordinate.getY() <= 7 && coordinate.getY() >= 0))) return nullptr;
    int row = coordinate.getY();
    int col = coordinate.getX();
    return gb[row][col]; // Retunrs the piece at that coordinate where Y is row and X is column
}

// Checks if it is an empty piece
bool Piece::isEmptyPiece(shared_ptr<Piece> p) {
    if (p->getType() == ' ' || p->getType() == '_') {
        return true;
    } else {
        return false;
    }
}

// Check if the coordinate is in bounds of the gameboard
bool Piece::inBounds(Vec coordinate) {
    int row = coordinate.getY();
    int col = coordinate.getX();
    return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
}

// A getter method
vector<Vec> Piece::returnPossibleMoves() {
    return possibleMoves;
}
