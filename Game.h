#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
using namespace std;

class Game {
    float blackScore; // Score of the Black and White team
    float whiteScore;
    public:
        Game();

        // Update the whiteScore field
        void updateWhite(bool half); 

        // Update the blackScore field
        void updateBlack(bool half);

        // Output operator for the scores of the current game
        friend ostream &operator<<(ostream &out, const Game &g);

};

#endif
