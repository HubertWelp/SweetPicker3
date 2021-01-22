#ifndef OBJEKTINFORMATION_H
#define OBJEKTINFORMATION_H


#include <QImage>
#include <QPixmap>
#include <QImageReader>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "konfig.h"
//#include <QStringList>



/** @class Objektinformation
 * @brief
 *
 *
 * @author Lars Jepkens
 *
 */
class Objektinformation
{
public:
    /** @brief construktor
    *
    * Erstellt ein Objekt der Klasse und lädt die Bilder in den Speicher.
    *
    */
    Objektinformation();

    /** @brief Setzt den Dateipfad für die Bildablage
    *
    * @return void
    */
    void setBildablage(QString pfad);

    /** @brief Aktualisiert die geladenen Bilder des Objekts
    *
    * @return  Gibt 0 zurück, wenn das Laden erfolgreich ist. Gibt -1 zurück, wenn nicht erfolgreich.
    */
    int aktualisieren();

    /** @brief Stellt das momentan geladenen Bild AktuelleSzene zur Verfügung
    *
    * @return  Gibt ein Bild im Format QImage aus. Falls kein Bild geladen ist, wird ein Nullpointer zurückgegeben.
    */
    QImage getAktuelleSzene();

    /** @brief Stellt das momentan geladenen Bild AktuelleSzeneRahmen zur Verfügung
    *
    * @return  Gibt ein Bild im Format QImage aus. Falls kein Bild geladen ist, wird ein Nullpointer zurückgegeben.
    */
    QImage getAktuelleSzeneRahmen();

    /** @brief Stellt das momentan geladenen Bild Ausschnitt zur Verfügung
    *
    * @return  Gibt ein Bild im Format QImage aus. Falls kein Bild geladen ist, wird ein Nullpointer zurückgegeben.
    */
    QImage getAusschnitt();

    /** @brief Stellt das momentan geladenen Bild AusschnittSW zur Verfügung
    *
    * @return  Gibt ein Bild im Format QImage aus. Falls kein Bild geladen ist, wird ein Nullpointer zurückgegeben.
    */
    QImage getAusschnittSW();

    /** @brief Stellt das momentan geladenen Bild AusschnittSWprocessed zur Verfügung
    *
    * @return  Gibt ein Bild im Format QImage aus. Falls kein Bild geladen ist, wird ein Nullpointer zurückgegeben.
    */
    QImage getAusschnittSWprocessed();

    /** @brief Stellt das momentan geladenen Bild AusschnittErgebnis zur Verfügung
    *
    * @return  Gibt ein Bild im Format QImage aus. Falls kein Bild geladen ist, wird ein Nullpointer zurückgegeben.
    */
    QImage getAusschnittErgebnis();

    /** @brief Stellt die momentan geladene angeforderte Objektnummer zur Verfügung
    *
    * @return  Gibt die Objektnummer des angeforderten Objekts aus
    */
    QString getAngefordertesObjekt();

    /** @brief Stellt den momentan geladene Richtung des Objekts in Grad zur Verfügung
    *
    * @return  Gibt einen Winkel in  Grad aus
    */
    float getWinkel();

    /** @brief Stellt den momentan geladene Breite des Objekts Meter zur Verfügung
    *
    * @return  Gibt eine Breite in Meter aus
    */
    float getBreite();

    /** @brief Stellt den momentan geladene x-Position des Objekts in Meter zur Verfügung
    *
    * @return  Gibt eine Länge der x-Position in Meter aus
    */
    float getXPosi();

    /** @brief Stellt den momentan geladene y-Position des Objekts in Meter zur Verfügung
    *
    * @return  Gibt eine Länge der y-Position in Meter aus
    */
    float getYPosi();

private:
    Konfig k;
    QString bildablage;
    QImage AktuelleSzene;
    QImage AktuelleSzeneRahmen;
    QImage Ausschnitt;
    QImage AusschnittSW;
    QImage AusschnittSWprocessed;
    QImage AusschnittErgebnis;
    QString name;
    float winkel;
    float breite;
    float xposi;
    float yposi;
};

#endif // OBJEKTINFORMATION_H
