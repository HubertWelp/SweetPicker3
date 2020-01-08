#include "kamera.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int wahl;

    // Erstellen eines Objekts
    Kamera c("/home/Student/git/SweetPicker3/SP3Bildanalysator");

    while(1)
    {
        // Empfangen eines Zeichens (später hört es den UDP-Node ab und empfängt ein Zeichen)
        printf("\nGeben Sie 1,2,3 oder 4 für ein Bild / 0 zum Schließen\n");
        scanf("%i",&wahl);

        // Auswertung der Eingabe
        if(wahl == 1 || wahl == 2 || wahl == 3 || wahl == 4)
        {
            c.nehmeAuf("/SP3Bilderkennung/aktuelleSzene.jpg");
        }

        else if(wahl == 0)
        break;
    }
    return 0;
}
