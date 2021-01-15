#include "textauswerter.h"
using std::cout;
using std::endl;

/**
* Konstruktor
*/
Textauswerter::Textauswerter()
{

}

/**
* Diese Funktion liest den Text von der Text-Datei ein und benutzt dafür die Funktionen:
* {@link detection_classes}, {@link detection_scores} und {@link detection_boxes}
*
* @version 1.0
* @return die Anzahl der erfolgreich o.g. aufgrufenen Funktionen
*/
int Textauswerter::liesEin(QString datei)
{
    QFile text (datei);

    if(!text.open(QIODevice::ReadOnly))
    {
        printf("\nDatei könnte nicht geöffnet werden !");
    }

    QTextStream datenstrom(&text);
    QString string;

    //ermittle Anzahl der Zeilen in Datei
    anzMaxZeilen = 0;
    std::ifstream inFile(datei.toStdString());
    anzMaxZeilen = std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(),'\n');
    anzGlsnZeilen = 0;
    int erfolgreich = 0;

    while(datenstrom.readLineInto(&string,MAXLESEN))
    {
        anzGlsnZeilen++;
        if(anzGlsnZeilen > anzMaxZeilen+1)
        {
            text.close();
            return erfolgreich;
        }
        if (string.contains(DCLASS,Qt::CaseInsensitive))
        {
            //cout << "bin bei detection classes " << endl;
            if (detection_classes(datei,anzGlsnZeilen)) erfolgreich++;
            //cout << erfolgreich << endl;
        }
        else if (string.contains(DSCORE,Qt::CaseInsensitive))
        {
            //cout << "bin bei detection scores" << endl;
            if (detection_scores(datei,anzGlsnZeilen)) erfolgreich++;
            //cout << erfolgreich << endl;
        }
        else if (string.contains(DBOX,Qt::CaseInsensitive))
        {
            //cout << "bin bei detection boxes" << endl;
            if (detection_boxes(datei,anzGlsnZeilen)){ erfolgreich++;}
            //cout << endl << erfolgreich << endl;
        }
    }
    // Der Cursor steht am Ende der Datei
    text.close();
    //cout << "Ende loop" << endl;
    // Return-Bedingung
    return erfolgreich;
}

