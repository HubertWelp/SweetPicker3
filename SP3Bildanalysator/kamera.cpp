#include "kamera.h"

Kamera::Kamera(const char* pfad)
{
    pwd = pfad;
    id = 0;
    videostream = cv::VideoCapture (id); // 0 = standardkamera
}
/**
 * @brief Kamera::nehmeAuf
 * @param pfad
 * @return < 0 wenn nicht erfolgreich. = 0 wenn erfolgreich
 */
int Kamera::nehmeAuf(const char* pfad)
{
    // Das Zielpfad konstruieren
    cv::String ziel = cv::String (pwd) + cv::String(pfad);

    // Ein Bild mit der Kamera aufnehmen
    /** videostream.open() first calls videostream.release() **/
    if(!videostream.open(id))
    {
        printf("Kamera konnte nicht geoeffnet werden\n");
        return -1;
    }
    /** grabs, decodes and returns the next video frame **/
    if(!videostream.read(bild))
    {
        printf("Bild konnte nicht erfasst werden\n");
        return -2;
    }
    // Das Bild im angegebenen Pfad Speichern
    if( !cv::imwrite(ziel,bild) )
    {
        printf("Bild konnte nicht am Ziel gespeichert werden\n");
        return -3;
    }
    videostream.release();
    return 0;
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
/**
 * @brief Kamera::setzeKameraID Methode zum Kamera ändern. Wenn die angegebene ID zu keiner Kamera führt wird die ID verworfen und die vorherige ID weiter verwendet.
 * @param idnew - neue Kamera ID
 * @return < 0 wenn nicht erfolgreich. = 0 wenn erfolgreich.
 */
int Kamera::setzeKameraID(int idnew)
{
    if(!videostream.open(idnew))
    {
        std::cout << idnew << " ist keine gültige Kamera" << std::endl;
        return -1;
    }
    else
    {
        /*Erzeuge neue Kamera mit neuer ID*/
        videostream.~VideoCapture();
        videostream = cv::VideoCapture (idnew);
        id = idnew;
        return 0;
    }
}
