#include "gioco.hpp"
#include "giocatore.hpp"
#include "tabellone.hpp"


Gioco::Gioco(Giocatore g1){
    giocatori.push_back(g1);
    tabellone.creaTabellone();
}
Gioco::~Gioco(){}
void Gioco::inizializza(){
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
    std::shared_ptr<Tessera> casella = tabellone.getTessera(g1.getPosizione());
    std::string tipo=casella->getTipo();
   if (tipo == "Proprieta") {
        std::cout << "Proprietà" << std::endl;
        std::cout<<casella->getTitolo()<<"\n";
    } else if (tipo == "Opportunita") {
        std::cout << "Opportunità" << std::endl;
    } else if (tipo == "Inconvenienti") {
        std::cout << "Inconvenienti" << std::endl;
    }else if (tipo == "Prigione") {
        std::cout << "Prigione" << std::endl;
    }  
    else {
        std::cout << "Caso non riconosciuto" << std::endl;
    }
    //std::cout<<p1.getTitolo()<<"\n";
    std::cout << "Cosa vuoi fare con questa proprietà? \n";
    //codice da implementare
  
    std::cout << "Posizione attuale: " <<g1.getPosizione() << "\n";
    }



  }

void Gioco::gioca(){
    while (!fine) {
        eseguiTurno();}
}

