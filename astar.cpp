#include "astar.h"
#include <QMouseEvent>
#include <QKeyEvent>
#include <cmath>
#include <deque>
#include <QThread>
#include <QApplication>



astar::astar(unsigned int m, unsigned int n, unsigned int w, unsigned int h) : GridWindow(m,n,7,w,h)
{
    colors[0]=QColor(0,255,0);     //start
    colors[1]=QColor(255,0,0);     //end
    colors[2]=QColor(0,0,0);       //blocked
    colors[3]=QColor(255,255,255); //empty
    colors[4]=QColor(0,0,255);     //path
    colors[5]=QColor(120,120,255); //closed
    colors[6]=QColor(220,220,255); //open

    for(unsigned int i=0;i<m;i++)
        for(unsigned int j=0;j<n;j++)
            grid[i][j]=3;
}



void astar::solve()
{
    struct pair
    {
        int x, y;
        pair(int a=-1, int b=-1) : x(a), y(b) {}
    };

    //*******************************

    eventsDisabled=true;
    clear();

    pair start;
    pair end;
    pair** prev=nullptr;
    bool** closed=nullptr;
    std::deque<pair> open;
    std::deque<int> g;

    for(unsigned int i=0;i<m;i++)
    {
        for(unsigned int j=0;j<n;j++)
        {
            if(grid[i][j]==0)
            {
                start=pair(i,j);
            }
            if(grid[i][j]==1)
            {
                end=pair(i,j);
            }
        }
    }
    if(start.x==-1 || end.x==-1)
    {
        eventsDisabled=false;
        return;
    }

    prev=new pair*[m];
    closed=new bool*[m];
    for(unsigned int i=0;i<m;i++)
    {
        closed[i]=new bool[n];
        prev[i]=new pair[n];
        for(unsigned int j=0;j<n;j++)
        {
            closed[i][j]=false;
            prev[i][j]=pair(-1,-1);
        }
    }

    //*******************************

    open.push_back(start);
    g.push_back(0);

    while(!open.empty())
    {
        if(delay!=0)
        {
            update();
            qApp->processEvents();
        }
        if(delay==5000)
        {
            while(pause)
            {
                qApp->processEvents();
            }
            pause=true;
        }
        else
            QThread::msleep(delay);

        pair q = open.front();
        int iq = 0;
        int gq = g[iq];
        int fq = g[iq] + distance(q.x,q.y,end.x,end.y);

        for(unsigned int i=1;i<open.size();i++)
        {
            pair p = open[i];
            if(g[i]+distance(p.x,p.y,end.x,end.y)<fq)
            {
                iq=i;
                q=p;
                fq=g[i] + distance(p.x,p.y,end.x,end.y);
                gq=g[i];
            }
        }
        open.erase(open.begin() + iq);
        g.erase(g.begin() + iq);
        closed[q.x][q.y]=true;
        if(q.x!=start.x || q.y!=start.y)
        {
            grid[q.x][q.y]=5;
            qApp->processEvents();
        }
        //***


        pair p;
        for(int i=-1;i<2;i++)
        {
            for(int j=-1;j<2;j++)
            {
                p.x=q.x+j;p.y=q.y+i;


                //***
                if((i==0 && j==0) || outOfBounds(p.x,p.y) || (grid[p.x][p.y]==2) || closed[p.x][p.y])
                {
                    continue;
                }
                //***


                //***
                if(p.x==end.x && p.y==end.y)
                {
                    while(q.x!=start.x || q.y!=start.y)
                    {
                        grid[q.x][q.y]=4;
                        q=prev[q.x][q.y];
                    }
                    i=2;j=2;
                    open.clear();
                    continue;
                }
                //***


                //***
                int fp=gq + distance(q.x,q.y,p.x,p.y) + distance(p.x,p.y,end.x,end.y);
                bool isOpen=false;
                for(unsigned int k=0;k<open.size();k++)
                {
                    pair a=open[k];
                    if(a.x==p.x && a.y==p.y)
                    {
                        isOpen=true;
                        if(fp<g[k]+distance(a.x,a.y,end.x,end.y))
                        {
                            g[k]=gq+distance(q.x,q.y,a.x,a.y);
                            prev[p.x][p.y]=q;
                        }
                    }
                }
                if(!isOpen)
                {
                    open.push_front(p);
                    g.push_front(gq + distance(q.x,q.y,p.x,p.y));
                    grid[p.x][p.y]=6;
                    prev[p.x][p.y]=q;
                }
                //***
            }
        }
    }


    for(unsigned int i=0;i<m;i++)
    {
        delete[] closed[i];
        delete[] prev[i];
    }
    delete[] prev;
    delete[] closed;
    eventsDisabled=false;

    update();
    qApp->processEvents();
}



void astar::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key()==53)
    {
        pause=false;
        if(delay==5000)
            delay=500;
        else if(delay==500)
            delay=50;
        else if(delay==50)
            delay=5;
        else if(delay==5)
            delay=0;
        else
        {
            delay=5000;
            pause=true;
        }
        return;
    }
    if(eventsDisabled && e->key()==32)
    {
        pause=false;
        return;
    }

    if(e->key()==32)
        solve();
    else if(e->key()>53)
        return;
    else
        GridWindow::keyReleaseEvent(e);
    update();
}



void astar::mouseMoveEvent(QMouseEvent *e)
{
    if(eventsDisabled)
        return;
    if(!(e->buttons() & Qt::LeftButton))
    {
        return;
    }
    mousePressEvent(e);
}



void astar::mousePressEvent(QMouseEvent *e)
{
    if(eventsDisabled)
        return;
    clear();
    int x=e->position().x();
    int y=e->position().y();
    int dw = w/m;
    int dh = h/n;
    int i=x/dw;
    int j=y/dh;
    if(outOfBounds(i,j))
        return;
    for(unsigned int i=0;i<m;i++)
    {
        for(unsigned int j=0;j<n;j++)
        {
            {
                if(selector==0 && grid[i][j]==0)
                {
                    grid[i][j]=3;
                }
                if(selector==1 && grid[i][j]==1)
                {
                    grid[i][j]=3;
                }
            }
        }
    }

    GridWindow::mousePressEvent(e);
}



int astar::distance(int x1, int y1, int x2, int y2)
{
    int dx = std::abs((float)x1 - x2);
    int dy = std::abs((float)y1 - y2);

    int diag=std::min(dx,dy);
    int rest=std::abs(dx-dy);

    return diag*14 + rest*10;
}


void astar::clear()
{
    for(unsigned int i=0;i<m;i++)
    {
        for(unsigned int j=0;j<n;j++)
        {
            if(grid[i][j]==4 || grid[i][j]==5 || grid[i][j]==6)
                grid[i][j]=3;
        }
    }
}
