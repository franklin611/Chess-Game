#ifndef _DISPLAYOBSERVER_H_
#define _DISPLAYOBSERVER_H_
class ChessBoard;

class DisplayObserver {
    public:
    virtual void notify(ChessBoard &cb) = 0; // TODO: pretty sure need to have cb because what calls notify when it changes each time is the cb?
    virtual ~DisplayObserver() = default;
};

#endif
