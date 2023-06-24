#include "gridwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>


GridWindow::GridWindow(unsigned int m, unsigned int n, unsigned int k, unsigned int w, unsigned int h, QWidget *parent)
    : QMainWindow(parent), w(w), h(h), m(m), n(n), k(k)
{
    if(k<2)
        k=2;
    if(m<1)
        m=1;
    if(n<1)
        n=1;
    if(w<0)
        w=800;
    if(h<0)
        h=800;


    colors=new QColor[k];
    float dc = (float)255/(k-1);
    for(unsigned int i=0;i<k;i++)
    {
        colors[i] = QColor((int)(i*dc),(int)(i*dc),(int)(i*dc));
    }
    grid = new unsigned int*[m];
    for(unsigned int i=0;i<m;i++)
    {
        grid[i]=new unsigned int[n];
        for(unsigned int j=0;j<n;j++)
        {
            grid[i][j]=0;
        }
    }
    selector = 0;

    resize(w,h);
}


GridWindow::~GridWindow()
{
    for(unsigned int i=0;i<m;i++)
    {
        delete[] grid[i];
    }
    delete[] colors;
}

void GridWindow::paintEvent(QPaintEvent *e)
{
    int dw = w/m;
    int dh = h/n;
    QPainter p(this);
    p.setPen(QPen(Qt::SolidLine));
    for(unsigned int i=0;i<m;i++)
       {
           for(unsigned int j=0;j<n;j++)
           {
               p.setBrush(QBrush(colors[grid[i][j]]));
               p.drawRect(i*dw, j*dh, dw, dh);
           }
       }
}

void GridWindow::keyReleaseEvent(QKeyEvent *e)
{
    int key = e->key();

    if(key<49 || key>49+k-1)
        return;
    else
        selector=key-49;
}

void GridWindow::mouseMoveEvent(QMouseEvent *e)
{
    if(!(e->buttons() & Qt::LeftButton))
    {
        return;
    }
    mousePressEvent(e);
}

void GridWindow::mousePressEvent(QMouseEvent *e)
{
    int x=e->position().x();
    int y=e->position().y();
    int dw = w/m;
    int dh = h/n;
    int i=x/dw;
    int j=y/dh;
    if(outOfBounds(i,j))
        return;
    grid[i][j]=selector;
    update();
}

int GridWindow::getValue(unsigned int i, unsigned int j)
{
    if(outOfBounds(i,j))
        return -1;
    return grid[i][j];
}

void GridWindow::setValue(unsigned int i, unsigned int j, unsigned int v)
{
    if(outOfBounds(i,j) || v<0 || v>k-1)
        return;
    grid[i][j]=v;
}

void GridWindow::setColor(unsigned int v, unsigned int r, unsigned int g, unsigned int b)
{
    if(v<0 || v>k-1)
        return;
    colors[v]=QColor(r,g,b);
}

bool GridWindow::outOfBounds(unsigned int i, unsigned int j)
{
    if(i<0 || i>m-1 || j<0 || j>n-1)
        return true;
    return false;
}
