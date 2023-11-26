#include "ChessBoard.h"
#include "Piece.h"
using namespace std;

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

vector<vector<Vec>> generateAllLevelMoves(vector<vector<Vec>> possibleMoves, int level) {
    vector<vector<Vec>> levelMoves;
    vector<vector<Vec>> checkmateMoves = generateCheckmateMoves(possibleMoves);
    vector<vector<Vec>> checkMoves = generateCheckMoves(possibleMoves);
    vector<vector<Vec>> captureMoves = generateCaptureMoves(possibleMoves);
    vector<vector<Vec>> avoidCaptureMoves = generateAvoidCaptureMoves(possibleMoves);

    if(level == 1) {
        return possibleMoves;
    } else if (level == 2) {
        levelMoves.insert(levelMoves.end(), checkMoves.start(), checkMoves.end());
        levelMoves.insert(levelMoves.end(), captureMoves.start(), captureMoves.end());
    } else if (level == 3) {
        levelMoves.insert(levelMoves.end(), checkMoves.start(), checkMoves.end());
        levelMoves.insert(levelMoves.end(), captureMoves.start(), captureMoves.end());
        levelMoves.insert(levelMoves.end(), avoidCaptureMoves.start(), avoidCaptureMoves.end());    
    } else if (level == 4) {
        if(!checkmateMoves.empty()) {
            return checkmateMoves;
        } else {
            levelMoves.insert(levelMoves.end(), checkMoves.start(), checkMoves.end());
            levelMoves.insert(levelMoves.end(), captureMoves.start(), captureMoves.end());
            levelMoves.insert(levelMoves.end(), avoidCaptureMoves.start(), avoidCaptureMoves.end());
        }
    }
    return levelMoves;
}

vector<vector<Vec>> generateCheckmateMoves(vector<vector<Vec>> possibleMoves) {
    vector<vector<Vec>> levelMoves;
    for (int i = 0; !possibleMoves.empty(); ++i) {
        Vec start = possibleMoves[i][0];
        Vec end = possibleMoves[i][1];
        if(isValid(start, end)) {
            // Asumption: Before we reach this point, the game is not in a "isEnd()" state. Is this valid?
            vector<vector<unique_ptr<Piece>>> copyBoard = gb;
            notify(start, end);
            // Now need to check if this is a check/checkmate Move. But we run into the same issue of we have to make sure that being in checkmate
            // Doesn't end the game. From my understanding, I will be calling isEnd() after every move made in main.
            // And ending the game if true. If i do this simulation in a function, as long as I revert the move before reaching the isEnd in main
            // No issues?

            if(isEnd()) levelMoves.emplace_back(vector<Vec>{start, end});  // Checks to see if after such a move, if the game is voer. 

            revertBoard(copyBoard, !turn);
        }
    }
    return levelMoves;
}

vector<vector<Vec>> generateCheckMoves(vector<vector<Vec>> possibleMoves) {
    vector<vector<Vec>> levelMoves;
    for (int i = 0; !possibleMoves.empty(); ++i) {
        Vec start = possibleMoves[i][0];
        Vec end = possibleMoves[i][1];
        if(isValid(start, end)) {
            vector<vector<unique_ptr<Piece>>> copyBoard = gb;
            notify(start, end);
            // Now need to check if this is a check/checkmate Move. But we run into the same issue of we have to make sure that being in checkmate
            // Doesn't end the game
            // void revertBoard(vector<vector<unique_ptr<Piece>>> oldPieces, bool oldTurn);
            if(isCheck(turn)) levelMoves.emplace_back(vector<Vec>{start, end}); // It is turn, not !turn because if it was white before, calling notify sets turn to black now which is what we wanted to check anyways
            revertBoard(copyBoard, !turn);
        }
    }
    return levelMoves;
}

vector<vector<Vec>> generateCaptureMoves(vector<vector<Vec>> possibleMoves) {
    vector<vector<Vec>> levelMoves;
    for (int i = 0; !possibleMoves.empty(); ++i) {
        Vec start = possibleMoves[i][0];
        Vec end = possibleMoves[i][1];
        if(isValid(start, end)) {
            if(isThere(end)) levelMoves.emplace_back(vector<Vec>{start, end});
            // No need to simulate any moves because if it is a valid move and there is a piece at end, then it is a capture move
        }
    }
    return levelMoves;
}

vector<vector<Vec>> generateAvoidCaptureMoves(vector<vector<Vec>> possibleMoves) {
// 1. We need to know the enemy moves firstly, not our piece’s move. We need to use the enemy piece’s end coordinates
// 2. Check compare all of the enemy piece’s capture move’s end points. Compare those end points to our our pieces current pieces start points. 
// 3. If they match, check if these piece’s end points are outside/dont exist in the enemy’s move’s end points.
// I am going to classify as an avoidCapture move as singular. If it avoids atleast 1 piece's capture/end point
// wherever I land after make ssaid avoidCapture move, I dont care whether it puts me in another capture spot or not. ()
// Technically, the move itself is already avoiding A capture, I will still code the idea for avoiding both captuyres.
    vector<vector<Vec>> enemyMoves = cb->getLegalMoves(!turn);
    vector<vector<Vec>> levelMoves;
    for(int i = 0; !possibleMoves.empty(); ++i) {
        bool check1 = false;
        bool check2 = false;
        Vec start = possibleMoves[i][0];
        Vec end = possibleMoves[i][1];

        // Simple Avoid Capture
        for (int j = 0; !enemyMoves.empty(); ++j) {
            if (enemyMoves[j][1] == start) {
                levelMoves.emplace_back(start, end);
                break; // Simple avoid capture move
            }
        }

        // // More complicated Avoid Capture
        // // Avoids not only capture of their stard coordinate, but also their end coordinate
        // for (int k = 0; !enemyMoves.empty(); ++k) {
        //     if(enemyMoves[k][1] == start) check1 = true;
        // }
        // for(int l = 0; !enemyMoves.empty(); ++l) {
        //     if(enemyMoves[l][1] == end) break;
        //     // This means the move's end position is also in danger of being captured. 
        // }
        // if(check! && check2) levelMoves.emplace_back(vector<Vec>{start, end});
    }
}

void ChessBoard::makeComputerMove(Player *p){
    // based on level, makeComputerMove 
    int level = p.getLevel();

    // get the legal moves for the player
    vector<vector<Vec>> legalMoves = cb->getLegalMoves(turn);
    vector<Vec> move; // there are two Vecs [start, end]
    vector<vector<Vec>> levelMoves = generateAllLevelMoves(legalMoves, level);

    if (turn){
        move = cb->playerWhite->selectMove(levelMoves);
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
