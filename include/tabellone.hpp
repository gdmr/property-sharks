#include "tessera.hpp"
#include "proprieta.hpp"
#include "inconvenienti.hpp"
#include "opportunita.hpp"
#include <vector>
#pragma once

class Tabellone
{
private:
    std::vector<Tessera> caselle;
    std::vector<Inconvenienti> inconvenienti;
    std::vector<Opportunita> opportunita;
public:
    Tabellone();
    ~Tabellone();
    void creaTabellone();
    Tessera getTessera(int posizione);
    Inconvenienti getInconveniente();
    Opportunita getOpportunita();
};


