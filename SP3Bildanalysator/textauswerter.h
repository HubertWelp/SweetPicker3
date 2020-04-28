#ifndef TEXTAUSWERTER_H
#define TEXTAUSWERTER_H

#include "ressourcen.h"

class Textauswerter
{

public:
    Textauswerter();
    int liesEin();
    Punkt werteAus(int wk);
    bool detection_classes(int aktlZeile);
    bool detection_scores(int aktlZeile);
    bool detection_boxes(int aktlZeile);
    ~Textauswerter();

private:
    int ergK[ANZELEMENT];
    double ergW[ANZELEMENT];
    RBox ergB[ANZELEMENT];
    int anzGlsnZeilen;
};

#endif // TEXTAUSWERTER_H
