#ifndef ORIENTIERUNGSERMITTLER_H
#define ORIENTIERUNGSERMITTLER_H

#include "ressourcen.h"
/**
 * @brief OrientierungsErmittler
 * @author Sahin Cosgun
 */
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
     * @brief ermittleOrientierung Methode zur Ermittlung der Orientierung. Zuvor muss der Rahmen, worin das gewünschte Objekt sich befindet,
     * mit {@link setzeKoordinaten} festgelegt werden und der Pfad des Bildes, falls diese nicht im Standardverzeichnis ist, mit {@link ladeBild}
     * angegeben werden.
     * Bevor die Orientierung ermittelt wird, wird zuerst {@link ausschnittROI} und {@link bearbeiteBild} ausgeführt.
     * @see setzeKoordinaten()
     * @see ladeBild()
     * @see ausschnittROI()
     * @see bearbeiteBild()
     * @return < 0,x,y> =>  0 = Methode erfolgreich ausgeführt, x = Winkel in °Grad, y = Breite in Milimeter.
     *         <<0,x,y> => -1 = Methode unerfolgreich ausgeführt.
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
     * @brief ausschnittPOI erzeugt einen Ausschnitt -> ausschnittSW.jpg
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    int ausschnittROI();

    /**
     * @brief bearbeiteBild denoised das SW Bild -> ausschnittSWprocessed.jpg
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    int bearbeiteBild();

    /**
     * @brief drawAxis zeichnet einen Pfeil welches den Winkel der Kontur entspricht
     * @param img das Bild worin gezeichnet werden soll
     * @param p Startpunkt des Pfeils (Mittelpunkt)
     * @param q
     * @param colour Farbe
     * @param scale längen skalierung
     */
    void drawAxis(cv::Mat &img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale);

    /**
     * @brief drawBreiteKontur zeichnet die Breite der Kontur ein
     * @param img das Bild worin gezeichnet werden soll
     * @param p Startpunkt des Pfeils (Mittelpunkt)
     * @param colour Farbe
     * @param contours zu verwendene Konturliste
     * @param idx Index der Kontur, welche Kontur verwendet werden soll
     */
    void drawBreiteKontur(cv::Mat &img, cv::Point p, cv::Scalar colour, std::vector<std::vector<cv::Point>> contours, size_t idx);

    /**
     * @brief drawBreite zeichnet die Breite aus der konfig.ini von Mittelpunkt ausgehend aus ein
     * @param img das Bild worin gezeichnet werden soll
     * @param p Startpunkt des Pfeils (Mittelpunkt)
     * @param colour Farbe
     * @param contours zu verwendene Konturliste
     * @param idx Index der Kontur, welche Kontur verwendet werden soll
     */
    void drawBreite(cv::Mat &img, cv::Point p, cv::Scalar colour, std::vector<std::vector<cv::Point>> contours, size_t idx);

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
    //  cv::Mat bildAusschnittBreit, bildAusschnittSchwarzWeissBreit, bildAusschnittSchwarzWeissBearbeitetBreit;
    cv::Point center;
    cv::Rect bildInputROI;
    cv::Scalar rahmenFarbe;
    unsigned int rahmenDicke;
    Konfig* konfig;

};

#endif // ORIENTIERUNGSERMITTLER_H
