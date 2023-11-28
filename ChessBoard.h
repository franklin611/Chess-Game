#include "Game.h"
#include <vector>
#include <iostream>
#include <memory>
#include "King.h"
#include "Pawn.h"
using namespace std;

class Piece;
class Vec;
class Player;
class TextDisplay;
class GraphicsDisplay;

// CASTLE MOVE
// to make a castle move -> validate that we are moving a king two spaces to the left or right -> have a function that returns true or false so if it is a castle move we know to move the rook as well

// remember that we want to make DEEP copies of pieces so then we need UNIQUE pointers to make sure that we don't accidentally make shallow copies

class ChessBoard: public Observer{
    vector<vector<shared_ptr<Piece>>> gb;
    vector<vector<unique_ptr<Piece>>> eb;
    unique_ptr<Player> playerWhite;
    unique_ptr<Player> playerBlack;
    Game game;
    bool bCheck;
    bool wCheck;
    bool turn; // true is for white, false is for black
    Vec bKing;
    Vec wKing;
    public:
        // makes a Human move
        bool makeHumanMove(Vec start, Vec end);

        // makes a computer move -> we need to return the end move to check if a pawn has reached the end
        void makeComputerMove(unique_ptr<Player> p);

        // returns the type of a piece at that coordinate
        char getType(Vec coordinate);

        // returns a piece pointer
        shared_ptr<Piece> getPiece(Vec coordinate);

        // check at that coordinate if a piece is a pawn and it has moved two -> here white represents the CURRENT PLAYER
        bool pawnMovedTwo(Vec coordinate, bool white);

        // check if there is a piece at that coordinate
        bool isThere(Vec coordinate);

        // replace a piece at coordinate with replacement
        void replacePiece(Vec coordinate, shared_ptr<Piece> replacement);

        // check if a move is valid
        bool isValid(Vec start, Vec end);

        // chessboard ctor
        ChessBoard();

        // setUp players
        void setupPlayers(unique_ptr<Player> white, unique_ptr<Player> black);

        void regMove(Vec start, Vec end);

        void castleMove(Vec start, Vec end);

        void makeMove(Vec start, Vec end);

        void updatePawnMoved(Vec start, Vec end);

        void updateKingMoved(Vec end);

        void updateKingCoord(Vec end, bool white);

        // change the gameboard based on validated move
        void notify(Vec start, Vec end) override;

        void testMove(Vec start, Vec end) override;

        void resetAllLegalMoves();

        // undos a notification
        //void revertBoard(vector<vector<shared_ptr<Piece>>> oldPieces);
        // void revertBoard(Vec start, Vec end);

         // access the gameboard
        vector<vector<shared_ptr<Piece>>> getGameBoard();

        // checks if the king is in check -> ie. any of the opponents legal moves capture king
        bool isCheck(bool white);

        // get the turn status
        bool getTurn();

        // Setup functions for char and piece
        void setupWithChar(char type, Vec coordinate);
        void setupWithPiece(shared_ptr<Piece> p, Vec coordinate);

        // returns a DEEP COPY of an empty piece
        shared_ptr<Piece> getEmptyPiece(Vec coord);

        // main calls this function if a human wants to forfeit
        void forfeit();

        // main calls this function to check if the game has ended
        bool isEnd();

        // main calls this function to restart a game this will reset gameboard, reset turn, reset playerWhite and playerBlack
        void restartGame();

        // at this point, the move/turn is finished, we want to check if the piece at end is a pawn and return true/false accordingly
        bool upgradePawn(Vec end);

        // this will return all the legal moves of a team
        vector<vector<Vec>> getLegalMoves(bool white);

        // set the default board
        void defaultBoard();

        // set white king
        void setWhiteKing(Vec coordinate);

        // set black king
        void setBlackKing(Vec coordinate);
    
};

ostream& operator<<(ChessBoard& cb, ostream& out);
