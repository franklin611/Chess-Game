#include "Vec.h"
class Observer {
 public:
  virtual void notifyLM(Vec start, Vec end) = 0;
  virtual void notifyCapM(Vec start, Vec end) = 0;
  virtual void notifyCheckM(Vec start, Vec end) = 0;
  virtual void notifyCMM(Vec start, Vec end) = 0;
  virtual ~Observer();
};
