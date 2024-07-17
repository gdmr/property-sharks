#include "giocatore.hpp"

Giocatore::Giocatore(std::string nome, int saldo){
    this->nome=nome;
    this->saldo=saldo;
}
Giocatore::~Giocatore(){}

void Giocatore::modificaSaldo(int soldi){
    saldo+=soldi;
}

void Giocatore::muoviGiocatore(int numeroCaselle){

}

void Giocatore::acquistaProprieta(Proprieta proprieta){
    proprieta.setProprietario(nome);
    saldo= saldo - proprieta.getCosto();
}

void Giocatore::pagaAffitto(Giocatore proprietario, int importo){
    proprietario.modificaSaldo(importo);
    modificaSaldo(-importo);
}

int Giocatore::getSaldo(){
    return saldo;
}