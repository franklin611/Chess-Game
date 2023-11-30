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

        // the dtor here doesn't need to be explicitly written out, we just use compiler provided one by not writing signature at all
};

#endif
