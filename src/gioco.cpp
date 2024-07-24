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
    Giocatore& g1 = giocatori.back();
    if(g1.getGiorniDiPrigione()<1){
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
        std::shared_ptr<Opportunita> opp = std::dynamic_pointer_cast<Opportunita>(casella);
        if (opp) {  // Verifica che il cast sia andato a buon fine
            std::cout << "Opportunità" << std::endl;
            Opportunita o1=opp->pescaCarta();
            std::cout <<o1.getTitolo() << "\n";
            g1.opportunita(o1);
        }
    } else if (tipo == "Inconvenienti") {
         std::shared_ptr<Inconvenienti> inco = std::dynamic_pointer_cast<Inconvenienti>(casella);
        if (inco) {  // Verifica che il cast sia andato a buon fine
            std::cout << "Inconveninti" << std::endl;
            Inconvenienti i1=inco->pescaCarta();
            std::cout <<i1.getTitolo() << "\n";
            g1.inconveniente(i1);
            
        }
    }else if (tipo == "Prigione") {
         std::shared_ptr<Prigione> prig = std::dynamic_pointer_cast<Prigione>(casella);
        if (prig) {  // Verifica che il cast sia andato a buon fine
            std::cout << "Prigione" << std::endl;
            std::cout << prig->getTitolo() << "\n";
            g1.vaiInPrigione();
        }
    }  
    else {
        std::cout << "Caso non riconosciuto" << std::endl;
    }
  
    }

    }else
    std::cout << "Sei in prigione per questo turno" << std::endl;
    g1.scontaGiornoDiPrigione();




  }

void Gioco::gioca(){
    while (!fine) {
        eseguiTurno();}
}

