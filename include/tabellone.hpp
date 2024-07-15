#include "tessera.hpp"
#include <vector>
#define totcaselle 16;
#pragma once

class Tabellone
{
private:
    std::vector<Tessera> caselle;
    std::vector<Tessera> inconvenienti;
    std::vector<Tessera> opportunità;
public:
    Tabellone();
    ~Tabellone();
};


