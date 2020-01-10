#include "ressourcen.h"

#include "kamera.h"
#include "verwalter.h"

int main(int argc, char *argv[])
{
    int wahl;
    const char* antwort;

    // Erstellen von Objekten
    Kamera c(PWD);
    Verwalter v;

    while(1)
    {
        // Empfangen eines Zeichens (später hört es den UDP-Node ab und empfängt ein Zeichen)
        printf("\nGeben Sie 1,2,3 oder 4 für ein Bild / 0 zum Schließen\n");
        scanf("%i",&wahl);

        // Verarbeitung der Anfrage
        if(wahl == 1 || wahl == 2 || wahl == 3 || wahl == 4)
        {
            // altes Bild und alte Ergebnisse löschen
            v.loescheAlt();
            v.warte(2);

            // aktuelles Bild aufnehmen und im folgenden relativen Verzeichnis ablegen
            c.nehmeAuf(BILDABLAGE);

            // Ein Python-Skript vom SP3Objekterkenner ausführen (python programmname TEXTABLAGE wahl)
            v.fuehreSkriptAus();

            // warten, bis SP3Objektereknner fertig ist
            v.warte(2);

            // Erkennungsergebnis auslesen und auswerten
            antwort = v.verarbeiteText();

            // Informationen über Verfügbarkeit und Position der ausgewählten Süßigkeit an SP3Koordinator übergeben
            printf("\nSuche nach \"aktuell\" mit strstr(): %s, die Auswahl war %i\n",antwort,wahl);
        }

        // Beendung des Programms
        else if(wahl == 0)
        {
            break;
        }

        // Behandlung von ggf. Fehlermeldungen
        else if (wahl < 0)
        {
            printf("\n--------------------------\n");
            printf("          Oh Oh !         \n");
            printf("Ein Fehler ist aufgetreten\n");
            printf("--------------------------\n");
        }
    }
    return 0;
}
