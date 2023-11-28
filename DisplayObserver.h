#ifndef _DISPLAYOBSERVER_H_
#define _DISPLAYOBSERVER_H_
#include "Vec.h"

class DisplayObserver {
    public:
    virtual void notifyMoves(Vec start, char typeStart, Vec end, char typeEnd) = 0;
    virtual void notify(Vec start, char typeStart) = 0;
    virtual ~DisplayObserver();
};

#endif
