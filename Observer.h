#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "Vec.h"

class Observer {
 public:
  // Pure Virtual functions to be overriden in each subclass
  // They will be used by the Observer subclasses to notify the player,a subclass, about new moves
  virtual void notifyLM(Vec start, Vec end) = 0; // notify the player that a move is legal
  virtual void notifyCapM(Vec start, Vec end) = 0; // notify the player that a move is a capture move
  virtual void notifyCheckM(Vec start, Vec end) = 0; // notify the player that a move is a check move
  virtual void notifyCMM(Vec start, Vec end) = 0; // notify the player that a move is a checkmate move
  virtual void notifyACM(Vec start, Vec end) = 0; // notify the player that a move is an avoid capture move 
  virtual ~Observer(); // destructor 
};

#endif
