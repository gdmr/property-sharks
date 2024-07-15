#include "banca.hpp"

Banca::Banca(){}
Banca::~Banca(){}

void Banca::pagaGiocatore(Giocatore g, int importo){
    g.modificaSaldo(importo);
}

void Banca::riscuotiDaGiocatore(Giocatore g, int importo){
    g.modificaSaldo(importo);
    //saldo alla banca
}

//g1 è quello che guadagna
void Banca::trasferisciSoldi(Giocatore g1, Giocatore g2, int importo){
    g1.modificaSaldo(importo);
    g2.modificaSaldo(-importo);
}