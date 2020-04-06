#include "textauswerter.h"

/**
* Konstruktor
*/
Textauswerter::Textauswerter(QWidget *parent)
    : QWidget(parent)
{

}

/**
* Diese Funktion liest den Text von der Text-Datei ein und benutzt dafür die Funktionen:
* {@link detection_classes}, {@link detection_scores} und {@link detection_boxes}
*
* @version 1.0
* @return die Anzahl der erfolgreich o.g. aufgrufenen Funktionen
*/
int Textauswerter::liesEin()
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
            QMessageBox::information(this,"detection_classes","Klassen werden eingelesen");
            if (detection_classes(anzGlsnZeilen)) erfolgreich++;
        }
        else if (string.contains(DSCORE,Qt::CaseInsensitive))
        {
            QMessageBox::information(this,"detection_scores","Erkennungsraten werden eingelesen");
            if (detection_scores(anzGlsnZeilen)) erfolgreich++;
        }
        else if (string.contains(DBOX,Qt::CaseInsensitive))
        {
            QMessageBox::information(this,"detection_boxes","Boxen werden eingelesen");
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
* Diese Funktion sucht im Member-Array der Klassen nach der gewünschten Klasse und ermittelt den Index der Klasse mit der höchsten Wahrscheinlichkeit.
* Dann werden die Koordinaten dieser Klasse zurückgegeben.
*
* @version 1.0
* @param wk [in] die gewünschte/gesuchte Klasse
* @return die Koordinaten der gewünschten/gesuchten Klasse
*/
RBox Textauswerter::werteAus(int wk)
{
    int m[ANZSUCHE];    // Index-Array der Klassen
    int ki;     // Zähler-Variable für das Klassen-Array
    int mi=0;   // enthält die Anzahl der vorhandenen Klassen
    int ziel;   // Der Index mit der größten Möglichkeit

    // Die Indexe der gesuchten Klasse aussuchen und in m[] einschreiben
    for (ki=0 ; ki<ANZELEMENT ; ki++ )
    {
        if (ergK[ki] == wk && mi<ANZSUCHE-1)
        {
            m[mi] = ki;
            QMessageBox::information(this,"werteAus","m[" + QString::number(mi) + "] = " + QString::number(ki));
            mi++;
        }
    }

    // Den Index mit der höchstmöglichen Wahrscheinlichkeit ermitteln
    ziel = m[0];
    for (int i=1 ; i<mi ; i++ )
    {
        if(ergW[m[i]] > ergW[ziel])
        {
            ziel = m[i];
        }
    }
    QMessageBox::information(this,"werteAus","Index " + QString::number(ziel) + " hat die größte Wahrscheinlichkeit: " + QString::number(ergW[ziel]));

    // Die Koordinaten der am besten passenden Klasse zurückgeben
    return ergB[ziel];
}

/**
* Diese Funktion sucht nach dem Schlüsselwort "detection_classes" in der Text-Datei und liest die Zahlen danach ein.
* Diese Zahlen stellen die Klassen der Erennungsergebnisse dar und werden in Arrays gespeichert dann entsprechend später bearbeitet.
*
* @version 1.0
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
    int element=0,laenge,anzZeichen;

    // Den Cursor auf die aktuelle Zeile setzen
    for (int n=0 ; n<aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}
//    QMessageBox::information(this,QString(DCLASS) + " starten","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");

    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;

        // Ausgabe des Inhalts der aktuellen Zeile
//        QMessageBox::information(this,QString(DCLASS) + " Zeile" + QString::number(aktlZeile),linie);

        // Die Anzahl der Vorhandenen Elemente im String sowie die String-Länge ermitteln (Anzahl der Leerzeichen + 1)
        anzZeichen = linie.count(QChar(' ')) + 1 ;
        laenge = linie.size();

        // Die Zahlen (Klassen) in das Array ergK[] einschreiben
        for (int i=0 ; i<laenge ; i++)
        {
            if(linie.at(i).isDigit())
            {
                ergK[element] = linie.at(i).digitValue();
//                QMessageBox::information(this,"Elemente einlesen","ergK[" + QString::number(element) + "] = " + QString::number(ergK[element]));
                element++;
            }
        }
    }
    while(!linie.contains("]"));

    // Die Text-Datei schließen
//    QMessageBox::information(this,QString(DCLASS) + " beenden","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");
    text.close();

    // Rückgabe
    return true;
}

/**
* Diese Funktion sucht nach dem Schlüsselwort "detection_scores" in der Text-Datei und liest die Zahlen danach ein.
* Diese Zahlen stellen die Erkennungsrate der gefundenen Klassen dar und werden in Arrays gespeichert dann entsprechend später bearbeitet.
*
* @version 1.0
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
    int cursor=0,laenge=10,anzZeichen,anzZeilen=0;

    // Den Cursor auf die aktuelle Zeile bringen
    for (int n=0 ; n<aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}
//    QMessageBox::information(this,QString(DSCORE) + " starten","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");

    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;

        // Ausgabe des Inhalts der aktuellen Zeile
//        QMessageBox::information(this,QString(DSCORE) + " Zeile" + QString::number(aktlZeile),linie);

        // Die Anzahl der Vorhandenen Elemente im String ermitteln (Anzahl der Punkte)
        anzZeichen = linie.count('.');

        // Die Zahlen (Erkennungsraten) in das Array ergW[] einschreiben
        for (int i=0 ; i<anzZeichen ; i++)
        {
            cursor = linie.indexOf('.') - 1;
            ergW[i+anzZeilen] = linie.mid(cursor,laenge).toDouble();
//            QMessageBox::information(this,"Elemente einlesen","ergW[" + QString::number(i+anzZeilen) + "] = " + QString::number(ergW[i+anzZeilen]));
            linie = linie.mid(laenge);
        }

        // Variable zur Erhöhung der Anzahl des Indexes beim Einlesen neuer Zeilen
        anzZeilen = anzZeilen + anzZeichen;
    }
    while(!linie.contains("]"));

    // Die Text-Datei schließen
//    QMessageBox::information(this,QString(DSCORE) + " beenden","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");
    text.close();

    // Rückgabe
    return true;
}

/**
* Diese Funktion sucht nach dem Schlüsselwort "detection_boxes" in der Text-Datei und liest die Koordinaten danach ein.
* Diese Koordinaten formen eine Box und werden in Arrays gespeichert.
*
* @version 1.0
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
    int cursor=0,laenge=10,anzZeilen=0,anzZeichen=4;

    // Den Cursor auf die aktuelle Zeile bringen
    for (int n=0 ; n<aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}
//    QMessageBox::information(this,QString(DBOX) + " starten","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");

    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;

        // Ausgabe des Inhalts der aktuellen Zeile
//        QMessageBox::information(this,QString(DBOX) + " Zeile" + QString::number(aktlZeile),linie);

        // Die Zahlen (Koordinaten) in das Array ergB[] einschreiben
        for (int i=0 ; i<anzZeichen ; i++)
        {
            cursor = linie.indexOf('.') - 1;
            if (i==0)
            {
                ergB[anzZeilen].a = linie.mid(cursor,laenge).toDouble();
//                QMessageBox::information(this,"Elemente einlesen","ergB[" + QString::number(anzZeilen) + "].a = " + QString::number(ergB[anzZeilen].a));
            }
            else if (i==1)
            {
                ergB[anzZeilen].b = linie.mid(cursor,laenge).toDouble();
//                QMessageBox::information(this,"Elemente einlesen","ergB[" + QString::number(anzZeilen) + "].b = " + QString::number(ergB[anzZeilen].b));
            }
            else if (i==2)
            {
                ergB[anzZeilen].c = linie.mid(cursor,laenge).toDouble();
//                QMessageBox::information(this,"Elemente einlesen","ergB[" + QString::number(anzZeilen) + "].c = " + QString::number(ergB[anzZeilen].c));
            }
            else if (i==3)
            {
                ergB[anzZeilen].d = linie.mid(cursor,laenge).toDouble();
//                QMessageBox::information(this,"Elemente einlesen","ergB[" + QString::number(anzZeilen) + "].d = " + QString::number(ergB[anzZeilen].d));
            }
            linie = linie.mid(laenge);
        }

        // Variable zur Erhöhung der Anzahl des Indexes beim Einlesen neuer Zeilen
        anzZeilen++;;
    }
    while(!linie.contains("]]"));

    // Die Text-Datei schließen
//    QMessageBox::information(this,QString(DBOX) + " beenden","Ich stehe jetzt in der " + QString::number(aktlZeile) + ".ten Zeile");
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
