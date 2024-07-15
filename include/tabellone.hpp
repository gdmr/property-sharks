#include "tessera.hpp"
#include "proprieta.hpp"
#include "inconvenienti.hpp"
#include "opportunita.hpp"
#include <vector>
#pragma once

class Tabellone
{
private:
    std::vector<Proprieta> caselle;
    std::vector<Inconvenienti> inconvenienti;
    std::vector<Opportunita> opportunita;
public:
    Tabellone();
    ~Tabellone();
    void creaTabellone();
};


