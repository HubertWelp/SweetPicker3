#include "kamera.h"
#include <stdio.h>
#include <chrono>
#include <thread>

#define PWD "/home/Student/git/SweetPicker3/SP3Bildanalysator"
#define BILDABLAGE "/SP3Bilderkennung/aktuelleSzene.jpg"
#define TEXTABLAGE "/SP3Bilderkennung/gefundeneObjekte.txt"

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
            /* remove(PWD + BILDABLAGE);
               remove(PWD + TEXTABLAGE); */

            // aktuelles Bild aufnehmen und im folgenden relativen Verzeichnis ablegen
            c.nehmeAuf(BILDABLAGE);

            // Ein Python-Skript vom SP3Objekterkenner ausführen (python programmname TEXTABLAGE wahl)
            /* befehl = "python" + "programmname" + TEXTABLAGE + wahl + BILDABLAGE
               system(befehl); */

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
