#include "Computer.h"
#include "Level.h"
#include <random>
using namespace std;

// function to randomly select a vector from the level's moves
// info was sourced from https://en.cppreference.com/w/cpp/numeric/random
vector<Vec> Computer::selectRandomMove(vector<vector<Vec>> &vectors) {
    // seeding random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<size_t> outerDist(0, vectors.size() - 1);
    size_t outerIndex = outerDist(gen);

    return {vectors[outerIndex]};
    // vectors[outerIndex];
}

Computer::Computer(bool colour, shared_ptr<ChessBoardObserver> cb, int userLevel) : Player{colour, cb}, userLevel{userLevel} {
    if (userLevel == 1) {level = make_unique<LevelOne>();} // We are correctly making the levels
    else if (userLevel == 2) {level = make_unique<LevelTwo>();}
    else if (userLevel == 3) {level = make_unique<LevelThree>();}
    else if (userLevel == 4) {level = make_unique<LevelFour>();}
}

// DONE
Vec Computer::makeComputerMove(int userLevel) {
    
    for (vector<Vec> move : legalMoves) {
        cout << "legalMoves Move: " <<  move[0] << " to " << move[1]  << endl;
    }
    for (vector<Vec> move : captureMoves) {
        cout << "Capture Move: " <<  move[0] << " to " << move[1]  << endl;
    }
    for (vector<Vec> move : checkMoves) {
        cout << "checkMoves Move: " <<  move[0] << " to " << move[1]  << endl;
    }
    for (vector<Vec> move : checkMateMoves) {
        cout << "checkMateMoves Move: " <<  move[0] << " to " << move[1]  << endl;
    }
    for (vector<Vec> move : avoidCaptureMoves) {
        cout << "avoidCaptureMoves Move: " <<  move[0] << " to "  << move[1]  << endl;
    }

    vector<vector<Vec>> levelsMoves = level->createMoves(legalMoves, captureMoves, checkMoves, checkMateMoves, avoidCaptureMoves);
    // cout << "level Moves size: " << levelsMoves.size() << endl;
    // for (int i = 0; i < levelsMove.size)
    // vector<Vec> selectedMove = selectRandomMove(levelsMoves);
    if (!levelsMoves.empty()) {
        vector<Vec> selectedMove = selectRandomMove(levelsMoves);
        // cout << "level Moves size: " << levelsMoves.size() << endl;
        // cout << "selected move: " << selectedMove[0] << selectedMove[1] << endl;
        cb->notify(selectedMove[0], selectedMove[1]);

        captureMoves.clear();
        checkMoves.clear(); // WIP
        checkMateMoves.clear(); // WIP
        avoidCaptureMoves.clear();
        legalMoves.clear();
        return selectedMove[1];
    } else {
        vector<Vec> onlyLegalMove = selectRandomMove(legalMoves);
        cb->notify(onlyLegalMove[0], onlyLegalMove[1]);
        // cout << "legal Moves size: " << legalMoves.size() << endl;
        // cout << "selected move: " << onlyLegalMove[0] << onlyLegalMove[1] << endl;
        captureMoves.clear();
        checkMoves.clear();
        checkMateMoves.clear();
        avoidCaptureMoves.clear();
        legalMoves.clear();
        return onlyLegalMove[1];
    }

}


int Computer::getLevel() {
    return userLevel;
}


// shared_ptr<Player> Computer::clone() const {
//     return make_shared<Computer>(*this);
// }

