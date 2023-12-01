#include "ChessBoard.h"
#include "Pawn.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Empty.h"
#include "Game.h"
#include <utility>
#include "Vec.h"

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

    // int rowSize = eb.size();
    // int colSize = eb[1].size();

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
            if(p->getTeam() == turn) {
                p->getPossibleMoves(gb);
                Vec v = p->getCoordinate();
                vector<Vec> moves = p->returnPossibleMoves();
                for (Vec end : moves) {
                    testMove(v, end);
                }
            } // Sets up that piece'possible moves
        }
    }
    // turn = !turn;
    td->notify(turn);
    // confirm with franklin this logic works
    return true;
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

    if (pawn->pawnMovedTwo(gb, coordinate, !white)){ // Idk why has issues
    // It has to be !white 
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

// DONE
bool ChessBoard::isThere(Vec coordinate, bool white, vector<vector<shared_ptr<Piece>>> board){
	for (vector<shared_ptr<Piece>> vec : board){
		for (shared_ptr<Piece> p : vec){
			if ((p->getType() != ' ' || p->getType() != '_') && p->getCoordinate() == coordinate && p->getTeam() == white){ return true; }
		}
	}
	return false;
}

// DONE
bool twoStep(Vec start, Vec end){
    int startY = start.getY();
    int endY = end.getY();
    if (startY == endY - 2 || startY == endY + 2){ return true; }
    return false;
}

// Attach the player observers to each piece
// It will also now attach the playerWhite and playerBlack pointers
void ChessBoard::setupPlayers(shared_ptr<Observer> pWhite, shared_ptr<Observer> pBlack) {
    // You can make a unique to a shared, but not other way around
    // shared_ptr<Observer> sharedWhite = make_shared<Observer>(pWhite);
    // shared_ptr<Observer> sharedBlack = make_shared<Observer>(pBlack);
    playerWhite = pWhite;
    playerBlack = pBlack;

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

// TODO: temporarily taking out graphics display stuff
// gd{make_shared<GraphicsDisplay>()}
ChessBoard::ChessBoard() : playerWhite{nullptr}, playerBlack{nullptr}, td{make_shared<TextDisplay>()}, game{}, bCheck{false}, wCheck{false}, turn{false}, bKing{}, wKing{}, displayScore{false} {
    // Setup the empty board and gameboard
    // unique_ptr<TextDisplay> td, unique_ptr<GraphicDisplay> gd, I have to make this here

    for (int row = 0; row < 8; row++) {
        vector<unique_ptr<Empty>> ebRow;
        vector<shared_ptr<Piece>> gbRow;
        for (int col = 0; col < 8; ++col) {
            // gb[row][col] = make_shared<Piece>();
            // Top left corner, the colour of the board is white. Bottom right (7,7) is white as well
            if((((row % 2 == 0) && (col % 2 == 0)) || ((row % 2 == 1) && (col % 2 == 1)))) { // Alternating of black and white
                ebRow.push_back(make_unique<Empty>(Empty(Vec{row, col}, '_', true)));
                shared_ptr<Empty> emptyPtr = std::make_shared<Empty>(Vec{row, col}, '_', true);
                gbRow.push_back(dynamic_pointer_cast<Piece>(emptyPtr));
            } else {
                ebRow.push_back(make_unique<Empty>(Empty(Vec{row, col}, ' ', false)));
                shared_ptr<Empty> emptyPtr = std::make_shared<Empty>(Vec{row, col}, ' ', false);
                gbRow.push_back(dynamic_pointer_cast<Piece>(emptyPtr));
            }
        }
        eb.push_back(move(ebRow));
        gb.push_back(move(gbRow));
    }
    // graphicsDisplay = gd;
}

void ChessBoard::regMove(Vec start, Vec end){
    shared_ptr<Piece> startPiece = getPiece(start);
    shared_ptr<Piece> endPiece = getPiece(end);

    // Vec v = startPiece->getCoordinate();
    // cout << "here" << endl;
    // cout << startPiece->getType() << endl;
    // cout << v << endl;
    // cout << end << endl;
    // cout << "here" << endl;

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

    // cout << startX << " " << endX << endl;

    Vec rookCoord;
    // the y coordinate tells us which colour we want -> keep the y coordinate the same to get the correct rook
    rookCoord.setY(end.getY());

    if (endX == startX - 2){ 
        rookCoord.setX(0);
        Vec endCoord = Vec(end.getX() + 1, end.getY());
        //cout << "ROOK MOVES TO LEFT: " << gb[endCoord.getY()][endCoord.getX()]->getType() << endl;
        regMove(rookCoord, endCoord);
        //cout << "ROOK MOVES TO LEFT: " << gb[endCoord.getY()][endCoord.getX()]->getType() << endl;
    } else if (endX == startX + 3){ 
        rookCoord.setX(7);
        Vec endCoord = Vec(end.getX() - 1, end.getY());
        //cout << "ROOK MOVES TO RIGHT: " << gb[endCoord.getY()][endCoord.getX()]->getType() << endl;
        regMove(rookCoord, endCoord);
        //cout << "ROOK MOVES TO RIGHT: " << gb[endCoord.getY()][endCoord.getX()]->getType() << endl;
    }

}

void ChessBoard::isCastleMove(Vec start, Vec end){
    int row = start.getY();
    int col = start.getX();
    int endRow = end.getY();
    int endCol = end.getX();
    Vec rookCoord;
    rookCoord.setY(end.getY());
    if ((gb[endRow][endCol]->getType() == 'K' || gb[endRow][endCol]->getType() == 'k')  && (col == endCol - 3)){
        Vec endCoord = Vec(end.getX() - 1, end.getY());
        rookCoord.setX(7);
        char rook = gb[rookCoord.getY()][rookCoord.getX()]->getType();
        char endPiece = gb[endCoord.getY()][endCoord.getX()]->getType();
        td->notifyMoves(rookCoord, rook, endCoord, endPiece, checkString());
    } else if ((gb[endRow][endCol]->getType() == 'K' || gb[endRow][endCol]->getType() == 'k')  && (col == endCol + 2)){
        Vec endCoord = Vec(end.getX() + 1, end.getY());
        rookCoord.setX(0);
        char rook = gb[rookCoord.getY()][rookCoord.getX()]->getType();
        char endPiece = gb[endCoord.getY()][endCoord.getX()]->getType();
        td->notifyMoves(rookCoord, rook, endCoord, endPiece, checkString());
    }
}

// DONE
void  ChessBoard::makeMove(Vec start, Vec end){
    char startType = getType(start);
    // check if it was a castle move and if it was make the appropriate rook move
    if (startType == 'K' || startType == 'k'){ castleMove(start, end);}
     // make the move
    regMove(start, end);
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
    bool isEnd = true;
    turn = !turn;
    for (vector<shared_ptr<Piece>> vec : gb){
		for (shared_ptr<Piece> p : vec){
            if (p->getTeam() == turn) {continue; }
            p->resetMoves(); // clear all the legal moves
            p->getPossibleMoves(gb); // get the possible moves for this piece
            // test every possible move -> which will add it to the legal moves if it passes
            Vec v = p->getCoordinate();
            vector<Vec> moves = p->returnPossibleMoves();
            for (Vec move : moves){
                if (testMove(v, move)){ isEnd = false; };
            }
        }
    }

    shared_ptr<Piece> emptyPiece = getPiece(start);
    shared_ptr<Piece> endPiece = getPiece(end);

    // notify the gd and td
    char startChar = emptyPiece->getType();
    char endChar = endPiece->getType();
    td->notifyMoves(start, startChar, end, endChar, checkString());
    // NEED TO NOTIFY TD OF THE CASTLE MOVE !!!!!
    isCastleMove(start, end);
    td->notify(turn);
    // graphicsDisplay->notifyMoves(start, startChar, end, endChar, checkString());
    
    if (isEnd) { endGame(); displayScore = true;  }

    // cout << "CURRENT BOARD" << endl;
    // for (vector<shared_ptr<Piece>> vec : gb){
	//     for (shared_ptr<Piece> p : vec){
	//         cout << p->getType();
	//     }
	//     cout << endl;
	// }

}

string ChessBoard::checkString(){
    if (wCheck){ return "White"; }
    else if (bCheck) { return "Black"; }
    return "";
}

// DONE
// we can assume that the turn player has no moves
void ChessBoard::endGame() {
    if (turn) {
        if (wCheck) { game.updateWhite(false); }
        else { game.updateWhite(true); }
    } else {
        if (bCheck) { game.updateBlack(false); }
        else { game.updateBlack(true); }
    }
}


// DONE
bool ChessBoard::testMove(Vec start, Vec end){
    // make a deep copy of the gb
    // consult about making a deep copy of the board
    // creating a 2D vector of unique pointers by copying from the shared vector

    // the knight should be at (b, 1)

    // cout << "start: " << start << endl;
    // cout << "end: " << end << endl;

    vector<vector<shared_ptr<Piece>>> boardCopy;

    for (std::vector<std::shared_ptr<Piece>> vec : gb) {
        std::vector<std::shared_ptr<Piece>> uniqueRow;
        for (std::shared_ptr<Piece> p : vec) {
            // Copying data from shared_ptr to unique_ptr
            shared_ptr<Piece> newPiece = p->clone();
            uniqueRow.push_back(newPiece);
        }
        boardCopy.push_back(uniqueRow);
    }

    char startType = getType(start);
    Vec wKingCoord;
    Vec bKingCoord;

    // REWORKED WITH TURN NOW STARTING AT FALSE
    if (turn && startType != 'K'){
        wKingCoord = wKing;
    } else if (!turn && startType != 'k'){
        bKingCoord = bKing;
    } else if (turn){
        wKingCoord = start;
    } else {
        bKingCoord = start;
    }

    // now we can make edits on the game board which we will later revert
    makeMove(start, end);
    // we can safely update the booleans of pieces and update


    // cout << "AFTER MOVE: " << endl;

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
            if (p->getTeam() != turn || p->getType() == ' ' || p->getType() == '_'){ continue; }
            p->resetMoves(); // clear all the legal moves
            p->getPossibleMoves(gb); // get the possible moves for this piece
            // seg fault on the last pawn 
        }
    }

    // cout << "here"<< endl;
    // --------------------- at this point ALL the pieces have possible moves -----------------------------
    // we need to decide if any of these moves will put the opponent's king in check


    // need to check if that move puts the opponent in check
    bool check = isCheck(!turn);
    bool legal = false;

    // we decide its legal -> notify player
    if (!check){
        if (!turn){ 
            playerWhite->notifyLM(start, end); 
        } // if the next turn (opponent is white)
        else { 
            playerBlack->notifyLM(start, end); 
        }
        isCaptureMove(start, end, boardCopy);
        isCheckMove(start, end);
        isCheckMateMove(start, end);
        isAvoidCaptureMove(start, end, boardCopy);
        legal = true;
    }

    // revert the board -> switch the board copy to the gb
    // this swap might not work
    // Yup chatgpt said nada
    // knight should be at (c, 3) end 

    // after the move was made 
    int row = start.getY();
    int col = start.getX();
    // should be knight
    // cout << "OLD BOARD : " << start << ' ' << boardCopy[row][col]->getType() << endl;
    // should be empty
    // cout << "MOVED BOARD : " << start << ' ' << gb[row][col]->getType() << endl;
    // should be the start coordinate 
    // Vec c = gb[row][col]->getCoordinate();
    // cout << c << endl;
    for (size_t row = 0; row < gb.size(); ++row) {
        for (size_t col = 0; col < gb[row].size(); ++col) {
            gb[row][col] = move(boardCopy[row][col]);
        }
    }
    // should be knight
    // Vec current = gb[row][col]->getCoordinate();
    // cout << "CURRENT BOARD : " << current << ' ' << gb[row][col]->getType() << endl;
    // knight should be at (b, 1) start

    // --------------------- UP TO THIS POINT THE KNIGHT COORDINATES ARE CORRECT -------------------------

    // revert the king's coordinates
    if (!turn){ // TODO: change to !turn because we set white turn as false in default
        swap(wKingCoord, wKing);
    } else {
        swap(bKingCoord, bKing);
    }

    return legal;
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
            for(Vec move : p->returnPossibleMoves()){
                if (move == kingCoord){
                    return true;
                }
            }
        }
    }
    return false;
}

