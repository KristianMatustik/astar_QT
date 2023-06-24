#include "astar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<int> v{1,2,3,4,5,6};

    astar as(50,50,800,800);
    as.show();

    //GridWindow g(10,10,3,800,800);
    //g.show();

    return a.exec();
}
