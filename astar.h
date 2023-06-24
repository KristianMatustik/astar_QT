#ifndef ASTAR_H
#define ASTAR_H

#include "gridwindow.h"


class astar : public GridWindow
{
protected:
    bool eventsDisabled=false;
    int delay = 5000;
    bool pause=true;

    void keyReleaseEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    void solve();
    void clear();
    int distance(int x1, int y1, int x2, int y2);

public:
    astar(unsigned int m=1, unsigned int n=1, unsigned int w=800, unsigned int h=800);
};

#endif // ASTAR_H
