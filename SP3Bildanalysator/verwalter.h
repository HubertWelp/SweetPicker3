#ifndef VERWALTER_H
#define VERWALTER_H

#include "ressourcen.h"
#include "udpnode.hpp"
#include "kamera.h"
#include "textauswerter.h"
#include "orientierungsermittler.h"

class Verwalter : public UDPNode
{
public:
    Verwalter();

    void loescheAlt(void);
    void fuehreSkriptAus(void);
    bool warte();
    const char* verarbeiteText(void);
    void messageReceived(std::string msg) override;
    int wahl;
    const char* antwort;
    void testTextauswerter();
private:

    Kamera* cam;
    std::string rueckmeldung;
    Textauswerter* textAuswerter;
    OrientierungsErmittler* orientierungsErmittler;
    UDPNode* node;
    double yMin, xMin, yMax, xMax, xMittelpunkt, yMittelpunkt, winkel, breite;
    int erfolg;
    Konfig* konfig;
};

#endif // VERWALTER_H
