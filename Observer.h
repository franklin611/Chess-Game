#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "Vec.h"
#include <memory> // Not sure if we need
class Observer {
  vector<vector<Vec>> legalMoves;
 public:
  virtual void notifyLM(Vec start, Vec end) = 0;
  virtual void notifyCapM(Vec start, Vec end) = 0;
  virtual void notifyCheckM(Vec start, Vec end) = 0;
  virtual void notifyCMM(Vec start, Vec end) = 0;
  virtual ~Observer();
};

#endif
