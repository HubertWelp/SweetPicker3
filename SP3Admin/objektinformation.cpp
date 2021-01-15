#include "objektinformation.h"

Objektinformation::Objektinformation(QString pfad)
{
    dateipfad=pfad;
    Konfig k;
    aktualisieren();
}

int Objektinformation::aktualisieren()
{
    QImageReader reader;
    //reader.setFormat("jpg");

    reader.setFileName(QString("%1%2").arg(BILDABLAGE).arg("aktuelleSzene.jpg"));
    AktuelleSzene = reader.read();

    reader.setFileName(QString("%1%2").arg(BILDABLAGE).arg("aktuelleSzeneRahmen.jpg"));
    AktuelleSzeneRahmen = reader.read();

    reader.setFileName(QString("%1%2").arg(BILDABLAGE).arg("ausschnitt.jpg"));
    Ausschnitt = reader.read();

    reader.setFileName(QString("%1%2").arg(BILDABLAGE).arg("ausschnittSW.jpg"));
    AusschnittSW = reader.read();

    reader.setFileName(QString("%1%2").arg(BILDABLAGE).arg("ausschnittSWprocessed.jpg"));
    AusschnittSWprocessed = reader.read();

    reader.setFileName(QString("%1%2").arg(BILDABLAGE).arg("ausschnittErgebnis.jpg"));
    AusschnittErgebnis = reader.read();

    //3;25.2016;0;275.317;226.553
    //Name Winkel Breite x y

    QFile text(QString("%1%2").arg(BILDABLAGE).arg("ausschnittErgebnis.csv"));
    text.open(QIODevice::ReadOnly);
    QString string = QTextStream(&text).readLine();

    QStringList pieces = string.split(';');
    name = k.getObjektname(pieces.value(0).toInt());
    winkel = pieces.value(1).toFloat();
    breite = pieces.value(2).toFloat();
    xposi = pieces.value(3).toFloat();
    yposi = pieces.value(4).toFloat();

    text.close();

    if(reader.error() || text.error())
    {
        reader.setFileName(":/standardbild.jpg");
        AktuelleSzene = reader.read();
        AktuelleSzeneRahmen = AktuelleSzene;
        Ausschnitt = AktuelleSzene;
        AusschnittSW = AktuelleSzene;
        AusschnittErgebnis = AktuelleSzene;
        AusschnittSWprocessed = AktuelleSzene;
        name = "";
        winkel = 0;
        breite = 0;
        xposi = 0;
        yposi = 0;
        return -1;
    }
    else return 0;
}

QImage Objektinformation::getAktuelleSzene()
{
    return AktuelleSzene;
}

QImage Objektinformation::getAktuelleSzeneRahmen()
{
    return AktuelleSzeneRahmen;
}

QImage Objektinformation::getAusschnitt()
{
    return Ausschnitt;
}

QImage Objektinformation::getAusschnittSW()
{
    return AusschnittSW;
}

QImage Objektinformation::getAusschnittSWprocessed()
{
    return AusschnittSWprocessed;
}

QImage Objektinformation::getAusschnittErgebnis()
{
    return AusschnittErgebnis;
}

QString Objektinformation::getAngefordertesObjekt()
{
    return name;
}

float Objektinformation::getWinkel()
{
    return winkel;
}

float Objektinformation::getBreite()
{
    return breite;
}

float Objektinformation::getXPosi()
{
    return xposi;
}

float Objektinformation::getYPosi()
{
    return yposi;
}

