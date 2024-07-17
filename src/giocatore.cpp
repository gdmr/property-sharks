#include "giocatore.hpp"
#include <algorithm>

Giocatore::Giocatore(std::string nome, int saldo) : nome(nome), saldo(saldo), proprietaPossedute(), posizione(1) {}
Giocatore::~Giocatore(){}

void Giocatore::modificaSaldo(int soldi){
    saldo+=soldi;
}

void Giocatore::muoviGiocatore(int lancio){
     posizione += lancio;
    if (posizione > 16) {
        posizione = (posizione % 16);
        if (posizione == 0) {
            posizione = 16;
        }
    }
}

void Giocatore::acquistaProprieta(Proprieta proprieta){
    proprieta.setProprietario(nome);
    saldo= saldo - proprieta.getCosto();
    proprietaPossedute.push_back(proprieta);
    
}

void Giocatore::vendiProprieta(Proprieta proprieta, Giocatore acquirente){
    std::string rimuovi=proprieta.getTitolo();
    //for (int i = 0; i < proprietaPossedute.size(); i++)
    auto it = std::find(proprietaPossedute.begin(), 
                 proprietaPossedute.end(), rimuovi);
    if (it != proprietaPossedute.end()) 
  {
    std::cout << "Element " << rimuovi << " found at position : ";
    std::cout << it - proprietaPossedute.begin() << 
                 " (counting from zero) \n";
    proprietaPossedute.erase(it);
  }
  else{
    std::cout << "Element not found.\n\n";
  }
    proprieta.setProprietario(acquirente.nome);
    saldo= saldo + proprieta.getCosto();
}

void Giocatore::pagaAffitto(Giocatore proprietario, int importo){
    proprietario.modificaSaldo(importo);
    modificaSaldo(-importo);
}

int Giocatore::getSaldo() const{
    return saldo;
}

int Giocatore::getPosizione() const{
    return posizione;
}

std::vector<Proprieta> Giocatore::getProprietaPossedute(){
    return proprietaPossedute;
}