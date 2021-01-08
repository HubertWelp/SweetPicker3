#include "login.h"
#include "monitor.h"
#include <QApplication>
#include <iostream>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login w;
    w.show();

    return a.exec();
}
