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
    unique_ptr<TextDisplay> td;
    unique_ptr<GraphicsDisplay> gd;
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
        Vec makeComputerMove(unique_ptr<Player> p);

        // returns the type of a piece at that coordinate
        char getType(Vec coordinate);

        // returns a piece pointer
        shared_ptr<Piece> getPiece(Vec coordinate);

        // check at that coordinate if a piece is a pawn and it has moved two -> here white represents the CURRENT PLAYER
        bool pawnMovedTwo(Vec coordinate, bool white);

        // check if there is a piece at that coordinate
        bool isThere(Vec coordinate);

        // check if a move is valid
        bool isValid(Vec start, Vec end);

        // chessboard ctor
        ChessBoard(unique_ptr<Player> playerWhite, unique_ptr<Player> playerBlack);

        // setUp players
        void setupPlayers(unique_ptr<Player> playerWhite, unique_ptr<Player> playerBlack);


        // ----------------------------------------------------------------------

        // change the gameboard based on validated move
        void notify(Vec start, Vec end) override;

        // replace a piece at coordinate with replacement
        void replacePiece(Vec coordinate, shared_ptr<Piece> replacement);

        // undos a notification
        void revertBoard(vector<vector<unique_ptr<Piece>>> oldPieces, bool oldTurn);

         // access the gameboard
        vector<vector<unique_ptr<Piece>>> getGameBoard();

        // ----------------------------------------------------------------------

        // checks if the king is in check -> ie. any of the opponents legal moves capture king
        bool isCheck(bool white);

        // get the turn status
        bool getTurn();

        // main will instansiate a piece pointer and this function places the piece at this coordinate (empty piece)
        void setupByPiece(unique_ptr<Piece> p, Vec coordinate);

        // main will receive a char type and this function needs to create the Piece and put it at the coordinate
        void setupByChar(char type, Vec coordinate);

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

        // Setup functions for char and piece
        void setupWithChar(char type, Vec coordinate);
        void setupWithPiece(Piece &p, Vec coordinate);
    
};

ostream& operator<<(ChessBoard& cb, ostream& out);
