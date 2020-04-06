#include "textauswerter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Textauswerter w;
    int erg = w.liesEin();

    // Ergebnis des Einlesens ausgeben
    if(erg == 1)
    {
        QMessageBox::warning(&w,"Anwendung","Nur 1 Ergebnis wurde eingelesen");
    }
    else if (erg == 2)
    {
        QMessageBox::warning(&w,"Anwendung","Nur 2 Ergebnisse wurde eingelesen");
    }
    else if (erg == 3)
    {
        QMessageBox::information(&w,"Anwendung","Alles erfolgreich eingelesen");
    }
    else if (erg == 0)
    {
        QMessageBox::warning(&w,"Anwendung","Nichts wurde eingelesen");
    }
    else if (erg > 3)
    {
        QMessageBox::warning(&w,"Anwendung","Es wurden wiederholte Ergebnisse eingelesen");
    }

    w.werteAus(2);

    return erg;
}
