#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_

#include "DisplayObserver.h"
#include "Window.h"
#include <vector>
#include <string>
#include "Window.h"
#include <memory>
class GraphicsDisplay: public DisplayObserver{
    unique_ptr<Xwindow> w;
    int dim;
    public:
        GraphicsDisplay();
        void notifyMoves(Vec start, char typeStart, Vec end, char typeEnd, string check) override;
        void notify(Vec start, char typeStart) override;
        void notify(bool white) override;
        virtual ~GraphicsDisplay();
};

#endif