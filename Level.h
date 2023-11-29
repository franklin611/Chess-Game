#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Vec.h"
#include "ChessBoard.h"
#include <Vector>
using namespace std;


class Level {
    protected:

    public:
    virtual vector<vector<Vec>> createMoves() = 0;
};
// You need a start Vec and end Vec
// so vector<vector<Vec>> moves


class LevelOne : public Level {
    public:
    vector<vector<Vec>> createMove();
};

class LevelTwo : public Level {
    public:
    vector<vector<Vec>> createMove();
};

class LevelThree : public Level {
    public:
    vector<vector<Vec>> createMove();
};

class LevelFour : public Level {
    public:
    vector<vector<Vec>> createMove();
};

#endif
