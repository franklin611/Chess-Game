#include "Computer.h"

// function to randomly select a vector from the level's moves
// info was sourced from https://en.cppreference.com/w/cpp/numeric/random
vector<Vec> selectRandomMove(vector<vector<Vec>> &vectors) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> outerDist(0, vectors.size() - 1);
    size_t outerIndex = outerDist(gen);
    return {vectors[outerIndex]};
}

// Computer Constructor 
Computer::Computer(bool colour, shared_ptr<ChessBoardObserver> cb, int userLevel) : Player{colour, cb}, userLevel{userLevel} {
    if (userLevel == 1) {level = make_unique<LevelOne>();} 
    else if (userLevel == 2) {level = make_unique<LevelTwo>();}
    else if (userLevel == 3) {level = make_unique<LevelThree>();}
    else if (userLevel == 4) {level = make_unique<LevelFour>();}
}

Computer::Computer(Computer &&other) {
    swap(userLevel, other.userLevel);
    swap(level, other.level);
}
// computer player chooses a move 
Vec Computer::makeComputerMove() {

    // gets all the moves based on its level 
    vector<vector<Vec>> levelsMoves = level->createMoves(legalMoves, captureMoves, checkMoves, checkMateMoves, avoidCaptureMoves);


    // if there are any moves based on the level 
    if (!levelsMoves.empty()) {
        vector<Vec> selectedMove = selectRandomMove(levelsMoves);
        cb->notify(selectedMove[0], selectedMove[1]);
        captureMoves.clear();
        checkMoves.clear(); 
        checkMateMoves.clear(); 
        avoidCaptureMoves.clear();
        legalMoves.clear();
        cout << "MOVE: " << selectedMove[0] << ' ' << selectedMove[1] << endl;
        return selectedMove[1];
    // otherwise just pick a legal move 
    } else {
        vector<Vec> onlyLegalMove = selectRandomMove(legalMoves);
        cb->notify(onlyLegalMove[0], onlyLegalMove[1]);
        captureMoves.clear();
        checkMoves.clear();
        checkMateMoves.clear();
        avoidCaptureMoves.clear();
        legalMoves.clear();
        cout << "MOVE: " << onlyLegalMove[0] << ' ' << onlyLegalMove[1] << endl;
        return onlyLegalMove[1];
    }

}

// gets the level of the computer player 
int Computer::getLevel() {
    return userLevel;
}

shared_ptr<Player> Computer::clone() const {
    return make_shared<Computer>(*this);
}

Computer::Computer(const Computer& other)
        : Player(other), userLevel(other.userLevel) {
            if (other.userLevel) {
                // Assuming Level has a copy constructor
                if (userLevel == 1){
                    level = make_unique<LevelOne>(*dynamic_cast<LevelOne*>(other.level.get()));
                } else if (userLevel == 2){
                    level = make_unique<LevelTwo>(*dynamic_cast<LevelTwo*>(other.level.get()));
                } else if (userLevel == 3){
                    level = make_unique<LevelThree>(*dynamic_cast<LevelThree*>(other.level.get()));
                } else {
                    level = make_unique<LevelFour>(*dynamic_cast<LevelFour*>(other.level.get()));
                }
            }
        }