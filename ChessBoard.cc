#include "ChessBoard.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Empty.h"
#include <utility>

#include "TextDisplay.h"
#include "GraphicsDisplay.h" // We call their notify
#include "Observer.h"
using namespace std;

// DONE
bool ChessBoard::boardIsValid() {
    // One White KIng - good
    // One Black King - good
    // No Pawns on the First Row (Row 0)   -good
    // No Pawns on the Last Row (Row 7) - good
    // Neither king is inCheck
    bool oneBlack = false;
    bool oneWhite = false;

    int rowSize = eb.size();
    int colSize = eb[1].size();

	for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            // CHECKS THAT THERE IS ONLY ONE BLACK PIECE
            if (!oneBlack && (p->getType() == 'k')) {
                oneBlack = true;
            } else if(oneBlack && (p->getType() == 'k')) {
                return false;
            }
            // CHECKS THAT THERE IS ONLY ONE WHITE PIECE
            if (!oneWhite && (p->getType() == 'K')) {
                oneWhite = true;
            } else if(oneWhite && (p->getType() == 'K')) {
                return false;
            }
        }
    }
    // If either white (true) or black (false) are in check, not a valid board
    if (isCheck(true) || isCheck(false)) return false;


    // Checks for Pawns on the first row
	for (shared_ptr<Piece> p : gb[0]){
        if(p->getType() == 'p' || p->getType() == 'P') return false;
    }
    // Checks for Pawns on the last row
    for (shared_ptr<Piece> p : gb[7]){
        if(p->getType() == 'p' || p->getType() == 'P') return false;
    }
    // After board is determined to be valid
    
	for (vector<shared_ptr<Piece>> vec : gb) {
		for (shared_ptr<Piece> p : vec) {
            if(p->getTeam() = turn) {
                p->getPossibleMoves();
                for (Vec end : p->returnPossibleMoves) {
                    testMove(p->getCoordinate(), end);
                }
            } // Sets up that piece'possible moves
        }
    } 
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
    if (type == 'P' || type == 'p'){ shared_ptr<Pawn> pawn = dynamic_pointer_cast<Pawn>(p); }
    else { return false; }

    if (pawn->pawnMovedTwo(gb, coordinate, white)){ // Idk why has issues
        return true; 
    }
    return false;
}

// DONE
void ChessBoard::replacePiece(Vec coordinate, shared_ptr<Piece> replacement){
    int row = coordinate.getY();
    int col = coordinate.getX();
    gb[row][col] = replacement;
}

// DONE --> NO STILL NEED FOR GENERATECAPTUREMOVES TODO: HELENA
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
bool twoStep(Vec start, Vec end){
    int startY = start.getY();
    int endY = end.getY();
    if (startY = endY - 2 || startY == endY + 2){ return true; }
    return false;
}

// Attach the player observers to each piece
// It will also now attach the playerWhite and playerBlack pointers
void ChessBoard::setupPlayers(unique_ptr<Observer> pWhite, unique_ptr<Observer> pBlack) {
    // You can make a unique to a shared, but not other way around
    // shared_ptr<Observer> sharedWhite = make_shared<Observer>(pWhite);
    // shared_ptr<Observer> sharedBlack = make_shared<Observer>(pBlack);
    playerWhite = std::move(pWhite);
    playerBlack = std::move(pBlack);

    // Iterate through the game board and set up observers for each piece
    // for (auto& row : gb) {
    //     for (auto& p : row) {
    //         if (p) { // Check if the pointer is not null
    //             p->attachWhite(sharedWhite); // We might have to change this to handle shared_ptr not unique_ptr
    //             p->attachBlack(sharedBlack);
    //         }
    //     }
    // }

}

// Piece::Piece(struct Vec coordinate, char type, bool colour): coordinate{coordinate}, type{type}, white{colour} {} Piece constructor
// Empty piece seems to just have a superclass constructor of parent class Piece.
// To create the empty construcotr, what do I actually pass? (Empty(Vec{row,col}, _ or ' ', true or false)))

