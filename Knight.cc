#include "Knight.h"
#include "ChessBoard.h"
// Can just call the Piece's default constructor because no difference between Knight and Piece


void Knight::resetMoves() {
    legalMoves.clear();
	// for (vector<Piece> vec : game->getGameBoard()){
	// 	for (Piece p : vec){
	// 		vector<Vec> moves = knightMoves(); 
	// 		for (Vec end: moves){
	// 			if (!willCheck(coordinate, end)){
	// 				legalMoves.push_back(end);
	// 			};
	// 		} 
	// 	}
	// }
}

void Knight::getPossibleMoves(vector<vector<shared_ptr<Piece>>> gb) {
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
    topRight1 = Vec{coordx + 1, coordy - 2};
    topRight2 = Vec{coordx + 2, coordy - 2};
        
    topLeft1 = Vec{coordx - 1, coordy - 2};
    topLeft2 = Vec{coordx - 2, coordy - 1};

    bottomRight1 = Vec{coordx + 2, coordy + 1};
    bottomRight2 = Vec{coordx + 1, coordy + 2};

    bottomLeft1 = Vec{coordx - 2, coordy + 1};
    bottomLeft2 = Vec{coordx - 1, coordy + 2};
    
    // Need to check if teammate or enemy team
    
    if(inBounds(topRight1) && !(pieceAt(gb, topRight1)->getTeam() == getTeam())) {
        possibleMovess.push_back(topRight1);
    } 
    if(inBounds(topRight2) && !(pieceAt(gb, topRight2)->getTeam() == getTeam())) {
        possibleMovess.push_back(topRight2);
    } 
    if(inBounds(topLeft1) && !(pieceAt(gb, topLeft1)->getTeam() == getTeam())) {
        possibleMovess.push_back(topLeft1);
    } 
    if(inBounds(topLeft2) && !(pieceAt(gb, topLeft2)->getTeam() == getTeam())) {
        possibleMovess.push_back(topLeft2);
    } 
    if(inBounds(bottomRight1) && !(pieceAt(gb, bottomRight1)->getTeam() == getTeam())) {
        possibleMovess.push_back(bottomRight1);
    } 
    if(inBounds(bottomRight2) && !(pieceAt(gb, bottomRight2)->getTeam() == getTeam())) {
        possibleMovess.push_back(bottomRight2);
    } 
    if(inBounds(bottomLeft1) && !(pieceAt(gb, bottomLeft1)->getTeam() == getTeam())) {
        possibleMovess.push_back(bottomLeft1);
    } 
    if(inBounds(bottomLeft2) && !(pieceAt(gb, bottomLeft2)->getTeam() == getTeam())) {
        possibleMovess.push_back(bottomLeft2);
    } 
}
