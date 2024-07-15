#include "tessera.hpp"
#include "proprieta.hpp"
#include <vector>
#pragma once

class Tabellone
{
private:
    std::vector<Proprieta> caselle;
    std::vector<Tessera> inconvenienti;
    std::vector<Tessera> opportunita;
public:
    Tabellone();
    ~Tabellone();
    void creaTabellone();
};


