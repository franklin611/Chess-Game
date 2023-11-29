#include "Computer.h"
#include "Level.h"
#include <random>

Computer::Computer(bool colour, unique_ptr<Observer> cb, int userLevel) : Player{colour, std::move(cb)}, userLevel{userLevel} {
    if (userLevel == 1) {level = make_unique<LevelOne>();}
    else if (userLevel == 2) {level = make_unique<LevelTwo>();}
    else if (userLevel == 3) {level = make_unique<LevelThree>();}
    else if (userLevel == 4) {level = make_unique<LevelFour>();}
}

vector<vector<Vec>> Computer::selectMove() {

}

// DONE
void Computer::makeComputerMove(bool white, int userLevel){

    vector<vector<Vec>> legalMoves = level->createMoves( );
        // n = l->createMove(*this);
    }

    // // get the legal moves for the player
    // vector<vector<Vec>> legalMoves = getLegalMoves(turn);
    vector<Vec> move; // there are two Vecs [start, end]
    // vector<vector<Vec>> levelMoves = generateAllLevelMoves(legalMoves, level);

    if (turn){
        move = playerWhite->selectMove(legalMoves); // we do not have a selectMove
    } else {
        move = playerBlack->selectMove(legalMoves);
    }
    notify(move[0], move[1]);
}