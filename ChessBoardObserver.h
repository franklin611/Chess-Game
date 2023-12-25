#ifndef _CHESSBOARDOBSERVER_H_
#define _CHESSBOARDOBSERVER_H_

#include "Vec.h"

class ChessBoardObserver {
 public:
  // notifies the chessboard of a move that needs to be played on the gameboard and to setup the next turn
  virtual void notify(Vec start, Vec end) = 0;
  // destructor 
  virtual ~ChessBoardObserver();
};

#endif
