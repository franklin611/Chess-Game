#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Player.h"
#include "Vec.h"

class Human: public Player {
    public:
        // Human Constructor
        Human(bool colour, shared_ptr<ChessBoardObserver> cb);

        // Returns true or false if a move inputted by the human user was made
        bool makeHumanMove(Vec start, Vec end);

        // clone function 
        virtual shared_ptr<Player> clone() const override; 
};

#endif
