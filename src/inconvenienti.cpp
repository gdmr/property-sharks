#include "inconvenienti.hpp"

Inconvenienti::Inconvenienti(std::string nome, int importo, bool prigione){
    setTitolo(nome);
    this->importo=importo;
    this->prigione=prigione;
}

Inconvenienti::~Inconvenienti(){}