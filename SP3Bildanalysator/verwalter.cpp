#include "verwalter.h"

Verwalter::Verwalter()
{
    cam = new Kamera(PWD);
}

void Verwalter::loescheAlt()
{
    // Char-Array anlegen, um den Gesamtpfad zusammenzustellen
    char* pfad_dateien = (char *) malloc(100);

    // Das alte Bild löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,BILDABLAGE);     remove(pfad_dateien);

    // Die alten Ergebnisse löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,TEXTABLAGE);     remove(pfad_dateien);

    // Wartezeit
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Verwalter::fuehreSkriptAus()
{
    char* skript = (char *) malloc(300);

    strcpy(skript,"python");
    strcat(skript," ");
    strcat(skript,PROGNAME);
    strcat(skript," ");
    strcat(skript,PWD);
    strcat(skript,BILDABLAGE);
    strcat(skript," ");
    strcat(skript,PWD);
    strcat(skript,"/SP3Bilderkennung");


    // Ausgabe
    printf("\nIhr Skript sehe so aus: %s\n",skript);

    // Befehl absetzen
    system(skript);

    // Wartezeit
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void Verwalter::warte(int anzahl)
{
    for(int n=1 ; n<=anzahl ; n++)
    {
        // Abfrage, ob SP3Objekterkenner fertig ist
        printf("\n%i. Sekunde",n);

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

    printf("\nHabe %i empfangen\n",wahl);

    if(wahl == 1 || wahl == 2 || wahl == 3 || wahl == 4)
    {
        // altes Bild und alte Ergebnisse löschen
        loescheAlt();
        warte(2);

        // aktuelles Bild aufnehmen und im folgenden relativen Verzeichnis ablegen
        cam->nehmeAuf(BILDABLAGE);

        // Ein Python-Skript vom SP3Objekterkenner ausführen (python programmname TEXTABLAGE wahl)
        fuehreSkriptAus();

        // warten, bis SP3Objektereknner fertig ist
        warte(2);

        // Erkennungsergebnis auslesen und auswerten
        antwort = verarbeiteText();

        // Informationen über Verfügbarkeit und Position der ausgewählten Süßigkeit an SP3Koordinator übergeben
        printf("\nSuche nach \"aktuell\" mit strstr(): %s, die Auswahl war %i\n--------fetig!--------\n",antwort,wahl);

        std::string s1 = "x y z φ B ";
        std::string s2 = std::to_string(wahl);
        rueckmeldung = s1 + s2;

        sendmessage(rueckmeldung);
    }

    else if(wahl == 0)
    {
        // Beenden
    }
}
