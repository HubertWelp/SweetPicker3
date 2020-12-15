#ifndef BILDERVERWALTER_H
#define BILDERVERWALTER_H

#include <QImage>
#include <QPixmap>

/** @class Bilderverwalter
 * @brief
 *
 *
 * @author Lars Jepkens
 *
 */
class Bilderverwalter
{
public:
    /** @brief construktor
    *
    * Erstellt ein Objekt der Klasse und lädt die Bilder in den Speicher.
    *
    */
    Bilderverwalter(QString pfad="");

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

private:
    QString dateipfad;
    QImage AktuelleSzene;
    QImage AktuelleSzeneRahmen;
    QImage Ausschnitt;
    QImage AusschnittSW;
    QImage AusschnittSWprocessed;
    QImage AusschnittErgebnis;

};

#endif // BILDERVERWALTER_H
