#include <string>
#include <iostream>
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
    
};

