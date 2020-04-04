#include "textauswerter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Textauswerter w;
    w.werteAus();

    return a.exec();
}
