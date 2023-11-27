#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_

#include "Vec.h"

class TextDisplay {
    vector<vector<char>> theDisplay;
    // shared_ptr<ChessBoard> cb;
    // ChessBoard *cb;
    public:
        TextDisplay();
        // ~TextDisplay(); // since pointer? or don't need since unique_ptr?
        void notify(Vec start, char typeStart, Vec end, char typeEnd);
        friend ostream &operator<<(ostream &out, const TextDisplay &td);

};



// textdisplay observes chessboard, chessboard notifies textdisplay, attach textdisplay as an observer of chessboard

    // chessboard.attach(td)

    // Hi sorry just to confirm, basically we have a pointer to chessboard in textdisplay, and then whenever chessboard changes it notifies textdisplay (textdisplay is observer to chessboard) and then textdisplay has an overwritten output operator which prints the actual outboard/game right?
    // Ok slay and then for outputting the score it’s using the overwritten output operator in game (and we have access to it since we have a pointer to chessboard right)?

    // if give textdisplay a pointer to chessboard we can access gameboard and directly print that, only issue is what is being observed? is this observer still?
    // elsewise have two diff notifies, one for setup and one for move

#endif

