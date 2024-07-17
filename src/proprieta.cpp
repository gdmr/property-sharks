#include "proprieta.hpp"

Proprieta::Proprieta(std::string nome, int costoProprieta, int costoCasa, int costoAlbergo){
    setTitolo(nome);
    this->costoProprieta=costoProprieta;
    this->costoCasa=costoCasa;
    this->costoAlbergo=costoAlbergo;
}

Proprieta::~Proprieta(){}


void Proprieta::aggiungiCasa(){
    if(!albergo){
        numCase++;
    }
   
}

void Proprieta::costruisciAlbergo(){
  if (numCase == 4) {
            albergo = true;
            numCase = 0;
        }
}


int Proprieta::calcolaPagamento() {
        if (albergo) {
            return costoAlbergo*3;
        }
        return numCase * costoCasa;
}

int Proprieta::getCosto(){
    return costoProprieta;
}

  // Operatore di uguaglianza
bool Proprieta::operator==(Proprieta other) {
    return getTitolo() == other.getTitolo();
}

 // Operatore di uguaglianza per confrontare Proprieta con std::string (titolo)
bool Proprieta::operator==(std::string titolo) {
        return getTitolo() == titolo;
    }