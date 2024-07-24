#include "inconvenienti.hpp"

Inconvenienti::Inconvenienti(const std::vector<Inconvenienti>& carte): setCarte(carte) {}

Inconvenienti::Inconvenienti(std::string nome, int importo, bool prigione){
    setTitolo(nome);
    this->importo=importo;
    this->prigione=prigione;
}

Inconvenienti::~Inconvenienti(){}

Inconvenienti Inconvenienti::pescaCarta(){
    Inconvenienti card = setCarte.front();
    setCarte.erase(setCarte.begin());
    return card;
}

int Inconvenienti::getImporto(){
    return importo;
}
bool Inconvenienti::isPrigione(){
    return prigione;
}