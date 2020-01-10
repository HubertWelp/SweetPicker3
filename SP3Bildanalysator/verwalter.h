#ifndef VERWALTER_H
#define VERWALTER_H

#include "ressourcen.h"

#include "udpnode.hpp"

class Verwalter : public UDPNode
{
public:
    Verwalter();

    void loescheAlt(void);
    void fuehreSkriptAus(void);
    void warte(int anzahl);
    const char* verarbeiteText(void);

    void messageReceived(std::string msg) override;
};

#endif // VERWALTER_H
