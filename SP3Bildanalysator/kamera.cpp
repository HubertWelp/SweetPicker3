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
    videostream.release();
}
/**
 * @brief Kamera::nehmeAufTest überspringt die Kamera und übergibt direkt ein Bild aus den Trainingsdaten. nur für Testzwecke.
 * @param pfad
 */
void Kamera::nehmeAufTest(const char *pfad)
{
    cv::String ziel = cv::String (pwd) + cv::String(pfad);
    bild = cv::imread("/home/Student/git/SP3/SweetPicker3/Trainingsdaten-bunt/2.jpg");
    if( !cv::imwrite(ziel,bild) )
    {
        printf("Bild konnte nicht am Ziel gespeichert werden\n");
    }
}
