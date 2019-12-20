#include "kamera.h"

Kamera::Kamera(char* pfad)
{
    pwd = pfad;
    videostream = cv::VideoCapture (0);
}

void Kamera::nehmeAuf(char* pfad)
{
    cv::String ziel = cv::String (pwd) + cv::String(pfad);
    videostream.read(bild);
    if( !cv::imwrite(ziel,bild) )
    {
        printf("\nFehler bei der Speicherung !\n");
    }
}
