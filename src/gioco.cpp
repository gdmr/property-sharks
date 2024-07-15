#include "gioco.hpp"
#include "giocatore.hpp"
#include "tabellone.hpp"
#define caselle 16
#define inco 0
#define oppo 0

Gioco::Gioco(){}
Gioco::~Gioco(){}
void Gioco::inizializza(){
tabellone.creaTabellone(caselle, inco, oppo);
}