#include "textauswerter.h"

Textauswerter::Textauswerter(QWidget *parent)
    : QWidget(parent), anzGlsnZeilen(0)
{

}

bool Textauswerter::werteAus()
{
    QFile text (PFAD);

    if(!text.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"Datei öffnen","Datei konnte nicht geöffnet werden !");
    }

    QTextStream datenstrom(&text);
    QString string;

    while(datenstrom.readLineInto(&string,MAXLESEN))
    {
        anzGlsnZeilen++;

        if (string.contains(DCLASS,Qt::CaseInsensitive))
        {
            QMessageBox::information(this,"detection_classes","Klassen werden ausgewertet");
            detection_classes();
        }
        else if (string.contains(DSCORE,Qt::CaseInsensitive))
        {
            QMessageBox::information(this,"detection_scores","Erkennungsraten werden ausgewertet");
            detection_scores();
        }
        else if (string.contains(DBOX,Qt::CaseInsensitive))
        {
            QMessageBox::information(this,"detection_boxes","Boxen werden ausgewertet");
            detection_boxes();
        }
    }
}

bool Textauswerter::detection_classes()
{
    // Die Text-Datei erneuert öffnen
    QFile text (PFAD);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;

    // Den Cursor sozusagen auf die aktuelle Zeile bringen
    for (int n=0 ; n<anzGlsnZeilen ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}

    // Hier die gewünschten Daten einlesen
    // Erste Klammer entfernen
    // Zahlen von jeder Zeile in Strings einlesen
    // Letzte Klammer finden und Funktion beenden
}

bool Textauswerter::detection_scores()
{
    // Die Text-Datei erneuert öffnen
    QFile text (PFAD);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;

    // Den Cursor sozusagen auf die aktuelle Zeile bringen
    for (int n=0 ; n<anzGlsnZeilen ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}

    // Hier die gewünschten Daten einlesen
    // Erste Klammer entfernen
    // Zahlen von jeder Zeile in Strings einlesen
    // Letzte Klammer finden und Funktion beenden
}

bool Textauswerter::detection_boxes()
{
    // Die Text-Datei erneuert öffnen
    QFile text (PFAD);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;

    // Den Cursor sozusagen auf die aktuelle Zeile bringen
    for (int n=0 ; n<anzGlsnZeilen ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}

    // Hier die gewünschten Daten einlesen
    // Erste Klammer entfernen
    // Zahlen von jeder Zeile in Strings einlesen
    // Letzte Klammer finden und Funktion beenden
}

Textauswerter::~Textauswerter()
{

}
