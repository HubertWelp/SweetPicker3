#ifndef KONFIG_H
#define KONFIG_H

#include <QSettings>                // Für das Speichern und Laden der konfig.ini Datei
#include <QColor>                   //RGB string (such as "#112233")
#include <QStandardPaths>           // Für Standardspeicherpfad von konfig.ini


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

    /** @brief Stellt den Speicherort der verwendeten Dateien zur Verfügung
    *
    * Diese Methode liest die konfig.ini Datei ein und stellt den Speicherort der von SP3Admin, SP3Bildanalysator und SP3Objekterkenner genutzen Dateien aus.
    * Der Speicherort wird als Absoluter Pfad in der Konfig.ini  gespeichert und endet ohne einem "/".
    *
    * @return  Gibt den Speicherort als Zeichenfolge aus. Falls das Auslesen nicht erfolgreich ist, wird das Standardpasswort "SP3" ausgegeben. Der Pfad endet ohne "/".
    */
    QString getAblageort();

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

    /** @brief Gibt die Breite eines Objekts
    *
    * Diese Methode erwartet eine Objektnummer als Eingabeparameter und übersetzt diese mit Hilfe der
    * konfig.ini Datei in eine dazugehörige Objektbreite und gibt diesen als Rückgabewert aus.
    * Falls die Objektnummer nicht existiert, gibt die Methode die Breite -1 als Rückgabewert aus.
    *
    * @return  Gibt den Wert Objektbreite aus. Falls das Auslesen nicht erfolgreich ist, wird -1 ausgegeben.
    */
    float getObjektbreite(int nr);

    /** @brief Gibt den Kameraparameter Bildbreite aus
    *
    * Diese Methode gibt den momentan gespeicherten Wert "Bildbreite" aus der konfig.ini Datei aus.
    *
    * @return  Gibt den Wert Bildbreite aus. Falls das Auslesen nicht erfolgreich ist, wird -1 ausgegeben.
    */
    int getBildbreite();

    /** @brief Gibt den Analyseparameter Kameraparameter Bildhöhe aus
    *
    * Diese Methode gibt den momentan gespeicherten Wert "Bildhoehe" aus der konfig.ini Datei aus.
    *
    * @return  Gibt den Wert Bildhoehe aus. Falls das Auslesen nicht erfolgreich ist, wird -1 ausgegeben.
    */
    int getBildhoehe();

    /** @brief Gibt die einzustellende Rahendicke aus
    *
    * Diese Methode gibt den momentan gespeicherten Wert der Rahmendicke, mit der der Rahmen des erkannten Objekts gezeichnet werden soll, aus der konfig.ini Datei aus.
    *
    * @return  Gibt den Wert "Rahmendicke" aus. Falls das Auslesen nicht erfolgreich ist, wird -1 ausgegeben.
    */
    int getRahmendicke();

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

    /** @brief Speichert eine übergebene Rahmendicke in die konfig.ini Datei
    *
    * Diese Methode speichert die übergebene Rahmendicke in der konfig.ini Datei unter dem Schlüssel "Rahmendicke" ab.
    *
    * @param [in] input ganzzahliger positiver Wert
    *
    * @return   0, wenn erfolgreich
    *           -1, wenn nicht erfolgreich
    *
    */
    int setRahmendicke(int input);

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

    /** @brief Speichert den übegebenen Wert Bildbreite ab.
    *
    * Diese Methode speichert den übergebenen Wert in der konfig.ini Datei unter dem Schlüssel "Bildbreite" ab.
    *
    * @param [in] input ganzzahliger positiver Wert
    *
    * @return   0, wenn erfolgreich
    *           -1, wenn nicht erfolgreich
    *
    */
    int setBildbreite(int input);

    /** @brief Speichert den übergebenen Wert Bildhöhe ab.
    *
    * Diese Methode speichert den übergebenen Wert in der konfig.ini Datei unter dem Schlüsel "Bildhoehe" ab.
    *
    * @param [in] inout ganzzahliger positiver Wert
    *
    * @return   0, wenn erfolgreich
    *           -1, wenn nicht erfolgreich
    *
    */
    int setBildhoehe(int input);

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
