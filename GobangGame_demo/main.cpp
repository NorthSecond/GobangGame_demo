#include "GobangGame_demo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GobangGame_demo w;
    w.show();
    return a.exec();
}
