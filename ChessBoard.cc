#include "ChessBoard.h"
#include "Piece.h"
using namespace std;
#include "Player.h"
#include "Computer.h"
#include "TextDisplay.h"
#include "GraphicsDisplay.h"
#include "Pawn.h"
#include "King.h"
#include <vector>
#include "Level.h"

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

// DONE
void ChessBoard::makeComputerMove(unique_ptr<Player> p){

    unique_ptr<Level> l = nullptr;
    auto computerPlayer = dynamic_cast<Computer *>(p.get()) // TODO: idk if this is right, how to dynamic cast from shared ptr

//     // based on level, makeComputerMove
    int level = p->getLevel();
    if (level == 1) {l = make_unique<LevelOne>();}
    if (level == 2) {l = make_unique<LevelTwo>();}
    if (level == 3) {l = make_unique<LevelThree>();}
    if (level == 4) {l = make_unique<LevelFour>();}

    vector<vector<Vec>> legalMoves;
    for (auto &n : legalMoves) {
        n = l->createMove(make_shared<ChessBoard>(this));
        // n = l->createMove(*this);
    }

    // // get the legal moves for the player
    // vector<vector<Vec>> legalMoves = getLegalMoves(turn);
    vector<Vec> move; // there are two Vecs [start, end]
    // vector<vector<Vec>> levelMoves = generateAllLevelMoves(legalMoves, level);

    if (turn){
        move = playerWhite->selectMove(legalMoves); // we do not have a selectMove
    } else {
        move = playerBlack->selectMove(legalMoves);
    }
    notify(move[0], move[1]);
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


// Piece::Piece(struct Vec coordinate, char type, bool colour): coordinate{coordinate}, type{type}, white{colour} {} Piece constructor
// Empty piece seems to just have a superclass constructor of parent class Piece.
// To create the empty construcotr, what do I actually pass? (Empty(Vec{row,col}, _ or ' ', true or false)))

// FRANKLIN
ChessBoard::ChessBoard(unique_ptr<Player> playerWhite, unique_ptr<Player> playerBlack){

// FRANKLIN
ChessBoard::ChessBoard() : playerWhite{make_unique<Player>()}, playerBlack{make_unique<Player>()}, game{}, bCheck{false}, wCheck{false}, turn{true}, bKing{}, wKing{} {
    // Setup the empty board and gameboard
    bool switch = true;
    for (int row = 0; row < 8; row+i) {
        vector<unique_ptr<Piece>> ebRow;
        vector<shared_ptr<Piece>> gbRow;/
        for (int col = 0; col < 8; ++col) {
            // gb[row][col] = make_shared<Piece>();
            // Top left corner, the colour of the board is white. Bottom right (7,7) is white as well
            if(switch) { // Alternating of black and white
                ebRow.push_back(make_unique<Piece>(Piece::Empty(Vec{row, col}, ' ', true)));
                gbRow.push_back(make_shared<Piece>(Piece::Empty(Vec{row, col}, ' ', true)));
                switch = false;
            } else {
                ebRow.push_back(make_unique<Piece>(Piece::Empty(Vec{row, col}, '_', false)));
                gbRow.push_back(make_shared<Piece>(Piece::Empty(Vec{row, col}, '_', false)));
                switch = true;
            }
        }
        eb.push_back(move(ebRow));
        gb.push_back(move(gbRow));
    }
}

// FRANKLIN
// I need to use move() because they are unique ptrs. Transfer ownership of white and black
// to playerWhite and playerBlack respectively.
// Once function goes out of scope, white and black will be nullptrs and be destroyed
void ChessBoard::setupPlayers(unique_ptr<Player> white, unique_ptr<Player> black){
    playerWhite = move(white);
    playerBlack = move(black);
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

    // ------ at this point we want to check if the move was a castle move and move the rook accordingly
    // validate if the piece is a king and it wants to move two spaces to the left or right
    // assume that is true then we want ALREADY moved that king
        // if it moved to the right -> get the rook to the right and move it to the left
        // if it moved to the left -> get the rook to the left and move it to the right


    // 4 Castle Move Cases
    // Case 1: White -> Right
        //
    // Case 2: White -> Left
        //
    // Case 3: Black -> Right
        //
    // Case 4: Black -> Left
        //

    // I WAS CHANGED HERE


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
        regMove(rookCoord, endCoord);
    } else if (endX = startX - 3){ // moved to the left -> move the rook to the left TO the right
        rookCoord.setY(0);
        Vec endCoord = Vec(end.getX() + 1, end.getY());
        regMove(rookCoord, endCoord);
    }

}

// DONE
void ChessBoard::makeMove(Vec start, Vec end){
     // make the move
    regMove(start, end);
    char startType = getType(end);
    // check if it was a castle move and if it was make the appropriate rook move
    if (startType == 'K' || startType == 'k'){ castleMove(start, end); }
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

// ALMOST DONE -> CONFIRM WITH HELENA
void ChessBoard::notify(Vec start, Vec end){

    makeMove(start, end);

    char startType = getType(end);

    // we will also change the king's booleans
    if (startType == 'K' || startType == 'k'){
        updateKingCoord(end, turn);
        updateKingMoved(end);
    }

    // check if the piece that moved is a pawn
    if (startType == 'P' || startType == 'p'){ updatePawnMoved(start, end); }

    // update if THE OTHER TEAM is in check
    if (turn){
        bCheck = isCheck(false);
    } else {
        wCheck = isCheck(true);
    }

    // change the turn
    turn? false : true;


    // DEFINITIONS
    // a possible move is a legal move a piece could make on an empty board
        // it will not capture a teammate
        // it will not jump over pieces (unless it is a knight)
        // it COULD put it's own king in check
    // a tested move is a move that is validated under the as
        // it will not put its own team in check
    // testMove: simulate that move -> we want to know
    // did that move put my king in check
        // look at the opposing teams possible moves and see if my king will get captured

     // reset the legal moves of every piece
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            p->resetMoves(); // clear all the legal moves
            vector<Vec> possibleMoves = p->getPossibleMoves(); // get the possible moves for this piece
            // test every possible move -> which will add it to the legal moves if it passes
            // this will test
            for (Vec move : possibleMoves){
                testMove(p->getCoordinate(), move);
            }
        }
    }

    // notify the
    // char startChar = emptyPiece->getType();
    // char endChar = endPiece->getType();
    // // add coordinate
    // td->notify(startChar, endChar);
    // gd->notify(startChar, endChar);

}

