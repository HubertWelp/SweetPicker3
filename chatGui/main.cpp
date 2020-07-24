#include "dialog.h"
#include <QApplication>
#include <iostream>
#include <string.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog* w;


    for(int i=0;i<argc;i++)
        std::cout << argv[i];
    std::cout << std::endl;
    if(argc==2 && strncmp(argv[1],"-h",2)==0)
    {
        std::cout << "usage: chatGui <remoteIPAdress> <remotePortNumber> <localPortNumber>" << std::endl;
        return 0;
    }else if(argc!=4)
    {
        std::cout << "Standardinitalisierung: 127.0.0.1 5842 5843" << std::endl;
        w=new Dialog("127.0.0.1",5842,5843);

    }else
    {
        w = new Dialog(argv[1],atoi(argv[2]),atoi(argv[3]));
    }
    w->show();

    return a.exec();
}
