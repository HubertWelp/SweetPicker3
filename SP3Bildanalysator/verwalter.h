#ifndef VERWALTER_H
#define VERWALTER_H

#include "ressourcen.h"
#include "udpnode.hpp"
#include "kamera.h"
#include "textauswerter.h"

class Verwalter : public UDPNode
{
public:
    Verwalter();

    void loescheAlt(void);
    void fuehreSkriptAus(void);
    void warte(int anzahl);
    const char* verarbeiteText(void);

    void messageReceived(std::string msg) override;

    int wahl;
    const char* antwort;

private:
    Kamera* cam;
    std::string rueckmeldung;
    Textauswerter* textAuswerter;
    Punkt ergKoordinaten;
};

#endif // VERWALTER_H