// CHIARA
// flow of the program
// 1. takes input about a move
// 2. validates that the move is valid
// 3. call notify
// in notify
// 4. make the move + update the board
// 5. moves are reset
//      a.) every piece will call its own resetmoves to clear the legal moves
//      b.) every piece will call get possible moves to get a list of possible moves
//      c.) each move will be tested and added to the legalmoves of the piece (at start) if it passes

// CHIARA -> SHARE WITH THE CLASS
// office hours
// two ideas -> make this a notification
// allow pieces to have a chessboard pointer so they can call the function
// this function will ALSO reset the moves of a piece
// this need to simulate the move and just check if the move puts it's own team into check
// ISSUE: when testing a move, the opposing team's set of legal moves includes moves that would put their king in check
// there is a case where your move is considered "illegal" because it puts your king in check, based on a move from the other team that puts their own king in check
// in other words, your move is considered illegal based on an illegal move which (since the hypothesis was false, the conclusion is true!)
// therefore, TECHNICALLY not all the legal moves will be added, but this is a special case that we are omitting to avoid an infinite loop in our implementation
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
    // now the pieces need to reset their possible moves
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            p->resetMoves(); // clear all the legal moves
            vector<Vec> possibleMoves = p->getPossibleMoves(); // get the possible moves for this piece
            // add all the possible moves as legal moves
            for (Vec move : possibleMoves){
               p->addLegalMove(move);
            }
        }
    }


    shared_ptr<Piece> p = getPiece(end);

    // need to check if that move put myself in check
    bool check = isCheck(p->getTeam());

    if (!check){
        // add the end vec to the legal moves
        p->addLegalMove(end);
    }

    // revert the board -> switch the board copy to the gb
    swap(gb, boardCopy);

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
        gb[row][col] = make_shared<Piece>(coordinate, type, 1);
    } else if (type >= 'a' && type <= 'z' || type == '_') {
        gb[row][col] = make_shared<Piece>(coordinate, type, 0);
    }
    // So creates white pieces for upper cases and ' '
    // Creates black pieces for lower case and _
    // I dont think I even need to have the ' ' and _, but keeping it for now!!
}

