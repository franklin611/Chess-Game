#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
using namespace std;

class Game {
    float blackScore; // Score of the Black team
    float whiteScore; // Score of the White team
    public:
        // default constructor 
        Game();

        // Update the whiteScore field
        void updateWhite(bool half); 

        // Update the blackScore field
        void updateBlack(bool half);

        // Output operator for the scores of the current game
        friend ostream &operator<<(ostream &out, const Game &g);

};

#endif
