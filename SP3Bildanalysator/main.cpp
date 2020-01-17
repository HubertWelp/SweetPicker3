#include "ressourcen.h"

#include <QApplication>
#include "verwalter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    Verwalter v;

    return a.exec();
}
