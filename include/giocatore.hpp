#include <string>
#include <iostream>
#include "proprieta.hpp"
#pragma once

class Giocatore
{
private:
std::string nome;
int saldo;


public:
    Giocatore(std::string nome, int saldo);
    ~Giocatore();
    void modificaSaldo(int soldi);
    void muoviGiocatore(int numeroCaselle); 
    void acquistaProprieta(Proprieta proprieta);
    void pagaAffitto(Giocatore proprietario, int importo);
    int getSaldo();
};

