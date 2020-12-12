#ifndef TEXTAUSWERTER_H
#define TEXTAUSWERTER_H

#include "ressourcen.h"
#include <tuple>

class Textauswerter
{

public:
    Textauswerter();
    int liesEin(QString datei);
    Punkt werteAus(int wk);
    Punkte werteAus2(int wk);
    std::tuple<double, double, double, double, double, double> werteAus3(int wk);
    int detection_classes(QString datei, int aktlZeile);
    int detection_scores(QString datei, int aktlZeile);
    int detection_boxes(QString datei, int aktlZeile);
    ~Textauswerter();

private:
    int ergK[ANZELEMENT];
    double ergW[ANZELEMENT];
    RBox ergB[ANZELEMENT];
    int anzGlsnZeilen, anzMaxZeilen;
};

#endif // TEXTAUSWERTER_H
