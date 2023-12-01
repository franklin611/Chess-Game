#include <iostream>
#include "TextDisplay.h"
#include "ChessBoard.h"
using namespace std;

TextDisplay::TextDisplay() {
    for (size_t i = 0; i <= 7; ++i) {
        vector<char> row;
        for (size_t j = 0; j <= 7; ++j) {
            if (((i % 2 == 0) && (j % 2 == 0)) || ((i % 2 == 1) && (j % 2 == 1))) {
                row.emplace_back('_'); // this makes the columns in the row (8 columns per row)
            } else {
                row.emplace_back(' ');
            }
        }
        theDisplay.emplace_back(row);
    }
}

void TextDisplay::notifyMoves(Vec start, char typeStart, Vec end, char typeEnd, string check) { // notify should be only printing the moves
    str_check = check;
    // change thedisplay's character at start, change thedisplay's character at end
    theDisplay[start.getY()][start.getX()] = typeStart;
    theDisplay[end.getY()][end.getX()] = typeEnd;
    // TODO: if grid is fucked up then switch getX and getY
}

void TextDisplay::notify(Vec start, char typeStart) {
    theDisplay[start.getY()][start.getX()] = typeStart;
}

void TextDisplay::notify(bool white) { // call this inside of setup as well as when making any move
// Everything is inverted!
    if (white) {colour = "Black";}
    else {colour = "White";}
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    int num = 8;
    for (int i = td.theDisplay.size() - 1; i >= 0; --i) {
        out << to_string(num) + ' ';
        for (int j = 0; j < td.theDisplay.size(); ++j) {
            out << td.theDisplay[i][j];
        }
        out << endl; // since each row printed on newline
        --num;
    }
    // int num = 0;
    // for (int i = 0; i <= td.theDisplay.size() - 1; ++i) {
    //     out << to_string(num) + ' ';
    //     for (int j = td.theDisplay.size(); j > 0; --j) {
    //         out << td.theDisplay[i][j];
    //     }
    //     out << endl; // since each row printed on newline
    //     ++num;
    // }
    out << endl;
    out << "  abcdefgh" << endl;
    if (td.str_check.size() > 1) {out << td.str_check << "is in check." << endl;} // empty string is true, so if not empty string output
    out << "It's " << td.colour << "'s turn" << endl;
    out << "---------------------" << endl;
    return out;
}