// FRANKLIN
ChessBoard::ChessBoard() : playerWhite{nullptr}, playerBlack{nullptr}, td{make_unique<TextDisplay>()}, gd{make_unique<GraphicsDisplay>()}, game{}, bCheck{false}, wCheck{false}, turn{true}, bKing{}, wKing{} {
    // Setup the empty board and gameboard
    // unique_ptr<TextDisplay> td, unique_ptr<GraphicDisplay> gd, I have to make this here

    bool back = true;
    for (int row = 0; row < 8; row++) {
        vector<unique_ptr<Piece>> ebRow;
        vector<shared_ptr<Piece>> gbRow;
        for (int col = 0; col < 8; ++col) {
            // gb[row][col] = make_shared<Piece>();
            // Top left corner, the colour of the board is white. Bottom right (7,7) is white as well
            if(back) { // Alternating of black and white
                ebRow.push_back(make_unique<Empty>(Empty(Vec{row, col}, ' ', true)));
                gbRow.push_back(make_shared<Piece>(Empty(Vec{row, col}, ' ', true)));
                back = false;
            } else {
                ebRow.push_back(make_unique<Empty>(Empty(Vec{row, col}, '_', false)));
                gbRow.push_back(make_shared<Piece>(Empty(Vec{row, col}, '_', false)));
                back = true;
            }
        }
        eb.push_back(move(ebRow));
        gb.push_back(move(gbRow));
    }
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

// DONE
void ChessBoard::notify(Vec start, Vec end){

    makeMove(start, end);

    char startType = getType(end);

    // we will also change the king's booleans
    if (startType == 'K' || startType == 'k'){
        updateKingCoord(end, turn);
        updateKingMoved(end);
    }

    // check if the piece that moved is a pawn
    if (startType == 'P' || startType == 'p'){
        updatePawnMoved(start, end);
    }

    // update if THE OTHER TEAM is in check
    if (turn){
        bCheck = isCheck(false);
    } else {
        wCheck = isCheck(true);
    }

     // reset the legal moves of every piece // only go through the opponents
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            p->resetMoves(); // clear all the legal moves
            p->getPossibleMoves(gb); // get the possible moves for this piece
            // It was initially just possibleMoves
            // test every possible move -> which will add it to the legal moves if it passes
            // this will test
            for (Vec move : p->returnPossibleMoves()){
                testMove(p->getCoordinate(), move);
            }
        }
    }

    // change the turn
    turn? false : true;

    shared_ptr<Piece> emptyPiece = getPiece(start);
    shared_ptr<Piece> endPiece = getPiece(end);

    // notify the gd and td
    char startChar = emptyPiece->getType();
    char endChar = endPiece->getType();
    td->notify(start, startChar, end, endChar);
    gd->notify(start, startChar, end, endChar);

}


// ALMOST DONE
// this needs to keep track of if there are no possible moves
void ChessBoard::testMove(Vec start, Vec end){
    // make a deep copy of the gb
    // consult about making a deep copy of the board
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

    char startType = getType(start);
    Vec wKingCoord;
    Vec bKingCoord;

    if (turn && startType != 'K'){
        wKingCoord = wKing;
    } else if (!turn, startType != 'k'){
        bKingCoord = bKing;
    } else if (turn){
        wKingCoord = start;
    } else {
        bKingCoord = start;
    }

    // now we can make edits on the game board which we will later revert
    makeMove(start, end);
    // we can safely update the booleans of pieces and update

    // we will also change the king's booleans
    if (startType == 'K' || startType == 'k'){
        updateKingCoord(end, turn);
        updateKingMoved(end);
    }

    // check if the piece that moved is a pawn
    if (startType == 'P' || startType == 'p'){
        updatePawnMoved(start, end);
    }

    // TODO: technically to make this more efficient we only have it iterate through the current's possible moves 
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            if (p->getTeam() == turn){ continue; } 
            p->resetMoves(); // clear all the legal moves
            p->possibleMoves(gb); // get the possible moves for this piece
        }
    }
    // TODO: i think somewhere above need break because what if not possible move?
    // --------------------- at this point ALL the pieces have possible moves -----------------------------
    // we need to decide if any of these moves will put the opponent's king in check

    // need to check if that move puts the opponent in check 
    bool check = isCheck(!turn);
    
    // we decide its legal -> notify player 
    if (!check){
        if (!turn){ playerWhite->notifyLM(start, end); } // if the next turn (opponent is white)
        else { playerBlack->notifyLM(start, end); }
    }

    if (isCaptureMove(start, end)) {
        if (!turn){ playerWhite->notifyCapM(start, end); } // if the next turn (opponent is white)
        else { playerBlack->notifyCapM(start, end); }
    }

    if (isCheckMove(start, end)) {
        if (!turn){ playerWhite->notifyCheckM(start, end); } // if the next turn (opponent is white) // TODO: take away observer.h? make player directly observer
        else { playerBlack->notifyCheckM(start, end); }
    }

    if (isCheckmateMove(start, end)) {
        if (!turn){ playerWhite->notifyCMM(start, end); } // if the next turn (opponent is white)
        else { playerBlack->notifyCMM(start, end); }
    }
