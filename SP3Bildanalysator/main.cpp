#include "kamera.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string.h>

#define PWD "/home/Student/git/SweetPicker3/SP3Bildanalysator"
#define BILDABLAGE "/SP3Bilderkennung/aktuelleSzene.jpg"
#define TEXTABLAGE "/SP3Bilderkennung/gefundeneObjekte.txt"
#define PROGNAME "/home/Student/git/SweetPicker3/SP3Objekterkenner/SP3Objekterkenner.py"

void fuehreSkriptAus(void);
void loescheAlt(void);
void warte(int anzahl);

int main(int argc, char *argv[])
{
    int wahl;

    // Erstellen eines Objekts
    Kamera c(PWD);

    while(1)
    {
        // Empfangen eines Zeichens (später hört es den UDP-Node ab und empfängt ein Zeichen)
        printf("\nGeben Sie 1,2,3 oder 4 für ein Bild / 0 zum Schließen\n");
        scanf("%i",&wahl);

        // Auswertung der Eingabe
        if(wahl == 1 || wahl == 2 || wahl == 3 || wahl == 4)
        {
            // altes Bild und alte Ergebnisse löschen
            loescheAlt();
            warte(2);

            // aktuelles Bild aufnehmen und im folgenden relativen Verzeichnis ablegen
            c.nehmeAuf(BILDABLAGE);

            // Ein Python-Skript vom SP3Objekterkenner ausführen (python programmname TEXTABLAGE wahl)
            fuehreSkriptAus();

            // warten, bis SP3Objektereknner fertig ist
            warte(2);

            // Erkennungsergebnis auslesen und auswerten

            // Informationen über Verfügbarkeit und Position der ausgewählten Süßigkeit an SP3Koordinator übergeben

        }

        else if(wahl == 0)
        break;
    }
    return 0;
}

void fuehreSkriptAus(void)
{
    char* skript = (char *) malloc(300);
    //             6     +       20       +     83     +     83
    // befehl = "python" + "programmname" + BILDABLAGE + TEXTABLAGE

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
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void loescheAlt(void)
{
    // Char-Array anlegen, um den Gesamtpfad zusammenzustellen
    char* pfad_dateien = (char *) malloc(100);

    // Das alte Bild löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,BILDABLAGE);     remove(pfad_dateien);

    // Die alten Ergebnisse löschen
    strcpy(pfad_dateien,PWD);    strcat(pfad_dateien,TEXTABLAGE);     remove(pfad_dateien);

    // Wartezeit
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void warte(int anzahl)
{
    for(int n=1 ; n<=anzahl ; n++)
    {
        // Abfrage, ob SP3Objekterkenner fertig ist
        printf("\n%i. Sekunde",n);

        // wenn keine Textdatei voranden ist, führt es diese Wartefunktion aus
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