void ChessBoard::isCheckMateMove(Vec start, Vec end){
    // get the possible moves of the current
    bool empty = true;
    for (vector<shared_ptr<Piece>> vec : gb){
        for (shared_ptr<Piece> p : vec){
            if (p->getTeam() != turn){ continue;}
            p->resetMoves();
            p->getPossibleMoves(gb);
            if (p->returnPossibleMoves().size() != 0){ empty = false; }
        }
    }

    if (isCheck(turn) && empty){
        if (!turn){ playerWhite->notifyCMM(start, end); } // if the next turn (opponent is white)
        else { playerBlack->notifyCMM(start, end); }
    }
}

//  did this move put the current team in check
void ChessBoard::isCheckMove(Vec start, Vec end){
    if (isCheck(turn)){
        if (!turn){ playerWhite->notifyCheckM(start, end); }
        else { playerBlack->notifyCheckM(start, end); }
    }
}

// WILL this move capture any pieces on the opposing team
void ChessBoard::isCaptureMove(Vec start, Vec end, vector<vector<shared_ptr<Piece>>> ob){
    // if there is a piece at the end coordinate -> it is a capture move
    if (isThere(end, turn, ob)){
        if (!turn){ playerWhite->notifyCapM(start, end); } // if the next turn (opponent is white)
        else { playerBlack->notifyCapM(start, end); }
    }
}

