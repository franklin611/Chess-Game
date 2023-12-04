#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Vec.h"
#include <vector>
using namespace std;

// Implementing Factory Design Pattern
class Level {
public:
    virtual vector<vector<Vec>> createMoves(
        vector<vector<Vec>> legalMoves,
        vector<vector<Vec>> captureMoves,
        vector<vector<Vec>> checkMoves,
        vector<vector<Vec>> checkMateMoves,
        vector<vector<Vec>> avoidCaptureMoves) = 0;
        // Each level will override this pure virtual method and take in parameters, which could be empty
        // for each set of moves
};

// Each Level Class, from 1-4 
class LevelOne : public Level {
public:
    vector<vector<Vec>> createMoves(
        vector<vector<Vec>> legalMoves,
        vector<vector<Vec>> captureMoves,
        vector<vector<Vec>> checkMoves,
        vector<vector<Vec>> checkMateMoves,
        vector<vector<Vec>> avoidCaptureMoves) override;
};

class LevelTwo : public Level {
public:
    vector<vector<Vec>> createMoves(
        vector<vector<Vec>> legalMoves,
        vector<vector<Vec>> captureMoves,
        vector<vector<Vec>> checkMoves,
        vector<vector<Vec>> checkMateMoves,
        vector<vector<Vec>> avoidCaptureMoves) override;
};

class LevelThree : public Level {
public:
    vector<vector<Vec>> createMoves(
        vector<vector<Vec>> legalMoves,
        vector<vector<Vec>> captureMoves,
        vector<vector<Vec>> checkMoves,
        vector<vector<Vec>> checkMateMoves,
        vector<vector<Vec>> avoidCaptureMoves) override;
};

class LevelFour : public Level {
public:
    vector<vector<Vec>> createMoves(
        vector<vector<Vec>> legalMoves,
        vector<vector<Vec>> captureMoves,
        vector<vector<Vec>> checkMoves,
        vector<vector<Vec>> checkMateMoves,
        vector<vector<Vec>> avoidCaptureMoves) override;
};

#endif
