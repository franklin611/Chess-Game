#include "ChessBoard.h"
#include "Piece.h"
using namespace std;
#include "Player.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "Pawn.h"
#include "King.h"

// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK
// YOU CANNOT CASTLE WHILE IN CHECK

// DONE
void ChessBoard::makeComputerMove(unique_ptr<Player> p){
    // based on level, makeComputerMove
    int level = p->getLevel();

    // get the legal moves for the player
    vector<vector<Vec>> legalMoves = getLegalMoves(turn);
    vector<Vec> move; // there are two Vecs [start, end]
    vector<vector<Vec>> levelMoves = generateAllLevelMoves(legalMoves, level);

    if (turn){
        move = playerWhite->selectMove(levelMoves);
    } else {
        move = playerBlack->selectMove(legalMoves);
    }
    notify(move[0], move[1]);
}

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

// DONE
void ChessBoard::replacePiece(Vec coordinate, shared_ptr<Piece> replacement){
    int row = coordinate.getY();
    int col = coordinate.getX();
    gb[row][col] = replacement;
}

// DONE
bool ChessBoard::isThere(Vec coordinate){
	for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
			if ((p->getType() != ' ' || p->getType() != '_') && p->getCoordinate() == coordinate){
				return true;
			}
		}
	}
	return false;
}

// DONE
bool ChessBoard::isValid(Vec start, Vec end){
    // use start to get piece
    int row = start.getY();
    int col = start.getX();
    shared_ptr<Piece> p = gb[row][col];

    // use end to validate move
    return p->isMoveValid(end);
}

// DONE
bool twoStep(Vec start, Vec end){
    int startY = start.getY();
    int endY = end.getY();
    if (startY = endY - 2 || startY == endY + 2){ return true; }
    return false;
}

// FRANKLIN 
ChessBoard::ChessBoard(unique_ptr<Player> playerWhite, unique_ptr<Player> playerBlack){

}

// FRANKLIN
void ChessBoard::setupPlayers(unique_ptr<Player> playerWhite, unique_ptr<Player> playerBlack){

}

// DONE
void ChessBoard::regMove(Vec start, Vec end){
    shared_ptr<Piece> startPiece = getPiece(start);
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

}

// DONE
void ChessBoard::castleMove(Vec start, Vec end){
    int startX = start.getX();
    int endX = end.getX();

    Vec rookCoord;
    // the y coordinate tells us which colour we want -> keep the y coordinate the same to get the correct rook
    rookCoord.setY(end.getY());

    if (endX = startX + 2){ // moved to the right -> move the rook to the right TO the left 
        rookCoord.setY(7);
        Vec endCoord = Vec(end.getX() - 1, end.getY()); 
        makeMove(rookCoord, endCoord);
    } else if (endX = startX - 3){ // moved to the left -> move the rook to the left TO the right
        rookCoord.setY(0);
        Vec endCoord = Vec(end.getX() + 1, end.getY());
        makeMove(rookCoord, endCoord);
    }

}

void ChessBoard::makeMove(Vec start, Vec end){

}

// DONE
void ChessBoard::updatePawnMoved(Vec start, Vec end){
    shared_ptr<Piece> endPiece = getPiece(end);
    shared_ptr<Pawn> pawn = dynamic_pointer_cast<Pawn>(endPiece);
    pawn->hasMoved();
    if (twoStep(start, end)){ pawn->hasMovedTwo(); }
}

// DONE
void ChessBoard::updateKingMoved(Vec end){
    shared_ptr<Piece> endPiece = getPiece(end);
    shared_ptr<King> king = dynamic_pointer_cast<King>(endPiece);
    king->hasMoved();
}

// DONE
void ChessBoard::updateKingCoord(Vec end, bool white){
    if (white){
        wKing == end;
    } else {
        bKing == end;
    }
}

void 
// ALMOST DONE -> CONFIRM WITH HELENA 
void ChessBoard::notify(Vec start, Vec end){

    // make the move 
    makeMove(start, end);
    char startType = getType(end);
    // check if it was a castle move and if it was make the appropriate rook move 
    if (startType == 'K' || startType == 'k'){ castleMove(start, end); }

    char startType = getType(end);

    // we will also change the king's booleans
    if (startType == 'K' || startType == 'k'){
        updateKingCoord(end, turn);
        updateKingMoved(end);
    }

    // check if the piece that moved is a pawn 
    if (startType == 'P' || startType == 'p'){ updatePawnMoved(start, end); }

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

    // might need to notify the td and gd 

}

// CHIARA 
// void ChessBoard::revertBoard(vector<vector<shared_ptr<Piece>>> boardCopy){

//     // we assume that boardCopy is a deep copy of the original board that we want to revert back to 
//     // copy every piece from boardCopy to gb
//     for (size_t i = 0; i < boardCopy.size(); ++i){
//         for (size_t j = 0; j < boardCopy[0].size(); ++j){
//             gb[i][j] = boardCopy[i][j];
//         }
//     }


// }

