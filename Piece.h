#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>

// #include "Observer.h"
#include <vector>
#include "Vec.h"
#include <memory>
using namespace std;

// class Vec;

// queen
// employ the same logic as bishop and rook combined

// king
// it only has 8 options + castle
// check in the 8 options if your own teammate is on that square, then you cannot have that move
// for castle check ??????????????

// bishop
// look for the first piece hit while going diagonal in each direction
// if that piece is your own team go back one space and thats the limit
// if that piece is not on your own team that space is the limit

// knight
// it only has 8 options
// check in the 8 options if your own teammate is on that square, then you cannot have that move
// can a knight jump over a piece?

// rook
// look for the first piece hit going forwards and sideways in both directions
// if that piece is your own team go back one space and thats the limit
// if that piece is not on your own team that space is the limit

// pawn
// case 1: move one forward
// can do this as long as no piece in front of them at all
// case 2: move two forward
// can do this only if the pawn has not moved and there is no piece in that square
// case 3: en passant
// case 4: capture diagonal
// only allowed if the opposite team is on that square

// class Empty;

class Piece{
		// not sure if this needs to be protected ****
		protected:
			// unique_ptr<Observer> playerWhite;
			// unique_ptr<Observer> playerBlack;
			Vec coordinate;
			char type;
			vector<Vec> possibleMoves;
			bool white;
		public:
			// Piece(const Piece* emptyBase);
			// Piece(Piece& other);
			// this will respond according to how p moved
			void resetMoves();
			// void addLegalMove(Vec end, bool white);  // Not sure if we even need anymore
			void addTestMove(Vec end);
			// Directly edits possibleMoves
			virtual void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) = 0;
			char getType() const;
			bool getTeam() const;
			Piece() = default;
			Piece(Vec coordinate, char type, bool white);
			Piece(const Piece& p);
			Piece(Piece&& p);
			virtual ~Piece() = default;
			vector<Vec> getLegalMoves();
			Vec getCoordinate() const;
			void setCoordinate(Vec coord);
			shared_ptr<Piece> pieceAt(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate);
			bool isEmptyPiece(shared_ptr<Piece> p);
			bool inBounds(Vec coordinate);
			vector<Vec> returnPossibleMoves();
			virtual shared_ptr<Piece> clone() const = 0;
};	

#endif



