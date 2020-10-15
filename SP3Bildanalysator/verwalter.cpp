#include "verwalter.h"

Verwalter::Verwalter()
{
    cam = new Kamera(PWD);
    textAuswerter = new Textauswerter;
    node = new UDPNode(5840);
}

void Verwalter::loescheAlt()
{
    // Char-Array anlegen, um den Gesamtpfad zusammenzustellen
    char* pfad_dateien = (char *) malloc(100);

    // Die alte Fotoaufnahme löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,BILDABLAGE);   strcat(pfad_dateien,BILD);     remove(pfad_dateien);

    // Das alte Erkennungsbild löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,BILDABLAGE);   strcat(pfad_dateien,ERKNT);     remove(pfad_dateien);

    // Die alten Ergebnisse löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,TEXTABLAGE);     remove(pfad_dateien);
}

void Verwalter::fuehreSkriptAus()
{
    node->sendmessage("run","127.0.0.1",5850);
}

bool Verwalter::warte()
{
    int i;
    QString pfad = QString(PWD);
    pfad.append(QString(TEXTABLAGE));

    QFile datei (pfad);

    for(i=0 ; (i<19)&&(datei.open(QIODevice::ReadOnly)==false) ; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    if ((i==19)&&(datei.open(QIODevice::ReadOnly)==false))
    {
        return false;
    }
    else
    {
        datei.close();
        return true;
    }
}

const char* Verwalter::verarbeiteText(void)
{
    FILE* datei;
    char inhalt[500];
    char* pfad = (char *) malloc(100);

    strcpy(pfad,PWD);
    strcat(pfad,TEXTABLAGE);

    datei = fopen(pfad,"r");
    if (!datei) printf("\n---------------\nFehler beim Öffnen der Textdatei\n---------------\n");

    fgets(inhalt,90,datei);
    return  strstr(inhalt,"aktuell");
}

void Verwalter::messageReceived(std::string msg)
{
    wahl = atoi(msg.c_str());

    if(wahl == Sorten::Maoam || wahl == Sorten::Snickers || wahl == Sorten::Milkyway || wahl == Sorten::Schokoriegel)
    {
        // altes Bild und alte Ergebnisse löschen
        loescheAlt();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // aktuelles Bild aufnehmen und im folgenden relativen Verzeichnis ablegen
        char* pfad = (char *) malloc(200);
        strcpy(pfad,BILDABLAGE);
        strcat(pfad,BILD);
        cam->nehmeAuf(pfad);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Ein Python-Skript vom SP3Objekterkenner ausführen (python programmname TEXTABLAGE wahl)
        fuehreSkriptAus();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // warten, bis SP3Objektereknner fertig ist
        if(warte())
        {
            // Erkennungsergebnis einlesen und auswerten
            if(textAuswerter->liesEin(QString(PWD)+QString(TEXTABLAGE))==3)
            {
                ergKoordinaten = textAuswerter->werteAus(wahl);

                std::string ergebnis = std::to_string(ergKoordinaten.x) + " " + std::to_string(ergKoordinaten.y) + " " + std::to_string(ergKoordinaten.z) + " p b";

                printf("\n%s\n",ergebnis.c_str());
                sendmessage(ergebnis,"127.0.0.1",5843);
            }
        }
    }

    else if(wahl == 0)
    {
        loescheAlt();
        node->sendmessage("stop","127.0.0.1",5850);
        QApplication::quit();
    }

    else {}
}
