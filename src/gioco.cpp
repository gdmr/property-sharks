#include "gioco.hpp"
#include "giocatore.hpp"
#include "tabellone.hpp"


Gioco::Gioco(){}
Gioco::~Gioco(){}
void Gioco::inizializza(){
tabellone.creaTabellone();
}