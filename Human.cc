#include "Human.h"
#include "ChessBoard.h"


Human::Human(bool colour, shared_ptr<ChessBoardObserver> cb) : Player{colour, cb} {}

bool Human::makeHumanMove(Vec start, Vec end){
    // cout << endl;
    // cout << "Number of Legal Moves for Player " << colour << ' ' << legalMoves.size() << endl;
    // cout << endl; 

    for (size_t i = 0; i < legalMoves.size(); ++i) {
        // cout << "start: " << start << endl;
        // cout << "end: " << end << endl;
        // cout << "start legal move: " << legalMoves[i][0] << endl;
        // cout << "end legal move: " << legalMoves[i][1] << endl;
        // cout << i << endl;

        // lot of duplicates
        // A legal move that is allowed is moving an empty piece to an actual piece. 
        // call move a2 a3 twice, for each turn
        if (legalMoves[i][0] == start && legalMoves[i][1] == end) {
            //cout << "hi" << endl;
            // if(!cb) cout << " I am null" << endl;
            // Identified that the cb passed to player is null
            cb->notify(start, end); // notifies chessboard to make the actual move (update td will be in chessboard's move function)
            //cout << "finish" << endl;
            legalMoves.clear();
            return true;
        }
    }

    return false;

}


// shared_ptr<Player> Human::clone() const {
//     return make_shared<Human>(*this);
// }
