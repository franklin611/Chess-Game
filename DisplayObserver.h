#ifndef _DISPLAYOBSERVER_H_
#define _DISPLAYOBSERVER_H_
#include "Vec.h"
#include <string>
using namespace std;

class DisplayObserver {
    public:
    // notifies the displays of the start, end and the characters that should be at those coordinates
    virtual void notifyMoves(Vec start, char typeStart, Vec end, char typeEnd, string check) = 0;
    // notifies the display to change a singular piece at a singular coordinate 
    virtual void notify(Vec start, char typeStart) = 0;
    // notify the display of a turn change 
    virtual void notify(bool white) = 0;
    // destructor 
    virtual ~DisplayObserver();
};

#endif
