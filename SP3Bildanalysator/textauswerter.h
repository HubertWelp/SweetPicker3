#ifndef TEXTAUSWERTER_H
#define TEXTAUSWERTER_H

#include "ressourcen.h"

class Textauswerter
{

public:
    Textauswerter();
    int liesEin(QString datei);
    Punkt werteAus(int wk);
    bool detection_classes(QString datei, int aktlZeile);
    bool detection_scores(QString datei, int aktlZeile);
    bool detection_boxes(QString datei, int aktlZeile);
    ~Textauswerter();

private:
    int ergK[ANZELEMENT];
    double ergW[ANZELEMENT];
    RBox ergB[ANZELEMENT];
    int anzGlsnZeilen;
};

#endif // TEXTAUSWERTER_H
