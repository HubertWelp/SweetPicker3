#include "textauswerter.h"

/**
* Konstruktor
*/
Textauswerter::Textauswerter(QWidget *parent)
    : QWidget(parent)
{

}

/**
* Diese Funktion wertet den Text in der Text-Datei aus und benutzt dafür die Funktionen:
* {@link detection_classes}, {@link detection_scores} und {@link detection_boxes}
*
* @return die Anzahl der erfolgreich o.g. aufgrufenen Funktionen
*/
int Textauswerter::werteAus()
{
    QFile text (PFAD);

    if(!text.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"Datei öffnen","Datei konnte nicht geöffnet werden !");
    }

    QTextStream datenstrom(&text);
    QString string;
    anzGlsnZeilen = 0;
    int erfolgreich = 0;

    while(datenstrom.readLineInto(&string,MAXLESEN))
    {
        anzGlsnZeilen++;

        if (string.contains(DCLASS,Qt::CaseInsensitive))
        {
            QMessageBox::information(this,"detection_classes","Klassen werden ausgewertet");
            if (detection_classes(anzGlsnZeilen)) erfolgreich++;
        }
        else if (string.contains(DSCORE,Qt::CaseInsensitive))
        {
            QMessageBox::information(this,"detection_scores","Erkennungsraten werden ausgewertet");
            if (detection_scores(anzGlsnZeilen)) erfolgreich++;
        }
        else if (string.contains(DBOX,Qt::CaseInsensitive))
        {
            QMessageBox::information(this,"detection_boxes","Boxen werden ausgewertet");
            if (detection_boxes(anzGlsnZeilen)) erfolgreich++;
        }
    }

    // Der Cursor steht am Ende der Datei
    QMessageBox::information(this,"gefundenenObjekteTest.txt","Ich stehe jetzt am Ende der Datei");
    text.close();

    // Return-Bedingung
    return erfolgreich;
}

/**
* Diese Funktion sucht nach dem Schlüsselwort "detection_classes" in der Text-Datei und liest die Zahlen danach ein.
* Diese Zahlen stellen die Klassen der Erennungsergebnisse dar und werden in Arrays gespeichert dann entsprechend später bearbeitet.
*
* @param [in] aktlZeile hat die Zeilennummer, an der der Cursor in der Schleife in {@link werteAus} steht, so dass diese Funktion ab da weiter einliest.
* @return true, falls der Ablauf der Funktion reibungslos lief
*/
bool Textauswerter::detection_classes(int aktlZeile)
{
    // Die Text-Datei erneuert öffnen
    QFile text (PFAD);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;

    // Den Cursor auf die aktuelle Zeile setzen
    for (int n=0 ; n<aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}
    QMessageBox::information(this,QString(DCLASS) + " starten","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");

    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;

        // Ausgabe des Inhalts der aktuellen Zeile
        QMessageBox::information(this,QString(DCLASS) + " Zeile" + QString::number(aktlZeile),linie);

        // Hier weiter
        // Die Anzahl der Vorhandenen Elemente im Array ermitteln (Anzahl der Leerzeichen + 1)

        // Erste Klammer oder Leerzeichen entfernen

        // String mittels " " aufteilen und ins Array ergK[] eintragen
    }
    while(!linie.contains("]"));

    // Die Text-Datei schließen
    QMessageBox::information(this,QString(DCLASS) + " beenden","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");
    text.close();

    // Rückgabe
    return true;
}

/**
* Diese Funktion sucht nach dem Schlüsselwort "detection_scores" in der Text-Datei und liest die Zahlen danach ein.
* Diese Zahlen stellen die Erkennungsrate der gefundenen Klassen dar und werden in Arrays gespeichert dann entsprechend später bearbeitet.
*
* @param [in] aktlZeile hat die Zeilennummer, an der der Cursor in der Schleife in {@link werteAus} steht, so dass diese Funktion ab da weiter einliest.
* @return true, falls der Ablauf der Funktion reibungslos lief
*/
bool Textauswerter::detection_scores(int aktlZeile)
{
    // Die Text-Datei erneuert öffnen
    QFile text (PFAD);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;

    // Den Cursor auf die aktuelle Zeile bringen
    for (int n=0 ; n<aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}
    QMessageBox::information(this,QString(DSCORE) + " starten","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");

    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;

        // Ausgabe des Inhalts der aktuellen Zeile
        QMessageBox::information(this,QString(DSCORE) + " Zeile" + QString::number(aktlZeile),linie);

        // Hier weiter
        // Die Anzahl der Vorhandenen Elemente im Array ermitteln (Anzahl der Punkte)

        // Erste Klammer oder Leerzeichen entfernen

        // String mittels " " aufteilen und ins Array ergS[] eintragen
    }
    while(!linie.contains("]"));

    // Die Text-Datei schließen
    QMessageBox::information(this,QString(DSCORE) + " beenden","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");
    text.close();

    // Rückgabe
    return true;
}

/**
* Diese Funktion sucht nach dem Schlüsselwort "detection_boxes" in der Text-Datei und liest die Koordinaten danach ein.
* Diese Koordinaten formen eine Box und werden in Arrays gespeichert.
*
* @param [in] aktlZeile hat die Zeilennummer, an der der Cursor in der Schleife in {@link werteAus} steht, so dass diese Funktion ab da weiter einliest.
* @return true, falls der Ablauf der Funktion reibungslos lief
*/
bool Textauswerter::detection_boxes(int aktlZeile)
{
    // Die Text-Datei erneuert öffnen
    QFile text (PFAD);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;

    // Den Cursor auf die aktuelle Zeile bringen
    for (int n=0 ; n<aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}
    QMessageBox::information(this,QString(DBOX) + " starten","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");

    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;

        // Ausgabe des Inhalts der aktuellen Zeile
        QMessageBox::information(this,QString(DBOX) + " Zeile" + QString::number(aktlZeile),linie);

        // Hier weiter
        // Die Anzahl der Vorhandenen Elemente im Array ermitteln (Anzahl der Punkte)

        // Erste Doppel-Klammer oder Leerzeichen+Klammer entfernen

        // String mittels " " aufteilen und ins Array ergB[] eintragen
    }
    while(!linie.contains("]]"));

    // Die Text-Datei schließen
    QMessageBox::information(this,QString(DBOX) + " beenden","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");
    text.close();

    // Rückgabe
    return true;
}

/**
* Destruktor
*/
Textauswerter::~Textauswerter()
{

}
