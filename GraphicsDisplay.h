#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_

#include "DisplayObserver.h"
#include "Window.h"
#include <vector>
#include <string>
#include <memory>

// Graphics Display class which is a subclass of DisplayObserver class
// Graphics Display also has a pointer to Xwindow
class GraphicsDisplay: public DisplayObserver{
    unique_ptr<Xwindow> w;
    int dim;
    public:
        GraphicsDisplay();
        // Overwritten notifyMoves to change the display's character at Vec start, and change the char at Vec end
        void notifyMoves(Vec start, char typeStart, Vec end, char typeEnd, string check) override;
        // Overwritten notify to change the display's character at a specific coordinate
        void notify(Vec start, char typeStart) override;
        void notify(bool white) override;
        ~GraphicsDisplay() = default; // default since using unique_ptrs
        void Blank();
};

#endif