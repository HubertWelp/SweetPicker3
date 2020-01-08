#include "kamera.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string.h>

#define PWD "/home/Student/git/SweetPicker3/SP3Bildanalysator"
#define BILDABLAGE "/SP3Bilderkennung/aktuelleSzene.jpg"
#define TEXTABLAGE "/SP3Bilderkennung/gefundeneObjekte.txt"
#define PROGNAME "objekterkennen.py"

void fuehreSkriptAus(int sorte);
void loescheAlt(void);

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

            // aktuelles Bild aufnehmen und im folgenden relativen Verzeichnis ablegen
            c.nehmeAuf(BILDABLAGE);

            // Ein Python-Skript vom SP3Objekterkenner ausführen (python programmname TEXTABLAGE wahl)
            fuehreSkriptAus(wahl);

            // warten, bis SP3Objektereknner fertig ist
            for(int n=1 ; n<6 ; n++)
            {
                // Abfrage, ob SP3Objekterkenner fertig ist
                printf("\n%i. Sekunde",n);

                // wenn keine Textdatei voranden ist, führt es diese Wartefunktion aus
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            // Erkennungsergebnis auslesen und auswerten

            // Informationen zur Verfügbarkeit und Position der ausgewählten Süßigkeit an SP3Koordinator geben

        }

        else if(wahl == 0)
        break;
    }
    return 0;
}

void fuehreSkriptAus(int sorte)
{
    char* skript = (char *) malloc(200);
    char zahl[1]; zahl[0] = sorte + 48;
    //             6     +       20       + 48  +     35     +  1   +    38
    // befehl = "python" + "programmname" + PWD + TEXTABLAGE + wahl + BILDABLAGE

    strcpy(skript,"python");
    strcat(skript," ");
    strcat(skript,PROGNAME);
    strcat(skript," ");
    strcat(skript,PWD);
    strcat(skript," ");
    strcat(skript,TEXTABLAGE);
    strcat(skript," ");
    strcat(skript,zahl);
    strcat(skript," ");
    strcat(skript,BILDABLAGE);

    // Ausgabe
    printf("\nIhr Skript sehe so aus: %s\n",skript);

    // Befehl absetzen
    //system(skript);

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
