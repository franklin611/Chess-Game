#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "Player.h"

class Computer : public Player{
    int level;
    public:
        Computer(bool colour, int level) : Player{colour}, level{level} {}
        int getLevel();
};

#endif
