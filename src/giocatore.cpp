#include <iostream>
#include <string>
#include "giocatore.hpp"

Giocatore::Giocatore(std::string nome, int saldo){
    this->nome=nome;
    this->saldo=saldo;
}
Giocatore::~Giocatore(){
}