#include "Level.h"

// Level 1: random legal moves.
vector<vector<Vec>> LevelOne::createMoves(
    vector<vector<Vec>> legalMoves,
    vector<vector<Vec>> captureMoves,
    vector<vector<Vec>> checkMoves,
    vector<vector<Vec>> checkMateMoves,
    vector<vector<Vec>> avoidCaptureMoves) {
    return legalMoves;
}

// Level 2: prefers capturing moves and checks over other moves.
vector<vector<Vec>> LevelTwo::createMoves(
    vector<vector<Vec>> legalMoves,
    vector<vector<Vec>> captureMoves,
    vector<vector<Vec>> checkMoves,
    vector<vector<Vec>> checkMateMoves,
    vector<vector<Vec>> avoidCaptureMoves) {
    vector<vector<Vec>> twoMoves = captureMoves;
    for (size_t i = 0; i < checkMoves.size(); ++i) {
        twoMoves.emplace_back(checkMoves[i]);
    };
    return twoMoves; // vector<vector<Vec>> that contains two classes of moves 
}

// Level 3: prefers avoiding capture, capturing moves, and checks.
vector<vector<Vec>> LevelThree::createMoves(
    vector<vector<Vec>> legalMoves,
    vector<vector<Vec>> captureMoves,
    vector<vector<Vec>> checkMoves,
    vector<vector<Vec>> checkMateMoves,
    vector<vector<Vec>> avoidCaptureMoves) {
    vector<vector<Vec>> threeMoves = captureMoves;
    for (size_t i = 0; i < checkMoves.size(); ++i) {
            threeMoves.emplace_back(checkMoves[i]);
    };
    for (size_t i = 0; i < avoidCaptureMoves.size(); ++i) {
        threeMoves.emplace_back(avoidCaptureMoves[i]);
    };
    return threeMoves; // vector<vector<Vec>> that contains three classes of moves 
}

// Level 4: prefers checkmate moves and checks
vector<vector<Vec>> LevelFour::createMoves(
    vector<vector<Vec>> legalMoves,
    vector<vector<Vec>> captureMoves,
    vector<vector<Vec>> checkMoves,
    vector<vector<Vec>> checkMateMoves,
    vector<vector<Vec>> avoidCaptureMoves) {
    vector<vector<Vec>> fourMoves = checkMateMoves;
    for (size_t i = 0; i < checkMoves.size(); ++i) {
        fourMoves.emplace_back(checkMoves[i]);
    };
    return fourMoves; // vector<vector<Vec>> that contains four classes of moves 
}
