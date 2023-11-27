#include "Knight.h"
#include "ChessBoard.h"


void Knight::resetMoves() {
    legalMoves.clear();
	for (vector<Piece> vec : game->getGameBoard()){
		for (Piece p : vec){
			vector<Vec> moves = knightMoves(); 
			for (Vec end: moves){
				if (!willCheck(coordinate, end)){
					legalMoves.push_back(end);
				};
			} 
		}
	}
}

vector<Vec> Knight::knightMoves() {
    vector<Vec> moves;

    Vec topRight1;
    Vec topRight2;
    
    Vec topLeft1;
    Vec topLeft2;

    Vec bottomRight1;
    Vec bottomRight2;

    Vec bottomLeft1;
    Vec bottomLeft2;

    if(white) {
        topRight1
    }



}