// did the move take this piece out of a position to be captured
void ChessBoard::isAvoidCaptureMove(Vec start, Vec end, vector<vector<shared_ptr<Piece>>> ob){
    // assume it is not in a position to be captured
    bool capture = false;
    // was the piece (on the opponent's team) in a position to be captured in the first place in the old board
    // look at the current team's possible moves if they are equal to the piece's start
    for (vector<shared_ptr<Piece>> vec : ob){
        for (shared_ptr<Piece> p : vec){
            if (p->getTeam() != turn){ continue; }
            p->resetMoves();
            p->getPossibleMoves(ob);
            for (Vec move: p->returnPossibleMoves()){
                if (move == start){ capture = true; break;}
            }
        }
    }

    if (!capture){ return; }

    // will the move take the piece out of a position to be captured
    // consider the board after the move was made, will any of the other team's pieces capture mine (which is at end)
    for (vector<shared_ptr<Piece>> vec: gb){
        for (shared_ptr<Piece> p : vec){
            if (p->getTeam() != turn){ continue; }
            p->resetMoves();
            p->getPossibleMoves(gb);
            for (Vec move: p->returnPossibleMoves()){
                if (move == end){ capture = true; break;}
            }
        }
    }

    if (!capture){
        if (!turn){ playerWhite->notifyCheckM(start, end); }
        else { playerBlack->notifyCheckM(start, end); }
    }
}


