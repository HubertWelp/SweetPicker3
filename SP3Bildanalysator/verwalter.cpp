#include "verwalter.h"

Verwalter::Verwalter()
{

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
