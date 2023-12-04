#include "Human.h"
#include "ChessBoard.h"


Human::Human(bool colour, shared_ptr<ChessBoardObserver> cb) : Player{colour, cb} {}

// Checks that the user inputted start and end exist in that speciic piece's, located at the start coordinate,
// set of legal moves
bool Human::makeHumanMove(Vec start, Vec end){
    for (size_t i = 0; i < legalMoves.size(); ++i) {
        if (legalMoves[i][0] == start && legalMoves[i][1] == end) {
            cb->notify(start, end); // notifies chessboard to make the actual move (update td will be in chessboard's move function)
            legalMoves.clear();
            return true;
        }
    }
    return false;
}
