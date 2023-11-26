#include "Piece.h"
#include "ChessBoard.h"

Piece::Piece(struct Vec coordinate, char type, bool colour): coordinate{coordinate}, type{type}, white{colour} {}

void Piece::attach(Observer* o){
	cb = o;
}
	
Piece::~Piece(){}

Vec Piece::getCoordinate(){
	return coordinate;
}

char Piece::getType(){
	return type;
}

vector<Vec> Piece::getLegalMoves(){
	return legalMoves;
}


Piece::Piece(Piece& p)
    : cb(p.cb), game(p.game), coordinate(p.coordinate), type(p.type),
      legalMoves(p.legalMoves), white(p.white), emptyMoves(p.emptyMoves) {
}

void Piece::setCoordinate(Vec coord){
	coordinate = coord;
}


// we get the oldBoard -> make a copy of it -> edit the actual board -> revert back to the original board
bool Piece::willCheck(Vec start, Vec end){
	// temp hold the original turn 
	bool turn = game->getTurn(); 
	// temp hold the original positions of the pieces -> we need to copy every individual piece pointer 
	// NEED A DEEP COPY OF THE PIECES 
	vector<vector<Piece>> oldBoard = game->getGameBoard();
	// copy every Piece 
	vector<vector<Piece>> boardCopy(oldBoard.size(), vector<Piece>(oldBoard[0].size()));
	for(vector<Piece> vec : oldBoard){
		for(Piece p : vec){
			Piece newPiece = p;
			int row = p.getCoordinate().getY();
			int col = p.getCoordinate().getX();
			boardCopy[row][col] = newPiece;
		}
	}
	// notify the chessBoard of the move  
	cb->notify(start, end); 
	// check if the king is in check 
	bool check = game->isCheck(white);
	// revert board back 
	game->revertBoard(boardCopy, turn); 
	// return if the move will put the king in check or not
	return check;
}

bool Piece::isMoveValid(Vec v){
	for(Vec move : legalMoves){
		if (move == v){ return true; }
	}
	return false;
}
