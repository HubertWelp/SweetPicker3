#include "kamera.h"

Kamera::Kamera(const char* pfad)
{
    pwd = pfad;
    videostream = cv::VideoCapture (0);
}

void Kamera::nehmeAuf(const char* pfad)
{
    cv::String ziel = cv::String (pwd) + cv::String(pfad);
    videostream.read(bild);
    if( !cv::imwrite(ziel,bild) )
    {
        printf("\nFehler bei der Speicherung !\n");
    }
}