// in player we ahve a bunch of notifoes just like nogtify legal move concatenate to add in categories, then inside of chessboard have the
// helper functions and call them inside testMove after check it does not make it check, which is where w put it in notify for player anwyays
// and then if it meets the category for the helper function we notify it accordinlgy for player to put in vectorvectorvec of category
// and we are okay if it's in more than one category

// player observes chessboard, chessboard calls player's notify for specific playerBlack/White so dont have
// a vector of observers?

    // revert the board -> switch the board copy to the gb
    // this swap might not work
    // Yup chatgpt said nada
    swap(gb, boardCopy);


    // revert the king's coordinates
    if (turn){
        swap(wKingCoord, wKing);
    } else {
        swap(bKingCoord, bKing);
    }

    // unique pointers will go out of scope once the function returns
}

// DONE
bool ChessBoard::isCheck(bool white){
    Vec kingCoord;
    if (white){
        kingCoord = wKing;
    } else {
        kingCoord = bKing;
    }

    // compare the legal moves of each piece with the king's coordinates
    for(vector<shared_ptr<Piece>> vec : gb){
        for(shared_ptr<Piece> p : vec){
            if (p->getTeam() == white){ continue; } // skip pieces on our own team
            for(Vec move : p->getPossibleMoves()){
                if (move == kingCoord){
                    return true;
                }
            }
        }
    }
    return false;
}

void isCheckMateMove(){
    // get the possible moves of the current 
    bool empty = true;
    for (vector<shared_ptr<Piece>> vec : gb){
        for (shared_ptr<Piece> p : vec){
            if (p->getTeam() != turn){ continue;}
            p->possibleMoves(gb);
            if (p->getPossibleMoves().size() != 0){ empty = false}
        }
    }

    if (isCheck(turn) && empty){ 
        // notify player 
    }
}

// DONE
bool ChessBoard::getTurn(){
    return turn;
}

// DONE
// I need to do dynamic type casting.
void ChessBoard::setupWithChar(char type, Vec coordinate) {
    int row = coordinate.getY();
    int col = coordinate.getX();

    if (type == 'K' || type == 'k') {
        gb[row][col] = make_shared<King>(coordinate, type, (type == 'K') ? 1 : 0); // King
    } else if (type == 'Q' || type == 'q') {
        gb[row][col] = make_shared<Queen>(coordinate, type, (type == 'Q') ? 1 : 0); // Queen
    } else if (type == 'P' || type == 'p') {
        gb[row][col] = make_shared<Pawn>(coordinate, type, (type == 'P') ? 1 : 0); // Pawn
    } else if (type == 'N' || type == 'n') {
        gb[row][col] = make_shared<Knight>(coordinate, type, (type == 'N') ? 1 : 0); // Knight
    } else if (type == 'R' || type == 'r') {
        gb[row][col] = make_shared<Rook>(coordinate, type, (type == 'R') ? 1 : 0); // Rook
    } else if (type == 'B' || type == 'b') {
        gb[row][col] = make_shared<Bishop>(coordinate, type, (type == 'B') ? 1 : 0); // Bishop
    } else if (type == ' ' || type == '_') { //These may not be needed but im just having. I dont think it would ever reach it
        gb[row][col] = getEmptyPiece(coordinate);
    } else {
        // Handle other cases or provide a default behavior
    }
}

// DONE
void ChessBoard::setupWithPiece(shared_ptr<Piece> p, Vec coordinate) {
    int row = coordinate.getY();
    int col = coordinate.getX();

    gb[row][col] = p;
    // That should be fine because I am using this to only setup empty pieces.
    // It is fine that the gameboard starts and has empty pieces at first
}

// DONE
shared_ptr<Piece> ChessBoard::getEmptyPiece(Vec coord){
    // access the empty board and get the Piece* we want
    int row = coord.getY();
    int col = coord.getX();
    shared_ptr<Piece> emptyPiece = make_shared<Piece>(*(eb[row][col]));
    // Assume this copy construtor will work

    // return the copied piece
    return emptyPiece;
}

