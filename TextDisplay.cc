
#include "TextDisplay.h"
#include "ChessBoard.h"
using namespace std;


// TextDisplay::TextDisplay(ChessBoard cb) : cb{move(cb)} {}; // move would transfer ownership right?
// also, text display doesn't "own" resource (we dont delete resource when td out of scope)

TextDisplay::TextDisplay(ChessBoard *cb) : cb{cb} {};

TextDisplay::notify(Vec start, char typeStart, Vec end, char typeEnd) { // notify should be only printing the moves
    // change thedisplay's character at start, change thedisplay's character at end
    theDisplay[start.getY()][start.getX()] = typeStart;
    theDisplay[end.getY()][end.getX()] = typeEnd;

    // TODO: if grid is fucked up then switch getX and getY
// maybe because we onlu have one notify now for td give the start and end coord and type to make easier?
//TODO: already have a notify() with start and end for cehssboard (this is for chessboard and piece observer pattern, can i use this observer too?)
//TODO: dont need another observer pattern for chess
    for (int i = 0; i <
}

 // ostream should be entire board

// ostream &operator<<(ostream &out, const TextDisplay &td) {
//   for (int i = 0; i < cb->gb.size(); ++i) {
//     for (int j = 0; j < cb->gb.size(); ++j) {
//         if () // understanding is that vector<vector<shared_ptr<Piece>>> is exactly the position it needs to be in
//       out << td.theDisplay[i][j];
//   }
//   out << endl; // since each row printed on newline
//   }
//   return out;
// }

stream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < cb->gb.size(); ++i) {
         // understanding is that vector<vector<shared_ptr<Piece>>> is exactly the position it needs to be in
      out << cb->gb->char[i][j];
  }
  out << endl; // since each row printed on newline
  }
  return out;
}


textdisplay, window, graphicsdisplay