// FRANKLIN
// I use this in main when I pass it a shared_ptr from the empty board.
// I only ever use this when I am deleting in main and passing an empty piece at the location
// Can I just make this a take a shared_ptr
// Looks Good
void ChessBoard::setupWithPiece(shared_ptr<Piece> p, Vec coordinate) {
    int row = coordinate.getY();
    int col = coordinate.getX();

    gb[row][col] = p;
}

// DONE -> DOUBLE CHECK THIS MIGHT NOT BE A DEEP COPY
shared_ptr<Piece> ChessBoard::getEmptyPiece(Vec coord){
    // access the empty board and get the Piece* we want
    int row = coord.getY();
    int col = coord.getX();
    shared_ptr<Piece> emptyPiece = make_shared<Piece>(*(eb[row][col]));
    // Assume this copy construtor will work

    // return the copied piece
    return emptyPiece;
}

// DONE -> DOES MAIN CALL THE GAME TO RESTART?
void ChessBoard::forfeit(){
    if (turn){
        // update score +1 for black
        game.updateBlack(false);
    } else {
        // update score +1 for white
        game.updateWhite(false);
    }
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

// CHIARA -> need to make sure this is a deep copy (can someone else do this)
void ChessBoard::restartGame() {
     for(size_t i = 0; i < eb.size(); ++i) {
        for (size_t j = 0; j < eb[0].size(); ++j) {
            gb[i][j] = eb[i][j];
    for(size_t i = 0; i < eb.size(); ++i) { //The row
        for (size_t j = 0; j < eb[i].size(); ++j) { // The column
        // Remmber, we have a vector<vector<>>>>
            gb[j][i] = make_shared<Piece>(*(eb[i][j]));
            // Assume the copy assignment operator works
        }
     }
    turn = true; // Default turn is always white
    //  Should be good

    turn = true; // Default turn is always white
    bCheck = false;
    wCheck = false;

    // We don't need to reset bKing and wKing because it will be reset in next
    // game or if not, will just be destroyed.
}

// CHIARA -> someone else could also do this
bool ChessBoard::upgradePawn(Vec end){

}

// CHIARA -> someone else could do this
vector<vector<Vec>> ChessBoard::getLegalMoves(bool white){

}


// CHIARA -> someone else could do this
void ChessBoard::setWhiteKing(Vec coordinate){

}

// CHIARA -> someone else could do this
void ChessBoard::setBlackKing(Vec coordinate){

}

// idk man TODO: how do I have a possibleMoves? what is possibleMoves? is it possibleMoves of a piece? how do I give a piece to
// player -> computer -> level -> levelone?
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
        //     if(enemyMoves[k][1] == start) check1 = true;getEmp
        // }
        // for(int l = 0; !enemyMoves.empty(); ++l) {
        //     if(enemyMoves[l][1] == end) break;
        //     // This means the move's end position is also in danger of being captured.
        // }
        // if(check! && check2) levelMoves.emplace_back(vector<Vec>{start, end});
    }
}

void ChessBoard::defaultBoard() {

    // First setup pawns
    for (int i = 0; i < 8; ++i) {
        setupWithChar('P', Vec{i, 1}); // White pawns
        setupWithChar('p', Vec{i, 7}); // Black
        // x, y. This corresponds to second row
    }

    // Whites are the top side of the board. 0,0

    // Setup Rooks
    setupWithChar('R', Vec{0,0});
    setupWithChar('R', Vec{0, 7}); // Whites
    setupWithChar('r', Vec{7,0});
    setupWithChar('r', Vec{7, 7}); // Whites

    // Setup Knights
    setupWithChar('K', Vec{1,0});
    setupWithChar('K', Vec{6, 0}); // Whites
    setupWithChar('k', Vec{1,7});
    setupWithChar('k', Vec{6, 7}); // Black

    // Setup Bishops
    setupWithChar('B', Vec{2,0});
    setupWithChar('B', Vec{5, 0}); // Whites
    setupWithChar('b', Vec{2,7});
    setupWithChar('b', Vec{5, 7}); // Black

    // Setup Kings
    setupWithChar('K', Vec{0,3}); // White King
    setupWithChar('k', Vec{7, 3}); // Black King

    // Setup Queens
    setupWithChar('K', Vec{0,4}); // White Queen
    setupWithChar('k', Vec{7, 4}); // Black Queen
}