// DONE
void ChessBoard::forfeit(){
    if (turn){
        // update score +1 for black
        game.updateBlack(false);
    } else {
        // update score +1 for white
        game.updateWhite(false);
    }
}

// DONE //TODO: use player ptr access legalMoves to see if empty
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
    for(size_t i = 0; i < eb.size(); ++i) { //The row
        for (size_t j = 0; j < eb[i].size(); ++j) { // The column
        // Remmber, we have a vector<vector<>>>>
            gb[j][i] = make_shared<Piece>(*(eb[i][j]));
            // Assume the copy assignment operator works
        }
    }
    turn = true; // Default turn is always white
    bCheck = false;
    wCheck = false;
    // We don't need to reset bKing and wKing because it will be reset in next
    // game or if not, will just be destroyed.
}

// DONE
bool ChessBoard::upgradePawn(Vec end){
    char type = getType(end);
    if (type == 'P' || type == 'p'){ return true; }
    else { return false; }
}


// DONE
void ChessBoard::setWhiteKing(Vec coordinate){
    wKing = coordinate;

}

// DONE
void ChessBoard::setBlackKing(Vec coordinate){
    bKing = coordinate;

}

//________________________________________________________ HELENAS CODE SORRY IT'S MESSY DONT TOUCH _____________________________

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

// HELENAS NEW
// TODO: checkmate basically puts opponent king in check (this part just like chiaras testMove function) and no more legalMoves for opponent (this fucked since never have legalMoves)
bool ChessBoard::isCheckmateMove(Vec start, Vec end) {
    // TODO: before from franklins it had isValid() checking start and end, im just gonna assume that it is already valid at this point because of testMove function

    //TODO: copied from chiara testMove
    // make a deep copy of the gb
    // consult about making a deep copy of the board
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

    char startType = getType(start);
    Vec wKingCoord;
    Vec bKingCoord;

    if (turn && startType != 'K'){
        wKingCoord = wKing;
    } else if (!turn, startType != 'k'){
        bKingCoord = bKing;
    } else if (turn){
        wKingCoord = start;
    } else {
        bKingCoord = start;
    }

    // now we can make edits on the game board which we will later revert
    makeMove(start, end);
    // we can safely update the booleans of pieces and update

    // we will also change the king's booleans
    if (startType == 'K' || startType == 'k'){
        updateKingCoord(end, turn);
        updateKingMoved(end);
    }

    // check if the piece that moved is a pawn
    if (startType == 'P' || startType == 'p'){
        updatePawnMoved(start, end);
    }

    // TODO: technically to make this more efficient we only have it iterate through the opponent's possible moves
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            if (p->getTeam() == turn){ continue; }
            p->resetMoves(); // clear all the legal moves
            p->getPossibleMoves(gb); // get the possible moves for this piece
        }
    }
    // TODO: i think somewhere above need break because what if not possible move?
    // --------------------- at this point ALL the pieces have possible moves -----------------------------
    // we need to decide if any of these moves will put the opponent's king in check

    // need to check if that move the opponent
    bool check = isCheck(turn); // TODO: checking if our move puts the opponent in check? or checking if puts our opponent in check?????
    // TODO: should be not putting our king in check

    if (check) { // check it's putting opponent king in check
        if (turn && playerWhite.getLegalMoves().size() == 0) //TODO: smth like this but this is also fucked up because player is observer subclass and observer doesnt have legalMoves???
        return true;
    }
    return false;

}

// FRANKLINS OLD
// vector<vector<Vec>> generateCheckmateMoves(vector<Vec> possibleMoves) {
//     vector<vector<Vec>> levelMoves;
//     for (int i = 0; !possibleMoves.empty(); ++i) {
//         Vec start = possibleMoves[i][0];
//         Vec end = possibleMoves[i][1];
//         if(isValid(start, end)) {
//             // Asumption: Before we reach this point, the game is not in a "isEnd()" state. Is this valid?
//             vector<vector<unique_ptr<Piece>>> copyBoard = gb;
//             notify(start, end);
//             // Now need to check if this is a check/checkmate Move. But we run into the same issue of we have to make sure that being in checkmate
//             // Doesn't end the game. From my understanding, I will be calling isEnd() after every move made in main.
//             // And ending the game if true. If i do this simulation in a function, as long as I revert the move before reaching the isEnd in main
//             // No issues?

