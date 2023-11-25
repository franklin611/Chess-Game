#include "ChessBoard.h"
#include "Piece.h"

// the players need to be unique pointers 
// the pieces need to be shared pointers 


// at this point we know this move is valid -> in main you would have to call piece->isValid() and ask for input again if it is not valid
// need to validate if the king is in check 
// add castle move -> king moves two spaces 
// make sure that the empty piece is a deep copy 
// make sure that the endpiece is deleted from memory 
// smart pointers YES 
void ChessBoard::notify(Vec start, Vec end){
    int endRow = end.getY(); 
    int endCol = end.getX();

    int startRow = start.getY();
    int startCol = start.getX(); 

    Piece* startPiece = gb[startRow][startCol];
    // get the piece type here 
    Piece* endPiece = gb[endRow][endCol];
    // get the piece type here 

    // find the piece at start and change the coordinates of the piece to end
    startPiece->setCoordinate(end);

    // move the start to the end in gb
    endPiece = startPiece;

    // replace the vector at start with the empty piece 
    startPiece = getEmptyPiece(start);

    // is my king in check ****
    if (isCheck(turn)){
        // update turn's player to be in check 
    }

    // reset the legal moves of every piece 
    for (vector<Piece*> vec : gb){
		for (Piece* p : vec){
            p->resetMoves();
        }
    }

    // at this point we know th emove is valid then we can change its booleans

    // change the turn 
    turn? false : true;
}

bool ChessBoard::isCheck(bool white){
    // decide who's king we want to see is in check
    Piece* king;
    if (white){
        king = wKing;
    } else {
        king = bKing;
    }
    Vec kingCoord = king->getCoordinate();

    // compare the legal moves of each piece with the king's coordinates
    for(vector<Piece> vec : gb){
        for(Piece p : vec){
            for(Vec move : p.getLegalMoves()){
                if (move == kingCoord){
                    return true;
                }
            }
        }
    }
    return false;
}


bool ChessBoard::getTurn(){
    return turn;
}

// update piece pointers 
vector<vector<Piece>> ChessBoard::getGameBoard(){
    return gb;
}

// update piece pointers 
// now the boardCopy need to be a deep copy -> reverttBoard can use the deep copy and let it be destroyed after, and then revert back to the original board 
void ChessBoard::revertBoard(vector<vector<Piece>> boardCopy, bool oldTurn){
    // delete the current gameboard -> this is the one we simulated and now want to get rid of 
    // replace with the pointers we originally had 
    // switch the turn back to what it was 

    //
    int row = 0; 
    int col = 0; 
    for (vector<Piece> vec : gb){
        for (Piece p : vec){
            p = boardCopy[row][col];
            ++col;
        }
        ++row;
    }
    turn = oldTurn;
}

Piece* ChessBoard::getEmptyPiece(Vec coord){
    // access the empty board and get the Piece* we want 
    int row = coord.getY();
    int col = coord.getX(); 
    Piece emptyPiece = eb[row][col];

    // return the copied piece 
    return emptyPiece;
}

void ChessBoard::makeComputerMove(Player* p){
    // based on level, makeComputerMove 




    // get the legal moves for the player
    vector<vector<Vec>> legalMoves = cb->getLegalMoves(turn);
    // pick a random legal move 
    vector<Vec> move; // there are two Vecs [start, end]
    if (turn){
        move = cb->playerWhite->selectMove(legalMoves);
    } else {
        move = cb->playerBlack->selectMove(legalMoves);
    }
    notify(move[0], move[1]);
}


// this is for a human player 
bool ChessBoard::makeHumanMove(Vec start, Vec end){
    // validate that the move is valid -> if not valid return false 
    if (isValid(start, end)){
        // call notify and return true 
        notify(start, end);
        return true;
    } 
    return false;

}

bool ChessBoard::isValid(Vec start, Vec end){
    // use start to get piece 
    int row = start.getY();
    int col = start.getX(); 
    Piece p = gb[row][col];

    // use end to validate move 
    return p.isMoveValid(end);
}

// update piece pointer 
bool ChessBoard::isThere(Vec coordinate){
	for (vector<Piece> vec : gb){
		for (Piece p : vec){
			if (p.getCoordinate() == coordinate){
				return true;
			}
		}
	}
	return false;
}

bool ChessBoard::pawnMovedTwo(Vec coordinate, bool white){
    int row = coordinate.getY(); 
    int col = coordinate.getX();

    Piece p = gb[row][col];

    // double check lower case is black 
    // we are checking at the passant coordinate if there is a piece that is an opposite team pawn
    // can't check if the pawn moved two places because its not a dynamic type. *************
    if ((white && p.getType() == 'p') || 
        (!white && p.getType() == 'P') && p.get){
            return true;
    }

    return false;

}
