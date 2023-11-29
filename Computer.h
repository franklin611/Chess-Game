#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "Player.h"
#include "Level.h"

class Computer : public Player {
    protected:
    int userLevel;
    unique_ptr<Level> level = nullptr;
    public:
        Computer(bool colour, unique_ptr<Observer> cb, int userLevel);
        void makeComputerMove(bool white, int userLevel);
        vector<vector<Vec>> selectMove();
        void notifyCapM(Vec start, Vec end); // TODO: idk if right here or in observer.h????
        void notifyCheckM(Vec start, Vec end);
        void notifyCMM(Vec start, Vec end); // then use these to make levels accordingly 
};

#endif


// makeComputerMove needs to select a move from selectMove from its associated level and then call cb's notify (notify chessboard to make the move)
// chessboard observes the player (subject)
// to select a move, it takes the vector of legal moves that player has, and then calls select move on that (since in select move we have logic)
// of filtering what move
// then based on turn (maybe colour since player has that?) it calls chessboard's notify (check if chessbord's notify takes in a colour/turn already)
// and then in chessboard's move it calls td notify

