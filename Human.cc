#include "Human.h"

Human::Human(bool colour, shared_ptr<ChessBoardObserver> cb) : Player{colour, cb} {}

bool Human::makeHumanMove(Vec start, Vec end){
    cout << endl;
    cout << "Number of Legal Moves for Player " << colour << ' ' << legalMoves.size() << endl;
    cout << endl; 
    
    for (int i = 0; i < legalMoves.size(); ++i) {
        cout << "start: " << start << endl;
        cout << "end: " << end << endl;
        if (legalMoves[i][0] == start && legalMoves[i][1] == end) {
            cb->notify(start, end); // notifies chessboard to make the actual move (update td will be in chessboard's move function)
            return true;
        }
    }
    return false;

}


// shared_ptr<Player> Human::clone() const {
//     return make_shared<Human>(*this);
// }
