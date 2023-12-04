#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include <vector>
#include <iostream>
#include <memory>
#include <utility>
#include "Game.h"
#include "Empty.h"
#include "King.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "ChessBoardObserver.h"
#include "Observer.h"
#include "Vec.h"
using namespace std;

// not entirely sure if we need forward declarations or just include the .h
class TextDisplay;
class GraphicsDisplay;

// ChessBoard is the controller of the game and controls how the pieces on the board should move as well as decide when a move is legal based on the board
class ChessBoard: public ChessBoardObserver {

    // holds the pieces of the game board
    vector<vector<shared_ptr<Piece>>> gb;

    // keeps a copy of what the empty board should look like
    vector<vector<unique_ptr<Empty>>> eb;

    // used to notify player white
    shared_ptr<Observer> playerWhite;

    // used to notify player black
    shared_ptr<Observer> playerBlack;

    // used to output the text display
    shared_ptr<TextDisplay> td;
    shared_ptr<GraphicsDisplay> gd;
    Game game;

    // keeps track if black is in check
    bool bCheck;

    // keeps track if white is in check
    bool wCheck;

    // keeps track of the turn
    bool turn;

    // keeps track of the black king's coordinates
    Vec bKing;

    // keeps track of the white king's coordinates
    Vec wKing;

    // if true the chessboard should output the score (the game has ended)
    bool displayScore;

    public:

        // update if a player took themselves out of check 
        void updateCheck(vector<Vec> moves, bool team);

        // updates if a rook moves on the board
        void updateRookMove(Vec end);

        // verifies if a team is in check
        void validCheck(vector<Vec> legalMoves);

        // decides if the td needs to output that a team is in check
        string checkString();

        // decides the starting legal moves when a user calls setup
        void setUpStartMoves();

        // returns the type of a piece at that coordinate
        char getType(Vec coordinate);

        // returns a pointer to the piece at coordinate
        shared_ptr<Piece> getPiece(Vec coordinate);

        // check at that coordinate if a piece is a pawn and it has moved two
        bool pawnMovedTwo(Vec coordinate, bool white);

        // check if there is a piece on the team "white" at coordinate on the gameboard
        bool isThere(Vec coordinate, bool white, vector<vector<shared_ptr<Piece>>> board);

        // replace a piece at coordinate with replacement
        void replacePiece(Vec coordinate, shared_ptr<Piece> replacement);

        // check if a move is valid
        bool isValid(Vec start, Vec end);

        // chessboard ctor
        ChessBoard();

        // attaches the players as observers
        void setupPlayers(shared_ptr<Observer> pWhite, shared_ptr<Observer> pblack);

        // makes a regular move on the board
        void regMove(Vec start, Vec end);

        // verifies the move is a castle move and makes the rook move part of the castle move
        void castleMove(Vec start, Vec end);

        // combines regular, en passant and castle moves
        void makeMove(Vec start, Vec end);

        // verifies a legal move is a castle move and notifies the display of the rook move
        void isCastleMove(Vec start, Vec end);

        // update the pawn's moved booleans
        void updatePawnMoved(Vec start, Vec end);

        // updates the king's moved booleans
        void updateKingMoved(Vec end);

        // updated the black and white king's coordinates kept in the ChessBoard if they change
        void updateKingCoord(Vec end, bool white);

        // change the gameboard based on validated move
        void notify(Vec start, Vec end) override;

        // simulate possible moves and test if they are legal, notify the players of their legal moves if notify is true
        bool testMove(Vec start, Vec end, bool notify);

        // determines if a move is considered an avoid capture move and notifies the player
        void isAvoidCaptureMove(Vec start, Vec end, vector<vector<shared_ptr<Piece>>> ob);

        // determines if a move is considered a capture move and notifies the player
        void isCaptureMove(Vec start, Vec end, vector<vector<shared_ptr<Piece>>> ob);

        // determines if a move is considered a check move and notifies the player
        void isCheckMove(Vec start, Vec end);

        // determines if a move is considered a checkmate move and notifies the player
        void isCheckMateMove(Vec start, Vec end);

        // determines if the team "white" is in check on the current gameboard
        // ISSUE: NEEDS TO BE REMOVED -> CHIARA
        bool isCheck(bool white);

        // get the turn status
        bool getTurn();

        // if a user calls setup we replace the piece at coordinate with type
        void setupWithChar(char type, Vec coordinate);

        // returns a deep copy of an empty piece
        shared_ptr<Empty> getEmptyPiece(Vec coord);

        // main calls this function if a human wants to forfeit
        void forfeit();

        // main calls this function to check if the game has ended
        void endGame();

        // main calls this function to restart a game this will reset gameboard, reset turn, reset playerWhite and playerBlack
        void restartGame();

        // at this point, the move/turn is finished, we want to check if the piece at end is a pawn and return true/false accordingly
        bool upgradePawn(Vec end);

        // set the default board if a user does not call setup
        void defaultBoard();

        // set white king coordinate
        void setWhiteKing(Vec coordinate);

        // set black king coordinate
        void setBlackKing(Vec coordinate);

        // check if it is a valid board after user calls setup
        bool boardIsValid();

        // skips a turn
        void setTurn(bool turn);

        // set the displayscore field to true or false if based on if the display need to output the score
        void setDisplayScore(bool b);

        // allows main to access playerWhite
        shared_ptr<Observer> getPlayerWhite();

        // allows main to access playerBlack
        shared_ptr<Observer> getPlayerBlack();

        // removes the captured piece from the board from en passant
        void passantMove(Vec start, Vec end);

        // change the turn during setup
        void setupTurn(bool turn);

        // Returns a bool value of whether a turn is in check or not
        bool IsvalidCheck(vector<Vec> legalMoves, bool playerTurn);



        // used to output the chessboard
        friend ostream& operator<<(ostream& out, const ChessBoard& cb);

};

#endif
