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

    // Das alte Bild löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,BILDABLAGE);   strcat(pfad_dateien,BILD);     remove(pfad_dateien);

    // Die alten Ergebnisse löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,TEXTABLAGE);     remove(pfad_dateien);

    // Wartezeit
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Verwalter::fuehreSkriptAus()
{
//    char* skript = (char *) malloc(300);
//    strcpy(skript,"python");
//    strcat(skript," ");
//    strcat(skript,PROGNAME);
//    strcat(skript," ");
//    strcat(skript,PWD);
//    strcat(skript,BILDABLAGE);
//    strcat(skript," ");
//    strcat(skript,BILD);

    // Ausgabe
//    printf("\nIhr Skript sehe so aus: %s",skript);

    // Umgebung aktivieren
//    char* befehl = (char *) malloc(500);
//    strcpy(befehl,"gnome-terminal --command=");
//    strcat(befehl,"\"");
//    strcat(befehl,skript);
//    strcat(befehl,"\"");

    // Befehl absetzen
//    system(befehl);
    node->sendmessage("run","127.0.0.1",5850);
}

void Verwalter::warte(QString prozess, int anzahl)
{
    for(int n=1 ; n<=anzahl ; n++)
    {
        // Abfrage, ob SP3Objekterkenner fertig ist
        printf("\n%s: %i. Sekunde",prozess.toLatin1().data(),n);

        // wenn keine Textdatei voranden ist, führt es diese Wartefunktion aus
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

//    printf("\nHabe %i empfangen\n",wahl);

    if(wahl == Sorten::Maoam || wahl == Sorten::Snickers || wahl == Sorten::Milkyway || wahl == Sorten::Schokoriegel)
    {
        // altes Bild und alte Ergebnisse löschen
        loescheAlt();
//        warte("Alte Dateien Loeschen", 2);

        // aktuelles Bild aufnehmen und im folgenden relativen Verzeichnis ablegen
        char* pfad = (char *) malloc(200);
        strcpy(pfad,BILDABLAGE);
        strcat(pfad,BILD);
        cam->nehmeAuf(pfad);

        // Ein Python-Skript vom SP3Objekterkenner ausführen (python programmname TEXTABLAGE wahl)
        fuehreSkriptAus();

        // warten, bis SP3Objektereknner fertig ist
        warte("Warten auf SP3Objekterkenner", 4);

        // Erkennungsergebnis einlesen und auswerten
        textAuswerter->liesEin(QString(PWD)+QString(TEXTABLAGE));
        ergKoordinaten = textAuswerter->werteAus(wahl);

        std::string ergebnis = std::to_string(ergKoordinaten.x) + " " + std::to_string(ergKoordinaten.y) + " " + std::to_string(ergKoordinaten.z) + " p b";

        printf("\n%s\n",ergebnis.c_str());
        sendmessage(ergebnis);
    }

    else if(wahl == 0)
    {
        QApplication::quit();
    }
}
