
#include "TextDisplay.h"
#include "ChessBoard.h"
using namespace std;

TextDisplay::TextDisplay() {
    for (int i = 0; i < 7; ++i) {
        vector<char> row;
        for (int j = 0; j < 7; ++j) {
            if ((i % 2 == 0) && (j % 2 == 0)) {
                row.emplace_back(' '); // this makes the columns in the row (8 columns per row)
            } else {
                row.emplace_back('_');
            }
        }
        theDisplay.emplace_back(row);
    }
}

void TextDisplay::notifyMoves(Vec start, char typeStart, Vec end, char typeEnd) { // notify should be only printing the moves
    // change thedisplay's character at start, change thedisplay's character at end
    theDisplay[start.getY()][start.getX()] = typeStart;
    theDisplay[end.getY()][end.getX()] = typeEnd;
    // TODO: if grid is fucked up then switch getX and getY
}

void TextDisplay::notify(Vec start, char typeStart) {
    theDisplay[start.getY()][start.getX()] = typeStart;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < td.theDisplay.size(); ++i) {
    for (int j = 0; j < td.theDisplay.size(); ++i) {
      out << td.theDisplay[i][j];
    }
    out << endl; // since each row printed on newline
  }
  return out;
}
