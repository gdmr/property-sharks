#include "gioco.hpp"
#include "giocatore.hpp"
#include "tabellone.hpp"


Gioco::Gioco(Giocatore g1){
    giocatori.push_back(g1);
    tabellone.creaTabellone();
}
Gioco::~Gioco(){}
void Gioco::inizializza(){
//tabellone.creaTabellone();
}
std::vector<Giocatore> Gioco::getListaGiocatori(){
    return giocatori;
}

  void Gioco::eseguiTurno(){
    Giocatore &g1 = giocatori.back();
    std::cout << "d per lanciare il dado, x per passare il turno senza lanciare il dado \n";
    char inserito;
    int result;
    std::cin>>inserito;
    if(inserito=='d'){
    result = dadi.lanciaDadi();
    std::cout << "Risultato del lancio: "<< result <<"\n";
    g1.muoviGiocatore(result);
    Proprieta p1=tabellone.getProprieta(g1.getPosizione());
    std::cout<<p1.getTitolo()<<"\n";
    std::cout << "Cosa vuoi fare con questa proprietà? \n";
    //codice da implementare
  
    std::cout << "Posizione attuale: " <<g1.getPosizione() << "\n";
    }



  }

void Gioco::gioca(){
    while (!fine) {
        eseguiTurno();}
}

