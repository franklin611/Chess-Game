#include "GraphicsDisplay.h"

GraphicsDisplay::GraphicsDisplay() : w{make_unique<Xwindow>()}, dim{500/8} {
    int x_pos = 0;
    int y_pos = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (((i % 2 == 0) && (j % 2 == 0)) || ((i % 2 == 1) && (j % 2 == 1))) {
                w->fillRectangle(x_pos, y_pos, dim, dim, Xwindow::Blue);
            } else {
                w->fillRectangle(x_pos, y_pos, dim, dim, Xwindow::White);
            }
            x_pos += dim; // Move to the next column
        }
        y_pos += dim;
        x_pos = 0; // this brings back to start (LHS) doesn't actually fill in
    }
}

void GraphicsDisplay::notifyMoves(Vec start, char typeStart, Vec end, char typeEnd, string check) {
    this->notify(start, typeStart); // TODO: doesn't work, need to overwrite the square
    this->notify(end, typeEnd);

    // int xCoord = (start.getX() - 1) * dim;
    // int yCoord = (start.getY() - 1) * dim;
    // w->drawString(xCoord + 90, yCoord + 100, string(1, typeStart));
    // xCoord = (end.getX() - 1) * dim;
    // yCoord = (end.getY() - 1) * dim;
    // w->drawString(xCoord, yCoord, string(1, typeEnd));
}

void GraphicsDisplay::notify(Vec start, char typeStart) {
    int xCoord = (start.getX() - 1) * dim;
    int yCoord = (start.getY() - 1) * dim;
    w->drawString(xCoord + 90, yCoord + 100, string(1, typeStart));
}

void GraphicsDisplay::notify(bool white) {}
GraphicsDisplay::~GraphicsDisplay() {}