//             if(isEnd()) levelMoves.emplace_back(vector<Vec>{start, end});  // Checks to see if after such a move, if the game is voer.

//             revertBoard(copyBoard, !turn);
//         }
//     }
//     return levelMoves;
// }

// HELENAS NEW
bool ChessBoard::isCheckMove(Vec start, Vec end) {
    // chiara's copied testMove

    // make a deep copy of the gb
    // consult about making a deep copy of the board
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

    char startType = getType(start);
    Vec wKingCoord;
    Vec bKingCoord;

    if (turn && startType != 'K'){
        wKingCoord = wKing;
    } else if (!turn, startType != 'k'){
        bKingCoord = bKing;
    } else if (turn){
        wKingCoord = start;
    } else {
        bKingCoord = start;
    }

    // now we can make edits on the game board which we will later revert
    makeMove(start, end);
    // we can safely update the booleans of pieces and update

    // we will also change the king's booleans
    if (startType == 'K' || startType == 'k'){
        updateKingCoord(end, turn);
        updateKingMoved(end);
    }

    // check if the piece that moved is a pawn
    if (startType == 'P' || startType == 'p'){
        updatePawnMoved(start, end);
    }

    // TODO: technically to make this more efficient we only have it iterate through the opponent's possible moves
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            if (p->getTeam() == turn){ continue; }
            p->resetMoves(); // clear all the legal moves
            p->getPossibleMoves(gb); // get the possible moves for this piece
        }
    }
    // TODO: i think somewhere above need break because what if not possible move?
    // --------------------- at this point ALL the pieces have possible moves -----------------------------
    // we need to decide if any of these moves will put the opponent's king in check

    // need to check if that move the opponent
    bool check = isCheck(turn); // TODO: checking if our move puts the opponent in check? or checking if puts our opponent in check?????
    // TODO: should be not putting our king in check

    // we decide its legal -> notify player
    if (check){
       return true;
    } else {
        return false;
    }
}

// FRANKLINS OLD
// vector<vector<Vec>> generateCheckMoves(vector<vector<Vec>> possibleMoves) {
//     vector<vector<Vec>> levelMoves;
//     for (int i = 0; !possibleMoves.empty(); ++i) {
//         Vec start = possibleMoves[i][0];
//         Vec end = possibleMoves[i][1];
//         if(isValid(start, end)) {
//             vector<vector<unique_ptr<Piece>>> copyBoard = gb;
//             notify(start, end);
//             // Now need to check if this is a check/checkmate Move. But we run into the same issue of we have to make sure that being in checkmate
//             // Doesn't end the game
//             // void revertBoard(vector<vector<unique_ptr<Piece>>> oldPieces, bool oldTurn);
//           levelMoves.emplace_back(vector<V  if(isCheck(turn)) ec>{start, end}); // It is turn, not !turn because if it was white before, calling notify sets turn to black now which is what we wanted to check anyways
//             revertBoard(copyBoard, !turn);
//         }
//     }
//     return levelMoves;
// }

// basically have it still observer pattern, calling player's notify to put it inside of the categorized
// vector of vector of vecs and then based on this, filter the moves (eg have a vectorvectorvec of generateCaptureMoves,

//capture move assume board has not made a move so we can check if move is gonna capture a piece
// for every other category, assume using board after move made
// arguments start and end, if passes notify player and append it to right field

// have a bunch of notifies

// HELENAS NEW
bool ChessBoard::isCaptureMove(Vec start, Vec end) {
    if(isThere(end)) return true;
    return false;
    // No need to simulate any moves because if it is a valid move and there is a piece at end, then it is a capture move
}

/// FRANKLINS OLD
// vector<vector<Vec>> generateCaptureMoves(vector<vector<Vec>> possibleMoves) {
//     vector<vector<Vec>> levelMoves;
//     for (int i = 0; !possibleMoves.empty(); ++i) {
//         Vec start = possibleMoves[i][0];
//         Vec end = possibleMoves[i][1];
//         if(isValid(start, end)) {
//             if(isThere(end)) levelMoves.emplace_back(vector<Vec>{start, end});
//             // No need to simulate any moves because if it is a valid move and there is a piece at end, then it is a capture move
//         }
//     }
//     return levelMoves;
// }

