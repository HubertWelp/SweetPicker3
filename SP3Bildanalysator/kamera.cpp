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

    // Das Bild im angegebenen Pfad Speichern
    if( !cv::imwrite(ziel,bild) )
    {
        printf("\nFehler bei der Speicherung !\n");
    }

    // Wartezeit, bis das Foto vollständig gespeichert ist
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
