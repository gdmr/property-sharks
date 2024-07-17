#include "gioco.hpp"
#include "giocatore.hpp"
#include "tabellone.hpp"


Gioco::Gioco(){}
Gioco::~Gioco(){}
void Gioco::inizializza(){
tabellone.creaTabellone();
}
std::vector<Giocatore> Gioco::getListaGiocatori(){
    return giocatori;
}