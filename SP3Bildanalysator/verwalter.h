#ifndef VERWALTER_H
#define VERWALTER_H

#include "ressourcen.h"

class Verwalter
{
public:
    Verwalter();

    void loescheAlt(void);
    void fuehreSkriptAus(void);
    void warte(int anzahl);
    const char* verarbeiteText(void);
};

#endif // VERWALTER_H
