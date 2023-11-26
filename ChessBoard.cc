#include "ChessBoard.h"
#include "Piece.h"
using namespace std;
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

    // ------ at this point we want to check if the move was a castle move and move the rook accordingly
    // validate if the piece is a king and it wants to move two spaces to the left or right 
    // assume that is true then we want ALREADY moved that king
        // if it moved to the right -> get the rook to the right and move it to the left 
        // if it moved to the left -> get the rook to the left and move it to the right 


    // 4 Castle Move Cases 
    // Case 1: White -> Right 
    // Case 2: White -> Left 
    // Case 3: Black -> Right 
    // Case 4: Black -> Left
    

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


    }

    // check if the piece that moved is a pawn -> also if it moved 2 spaces forward 
    if (startType == 'P' || startType == 'p'){
        shared_ptr<Pawn> pawn = dynamic_pointer_cast<Pawn>(endPiece);
        pawn->hasMoved();
        if (twoStep){ pawn->hasMovedTwo(); }
    }

     // reset the legal moves of every piece
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            p->resetMoves();
        }
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
        // // We can use this for higher levels of computer instead
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

void ChessBoard::setupWithChar(char type, Vec coordinate) {
    int row = coordinate.getX();
    int col = coordinate.getY();
    
    if(type >= 'A' && type <= 'Z' || type == ' ') { //White Colour
        gb[row][col] = Piece{coordinate, type, white};
    } else if (type >= 'a' && type <= 'z' || type == '_') {
        gb[row][col] = Piece{coordinate, type, black};
    }
    // So creates white pieces for upper cases and ' '
    // Creates black pieces for lower case and _
    // I dont think I even need to have the ' ' and _, but keeping it for now!!
}
void ChessBoard::setupWithPiece(Piece &p, Vec coordinate) {
    int row = coordinate.getX();
    int col = coordinate.getY();

    gb[row][col] = p;
}

