#ifndef KONFIG_H
#define KONFIG_H

#include <QSettings>              // Für das Speichern und Laden der konfig.ini Datei
#include <QColor>                 //RGB string (such as "#112233")
#include <QStandardPaths>


/** @class Konfig
 * @brief
 *
 *
 * @author Lars Jepkens
 *
 */
class Konfig
{
public:
    /** @brief construktor
    *
    * Erstellt ein Objekt der Klasse.
    *
    */
    Konfig(QString pfad = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)+"/"+"konfig.ini");

    /** @brief Gibt Name eines Objekts aus
    *
    * Diese Methode erwartet eine Objektnummer als Eingabeparameter und übersetzt diese mit Hilfe der
    * konfig.ini Datei in einen dazugehörigen Objektnamen und gibt diesen als Rückgabewert aus.
    * Falls die Objektnummer nicht existiert, gibt die Methode einen leeren Objektnamen ("") als Rückgabewert aus.
    *
    *
    * @param [in] nr Nummer des Objektes,
    *
    * @return  Liefert den Namen des Objektes mit der jeweiligen Objektnummer, falls es einen Objektnamen zu dieser Objektnummer gibt
    *          Falls es zu der Objektnummer keinen Objektnamen gibt, wird ein Leerstring ("") zurückgegeben.
    *
    */
    QString getObjektname(int nr);

    /** @brief Gibt den Analyseparameter Erode aus
    *
    * Diese Methode gibt den momentan gespeicherten Wert "Erode" aus der konfig.ini Datei aus.
    *
    * @return  Gibt den Wert Erode aus. Falls das Auslesen nicht erfolgreich ist, wird -1 ausgegeben.
    */
    int getErode();

    /** @brief Gibt den Analyseparameter Dillate aus
    *
    * Diese Methode gibt den momentan gespeicherten Wert "Dillate" aus der konfig.ini Datei aus.
    *
    * @return  Gibt den Wert Dillate aus. Falls das Auslesen nicht erfolgreich ist, wird -1 ausgegeben.
    */
    int getDillate();

    /** @brief Gibt eine Farbe aus
    *
    * Diese Methode gibt den momentan gespeicherten Wert der Rahmenfarbe aus der konfig.ini Datei aus.
    *
    * @return  Gibt den Wert "rahmenfarbe" aus. Falls das Auslesen nicht erfolgreich ist, wird Schwarz als Farbe ausgegeben.
    */
    QColor getRahmenfarbe();

    /** @brief Gibt eine KameraID aus
    *
    * Diese Methode gibt die momentan gespeicherte KemaraID aus der konfig.ini Datei aus.
    *
    * @return  Gibt eine Zahl als KameraID aus. Fall das Auslesen nicht erfolgreich ist, wird -1 ausgegeben.
    */
    int getKameraID();


protected:
    QString dateipfad;
private:

};

/** @class KofigAdmin
 * @brief
 *
 *
 * @author Lars Jepkens
 *
 */
class KonfigAdmin: public Konfig
{
public:
    /** @brief construktor
    *
    * Erstellt ein Objekt der Klasse.
    *
    */
    KonfigAdmin(QString pfad = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)+"/"+"konfig.ini");

    /** @brief Stellt das gespeicherte Passwort zur Verfügung
    *
    * Diese Methode liest die konfig.ini Datei ein und stellt das in ihr gespeicherte Passwort zur Verfügung
    *
    * @return  Gibt das Passwort als Zeichenfolge aus. Falls das Auslesen nicht erfolgreich ist, wird das Standardpasswort "SP3" ausgegeben
    */
    QString getPasswort();

    /** @brief Speichert eine übergebene Farbe in die konfig.ini Datei
    *
    * Diese Methode speichert die übergebene Farbe in der konfig.ini Datei unter dem Schlüssel "Boxfarbe" ab.
    *
    * @param [in] farbe Eine Farbe aus dem normalen Farbspektrum im Format QColor
    *
    * @return   0, wenn erfolgreich
    *           -1, wenn nicht erfolgreich
    *
    */
    int setRahmenfarbe(QColor farbe=QColor::fromRgb(127,255,0));

    /** @brief Speichert den übegebenen Wert Erdoe ab.
    *
    * Diese Methode speichert den übergebenen Wert in der konfig.ini Datei unter dem Schlüssel "Erode" ab.
    *
    * @param [in] input ganzzahliger positiver Wert
    *
    * @return   0, wenn erfolgreich
    *           -1, wenn nicht erfolgreich
    *
    */
    int setErode(int input);

    /** @brief Speichert den übergebenen Wert Dillate ab.
    *
    * Diese Methode speichert den übergebenen Wert in der konfig.ini Datei unter dem Schlüsel "Dillate" ab.
    *
    * @param [in] inout ganzzahliger positiver Wert
    *
    * @return   0, wenn erfolgreich
    *           -1, wenn nicht erfolgreich
    *
    */
    int setDillate(int input);

    /** @brief Speichert den übergebenen Wert KarmeraID ab.
    *
    * Diese Methode speichert den übergebenen Wert in der konfig.ini Datei unter dem Schlüssel "KameraID" ab.
    *
    * @param [in] input ganzzahliger positiver Wert
    *
    * @return   0, wenn erfolgreich
    *           -1, wenn nicht erfolgreich
    *
    */
    int setKameraID(int input);

private:

};


#endif // KONFIG_H
