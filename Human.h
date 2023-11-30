#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Player.h"
#include "Vec.h"

class Human: public Player {
    public:
        Human(bool colour, unique_ptr<ChessBoardObserver> cb);
        bool makeHumanMove(Vec start, Vec end);
};

#endif
