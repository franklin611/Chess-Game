#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "Vec.h"
// #include <memory> // Not sure if we need
class Observer {
 public:
  // Pure Virtual functions to be overriden in each subclass
  // They will be used by the Observer subclasses to notify the player,a subclass, about new moves
  virtual void notifyLM(Vec start, Vec end) = 0;
  virtual void notifyCapM(Vec start, Vec end) = 0;
  virtual void notifyCheckM(Vec start, Vec end) = 0;
  virtual void notifyCMM(Vec start, Vec end) = 0;
  virtual void notifyACM(Vec start, Vec end) = 0;
  virtual ~Observer();
};

#endif