// DONE
bool ChessBoard::getTurn(){
    return turn;
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
// CHIRA - this was initially shared_ptr<Piece> but i changed to empty
shared_ptr<Empty> ChessBoard::getEmptyPiece(Vec coord){
    // access the empty board and get the Piece* we want
    int row = coord.getY();
    int col = coord.getX();
    // COPY CTOR DIDNT WORK 
    // shoudl be row col,
    shared_ptr<Empty> emptyPiece = make_shared<Empty>(Vec{col, row}, eb[row][col]->getType(), eb[row][col]->getTeam()); // TODO CHIARA
    // shared_ptr<Empty> emptyPiece = eb[row][col]->clone();
    // Assume this copy construtor will work

    // return the copied piece
    return emptyPiece;
}

// DONE
void ChessBoard::forfeit(){
     // We have to change this?
    if (turn){
        // update score +1 for black
        game.updateBlack(false);
    } else {
        // update score +1 for white
        game.updateWhite(false);
    }
}

// CHIARA
void ChessBoard::restartGame() {
    for(size_t i = 0; i < eb.size(); ++i) { //The row
        for (size_t j = 0; j < eb[i].size(); ++j) { // The column
        // Remmber, we have a vector<vector<>>>>
            // COPY CTOR DIDNT WORK 
            // gb[j][i] = make_shared<Piece>(*(eb[i][j]));
            gb[j][i] = eb[i][j]->clone();
            // Assume the copy assignment operator works
        }
    }
    turn = false; // Default turn is always white
    bCheck = false;
    wCheck = false;
    // We don't need to reset bKing and wKing because it will be reset in next
    // game or if not, will just be destroyed.
}

// DONE
// needs to be fixed to check at the ned
// fixed
bool ChessBoard::upgradePawn(Vec end){
    char type = getType(end);
    if (type == 'P' && getPiece(end)->getCoordinate().getY() == 7) {
        return true;
    } else if (type == 'p' && getPiece(end)->getCoordinate().getY() == 0) {
        return true;
    }
    return false;
}


// DONE
void ChessBoard::setWhiteKing(Vec coordinate){
    wKing = coordinate;

}

// DONE
void ChessBoard::setBlackKing(Vec coordinate){
    bKing = coordinate;

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
    } 

    td->notify(coordinate, type);
    // gd->notify(coordinate, type);
}

