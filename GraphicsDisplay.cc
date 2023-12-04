#include "GraphicsDisplay.h"

// sets up the graphic's chessboard in window
GraphicsDisplay::GraphicsDisplay() : w{make_unique<Xwindow>()}, dim{500/8} {
    int x_pos = 0;
    int y_pos = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((((i % 2) == 0) && ((j % 2) == 0)) || (((i % 2) == 1) && ((j % 2) == 1))) {
                w->fillRectangle(x_pos, y_pos, dim, dim, Xwindow::White);
            } else {
                w->fillRectangle(x_pos, y_pos, dim, dim, Xwindow::Blue);
            }
            x_pos += dim; // goes to the next column
        }
        y_pos += dim;
        x_pos = 0; // this brings back to start (LHS) doesn't actually fill in
    }
}

// re-displays pieces that have been moved, including the tile/square
void GraphicsDisplay::notifyMoves(Vec start, char typeStart, Vec end, char typeEnd, string check) {

    // resetting the square to the correct color
    int xCoord = start.getX() * dim;
    int yCoord = (7 - start.getY()) * dim;

    if ((((start.getX() % 2) == 0) && ((start.getY() % 2) == 0)) || (((start.getX() % 2) == 1) && ((start.getY() % 2) == 1))) {
        w->fillRectangle(xCoord, yCoord, dim, dim, Xwindow::Blue);
    } else {
         w->fillRectangle(xCoord, yCoord, dim, dim, Xwindow::White);
    }

    xCoord = end.getX() * dim;
    yCoord = (7 - end.getY()) * dim;

    if ((((end.getX() % 2) == 0) && ((end.getY() % 2) == 0)) || (((end.getX() % 2) == 1) && ((end.getY() % 2) == 1))) {
        w->fillRectangle(xCoord, yCoord, dim, dim, Xwindow::Blue);
    } else {
         w->fillRectangle(xCoord, yCoord, dim, dim, Xwindow::White);
    }

    // only the end piece needs to be drawString-ed
    this->notify(end, typeEnd);
}

// draws the string/piece at the specified location
void GraphicsDisplay::notify(Vec start, char typeStart) {
    // string font = "-b&h-lucidatypewriter-bold-r-normal-sans-20-140-100-100-m-120-iso8859-10";
    int xCoord = (start.getX() - 1) * dim;
    int yCoord = (6 - start.getY()) * dim; // flip for y-coord to start from the bottom
    w->drawString(xCoord + 90, yCoord + 100, string(1, typeStart), 1);
}

// this notify is part of pure virtual from DisplayObservers but is never called, so no implementation
void GraphicsDisplay::notify(bool white) {}

