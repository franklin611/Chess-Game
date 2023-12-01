#ifndef _CHESSBOARDOBSERVER_H_
#define _CHESSBOARDOBSERVER_H_

#include "Vec.h"

class ChessBoardObserver {
 public:
  virtual void notify(Vec start, Vec end);
  virtual ~ChessBoardObserver();
};

#endif
