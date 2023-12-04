#ifndef _PIECE_H_
#define _PIECE_H_

#include <iostream>
#include <vector>
#include "Vec.h"
#include <memory>
using namespace std;

class Piece{
		protected:
			Vec coordinate; // Coordinate of the piece
			char type; // Char of the piece
			vector<Vec> possibleMoves; // The piece's possible moves
			bool white; // Bool value of whether it is a white piece
		public:
			// default constructor 
			Piece() = default;
			// default constructor 
			Piece(Vec coordinate, char type, bool white);
			// copy constructor 
			Piece(const Piece& p);
			// move constructor 
			Piece(Piece&& p);
			// destructor 
			virtual ~Piece() = default;
			void resetMoves(); // Clear the piece's possible moves
			void addTestMove(Vec end); // adds a move to the possible moves 
			char getType() const; // Getter
			bool getTeam() const; // Getter
			virtual void getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) = 0; // To be overriden in each subclass
			// Each piece would generates its own set of possible moves specific to that piece and the current state of the gameboard
			Vec getCoordinate() const; // Getter
			void setCoordinate(Vec coord); // Setter
			shared_ptr<Piece> pieceAt(vector<vector<shared_ptr<Piece>>> gb, Vec coordinate); // Returns the piece at the coordinate based on the passed gameboard
			bool isEmptyPiece(shared_ptr<Piece> p); // Returns whether the passed piece is an empty piece
			bool inBounds(Vec coordinate); // Checks the piece is in bounds of the gameboard
			vector<Vec> returnPossibleMoves(); // Getter method that returns possibleMoves
			virtual shared_ptr<Piece> clone() const = 0; // Pure Virtual that is overriden in each subclass
			// Used for copying/cloning pieces
};	

#endif



