#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
using namespace std;

class Game {
    float blackScore;
    float whiteScore;
    public:
        Game();
        void updateWhite(bool half);
        void updateBlack(bool half);
        friend ostream &operator<<(ostream &out, const Game &g);

};

#endif