/**
* Diese Funktion sucht im Member-Array der Klassen nach der gewünschten Klasse und ermittelt den Index der Klasse mit der höchsten Wahrscheinlichkeit.
* Dann werden die Koordinaten dieser Klasse zurückgegeben.
*
* @version 1.0
* @param wk [in] die gewünschte/gesuchte Klasse
* @return die Koordinaten des Mittelpunktes der gewünschten/gesuchten Klasse
*/
Punkt Textauswerter::werteAus(int wk)
{
    int m[ANZSUCHE];    // Index-Array der Klassen
    int ki;     // Zähler-Variable für das Klassen-Array
    int mi=0;   // enthält die Anzahl der vorhandenen Klassen
    int ziel;   // Der Index mit der größten Möglichkeit

    // Die Indexe der gesuchten Klasse aussuchen und in m[] einschreiben
    for (ki=0 ; ki<ANZELEMENT ; ki++ )
    {
        if (ergK[ki] == wk && mi<ANZSUCHE)
        {
            m[mi] = ki;
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

    if(ziel<0 || ziel > sizeof(ergB))
    {
        return {-1, -1, -1};
    }

    // Die Koordinaten der am besten passenden Klasse zurückgeben
    Punkt erg;
    erg.x = ressourcen::BILDBRT * (ergB[ziel].b/2 + ergB[ziel].d/2 );
    erg.y = ressourcen::BILDHHE* ( ergB[ziel].a/2 + ergB[ziel].c/2 );
    erg.z = 0;
    return erg;
}

/**
* Diese Funktion sucht im Member-Array der Klassen nach der gewünschten Klasse und ermittelt den Index der Klasse mit der höchsten Wahrscheinlichkeit.
* Dann werden die Koordinaten dieser Klasse zurückgegeben.
*
* @version 1.0
* @param wk [in] die gewünschte/gesuchte Klasse
* @return die Eck-Koordinaten [ymin,xmin,ymax,xmax] der gewünschten/gesuchten Klasse
*/
Punkte Textauswerter::werteAus2(int wk)
{
    int m[ANZSUCHE];    // Index-Array der Klassen
    int ki;     // Zähler-Variable für das Klassen-Array
    int mi=0;   // enthält die Anzahl der vorhandenen Klassen
    int ziel;   // Der Index mit der größten Möglichkeit

    // Die Indexe der gesuchten Klasse aussuchen und in m[] einschreiben
    for (ki=0 ; ki<ANZELEMENT ; ki++ )
    {
        if (ergK[ki] == wk && mi<ANZSUCHE)
        {
            m[mi] = ki;
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
    if(ziel<0 || ziel > sizeof(ergB))
    {
        return {-1, -1, -1, -1};
    }


    //Die Koordinaten der am besten passenden Klasse zurückgeben [ymin,xmin,ymax,xmax]
    return {ergB[ziel].a, ergB[ziel].b, ergB[ziel].c, ergB[ziel].d};

}

/**
* Diese Funktion sucht im Member-Array der Klassen nach der gewünschten Klasse und ermittelt den Index der Klasse mit der höchsten Wahrscheinlichkeit.
* Dann werden die Koordinaten dieser Klasse zurückgegeben.
*
* @version 1.0
* @param wk [in] die gewünschte/gesuchte Klasse
* @return [ymin,xmin,ymax,xmax,xMittelpunkt,yMittelpunkt] - die Eck-Koordinaten [ymin,xmin,ymax,xmax]
* und den Mittelpunkt [xMittelpunkt,yMittelpunkt] der gewünschten/gesuchten Klasse
*/
std::tuple<double, double, double, double, double, double> Textauswerter::werteAus3(int wk)
{
    //cout << "werte aus 3" << endl;
    int m[ANZSUCHE];    // Index-Array der Klassen
    int ki;     // Zähler-Variable für das Klassen-Array
    int mi=0;   // enthält die Anzahl der vorhandenen Klassen
    int ziel;   // Der Index mit der größten Möglichkeit

    // Die Indexe der gesuchten Klasse aussuchen und in m[] einschreiben
    for (ki=0 ; ki<ANZELEMENT ; ki++ )
    {
        if (ergK[ki] == wk && mi<ANZSUCHE)
        {
            m[mi] = ki;
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

    if(ziel<0 || ziel > sizeof(ergB))
    {
        return std::make_tuple(-1, -1, -1, -1, -1, -1);
    }
    double ergX = ressourcen::BILDBRT * ( ergB[ziel].b/2 + ergB[ziel].d/2 );
    double ergY = ressourcen::BILDHHE * ( ergB[ziel].a/2 + ergB[ziel].c/2 );

    //Die Koordinaten der am besten passenden Klasse zurückgeben [ymin,xmin,ymax,xmax,xMittelpunkt,yMittelpunkt]
    return std::make_tuple(ergB[ziel].a, ergB[ziel].b, ergB[ziel].c, ergB[ziel].d, ergX, ergY);

}


/**
* Diese Funktion sucht nach dem Schlüsselwort "detection_classes" in der Text-Datei und liest die Zahlen danach ein.
* Diese Zahlen stellen die Klassen der Erkennungsergebnisse dar und werden in Arrays gespeichert dann entsprechend später bearbeitet.
*
* @version 1.0
* @param [in] aktlZeile hat die Zeilennummer, an der der Cursor in der Schleife in {@link werteAus} steht, so dass diese Funktion ab da weiter einliest.
* @return true, falls der Ablauf der Funktion reibungslos lief
*/
int Textauswerter::detection_classes(QString datei, int aktlZeile)
{
    // Die Text-Datei erneuert öffnen
    QFile text (datei);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;
    int element=0,laenge,anzZeichen;

    // Den Cursor auf die aktuelle Zeile setzen
    for (int n=0 ; n<aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}

    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;
        //cout << "detection classes Aktuelle Zeile " << aktlZeile << "/" << anzMaxZeilen << endl;
        if(aktlZeile > anzMaxZeilen+1)
        {
            //cout << "detection classes Fehler" << endl;
            text.close();
            return 0;
        }

        // Die Anzahl der Vorhandenen Elemente im String sowie die String-Länge ermitteln (Anzahl der Leerzeichen + 1)
        anzZeichen = linie.count(QChar(' ')) + 1 ;
        laenge = linie.size();

        // Die Zahlen (Klassen) in das Array ergK[] einschreiben
        for (int i=0 ; i<laenge ; i++)
        {
            if(linie.at(i).isDigit())
            {
                ergK[element] = linie.at(i).digitValue();
                element++;
            }
        }
    }
    while(!linie.contains("]"));

    // Die Text-Datei schließen
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
int Textauswerter::detection_scores(QString datei, int aktlZeile)
{
    // Die Text-Datei erneuert öffnen
    QFile text (datei);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;
    int cursor=0,laenge=10,anzZeichen,anzZeilen=0;
    // Den Cursor auf die aktuelle Zeile bringen
    for (int n = 0 ; n < aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}
    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;
        //cout << "detection scores Aktuelle Zeile " << aktlZeile << "/" << anzMaxZeilen << endl;
        if(aktlZeile > anzMaxZeilen+1)
        {
            //cout << "detection scores Fehler" << endl;
            text.close();
            return 0;
        }
        // Ausgabe des Inhalts der aktuellen Zeile

        // Die Anzahl der Vorhandenen Elemente im String ermitteln (Anzahl der Punkte)
        anzZeichen = linie.count('.');

        // Die Zahlen (Erkennungsraten) in das Array ergW[] einschreiben
        for (int i=0 ; i<anzZeichen ; i++)
        {
            cursor = linie.indexOf('.') - 1;
            ergW[i+anzZeilen] = linie.mid(cursor,laenge).toDouble();
            linie = linie.mid(laenge);
        }

        // Variable zur Erhöhung der Anzahl des Indexes beim Einlesen neuer Zeilen
        anzZeilen = anzZeilen + anzZeichen;
    }
    while(!linie.contains("]"));
    // Die Text-Datei schließen
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
int Textauswerter::detection_boxes(QString datei, int aktlZeile)
{
    // Die Text-Datei erneuert öffnen
    QFile text (datei);
    text.open(QIODevice::ReadOnly);
    QTextStream datenstrom(&text);
    QString linie;
    int cursor=0,laenge=10,anzZeilen=0,anzZeichen=4;

    // Den Cursor auf die aktuelle Zeile bringen
    for (int n=0 ; n<aktlZeile ; n++) {datenstrom.readLineInto(&linie,MAXLESEN);}
    // Hier die gewünschten Daten einlesen
    do
    {
        // Weitere Zeile einlesen
        datenstrom.readLineInto(&linie,MAXLESEN);
        aktlZeile++;
        //cout << "detection boxes Aktuelle Zeile " << aktlZeile << "/" << anzMaxZeilen << endl;
        if(aktlZeile > anzMaxZeilen+1)
        {
            //cout << "detection boxes Fehler" << endl;
            text.close();
            return 0;
        }
        // Ausgabe des Inhalts der aktuellen Zeile

        // Die Zahlen (Koordinaten) in das Array ergB[] einschreiben
        for (int i=0 ; i<anzZeichen ; i++)
        {
            cursor = linie.indexOf('.') - 1;
            if (i==0)
            {
                ergB[anzZeilen].a = linie.mid(cursor,laenge).toDouble();
            }
            else if (i==1)
            {
                ergB[anzZeilen].b = linie.mid(cursor,laenge).toDouble();
            }
            else if (i==2)
            {
                ergB[anzZeilen].c = linie.mid(cursor,laenge).toDouble();
            }
            else if (i==3)
            {
                ergB[anzZeilen].d = linie.mid(cursor,laenge).toDouble();
            }
            linie = linie.mid(laenge);
        }

        // Variable zur Erhöhung der Anzahl des Indexes beim Einlesen neuer Zeilen
        anzZeilen++;
    }
    while(!linie.contains("]]"));
    // Die Text-Datei schließen
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
