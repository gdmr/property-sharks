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
    // Utilizza std::dynamic_pointer_cast per convertire il puntatore smart a Proprietà
    std::shared_ptr<Proprieta> prop = std::dynamic_pointer_cast<Proprieta>(casella);
    
    if (prop) {  // Verifica che il cast sia andato a buon fine
        std::cout << "Proprietà" << std::endl;
        std::cout << prop->getTitolo() << "\n";

        if (prop->getProprietario() == "banca") {
            std::cout << "Questa proprietà appartiene alla banca, cosa vuoi fare?" << std::endl;
            std::cout << "Costo proprieta: "<< prop->getCosto() << std::endl;
            std::cout << "Tuo saldo: "<< g1.getSaldo() << std::endl;
            char inserito;
            std::cout << "a per acquistare, x per rifiutare" << std::endl;
            std::cin >> inserito;

            if (inserito == 'a') {
                g1.acquistaProprieta(*prop);
                std::cout << "proprietà acquistata" << std::endl;
                std::cout << "proprietario " << prop->getProprietario()<<std::endl;
                
                std::cout << "Tuo saldo aggiornato: "<< g1.getSaldo() << std::endl;
            }
        }}
    }
    else if (tipo == "Opportunita") {
        std::cout << "Opportunità" << std::endl;
    } else if (tipo == "Inconvenienti") {
        std::cout << "Inconvenienti" << std::endl;
    }else if (tipo == "Prigione") {
        std::cout << "Prigione" << std::endl;
    }  
    else {
        std::cout << "Caso non riconosciuto" << std::endl;
    }
  
    }



  }

void Gioco::gioca(){
    while (!fine) {
        eseguiTurno();}
}

