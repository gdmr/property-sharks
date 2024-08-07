#include "giocatore.hpp"
#include <algorithm>

Giocatore::Giocatore(std::string nome, int saldo, bool bot) : nome(nome), saldo(saldo), proprietaPossedute(), posizione(0), turniDaSaltare(0), bonus(false), bot(bot)   {}
Giocatore::~Giocatore(){}

void Giocatore::modificaSaldo(int soldi){
    saldo+=soldi;
}

void Giocatore::muoviGiocatore(int lancio){
    posizione += lancio;
    if (posizione >= 32) {  
        modificaSaldo(100); //bonus start
        posizione = posizione % 32;
    }
}

void Giocatore::acquistaProprieta(Proprieta& proprieta){
    proprieta.setProprietario(nome);
    saldo= saldo - proprieta.getCosto();
    proprietaPossedute.push_back(proprieta);
    
}

int Giocatore::acquistaCasa(Proprieta& proprieta) {
    if (proprieta.getProprietario().compare(getNome()) == 0) {
        if (getSaldo() > proprieta.getCostoCasa()) {
            if (proprieta.getNumeroCase() < 4) {
                modificaSaldo(-proprieta.getCostoCasa());
                proprieta.aggiungiCasa();
                return 0;
            } else {
                return 1; // Numero massimo di case raggiunto
            }
        } else {
            return 2; // Saldo insufficiente
        }
    } else {
        return 3; // Proprietario non corrisponde
    }
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

void Giocatore::pagaAffitto(Proprieta proprieta){
    modificaSaldo(-proprieta.calcolaPagamento());
}

 std::string Giocatore::getNome(){
    return nome;
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

void Giocatore::vaiInPrigione() {
        std::cout << nome << " è andato in prigione e deve saltare due turni.\n";
        turniDaSaltare = 2;
    }

bool Giocatore::isBot(){
    return bot;
}

void Giocatore::inconveniente(Inconvenienti inc){
modificaSaldo(inc.getImporto());
if(inc.isPrigione()){
    vaiInPrigione();
}
}

void Giocatore::opportunita(Opportunita opp){
    modificaSaldo(opp.getImporto());

}

void Giocatore::attivaBonus(){
    bonus=true;
}

void Giocatore::disattivaBonus(){
    bonus=false;
}

bool Giocatore::isBonusAttivo(){
   return bonus;
}

int Giocatore::getGiorniDiPrigione(){
    return turniDaSaltare;
}

void Giocatore::scontaGiornoDiPrigione(){
    turniDaSaltare=turniDaSaltare-1;
}
