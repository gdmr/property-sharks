#include "prigione.hpp"
#include "giocatore.hpp"

Prigione::Prigione(std::string nome, int giorni) {
    setTitolo(nome);
    setGIorniDiPrigione(giorni);
};
Prigione::~Prigione(){};

void Prigione::setGIorniDiPrigione(int giorni){
    this->giorniDiPrigione=giorni;
}
int Prigione::getGIorniDiPrigione(){
    return giorniDiPrigione;
}

void Prigione::vaiInPrigione(Giocatore g1){
    g1.vaiInPrigione();
}