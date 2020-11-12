#include "kamera.h"

Kamera::Kamera(const char* pfad)
{
    pwd = pfad;
    videostream = cv::VideoCapture (0); // 0 = standardkamera
    //videostream.set(CV_CAP_PROP_BUFFERSIZE, 1):


}

void Kamera::nehmeAuf(const char* pfad)
{
    // Das Zielpfad konstruieren
    cv::String ziel = cv::String (pwd) + cv::String(pfad);

    // Ein Bild mit der Kamera aufnehmen

    /** videostream.open() first calls videostream.release() **/
    if(!videostream.open(0))
    {
        printf("Kamera konnte nicht geoeffnet werden\n");
    }
    /** grabs, decodes and returns the next video frame **/
    if(!videostream.read(bild))
    {
        printf("Bild konnte nicht erfasst werden\n");
    }

    // Das Bild im angegebenen Pfad Speichern
    if( !cv::imwrite(ziel,bild) )
    {
        printf("Bild konnte nicht am Ziel gespeichert werden\n");
    }

    // Wartezeit, bis das Foto vollständig gespeichert ist
   // std::this_thread::sleep_for(std::chrono::milliseconds(100)); // ist das eig nötig? wenn imwrite "true" zurückgibt sollte das bild erfolgreich gespeichert sein
}
