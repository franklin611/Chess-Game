#include "Vec.h"
class Observer {
 public:
  virtual void notifyLM(Vec start, Vec end) = 0;
  virtual ~Observer();
};
