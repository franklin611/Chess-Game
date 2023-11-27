#include "Knight.h"
#include "ChessBoard.h"
// Can just call the Piece's default constructor because no difference between Knight and Piece


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
    int coordx = coordinate.getX();
    int coordy = coordinate.getY();

    
// Actually, it shouldn't matter if it is black or white. 
    // if(white) {
        topRight1 = Vec{coordx + 1, coordy - 2};
        topRight2 = Vec{coordx + 2, coordy - 2};
        
        topLeft1 = Vec{coordx - 1, coordy - 2};
        topLeft2 = Vec{coordx - 2, coordy - 1};

        bottomRight1 = Vec{coordx + 2, coordy + 1};
        bottomRight2 = Vec{coordx + 1, coordy + 2};

        bottomLeft1 = Vec{coordx - 2, coordy + 1};
        bottomLeft2 = Vec{coordx - 1, coordy + 2};
    // }


// Actually, we dont even care if something was there or not. 
    // if(game->isThere(topRight1) && (topRight1.getX() >= 0 && topRight1.getX() <= 7) && (topRight1.getY() >= 0 && topRight1.getY() <= 7)) {
    //     moves.push_back(topRight1);
    // } else if(game->isThere(topRight2) && (topRight2.getX() >= 0 && topRight2.getX() <= 7) && (topRight2.getY() >= 0 && topRight2.getY() <= 7)) {
    //     moves.push_back(topRight2);
    // } else if(game->isThere(topLeft1) && (topLeft1.getX() >= 0 && topLeft1.getX() <= 7) && (topLeft1.getY() >= 0 && topLeft1.getY() <= 7)) {
    //     moves.push_back(topLeft1);
    // } else if(game->isThere(topLeft2) && (topLeft2.getX() >= 0 && topLeft2.getX() <= 7) && (topLeft2.getY() >= 0 && topLeft2.getY() <= 7)) {
    //     moves.push_back(topLeft2);
    // } else if(game->isThere(bottomRight1) && (bottomRight1.getX() >= 0 && bottomRight1.getX() <= 7) && (bottomRight1.getY() >= 0 && bottomRight1.getY() <= 7)) {
    //     moves.push_back(bottomRight1);
    // } else if(game->isThere(bottomRight2) && (bottomRight2.getX() >= 0 && bottomRight2.getX() <= 7) && (bottomRight2.getY() >= 0 && bottomRight2.getY() <= 7)) {
    //     moves.push_back(bottomRight2);
    // } else if(game->isThere(bottomLeft1) && (bottomLeft1.getX() >= 0 && bottomLeft1.getX() <= 7) && (bottomLeft1.getY() >= 0 && bottomLeft1.getY() <= 7)) {
    //     moves.push_back(bottomLeft1);
    // } else if(game->isThere(bottomLeft2) && (bottomLeft2.getX() >= 0 && bottomLeft2.getX() <= 7) && (bottomLeft2.getY() >= 0 && bottomLeft2.getY() <= 7)) {
    //     moves.push_back(bottomLeft2);
    // } 
    
    if((topRight1.getX() >= 0 && topRight1.getX() <= 7) && (topRight1.getY() >= 0 && topRight1.getY() <= 7)) {
        moves.push_back(topRight1);
    } else if((topRight2.getX() >= 0 && topRight2.getX() <= 7) && (topRight2.getY() >= 0 && topRight2.getY() <= 7)) {
        moves.push_back(topRight2);
    } else if((topLeft1.getX() >= 0 && topLeft1.getX() <= 7) && (topLeft1.getY() >= 0 && topLeft1.getY() <= 7)) {
        moves.push_back(topLeft1);
    } else if((topLeft2.getX() >= 0 && topLeft2.getX() <= 7) && (topLeft2.getY() >= 0 && topLeft2.getY() <= 7)) {
        moves.push_back(topLeft2);
    } else if((bottomRight1.getX() >= 0 && bottomRight1.getX() <= 7) && (bottomRight1.getY() >= 0 && bottomRight1.getY() <= 7)) {
        moves.push_back(bottomRight1);
    } else if((bottomRight2.getX() >= 0 && bottomRight2.getX() <= 7) && (bottomRight2.getY() >= 0 && bottomRight2.getY() <= 7)) {
        moves.push_back(bottomRight2);
    } else if((bottomLeft1.getX() >= 0 && bottomLeft1.getX() <= 7) && (bottomLeft1.getY() >= 0 && bottomLeft1.getY() <= 7)) {
        moves.push_back(bottomLeft1);
    } else if((bottomLeft2.getX() >= 0 && bottomLeft2.getX() <= 7) && (bottomLeft2.getY() >= 0 && bottomLeft2.getY() <= 7)) {
        moves.push_back(bottomLeft2);
    } 

    return moves; 


}