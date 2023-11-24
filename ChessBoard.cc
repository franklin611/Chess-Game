#include "ChessBoard.h"
#include "Piece.h"

// at this point we know this move is valid -> in main you would have to call piece->isValid() and ask for input again if it is not valid
void ChessBoard::notify(Vec start, Vec end){
    int endRow = end.getY(); 
    int endCol = end.getX();

    int startRow = start.getY();
    int startCol = start.getX(); 

    Piece startPiece = gb[startRow][startCol];
    Piece endPiece = gb[endRow][endCol];

    // find the piece at start and change the coordinates of the piece to end
    startPiece.setCoordinate(end);

    // move the start to the end in gb
    endPiece = startPiece;

    // replace the vector at start with the empty piece 
    startPiece = getEmptyPiece(start);

    // reset the legal moves of every piece 
    for (vector<Piece> vec : gb){
		for (Piece p : vec){
            p.resetMoves();
        }
    }

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

void ChessBoard::changePawn(char type, Vec coordinate, bool white){
    int row = coordinate.getY(); // double check this
    int col = coordinate.getX();

    // create a new piece type on the heap and correct the board at that coordinate 
    gb[row][col] = Piece(coordinate, type, white);
}

bool ChessBoard::getTurn(){
    return turn;
}

vector<vector<Piece>> ChessBoard::getGameBoard(){
    return gb;
}

void ChessBoard::revertBoard(vector<vector<Piece>> boardCopy, bool oldTurn){
    // delete the current gameboard -> this is the one we simulated and now want to get rid of 
    // replace with the pointers we originally had 
    // switch the turn back to what it was 
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

Piece ChessBoard::getEmptyPiece(Vec coord){
    // access the empty board and get the Piece* we want 
    int row = coord.getY();
    int col = coord.getX(); 
    Piece emptyPiece = eb[row][col];

    // return the copied piece 
    return emptyPiece;
}
