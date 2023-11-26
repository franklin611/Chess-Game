#include "Observer.h"
#include <vector>
#include "Vec.h"
using namespace std;

class ChessBoard;
class Vec;
class Observer;

class Piece{
		// not sure if this needs to be protected **** 
		protected:
			Observer* cb;
			ChessBoard* game;
			Vec coordinate; 
			char type; 
			vector<Vec> legalMoves;
			bool white; 
			static bool BCheck; 
			static bool WCheck; 
			bool emptyMoves; // this is true if the piece is empty so we can skip over them 
		public: 
			// this will respond according to how p moved
			virtual void resetMoves();
			char getType();
			Piece() = default;
			Piece(Vec coordinate, char type, bool white); 
			Piece(Piece& p);
			// when you construct the chessBoard, add the chessBoard as the observer* 
			void attach(Observer *o);
			bool isMoveValid(Vec v);
			vector<Vec> getLegalMoves();
			Vec getCoordinate();
			bool willCheck(Vec start, Vec end);
			void setCoordinate(Vec coord);
}; 



			