// CHIARA 
// office hours 
// two ideas -> make this a notification 
// allow pieces to have a chessboard pointer so they can call the function 
void ChessBoard::testMove(Vec start, Vec end){
    // make a deep copy of the gb  
    // creating a 2D vector of unique pointers by copying from the shared vector
    vector<vector<unique_ptr<Piece>>> boardCopy;

    for (std::vector<std::shared_ptr<Piece>> vec : gb) {
        std::vector<std::unique_ptr<Piece>> uniqueRow;
        for (std::shared_ptr<Piece> p : vec) {
            // Copying data from shared_ptr to unique_ptr
            uniqueRow.push_back(std::make_unique<Piece>(*p));
        }
        boardCopy.push_back(uniqueRow);
    }

    // now we can make edits on the game board which we will later revert 
    makeMove(start, end);
    if ()


    // unique pointers will go out of scope once the function returns 
}

// CHIARA
// update piece pointers
vector<vector<Piece>> ChessBoard::getGameBoard(){
    return gb;
}

// DONE
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

// DONE
bool ChessBoard::getTurn(){
    return turn;
}

// FRANKLIN 
void ChessBoard::setupWithChar(char type, Vec coordinate) {
    int row = coordinate.getY();
    int col = coordinate.getX();

    if(type >= 'A' && type <= 'Z' || type == ' ') { //White Colour
        gb[row][col] = Piece{coordinate, type, white};
    } else if (type >= 'a' && type <= 'z' || type == '_') {
        gb[row][col] = Piece{coordinate, type, black};
    }
    // So creates white pieces for upper cases and ' '
    // Creates black pieces for lower case and _
    // I dont think I even need to have the ' ' and _, but keeping it for now!!
}

// FRANKLIN 
void ChessBoard::setupWithPiece(Piece &p, Vec coordinate) {
    int row = coordinate.getY();
    int col = coordinate.getX();

    gb[row][col] = p;
}

// CHIARA
Piece* ChessBoard::getEmptyPiece(Vec coord){
    // access the empty board and get the Piece* we want
    int row = coord.getY();
    int col = coord.getX();
    Piece emptyPiece = eb[row][col];

    // return the copied piece
    return emptyPiece;
}

// DONE ???????? 
void ChessBoard::forfeit(){
    if (turn){
        // update score +1 for black
        game.updateBlack(false);
    } else {
        // update score +1 for white
        game.updateWhite(false);
    }
    // restart game
}

// DONE
bool ChessBoard::isEnd() {
    if (turn) {
        if (wCheck && getLegalMoves(turn).empty()) {
            game.updateWhite(false);
            return true;
        }
        else if (getLegalMoves(turn).empty()) {
            game.updateWhite(true);
            return true;
        }
    } else {
        if (bCheck && getLegalMoves(turn).empty()) {
            game.updateBlack(false);
            return true;
        }
        else if (getLegalMoves(turn).empty()) {
            game.updateBlack(true);
            return true;
        }
    }
}

// CHIARA
void ChessBoard::restartGame() {
     for(size_t i = 0; i < eb.size(); ++i) {
        for (size_t j = 0; j < eb[0].size(); ++j) {
            gb[i][j] = eb[i][j];
        }
     }
    turn = true; // Default turn is always white   
    bCheck = false;
    wCheck = false;
    
    // We don't need to reset bKing and wKing because it will be reset in next
    // game or if not, will just be destroyed.
}

// CHIARA 
bool ChessBoard::upgradePawn(Vec end){

}

// CHIARA 
vector<vector<Vec>> ChessBoard::getLegalMoves(bool white){

}


// CHIARA
void ChessBoard::setWhiteKing(Vec coordinate){

}

// CHIARA 
void ChessBoard::setBlackKing(Vec coordinate){

}

// idk man
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


// Helena to Update
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


void ChessBoard::defaultBoard() {

    // First setup pawns 
    for (int i = 0; i < 8; ++i) {
        setupByChar('P', Vec{i, 1}); // White pawns
        setupByChar('p', Vec{i, 7}); // Black
        // x, y. This corresponds to second row
    }

    // Whites are the top side of the board. 0,0 

    // Setup Rooks
    setupByChar('R', Vec{0,0});
    setupByChar('R', Vec{0, 7}); // Whites
    setupByChar('r', Vec{7,0});
    setupByChar('r', Vec{7, 7}); // Whites

    // Setup Knights
    setupByChar('K', Vec{1,0});
    setupByChar('K', Vec{6, 0}); // Whites
    setupByChar('k', Vec{1,7});
    setupByChar('k', Vec{6, 7}); // Black

    // Setup Bishops
    setupByChar('B', Vec{2,0});
    setupByChar('B', Vec{5, 0}); // Whites
    setupByChar('b', Vec{2,7});
    setupByChar('b', Vec{5, 7}); // Black

    // Setup Kings
    setupByChar('K', Vec{0,3}); // White King
    setupByChar('k', Vec{7, 3}); // Black King

    // Setup Queens
    setupByChar('K', Vec{0,4}); // White Queen
    setupByChar('k', Vec{7, 4}); // Black Queen
}

