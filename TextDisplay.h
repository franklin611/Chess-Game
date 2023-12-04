#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include "DisplayObserver.h"
#include "Vec.h"
#include "vector"

// Text Display class which is a subclass of DisplayObserver class
class TextDisplay : DisplayObserver {
    protected:
        string str_check = ""; // To be passed as "White" or "Black"
        string colour = "";
        vector<vector<char>> theDisplay; // The display of the char pieces
    public:
        TextDisplay();
        // Change the display's character at Vec start, and change the char at Vec end
        void notifyMoves(Vec start, char typeStart, Vec end, char typeEnd, string check) override;
        void notify(Vec start, char typeStart) override; // Sets the char at Vec start
        void notify(bool white) override; // Notifys the turn of the board
        friend ostream &operator<<(ostream &out, const TextDisplay &td); // Output operator
        ~TextDisplay() = default; // default because vector has its own dtor
};

#endif
