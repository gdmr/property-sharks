#include "tessera.hpp"
#include "proprieta.hpp"
#include "inconvenienti.hpp"
#include "opportunita.hpp"
#include "prigione.hpp"
#include <vector>
#pragma once

class Tabellone
{
private:
    std::vector<std::shared_ptr<Tessera>> caselle;
    //std::vector<Tessera> caselle;
    std::vector<Inconvenienti> inconvenienti;
    std::vector<Opportunita> opportunita;
    std::vector<Prigione> prigione;
public:
    Tabellone();
    ~Tabellone();
    void creaTabellone();
    std::shared_ptr<Tessera> Tabellone::getTessera(int posizione);
    Inconvenienti getInconveniente();
    Opportunita getOpportunita();
};


