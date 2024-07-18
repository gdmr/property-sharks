#include <string>
#include <iostream>
#include <vector>
#include "proprieta.hpp"
#pragma once

class Giocatore
{
private:
std::string nome;
int saldo;
std::vector<Proprieta> proprietaPossedute;
int posizione;
int turniDaSaltare;


public:
    Giocatore(std::string nome, int saldo);
    ~Giocatore();
    void modificaSaldo(int soldi);
    void muoviGiocatore(int lancio); 
    void acquistaProprieta(Proprieta proprieta);
    void vendiProprieta(Proprieta proprieta, Giocatore acquirente);
    void pagaAffitto(Giocatore proprietario, int importo);
    int getSaldo() const;
    int getPosizione() const;
    std::vector<Proprieta> getProprietaPossedute();
    void vaiInPrigione();
};

