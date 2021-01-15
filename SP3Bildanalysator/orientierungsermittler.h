#ifndef ORIENTIERUNGSERMITTLER_H
#define ORIENTIERUNGSERMITTLER_H

#include "ressourcen.h"

class OrientierungsErmittler
{
public:
    /**
     * @brief OrientierungsErmittler
     * @param morphOpenSize Stärke der Morph Operation "Open", welche eine Kombination aus der Morph Operation "Erode" und "Dilate" sind.
     */
    OrientierungsErmittler(unsigned short morphOpenSize = 6);

    /**
     * @brief setzeKoordinaten Methode zum setzen der Koordinaten, welche dem Rahmen entsprechen worin das gewünschte Objekt sich befindet
     * @param yMin Y-Koordinate (oben links)
     * @param xMin X-Koordinate (oben links)
     * @param yMax Höhe (unten links)
     * @param xMax Breite (oben rechts
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    int setzeKoordinaten(double yMin, double xMin, double yMax, double xMax);

    /**
     * @brief setzeBildPfad Methode zum ändern des zu verwendenen Bildpfades, falls es nicht am Standardort liegt.
     * @param pfad - Pfad für das Bild, welches zur Orientierungsermittlung verwendet werden soll (Absoluter Pfad inklusive Dateiname). Wenn ein Leerer String ("") übergeben wird, wird der Standardpfad wiederhergestellt
     * @return 0 = wenn ein Bild am angegebenen Pfad gelesen werden kann, -1 = wenn kein Bild am angegebenen Pfad gelesen werden kann
     */
    inline int setzeBildPfad(const std::string &pfad = "");

    inline int ladeParameter();

    /**
     * @brief ermittleOrientierung Methode zur Ermittlung der Orientierung. Zuvor muss der Rahmen, worin das gewünschte Objekt sich befindet,
     * mit {@link setzeKoordinaten} festgelegt werden und der Pfad des Bildes, falls diese nicht im Standardverzeichnis ist, mit {@link ladeBild}
     * angegeben werden.
     * Bevor die Orientierung ermittelt wird, wird zuerst {@link ausschnittROI} und {@link bearbeiteBild} ausgeführt.
     * @see setzeKoordinaten()
     * @see ladeBild()
     * @see ausschnittROI()
     * @see bearbeiteBild()
     * @return < 0,x,y> =>  0 = Methode erfolgreich ausgeführt, x = Winkel in °Grad, y = Breite in Meter.
     *         <-1,x,y> => -1 = Methode unerfolgreich ausgeführt.
     */
    std::tuple<int, double, double> ermittleOrientierung();

    /**
     * @brief setzeRahmen beeinflusst die Farbe und Dicke des Rahmens in AktuelleSzeneRahmen.jpg
     * @param farbe im QColor Format
     * @param dicke
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    int setzeRahmen(QColor farbe, unsigned int dicke);

    /**
     * @brief setzeRahmen beeinflusst die Farbe und Dicke des Rahmens in AktuelleSzeneRahmen.jpg
     * @param farbe im cv::Scalar Format
     * @param dicke
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    int setzeRahmen(cv::Scalar farbe, unsigned int dicke);

    /**
     * @brief setzeRahmenFarbe beeinflusst die Farbe des Rahmens in AktuelleSzeneRahmen.jpg
     * @param farbe im QColor Format
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    int setzeRahmenFarbe(QColor farbe);

    /**
     * @brief setzeRahmenFarbe beeinflusst die Farbe des Rahmens in AktuelleSzeneRahmen.jpg
     * @param farbe cv::Scalar Format
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    int setzeRahmenFarbe(cv::Scalar farbe);

    /**
     * @brief setzeRahmenDicke beeinflusst die Dicke des Rahmens in AktuelleSzeneRahmen.jpg
     * @param dicke
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    int setzeRahmenDicke(unsigned int dicke);

    /**
     * @brief getRahmenFarbeQColor
     * @return die Farbe des Rahmens in AktuelleSzeneRahmen.jpg im QColor Format
     */
    QColor getRahmenFarbeQColor();

    /**
     * @brief getRahmenFarbeCVScalar
     * @return die Farbe des Rahmens in AktuelleSzeneRahmen.jpg im CVScalar Format
     */
    cv::Scalar getRahmenFarbeCVScalar();

    /**
     * @brief getRahmenDicke
     * @return die Dicke des Rahmens in AktuelleSzeneRahmen.jpg
     */
    unsigned int getRahmenDicke();
    void setzeWahl(int wahl);

    ~OrientierungsErmittler();

private:
    /**
     * @brief ladeBild eine optionale Methode zum Angeben eines alternativen
     * @param pfad
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    inline int ladeBild();

    /**
     * @brief ausschnittPOI erzeugt einen Ausschnitt
     * @return
     */
    int ausschnittROI();

    /**
     * @brief bearbeiteBild
     * @return
     */
    int bearbeiteBild();

    /**
     * @brief drawAxis
     * @param img
     * @param p
     * @param q
     * @param colour
     * @param scale
     */
    void drawAxis(cv::Mat &img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale);

    /**
     * @brief drawBreite
     * @param img
     * @param p
     * @param q
     * @param colour
     * @param scale
     */
    void drawBreite(cv::Mat &img, cv::Point p, cv::Scalar colour, std::vector<std::vector<cv::Point>> contours, size_t secondlargestAreaIDX);

    /**
     * @brief qColor2CVScalar wandelt QColor in cv::Scalar um
     * @param color QColor was umgewandelt werden soll
     * @return cv::Scalar Format
     */
    cv::Scalar qColor2CVScalar(QColor color);

    /**
     * @brief cvScalar2QColor wandelt cv::Scalar in QColor um
     * @param color cv::Scalar was umgewandelt werden soll
     * @return QColor Format
     */
    QColor cvScalar2QColor(cv::Scalar color);



    cv::Size morphOpenSize;
    double xMin, xMax, yMin, yMax;
    int wahl;
    std::string bildPfad;
    cv::Mat bildInput, bildAusschnitt, bildAusschnitGraustufe, bildAusschnittSchwarzWeiss, bildAusschnittSchwarzWeissBearbeitet,bildAktuelleSzeneRahmen;
    //cv::Mat bildAusschnittBreit, bildAusschnittSchwarzWeissBreit, bildAusschnittSchwarzWeissBearbeitetBreit;
    cv::Point center;
    cv::Rect bildInputROI;
    cv::Scalar rahmenFarbe;
    unsigned int rahmenDicke;
    Konfig* konfig;

};

#endif // ORIENTIERUNGSERMITTLER_H
