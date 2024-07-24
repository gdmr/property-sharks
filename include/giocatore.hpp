#include <string>
#include <iostream>
#include <vector>
#include "proprieta.hpp"
#include "inconvenienti.hpp"
#include "opportunita.hpp"
#pragma once

class Giocatore
{
private:
std::string nome;
int saldo;
std::vector<Proprieta> proprietaPossedute;
int posizione;
int turniDaSaltare;
bool bonus;
bool bot; 


public:
    Giocatore(std::string nome, int saldo, bool bot);
    ~Giocatore();
    void modificaSaldo(int soldi);
    void muoviGiocatore(int lancio); 
    void acquistaProprieta(Proprieta& proprieta);
    void vendiProprieta(Proprieta proprieta, Giocatore acquirente);
    void pagaAffitto(Giocatore proprietario, int importo);
    int getSaldo() const;
    int getPosizione() const;
    std::vector<Proprieta> getProprietaPossedute();
    void vaiInPrigione();
    bool isBot();
    void inconveniente(Inconvenienti inconveniente);
    void opportunita(Opportunita opportunita);
    void attivaBonus();
    void disattivaBonus();
    bool isBonusAttivo();
    int getGiorniDiPrigione();
    void scontaGiornoDiPrigione();
};

