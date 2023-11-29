#include "Human.h"

Human::Human(bool colour, unique_ptr<Observer> cb) : Player{colour, std::move(cb)} {}

bool Human::makeHumanMove(Vec start, Vec end){

    for (int i = 0; !legalMoves.empty(); ++i) {
        if (legalMoves[i][0] == start && legalMoves[i][1] == end) {
            cb->notify(start, end); // notifies chessboard to make the actual move (update td will be in chessboard's move function)
            return true;
        }
    }
    return false;

}
