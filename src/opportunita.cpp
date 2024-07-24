#include "opportunita.hpp"

Opportunita::Opportunita(const std::vector<Opportunita>& carte): setCarte(carte) {}

Opportunita::Opportunita(std::string nome, bool bonus, int importo){
setTitolo(nome);
this->bonus=bonus;
this->importo=importo;
}

Opportunita::~Opportunita(){}

Opportunita Opportunita::pescaCarta(){
    Opportunita card = setCarte.front();
    setCarte.erase(setCarte.begin());
    return card;
}

bool Opportunita::isBonus(){
    return bonus;
}

int Opportunita::getImporto(){
    return importo;
}