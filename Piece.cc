#include "Piece.h"
#include "ChessBoard.h"

void Piece::resetMoves(){ possibleMoves.clear(); }

void Piece::addLegalMove(Vec end, bool white){ 
	if (white){ playerWhite->notify(coordinate, end); }
	else { playerBlack->notify(coordinate, end); }
}

void Piece::addTestMove(Vec end){ possibleMoves.push_back(end); }

char Piece::getType(){ return type; }

bool Piece::getTeam(){ return white; }

Piece::Piece(struct Vec coordinate, char type, bool colour): coordinate{coordinate}, type{type}, white{colour} {}

Piece::Piece(Piece& other) {
        // Copy member variables
        if (other.playerWhite) {
            playerWhite = make_unique<Observer>(*other.playerWhite);
        } else {
            playerWhite = nullptr;
        }

        if (other.playerBlack) {
            playerBlack = make_unique<Observer>(*other.playerBlack);
        } else {
            playerBlack = nullptr;
        }

        coordinate = other.coordinate;
        type = other.type;
        legalMoves = other.legalMoves;
        white = other.white;
}

void Piece::attachWhite(unique_ptr<Observer> o){ playerWhite = o; }

void Piece::attachBlack(unique_ptr<Observer> o){ playerBlack = o; }

vector<Vec> Piece::getLegalMoves(){ return legalMoves; }

Vec Piece::getCoordinate(){ return coordinate; }

void Piece::setCoordinate(Vec coord){ coordinate = coord; }


