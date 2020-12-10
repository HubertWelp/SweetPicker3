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
     * @brief ladeBild eine optionale Methode zum Angeben eines alternativen Pfades für das Bild, welches zur Orientierungsermittlung verwendet werden soll
     * @param pfad
     * @return 0 = Methode erfolgreich ausgeführt, -1 = Methode unerfolgreich ausgeführt
     */
    inline int ladeBild(const std::string &pfad);


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

    ~OrientierungsErmittler();

private:
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
    void drawAxis(cv::Mat& img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale = 0.2);
    cv::Size morphOpenSize;
    double xMin, xMax, yMin, yMax;
    std::string bildPfad;
    cv::Mat bildInput, bildAusschnitt, bildAusschnittSchwarzWeiss, bildAusschnittSchwarzWeissBearbeitet;
    //cv::Mat bildAusschnitGraustufe;
    cv::Point center;

};

#endif // ORIENTIERUNGSERMITTLER_H
