#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Player.h"
#include "Vec.h"

class Human: public Player {
    public:
        Human(bool colour, shared_ptr<ChessBoardObserver> cb);
        bool makeHumanMove(Vec start, Vec end);
        // shared_ptr<Player> clone() const override;
};

#endif
