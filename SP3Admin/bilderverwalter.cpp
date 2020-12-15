#include "bilderverwalter.h"

Bilderverwalter::Bilderverwalter(QString pfad)
{
    dateipfad=pfad;
    aktualisieren();
}

int Bilderverwalter::aktualisieren()
{
    return 0;
}

QImage Bilderverwalter::getAktuelleSzene()
{
    return QPixmap(100,100).toImage();
}

QImage Bilderverwalter::getAktuelleSzeneRahmen()
{
    return QPixmap(100,100).toImage();
}

QImage Bilderverwalter::getAusschnitt()
{
    return QPixmap(100,100).toImage();
}

QImage Bilderverwalter::getAusschnittSW()
{
    return QPixmap(100,100).toImage();
}

QImage Bilderverwalter::getAusschnittSWprocessed()
{
    return QPixmap(100,100).toImage();
}

QImage Bilderverwalter::getAusschnittErgebnis()
{
    return QPixmap(100,100).toImage();
}

