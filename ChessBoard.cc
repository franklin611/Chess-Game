#include "ChessBoard.h"
#include "Piece.h"
#include "Player.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "Pawn.h"
#include <map>

// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK

// DONE
bool ChessBoard::makeHumanMove(Vec start, Vec end){
    // validate that the move is valid -> if not valid return false
    if (isValid(start, end)){
        // call notify and return true
        notify(start, end);
        return true;
    }
    return false;

}

// FRANKLIN
// Vec ChessBoard::makeComputerMove(unique_ptr<Player> p){
//     // based on level, makeComputerMove
//     // get the legal moves for the player
//     vector<vector<Vec>> legalMoves = getLegalMoves(turn);
//     // pick a random legal move
//     vector<Vec> move; // there are two Vecs [start, end]
//     if (turn){
//         move = playerWhite->selectMove(legalMoves);
//     } else {
//         move = playerBlack->selectMove(legalMoves);
//     }
//     notify(move[0], move[1]);
// }


// DONE
char ChessBoard::getType(Vec coordinate){
    shared_ptr<Piece> p = getPiece(coordinate);
    char type = p->getType();
    return type;
}

// DONE
shared_ptr<Piece> ChessBoard::getPiece(Vec coordinate){
    int row = coordinate.getY();
    int col = coordinate.getX();
    return gb[row][col];
}


// CHIARA
// returns true if a the specified piece at that coordinate is 1. a pawn and 2. on the opposite team
// we don't know what piece is at coordinate
bool ChessBoard::pawnMovedTwo(Vec coordinate, bool white){
    char type = getType(coordinate);
    shared_ptr<Piece> p = getPiece(coordinate);
    std::shared_ptr<Pawn> pawn;
    if (type == 'P' || type == 'p'){ std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(p); }
    else { return false; }

    if (((white && type == 'p') || (!white && type == 'P')) && pawn->getMovedTwo()){ return true; }

    return false;




}

// convert Piece pointer type
// MAYBE ADD THIS FUNCTION


// DONE
void ChessBoard::replacePiece(Vec coordinate, shared_ptr<Piece> replacement){
    int row = coordinate.getY();
    int col = coordinate.getX();
    gb[row][col] = replacement;
}


// CHIARA
// at this point we know this move is valid -> in main you would have to call piece->isValid() and ask for input again if it is not valid
// need to validate if the king is in check
// add castle move -> king moves two spaces
// make sure that the empty piece is a deep copy
// make sure that the endpiece is deleted from memory
// smart pointers YES
void ChessBoard::notify(Vec start, Vec end){

    shared_ptr<Piece> startPiece = getPiece(start);
    char startType = getType(start);
    shared_ptr<Piece> endPiece = getPiece(end);

    // find the piece at start and change the coordinates of the piece to end
    startPiece->setCoordinate(end);

    // move the startPiece to end -> now the piece at end is pointing to the address of startPiece
    replacePiece(end, startPiece);
    endPiece = startPiece; // now the endPiece points at the (start)piece that we just moved to the end

    // ------ now only endPiece is pointing to the piece that was originally at end -> once endPiece goes out of scope the memory is automatically deallocated ----------

    // replace the vector at start with the empty piece -> getEmptyPiece needs to return a shared pointer but UNIQUE copy
    shared_ptr<Piece> emptyPiece = getEmptyPiece(start);

    // put the endPiece at start
    replacePiece(start, emptyPiece);

    // reset the legal moves of every piece
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            p->resetMoves();
        }
    }

    // ------ at this point we know the move is valid then we can change its booleans -------

    // check if the piece that moved is a king
    if (startType == 'K' || startType == 'k'){
        shared_ptr<Pawn> king = dynamic_pointer_cast<King>(endPiece);

    }


    // check if the piece that moved is a pawn -> also if it moved 2 spaces forward

    // update if the OTHER team is in check

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

// we assume that main calls this function because the user decided they want to forfeit in their current turn
// we can think of this as an alternate end?
void ChessBoard::forfeit(){
    if (turn){
        // update score +1 for black
        game.updateBlack();
    } else {
        // update score +1 for white
        game.updateWhite();
    }
    // restart game
}

bool ChessBoard::isEnd() {
    if (turn) {
        if (getLegalMoves(turn).empty()) {
            game.updateWhite();
            return true;
        }
    } else {
        if (getLegalMoves(turn).empty()) { 
            game.updateBlack();
            return true;
        }
    }
}
