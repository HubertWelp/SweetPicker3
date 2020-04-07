#include "textauswerter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Textauswerter w;
    Punkt ergKoordinaten;
    int erg = w.liesEin();

    // Ergebnis des Einlesens ausgeben
    if(erg == 1)
    {
        QMessageBox::warning(&w,"Einlesen","Nur 1 Ergebnis wurde eingelesen");
    }
    else if (erg == 2)
    {
        QMessageBox::warning(&w,"Einlesen","Nur 2 Ergebnisse wurde eingelesen");
    }
    else if (erg == 3)
    {
        QMessageBox::information(&w,"Einlesen","Alles erfolgreich eingelesen");
    }
    else if (erg == 0)
    {
        QMessageBox::warning(&w,"Einlesen","Nichts wurde eingelesen");
    }
    else if (erg > 3)
    {
        QMessageBox::warning(&w,"Einlesen","Es wurden wiederholte Ergebnisse eingelesen");
    }

    ergKoordinaten = w.werteAus(1);
    QMessageBox::information(&w,"Auswerten","Die gewünschten Koordinaten sind:\nx: " + QString::number(ergKoordinaten.x) + "\ny: " + QString::number(ergKoordinaten.y));

    return erg;
}
