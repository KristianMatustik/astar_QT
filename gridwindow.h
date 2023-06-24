#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QMainWindow>


class GridWindow : public QMainWindow
{
    Q_OBJECT

public:
    GridWindow(unsigned int m=1, unsigned int n=1, unsigned int k=0, unsigned int w=800, unsigned int h=800, QWidget *parent=nullptr);
    ~GridWindow();


    int getValue(unsigned int i, unsigned int j);
    void setValue(unsigned int i, unsigned int j, unsigned int v);
    void setColor(unsigned int v, unsigned int r, unsigned int g, unsigned int b);


protected:
    unsigned int w, h;  //window size (pixels)
    unsigned int m, n;  //grid size (squares)
    unsigned int k;     //number of states per square
    QColor* colors;       //colors of each state (array size k)
    unsigned int** grid;   //grid
    unsigned int selector;  //value asigned to tiles

    bool outOfBounds(unsigned int i, unsigned int j);

    void paintEvent(QPaintEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

};

#endif // GRIDWINDOW_H