// possible moves in pieces (making sure there's no piece there) legal moves ()
void ChessBoard::defaultBoard() {

    // First setup pawns
    for (int i = 0; i < 8; ++i) {
        setupWithChar('P', Vec{i, 1}); // White pawns
        setupWithChar('p', Vec{i, 6}); // Black
        // x, y. This corresponds to second row
    }

    // Whites are the top side of the board. 0,0

    // Setup Rooks
    setupWithChar('R', Vec{0,0});
    setupWithChar('R', Vec{7, 0}); // Whites
    setupWithChar('r', Vec{0,7});
    setupWithChar('r', Vec{7, 7}); // Black

    // Setup Knights
    setupWithChar('N', Vec{1,0}); 
    // cout << getPiece(Vec{1,0})->getType() << endl;
    // cout << char(getPiece(Vec{1,0})->getCoordinate().getX() + 97) << endl;
    // cout << getPiece(Vec{1,0})->getCoordinate().getY() + 1 << endl;
    setupWithChar('N', Vec{6, 0}); // Whites
    setupWithChar('n', Vec{1,7});
    setupWithChar('n', Vec{6, 7}); // Black

    // Setup Bishops
    setupWithChar('B', Vec{2,0});
    setupWithChar('B', Vec{5, 0}); // Whites
    setupWithChar('b', Vec{2,7});
    setupWithChar('b', Vec{5, 7}); // Black

    // Setup Kings
    setupWithChar('K', Vec{3,0}); // White King
    setupWithChar('k', Vec{3, 7}); // Black King
    setWhiteKing(Vec{3,0});
    setBlackKing(Vec{3, 7});

    // Setup Queens
    setupWithChar('Q', Vec{4,0}); // White Queen
    setupWithChar('q', Vec{4, 7}); // Black Queen

    for (vector<shared_ptr<Piece>> vec : gb) {
		for (shared_ptr<Piece> p : vec) {
            if(p->getTeam() != turn) {
                p->getPossibleMoves(gb); 
                Vec v = p->getCoordinate();
                // char c = p->getType();
                // cout << c << endl;
                // cout << "COORDINATE FIRST: " << v << endl;
                vector<Vec> moves = p->returnPossibleMoves();
                for (Vec end : moves) {
                    // cout << p->getType() << endl;
                    // cout << v.getX() << ' ' << v.getY() << endl;
                    // v = p->getCoordinate();
                    // cout << "COORDINATE SECOND: " << v << endl;
                    testMove(v, end);

                    // v = p->getCoordinate();
                    // cout << "COORDINATE THIRD: " << v << endl;
                }

                // cout << p->getType() << ':'<< p->getCoordinate().getX() << ' ' << p->getCoordinate().getY() << endl;
            } // Sets up that piece'possible moves
        }
    }
    // turn = !turn;
    td->notify(turn);
}

void ChessBoard::setTurn(bool turn) {
    this->turn = turn;
}

shared_ptr<Observer> ChessBoard::getPlayerWhite() {
    return playerWhite;
}

shared_ptr<Observer> ChessBoard::getPlayerBlack() {
    return playerBlack;
}


void ChessBoard::setDisplayScore(bool b) {
    displayScore = b;
}

ostream& operator<<(ostream& out, const ChessBoard& cb) {
    out << *(cb.td) << endl;
    if (cb.displayScore) out << cb.game << endl;
    return out;
}


