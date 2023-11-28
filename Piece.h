#include "Observer.h"
#include <vector>
#include "Vec.h"
using namespace std;

class ChessBoard;
class Vec;
class Observer;

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
// ????????????????????????????????????????????????????????????/
// case 4: capture diagonal 
// only allowed if the opposite team is on that square 

class Piece{
		// not sure if this needs to be protected ****
		protected:
			unique_ptr<Observer> playerWhite; 
			unique_ptr<Observer> playerBlack;
			Vec coordinate;
			char type;
			vector<Vec> legalMoves;
			bool white;
		public: 
			// this will respond according to how p moved
			virtual void resetMoves();
			void addLegalMove(Vec end, bool white); 
			void addTestMove(Vec end); 
			// return what the possibleMoves are based on the board 
			virtual vector<Vec> getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) = 0; 
			char getType(); 
			bool getTeam();
			Piece() = default;
			Piece(Vec coordinate, char type, bool white);
			Piece(Piece& p);
			void attachWhite(unique_ptr<Observer> o);
			void attachBlack(unique_ptr<Observer> o);
			vector<Vec> getLegalMoves();
			Vec getCoordinate();
			void setCoordinate(Vec coord);
};





