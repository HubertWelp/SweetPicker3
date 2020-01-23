#include "kamera.h"

Kamera::Kamera(const char* pfad)
{
    pwd = pfad;
    videostream = cv::VideoCapture (0);
}

void Kamera::nehmeAuf(const char* pfad)
{
    // Das Zielpfad konstruieren
    cv::String ziel = cv::String (pwd) + cv::String(pfad);

    // Ein Bild mit der Kamera aufnehmen
    videostream.read(bild);

    // Das bunte Bild in ein Schwarz-Weiß-Bild umwandeln
    cv::cvtColor(bild,bild,cv::COLOR_BGR2GRAY);

    // Den Kontrast des Bildes auf 1.3 erhöhen
    bild.convertTo(bild,-1,1.3,0);

    // Das Bild runterskalieren
    cv::resize(bild,bild,cv::Size(320,240));

    // Das Bild im angegebenen Pfad Speichern
    if( !cv::imwrite(ziel,bild) )
    {
        printf("\nFehler bei der Speicherung !\n");
    }
}
