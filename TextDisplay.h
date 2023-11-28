#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include "Vec.h"
#include "vector"

class TextDisplay : DisplayObserver {
    protected:
        string check; // please pass to me as "White" or "Black"
        vector<vector<char>> theDisplay;
    public:
        TextDisplay();
        void notifyMoves(Vec start, char typeStart, Vec end, char typeEnd, string check) override;
        void notify(Vec start, char typeStart) override;
        friend ostream &operator<<(ostream &out, const TextDisplay &td);
        ~TextDisplay() = default; // default because vector has its own dtor
};

#endif
