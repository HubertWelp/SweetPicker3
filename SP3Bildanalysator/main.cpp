#include "kamera.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    Kamera c("/home/Student/git/SweetPicker3/SP3Bildanalysator");

    printf("\nDrücken Sie f für ein Bild / c zum Schließen\n");

    while(1)
    {
        char ant;
        scanf("%c",&ant);

        if(ant == 'f')
        {
            c.nehmeAuf("/SP3Bilderkennung/aktuelleSzene.jpg");
        }

        else if(ant == 'c')
        break;

    }
    return 0;
}
