#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Vec.h"
#include "ChessBoard.h"
#include <Vector>
using namespace std;


class Level {
    protected:
    // we pass a shared_ptr to chessboard
        // shared_ptr<ChessBoard> cb; //TODO: does have to be unique_ptr? or shared_ptr? can i jsut use reg ptr

    // shared because itis not unique?other levels are pointing at it? not each level has its own chssboard?

    public:
    virtual vector<vector<Vec>> createMove(shared_ptr<ChessBoard> cb) = 0;
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
