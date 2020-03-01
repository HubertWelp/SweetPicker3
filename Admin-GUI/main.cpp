#include "gui.h"
#include "monitor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Monitor m;
//    m.show();
    GUI w;
    w.show();

    return a.exec();
}
