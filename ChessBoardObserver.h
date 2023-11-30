#include "Vec.h"
class ChessBoardObserver {
 public:
  virtual void notify(Vec start, Vec end) = 0;
  virtual ~ChessBoardObserver();
};
