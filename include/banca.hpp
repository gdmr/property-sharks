#include <string>
#include <vector>
#include "giocatore.hpp"
#pragma once


class Banca
{
private:

public:
    Banca();
    ~Banca();
    void pagaGiocatore(Giocatore giocatore, int importo);
    void riscuotiDaGiocatore(Giocatore giocatore, int importo);
    void trasferisciSoldi(Giocatore giocatore1, Giocatore giocatore2, int importo);

};