#include "ChessBoard.h"
#include "Piece.h"
#include "Player.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "Pawn.h"
#include "King.h"
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


// DONE
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

// DONE
// we know that is was a valid pawn move at this point 
bool twoStep(Vec start, Vec end){
    int startY = start.getY(); 
    int endY = end.getY(); 
    if (startY = endY - 2 || startY == endY + 2){ return true; }
    return false;
}

// CHIARA
// reset moves AFTER you castle !! 
// add castle move -> king moves two spaces 
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
    // ------ at this point we want to check if the move was a castle move and move the rook accordingly
    // validate if the piece is a king and it wants to move two spaces to the left or right 
    // assume that is true then we want ALREADY moved that king
        // if it moved to the right -> get the rook to the right and move it to the left 
        // if it moved to the left -> get the rook to the left and move it to the right 
    

    // ------ at this point we know the move is valid then we can change its booleans -------

    // check if the piece that moved is a king
    if (startType == 'K' || startType == 'k'){
        shared_ptr<King> king = dynamic_pointer_cast<King>(endPiece);
        king->hasMoved();
        // now the endpiece is the king, we want to update the kings cooordinates to end 
        if (startType == 'K') { wKing == end; }
        if (startType == 'k') { bKing == end; }

        // check if the move was a castle move 
        int startX = start.getX(); 
        int endX = end.getX();
        if (startX == endX - 2 || startX == endX + 2) {
            if (startX > endX){ // moved to the left
                Vec rookCoord;
                
            } else { // moved to the right 

            }
        }

    }

    // check if the piece that moved is a pawn -> also if it moved 2 spaces forward 
    if (startType == 'P' || startType == 'p'){
        shared_ptr<Pawn> pawn = dynamic_pointer_cast<Pawn>(endPiece);
        pawn->hasMoved();
        if (twoStep){ pawn->hasMovedTwo(); }
    }

    // update if the YOU or THE OTHER TEAM are in check
    wCheck = isCheck(true);
    bCheck = isCheck(false);
    
    // change the turn 
    turn? false : true;

}

bool ChessBoard::isCheck(bool white){
    // decide who's king we want to see is in check
    Vec kingCoord;
    if (white){
        kingCoord = wKing;
    } else {
        kingCoord = bKing;
    }

    // compare the legal moves of each piece with the king's coordinates
    for(vector<shared_ptr<Piece>> vec : gb){
        for(shared_ptr<Piece> p : vec){
            for(Vec move : p->getLegalMoves()){
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

// make sure that the empty piece is a deep copy 
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
// UPDATE THE SCORE 
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