// HELENAS NEW
vector<vector<Vec>> isAvoidCaptureMove(vector<vector<Vec>> possibleMoves) {
// 1. We need to know the enemy moves firstly, not our piece’s move. We need to use the enemy piece’s end coordinates
// 2. Check compare all of the enemy piece’s capture move’s end points. Compare those end points to our our pieces current pieces start points.
// 3. If they match, check if these piece’s end points are outside/dont exist in the enemy’s move’s end points.
// I am going to classify as an avoidCapture move as singular. If it avoids atleast 1 piece's capture/end point
// wherever I land after make ssaid avoidCapture move, I dont care whether it puts me in another capture spot or not. ()
// Technically, the move itself is already avoiding A capture, I will still code the idea for avoiding both captuyres.
    vector<vector<Vec>> enemyMoves = cb->getLegalMoves(!turn); // TODO: this is the issue, won't work because we don't have legalMoves because testMoves iterates 1 by 1
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

// FRANKLINS OLD
// vector<vector<Vec>> generateAvoidCaptureMoves(vector<vector<Vec>> possibleMoves) {
// // 1. We need to know the enemy moves firstly, not our piece’s move. We need to use the enemy piece’s end coordinates
// // 2. Check compare all of the enemy piece’s capture move’s end points. Compare those end points to our our pieces current pieces start points.
// // 3. If they match, check if these piece’s end points are outside/dont exist in the enemy’s move’s end points.
// // I am going to classify as an avoidCapture move as singular. If it avoids atleast 1 piece's capture/end point
// // wherever I land after make ssaid avoidCapture move, I dont care whether it puts me in another capture spot or not. ()
// // Technically, the move itself is already avoiding A capture, I will still code the idea for avoiding both captuyres.
//     vector<vector<Vec>> enemyMoves = cb->getLegalMoves(!turn);
//     vector<vector<Vec>> levelMoves;
//     for(int i = 0; !possibleMoves.empty(); ++i) {
//         bool check1 = false;
//         bool check2 = false;
//         Vec start = possibleMoves[i][0];
//         Vec end = possibleMoves[i][1];

//         // Simple Avoid Capture
//         for (int j = 0; !enemyMoves.empty(); ++j) {
//             if (enemyMoves[j][1] == start) {
//                 levelMoves.emplace_back(start, end);
//                 break; // Simple avoid capture move
//             }
//         }

//         // // More complicated Avoid Capture
//         // // We can use this for higher levels of computer instead
//         // // Avoids not only capture of their stard coordinate, but also their end coordinate
//         // for (int k = 0; !enemyMoves.empty(); ++k) {
//         //     if(enemyMoves[k][1] == start) check1 = true;getEmp
//         // }
//         // for(int l = 0; !enemyMoves.empty(); ++l) {
//         //     if(enemyMoves[l][1] == end) break;
//         //     // This means the move's end position is also in danger of being captured.
//         // }
//         // if(check! && check2) levelMoves.emplace_back(vector<Vec>{start, end});
//     }
// }

// possible moves in pieces (making sure there's no piece there) legal moves ()
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
    setupWithChar('N', Vec{1,0});
    setupWithChar('N', Vec{6, 0}); // Whites
    setupWithChar('n', Vec{1,7});
    setupWithChar('n', Vec{6, 7}); // Black

    // Setup Bishops
    setupWithChar('B', Vec{2,0});
    setupWithChar('B', Vec{5, 0}); // Whites
    setupWithChar('b', Vec{2,7});
    setupWithChar('b', Vec{5, 7}); // Black

    // Setup Kings
    setupWithChar('K', Vec{0,3}); // White King
    setupWithChar('k', Vec{7, 3}); // Black King
    setWhiteKing(Vec{0,3});
    setBlackKing(Vec{7, 3});

    // Setup Queens
    setupWithChar('Q', Vec{0,4}); // White Queen
    setupWithChar('q', Vec{7, 4}); // Black Queen

    for (vector<shared_ptr<Piece>> vec : gb) {
		for (shared_ptr<Piece> p : vec) {
            if(p->getTeam() = turn) {
                p->getPossibleMoves();
                for (Vec end : p->returnPossibleMoves) {
                    testMove(p->getCoordinate(), end);
                }
            } // Sets up that piece'possible moves
        }
    } 
}

ostream& operator<<(ChessBoard& cb, ostream& out) {
    out << *(cb.tdOutput);
}