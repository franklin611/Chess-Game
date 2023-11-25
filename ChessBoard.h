#include <vector>
#include "Player.h"
#include "Game.h"
#include <iostream>
using namespace std;

class Piece;
class Vec;

class ChessBoard: public Observer{
    vector<vector<Piece*>> gb;
    vector<vector<Piece*>> eb;
    Piece* wKing;
    Piece* bKing;
    // TextDisplay* td;
    // GraphicsDisplay* gd;
    // Player* playerWhite;
    // Player* playerBlack;
    // Game game;
    bool turn; // true is for white, false is for black
    public:
        bool makeHumanMove(Vec start, Vec end);
        
        // check at that coordinate if a piece is a pawn and it has moved two -> here white represents the CURRENT PLAYER
        bool pawnMovedTwo(Vec coordinate, bool white);
        bool isThere(Vec coordinate);
        bool isValid(Vec start, Vec end);
        ChessBoard(Player* white, Player* black);
        void notify(Vec start, Vec end) override;
        // checks if the king is in check -> any of the opponents legal moves capture king
        bool isCheck(bool white);
        void revertBoard(vector<vector<Piece>> oldPieces, bool oldTurn);
        bool getTurn();
        // where does changePawn happen
        void changePawn(char type, Vec coordinate, bool white);
        vector<vector<Piece>> getGameBoard();
        Piece* getEmptyPiece(Vec coord);
};

ostream& operator<<(ChessBoard& cb, ostream& out);
