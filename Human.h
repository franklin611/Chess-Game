#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "Player.h"

class Human: public Player {
    public:
        Human(bool colour): Player{colour} {}
};

#endif
